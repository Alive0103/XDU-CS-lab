#include "server.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <thread>    
#include <chrono>    

// ==================== Daemonizer 实现 ====================
void Daemonizer::daemonize() {
    // 第一次fork
    if (pid_t pid = fork(); pid < 0) {
        throw std::system_error(errno, std::generic_category(), "First fork failed");
    } else if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // 创建新会话
    if (setsid() < 0) {
        throw std::system_error(errno, std::generic_category(), "setsid failed");
    }

    // 第二次fork
    if (pid_t pid = fork(); pid < 0) {
        throw std::system_error(errno, std::generic_category(), "Second fork failed");
    } else if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // 关闭所有文件描述符
    for (int fd = sysconf(_SC_OPEN_MAX); fd >= 0; --fd) {
        close(fd);
    }

    // 设置文件权限掩码
    umask(0);

    // 设置工作目录
    if (chdir("/") < 0) {
        throw std::system_error(errno, std::generic_category(), "chdir failed");
    }

    // 重定向标准IO
    int nullfd = open("/dev/null", O_RDWR);
    if (nullfd == -1) {
        throw std::system_error(errno, std::generic_category(), "open /dev/null failed");
    }
    dup2(nullfd, STDIN_FILENO);
    dup2(nullfd, STDOUT_FILENO);
    dup2(nullfd, STDERR_FILENO);
    close(nullfd);
}

// ==================== ChatServer 实现 ====================
void ChatServer::broadcast(int senderFd, const char* msg, ssize_t len) {
    std::cout << "Broadcasting message to " << clients.size() << " clients" << std::endl;
    for (auto& [fd, _] : clients) {
        if (fd != senderFd) {
            if (write(fd, msg, len) == -1) {
                perror("Write error");
                close(fd);
                clients.erase(fd);
            }
        }
    }
}

void ChatServer::handleNewConnection() {
    sockaddr_in clientAddr{};
    socklen_t len = sizeof(clientAddr);
    
    int clientFd = accept(serverFd, reinterpret_cast<sockaddr*>(&clientAddr), &len);
    if (clientFd == -1) {
        perror("Accept error");
        return;
    }

    // 设置非阻塞模式
    int flags = fcntl(clientFd, F_GETFL, 0);
    if (flags == -1 || fcntl(clientFd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("Set non-block failed");
        close(clientFd);
        return;
    }

    // 添加epoll监听
    epoll_event ev{};
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = clientFd;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &ev) == -1) {
        perror("Epoll add error");
        close(clientFd);
        return;
    }

    // 记录客户端信息
    clients[clientFd] = inet_ntoa(clientAddr.sin_addr);
}

void ChatServer::initNetwork() {
    // 创建TCP套接字
    serverFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (serverFd == -1) {
        throw std::system_error(errno, std::generic_category(), "Socket creation failed");
    }

    // 绑定地址
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverFd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        throw std::system_error(errno, std::generic_category(), "Bind failed");
    }

    // 开始监听
    if (listen(serverFd, SOMAXCONN) == -1) {
        throw std::system_error(errno, std::generic_category(), "Listen failed");
    }
}
void ChatServer::handleEvents() {
    epoll_event events[MAX_EVENTS];
    int n = epoll_wait(epollFd, events, MAX_EVENTS, -1);
    if (n == -1) {
        if (errno == EINTR) return;
        throw std::system_error(errno, std::generic_category(), "Epoll wait error");
    }

    for (int i = 0; i < n; ++i) {
        if (events[i].data.fd == serverFd) {
            handleNewConnection();
        } else {
            // 处理客户端消息
            char buffer[4096];
            ssize_t len = read(events[i].data.fd, buffer, sizeof(buffer));
            if (len <= 0) {
                close(events[i].data.fd);
                clients.erase(events[i].data.fd);
            } else {
                broadcast(events[i].data.fd, buffer, len);
            }
        }
    }
}
void ChatServer::start() {
    try {
        Daemonizer::daemonize();
        initNetwork();
        
        // 添加初始化成功日志
        syslog(LOG_INFO, "服务启动成功，监听端口：%d", PORT);
        
        while (true) {
            handleEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } catch (const std::exception& e) {
        // 将错误记录到系统日志
        syslog(LOG_ERR, "致命错误：%s", e.what());
        exit(EXIT_FAILURE);
    }
}