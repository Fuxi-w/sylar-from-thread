#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1234);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenfd, (const sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind");
        close(listenfd);
        return 1;
    }

    if (listen(listenfd, 5) < 0) {
        perror("listen");
        close(listenfd);
        return 1;
    }

    std::cout << "Waiting for a connection on port 1234..." << std::endl;

    sockaddr_in clientaddr;
    socklen_t clientlen = sizeof(clientaddr);
    int connfd = accept(listenfd, (sockaddr*)&clientaddr, &clientlen);
    if (connfd < 0) {
        perror("accept");
        close(listenfd);
        return 1;
    }

    const char* msg = "Hello from server";
    // send(connfd, msg, strlen(msg), 0);
    sleep(10);
    close(connfd);
    close(listenfd);
    return 0;
}
