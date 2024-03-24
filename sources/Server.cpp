#include"../includes/Server.hpp"


Server::Server()
{
	_listen = "";
	_server_name = "";
	_host = "";
	_root = "";
	max_body_size = 0;
	
}

Server::Server(const Server& obj)
{
	*this = obj;
}

Server& Server::operator=(const Server& obj)
{
	_listen = obj._listen;
	_server_name = obj._server_name;
	_host = obj._host;
	_root = obj._root;
	_locs = obj._locs;
	_serverSoc = obj._serverSoc;
	_server_index = obj._server_index;
	max_body_size = obj.max_body_size;
	error_pages = obj.error_pages;

	return(*this);
}

Server::~Server(){}


/* Getters */
string Server::getListen(void)
{
	return _listen;
}
string &Server::getServername(void)
{
	return _server_name;
}
string &Server::getHost(void)
{
	return _host;
}
string &Server::getRoot(void)
{
	return _root;
}
unsigned long &Server::getMaxBdSize(void)
{
	return max_body_size;
}
vector<Location> &Server::getLocs(void)
{
	return _locs;
}
int &Server::getSoc(void)
{
	return _serverSoc;
}
vector<string> &Server::getErrorPages()
{
	return error_pages;
}

/* Setters*/

void Server::setListen(const string &listen)
{
	_listen = listen;
}
void Server::setServername(const string &server_name)
{
	_server_name = server_name;
}
void Server::setHost(const string &host)
{
	_host = host;
}
void Server::setRoot(const string &root)
{
	_root = root;
}
void Server::setMaxBdSize(unsigned long sz)
{
	max_body_size = sz;
}
void Server::setLocs(vector<Location> &loc)
{
	_locs = loc;
}
void Server::setSocket(int soc)
{
	_serverSoc = soc;
}
void Server::setErrorPages(vector<string> _err)
{
	error_pages = _err;
}