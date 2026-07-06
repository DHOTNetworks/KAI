#ifndef KAI_SOCKET_H
#define KAI_SOCKET_H

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
typedef int32_t kai_sock_len_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
typedef socklen_t kai_sock_len_t;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
#endif

#include <stdint.h>
#include <stdbool.h>

static inline void kai_socket_init(void) {
#if defined(_WIN32)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

static inline int64_t kai_socket_create(void) {
    kai_socket_init();
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return (int64_t)s;
}

static inline bool kai_socket_bind(int64_t fd, int64_t port) {
    SOCKET s = (SOCKET)fd;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons((uint16_t)port);
    return bind(s, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR;
}

static inline bool kai_socket_listen(int64_t fd, int64_t backlog) {
    SOCKET s = (SOCKET)fd;
    return listen(s, (int)backlog) != SOCKET_ERROR;
}

static inline int64_t kai_socket_accept(int64_t fd) {
    SOCKET s = (SOCKET)fd;
    struct sockaddr_in addr;
    kai_sock_len_t len = sizeof(addr);
    SOCKET client = accept(s, (struct sockaddr*)&addr, &len);
    return (int64_t)client;
}

static inline bool kai_socket_connect(int64_t fd, const char* ip, int64_t port) {
    SOCKET s = (SOCKET)fd;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)port);
#if defined(_WIN32)
    addr.sin_addr.s_addr = inet_addr(ip);
    if (addr.sin_addr.s_addr == INADDR_NONE) return false;
#else
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) return false;
#endif
    return connect(s, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR;
}

static inline int64_t kai_socket_send(int64_t fd, char* data, int64_t len) {
    SOCKET s = (SOCKET)fd;
#if defined(_WIN32)
    return (int64_t)send(s, data, (int)len, 0);
#else
    return (int64_t)send(s, data, (size_t)len, 0);
#endif
}

static inline int64_t kai_socket_recv(int64_t fd, char* buf, int64_t max_len) {
    SOCKET s = (SOCKET)fd;
#if defined(_WIN32)
    return (int64_t)recv(s, buf, (int)max_len, 0);
#else
    return (int64_t)recv(s, buf, (size_t)max_len, 0);
#endif
}

static inline void kai_socket_close(int64_t fd) {
    SOCKET s = (SOCKET)fd;
    if (s == INVALID_SOCKET) return;
#if defined(_WIN32)
    closesocket(s);
#else
    close(s);
#endif
}

#endif
