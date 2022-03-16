#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Session {
    int domain;
    int port;
    int protocol;
    int interface;
    int socket;
    struct sockaddr_in address;
};

struct Server server_constructor(int domain, int port, int protocol, int interface, void(*launch)(void));

#endif 