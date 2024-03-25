#ifndef LOCATION_HPP
#define LOCATION_HPP

#include"include.hpp"


class Location
{
    private:
        string _pattern;
        string _root;
        string _autoindex;
        string _index;
        string _redirection;
        vector<string> _upload;
        string _cgi;
        vector<string> _cgiPY;
        vector<string> _cgiPHP;
        vector<string> _cgiSH;

        vector<string> _allowMethods;
    
    public:
        Location();
        Location(const Location& obj);
        Location &operator=(const Location& obj);
        ~Location();

        /* Getters */
        string &getPattern(void);
        string &getAutoindex(void);
        string &getRoot(void);
        string getIndex(void);
        string &getRedirection(void);
        vector<string> &getUpload(void);
        string &getCgi(void);
        vector<string> &getCGI_PY(void);
        vector<string> &getCGI_PHP(void);
        vector<string> &getCGI_SH(void);
        // string &getUploadPath(void);
        vector<string> &getAllowedMethods(void);
        
        /* Setters */
        void setPattern(const string &listen);
        void setAutoindex(const string &server_name);
        void setRoot(const string &host);
        void setIndex(const string &root);
        void setRedirection(const string &redir);
        void setUpload(vector<string> upload);
        void setCgi(string &cgi);
        void setCGI_PY(vector<string> _cgiPY);
        void setCGI_PHP(vector<string> _cgiPHP);
        void setCGI_SH(vector<string> _cgiSH);
        // void setUploadPath(const string &uploadPath);
        void setAllowedMethods(vector<string> allow_methds);

        /* Methods */
        bool isIndexed();
        bool isRedirected();
        bool isAutoindexed();
        bool locHasGETallowed();
        bool locHasPOSTallowed();
        bool locHasDELETEallowed();
};


#endif