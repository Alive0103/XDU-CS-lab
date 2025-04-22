#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <cstring>
#include <ctime>
#include <csignal>
#include <vector>

#define SHM_SIZE 1024
#define NUM_CHILDREN 12

// 共享内存数据结构
struct SharedData {
    int counter;
    char message[256];
    double calculation_result;
    bool alarm_triggered;
};

// 信号量操作联合体
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// 全局变量用于信号处理
volatile sig_atomic_t alarm_flag = 0;

// 信号处理函数
void alarm_handler(int sig) {
    alarm_flag = 1;
}

// 信号量操作函数
void semaphore_op(int semid, int op) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = op;
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

// 计算进程函数
void calculation_process(int shmid, int semid) {
    SharedData *shm = (SharedData *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat in calculation process");
        exit(1);
    }

    while (true) {
        semaphore_op(semid, -1); // 获取信号量
        
        // 执行计算任务
        shm->calculation_result = 0;
        for (int i = 1; i <= shm->counter; i++) {
            shm->calculation_result += 1.0 / i;
        }
        std::cout << "Calculation Process (PID " << getpid() << "): Calculated harmonic series up to " 
                  << shm->counter << " = " << shm->calculation_result << std::endl;
        
        semaphore_op(semid, 1); // 释放信号量
        sleep(2); // 模拟计算耗时
    }

    shmdt(shm);
}

// 显示进程函数
void display_process(int shmid, int semid) {
    SharedData *shm = (SharedData *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat in display process");
        exit(1);
    }

    while (true) {
        semaphore_op(semid, -1); // 获取信号量
        
        std::cout << "Display Process (PID " << getpid() << "): Counter = " << shm->counter 
                  << ", Message = '" << shm->message << "', Result = " << shm->calculation_result 
                  << ", Alarm = " << (shm->alarm_triggered ? "ON" : "OFF") << std::endl;
        
        semaphore_op(semid, 1); // 释放信号量
        sleep(3); // 模拟显示间隔
    }

    shmdt(shm);
}

// 报警进程函数
void alarm_process(int shmid, int semid) {
    SharedData *shm = (SharedData *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat in alarm process");
        exit(1);
    }

    // 设置信号处理
    signal(SIGALRM, alarm_handler);

    while (true) {
        semaphore_op(semid, -1); // 获取信号量
        
        if (shm->counter > 50) {
            shm->alarm_triggered = true;
            std::cout << "ALARM Process (PID " << getpid() << "): Counter exceeded 50! Current value: " 
                      << shm->counter << std::endl;
        } else {
            shm->alarm_triggered = false;
        }
        
        semaphore_op(semid, 1); // 释放信号量
        sleep(1); // 频繁检查报警条件
    }

    shmdt(shm);
}

// 普通子进程函数
void child_process(int id, int shmid, int semid, int pipe_fd[2]) {
    SharedData *shm = (SharedData *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat in child process");
        exit(1);
    }

    close(pipe_fd[0]); // 关闭读端

    for (int i = 0; i < 5; i++) {
        semaphore_op(semid, -1); // 获取信号量
        
        // 更新共享数据
        shm->counter += id + i;
        snprintf(shm->message, sizeof(shm->message), "Message from child %d, iteration %d", id, i);
        
        // 通过管道发送消息给父进程
        std::string pipe_msg = "Child " + std::to_string(id) + " updated counter to " + 
                              std::to_string(shm->counter) + "\n";
        write(pipe_fd[1], pipe_msg.c_str(), pipe_msg.length());
        
        semaphore_op(semid, 1); // 释放信号量
        
        sleep(id % 3 + 1); // 不同进程有不同的睡眠时间
    }

    shmdt(shm);
    close(pipe_fd[1]);
    exit(0);
}

int main() {
    // 创建共享内存
    int shmid = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // 初始化共享内存
    SharedData *shm = (SharedData *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    shm->counter = 0;
    strcpy(shm->message, "Initial message");
    shm->calculation_result = 0.0;
    shm->alarm_triggered = false;
    shmdt(shm);

    // 创建信号量
    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }
    union semun su;
    su.val = 1;
    if (semctl(semid, 0, SETVAL, su) == -1) {
        perror("semctl");
        exit(1);
    }

    // 创建管道
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // 创建子进程
    std::vector<pid_t> child_pids;
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // 子进程
            if (i == 0) {
                // 第一个子进程作为计算进程
                calculation_process(shmid, semid);
            } else if (i == 1) {
                // 第二个子进程作为显示进程
                display_process(shmid, semid);
            } else if (i == 2) {
                // 第三个子进程作为报警进程
                alarm_process(shmid, semid);
            } else {
                // 其他普通子进程
                child_process(i, shmid, semid, pipe_fd);
            }
            exit(0); // 永远不会执行到这里
        } else {
            // 父进程记录子进程PID
            child_pids.push_back(pid);
        }
    }

    // 父进程代码
    close(pipe_fd[1]); // 关闭写端
    
    // 从管道读取数据
    char buf[256];
    fd_set readfds;
    struct timeval tv;
    
    std::cout << "Parent process (PID " << getpid() << ") started with " << NUM_CHILDREN << " children." << std::endl;
    
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(pipe_fd[0], &readfds);
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        
        int ret = select(pipe_fd[0] + 1, &readfds, NULL, NULL, &tv);
        if (ret == -1) {
            perror("select");
            break;
        } else if (ret) {
            // 有数据可读
            ssize_t n = read(pipe_fd[0], buf, sizeof(buf) - 1);
            if (n > 0) {
                buf[n] = '\0';
                std::cout << "Parent received: " << buf;
            } else if (n == 0) {
                // 管道关闭
                break;
            } else {
                perror("read");
                break;
            }
        }
        
        // 定期更新共享内存
        static int update_count = 0;
        if (++update_count % 5 == 0) {
            semaphore_op(semid, -1);
            shm = (SharedData *)shmat(shmid, NULL, 0);
            if (shm != (void *)-1) {
                time_t now = time(nullptr);
                strftime(shm->message, sizeof(shm->message), "%Y-%m-%d %H:%M:%S", localtime(&now));
                shmdt(shm);
            }
            semaphore_op(semid, 1);
        }
    }

    // 清理工作
    for (pid_t pid : child_pids) {
        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0);
    }
    
    close(pipe_fd[0]);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    
    std::cout << "Parent process exiting." << std::endl;
    return 0;
}