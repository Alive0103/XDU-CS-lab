#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <cstring>
#include <unordered_map>

#define MAX_EVENTS 100
#define BUFFER_SIZE 2048
#define PORT 8888

std::unordered_map<int, std::string> clients;

void handleMessage(int fd, char* buf) {
    ssize_t len = read(fd, buf, BUFFER_SIZE);
    if (len <= 0) {
        close(fd);
        clients.erase(fd);
    } else {
        buf[len] = '\0';
        for (auto& [clientFd, _] : clients) {
            if (clientFd != fd) {
                write(clientFd, buf, len);
            }
        }
    }
}

int main() {
    // 创建守护进程
    if (daemon(1, 0) == -1) {
        perror("daemon");
        exit(EXIT_FAILURE);
    }

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 修正的初始化部分
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(serverFd, (sockaddr*)&addr, sizeof(addr));
    listen(serverFd, 5);

    int epollFd = epoll_create1(0);
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = serverFd;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, serverFd, &event);

    while (true) {
        epoll_event events[MAX_EVENTS];
        int n = epoll_wait(epollFd, events, MAX_EVENTS, -1);
        
        for (int i = 0; i < n; ++i) {
            if (events[i].data.fd == serverFd) {
                sockaddr_in clientAddr;
                socklen_t len = sizeof(clientAddr);
                int clientFd = accept(serverFd, (sockaddr*)&clientAddr, &len);
                
                clients[clientFd] = inet_ntoa(clientAddr.sin_addr);
                epoll_event clientEvent;
                clientEvent.events = EPOLLIN;
                clientEvent.data.fd = clientFd;
                epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &clientEvent);
            } else {
                char buf[BUFFER_SIZE];
                handleMessage(events[i].data.fd, buf);
            }
        }
    }
    close(serverFd);
    return 0;
}