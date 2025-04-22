// server.hpp
#pragma once
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <system_error>

class Daemonizer {
public:
    static void daemonize();
};

class ChatServer {
public:
    static constexpr int MAX_EVENTS = 100;  // 定义为公共静态常量
    static constexpr int PORT = 8888;

private:
    void initNetwork();
    void handleEvents();
    int serverFd = -1;
    int epollFd = -1;
    std::unordered_map<int, std::string> clients;

    void broadcast(int senderFd, const char* msg, ssize_t len);
    void handleNewConnection();

public:
    void start();
};