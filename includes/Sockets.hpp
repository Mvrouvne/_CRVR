#ifndef SOCKETS_HPP
# define SOCKETS_HPP

#include"include.hpp"

class Server;

class Socket
{
    private:
        // Server sock_serv;
        int _socket_fd;
        struct sockaddr_in _host_addr;
        socklen_t _host_addrlen;

    public:
        int getSocketFd(void);
        struct sockaddr_in *getSockStruct(void);
        socklen_t *getSockLen(void);
        void init_serv(Server &_config);
        // void run_webserve(void);
};


#endif