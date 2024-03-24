#ifndef CGI_HPP
# define CGI_HPP

#include "include.hpp"
// #include "Request.hpp"
// #include "Config_parser.hpp"

class Request;

class	CGI
{
	private:
		std::string	scriptPath;
		std::string	queryString;
		char*	env[8];
		char* args[3];
		std::string	realPath;
		pid_t		pid;
		FILE*		file;
		FILE*		file_in;
		std::string	pipeRead;
		std::string cgiRoot;
		std::string _url;
		std::string	extension;
		bool		isPy;
		bool		isPHP;
		bool		isSh;
		clock_t		cgiStartTime;
        clock_t 	cgiEndTime;
		int			status;
		char uploadPath[PATH_MAX];
	public:
		std::string getcgiRoot()
		{
			return cgiRoot;
		}
		CGI();
		~CGI();
		int	cgi_handler(Request& reqObj);
		bool	checkPathExtension(Request& reqObj);
};

#endif