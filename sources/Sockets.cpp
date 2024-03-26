#include"../includes/Sockets.hpp"
#include"../includes/Config_parser.hpp"

int Socket::getSocketFd(void)
{
	return _socket_fd;
}

struct sockaddr_in *Socket::getSockStruct(void)
{
	return &_host_addr;
}

socklen_t *Socket::getSockLen(void)
{
	return &_host_addrlen;
}

void Socket::init_serv(Server &_config)
{
	int option = 1;
    _host_addrlen = sizeof(_host_addr);
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd == -1)
    {
        cout << "socket -> " << strerror(errno) << endl;
    }
	if (setsockopt(_socket_fd,SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
	{
		cout << "setSocket -> " << strerror(errno) << endl;
	}
    _host_addr.sin_family = AF_INET;
    _host_addr.sin_addr.s_addr = inet_addr(_config.getHost().c_str());
    _host_addr.sin_port = htons(_stoi(_config.getListen()));
    memset(_host_addr.sin_zero, 0, sizeof(_host_addr.sin_zero));
    if (bind(_socket_fd, (struct sockaddr*)&_host_addr, _host_addrlen) == -1) 
    {
        // close(_socket_fd);
        cout << "bind -> " << strerror(errno) << endl;
    }
    if (listen(_socket_fd, SOMAXCONN) == -1)
    {
        // close(_socket_fd);
        cout << "listen -> " << strerror(errno) << endl;
    }
}

