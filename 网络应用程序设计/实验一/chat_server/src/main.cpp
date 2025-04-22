#include "server.hpp"
#include <iostream> 

int main() {
    try {
        ChatServer server;
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Server fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}