#ifndef CONFIG_HPP
#define CONFIG_HPP

#include"include.hpp"
#include"Server.hpp"
#include"Location.hpp"
#include"Sockets.hpp"
#include"webserver.hpp"

#define NONE "\033[0m"
#define RED "\033[31m"

class Config
{
    private:

        vector<Server> _servers;
        vector<Socket> _sockets;
        map<int, Server> _map_servers;
        vector<string> duplicatesVecServ;
        vector<string> duplicatesVecLoc;
        bool _hasRoot;
        bool deleted;

    public:
        Config();
        ~Config();
        string &getFilename(void);
        void setFilename(const string& fl);
        void catchConfig(const string &conf_file);
        void validServerBlocks(Server serv);
        vector<Server> getServers(void);
        void handle_requests();
        int getServerIndex(string &port);
        void print();
        int checkSocket(int fd);
};


#endif