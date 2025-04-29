#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/rcupdate.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/sched/signal.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FuShengyuan");
MODULE_DESCRIPTION("A simple kernel module with a list and two threads.");

static struct list_head my_list;  // 定义链表头
static struct task_struct *thread1, *thread2;  // 定义两个内核线程
spinlock_t lock;  // 定义自旋锁

// 定义链表节点结构，包含进程的PID和进程名
struct pid_node {
    int pid;
    char comm[16];
    struct list_head list;  // 内核链表结构
};

// 线程1：遍历进程链表，将进程信息加入到内核链表
static int thread1_func(void *data) {
    struct task_struct *task;
    struct pid_node *node;

    while (!kthread_should_stop()) {
        rcu_read_lock();  // 读保护，防止进程链表被更改
        for_each_process(task) {
            // 为每个进程分配内存，保存PID和进程名
            node = kmalloc(sizeof(*node), GFP_KERNEL);
            if (!node)
                continue;

            node->pid = task->pid;
            strncpy(node->comm, task->comm, sizeof(node->comm));

            // 加锁并将节点加入链表
            spin_lock(&lock);
            list_add_tail(&node->list, &my_list);
            spin_unlock(&lock);
        }
        rcu_read_unlock();
        msleep(5000);  // 每隔5秒钟遍历一次
    }
    return 0;
}

// 线程2：从链表中取出节点并打印
static int thread2_func(void *data) {
    struct pid_node *node, *tmp;

    while (!kthread_should_stop()) {
        spin_lock(&lock);
        list_for_each_entry_safe(node, tmp, &my_list, list) {
            printk(KERN_INFO "PID: %d, Command: %s\n", node->pid, node->comm);

            // 从链表中删除节点并释放内存
            list_del(&node->list);
            kfree(node);
        }
        spin_unlock(&lock);
        msleep(5000);  // 每隔5秒钟打印一次
    }
    return 0;
}

// 模块初始化函数
int kernel_module_init(void) {
    printk(KERN_INFO "List and thread module init\n");

    INIT_LIST_HEAD(&my_list);  // 初始化链表
    spin_lock_init(&lock);  // 初始化自旋锁

    // 创建线程1和线程2
    thread1 = kthread_create(thread1_func, NULL, "thread1");
    if (IS_ERR(thread1)) {
        printk(KERN_ERR "Failed to create thread1\n");
        return PTR_ERR(thread1);
    }
    wake_up_process(thread1);

    thread2 = kthread_create(thread2_func, NULL, "thread2");
    if (IS_ERR(thread2)) {
        printk(KERN_ERR "Failed to create thread2\n");
        kthread_stop(thread1);  // 如果线程2创建失败，停止线程1
        return PTR_ERR(thread2);
    }
    wake_up_process(thread2);

    return 0;
}

// 模块清理函数
void kernel_module_exit(void) {
    struct pid_node *node, *tmp;

    printk(KERN_INFO "List and thread module exit\n");

    // 停止线程1和线程2
    if (thread1)
        kthread_stop(thread1);
    if (thread2)
        kthread_stop(thread2);

    // 清理链表并释放内存
    spin_lock(&lock);
    list_for_each_entry_safe(node, tmp, &my_list, list) {
        list_del(&node->list);
        kfree(node);
    }
    spin_unlock(&lock);
}

module_init(kernel_module_init);
module_exit(kernel_module_exit);
