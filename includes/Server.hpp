#ifndef SERVER_HPP
#define SERVER_HPP

#include"include.hpp"
#include"Location.hpp"
#include"Sockets.hpp"

class Server
{
    private:
        string _listen;
        string _server_name;
        string _host;
        string _root;
        vector<Location> _locs;
        int _serverSoc;
        int _server_index;
        vector<string> _errorPages;
        unsigned long max_body_size;
        vector<string> error_pages;

    public:
        Server(const Server& obj);
        Server();
        ~Server();
        Server& operator=(const Server& obj);
        
        /* Getters */
        string getListen(void);
        string &getServername(void);
        string &getHost(void);
        string &getRoot(void);
        int &getSoc(void);
        vector<Location> &getLocs(void);
        unsigned long int &getMaxBdSize(void);
        vector<string> &getErrorPages(void);


        /* Setters */
        void setListen(const string &listen);
        void setServername(const string &server_name);
        void setHost(const string &host);
        void setRoot(const string &root);
        void setLocs(vector<Location> &loc);
        void setSocket(int soc);
        void setMaxBdSize(unsigned long sz);
        void setErrorPages(vector<string> _errPages);

        /* Methods */
        bool checkSocket(int fd);
};



#endif