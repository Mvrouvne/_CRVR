#include "../includes/Config_parser.hpp"

Config::Config()
{
	_hasRoot = false;
}

Config::~Config()
{

}

/* Getters */

vector<Server> Config::getServers(void)
{
	return _servers;
}

/* Setters */

/* Methods */

string	readFile(string path)
{
	if (path.empty() || path.length() == 0)
		errorHolder("invalid file 1");
	ifstream config_file(path.c_str());
	if (!config_file || !config_file.is_open())
		errorHolder("invalid file 2");

	stringstream stream_binding;
	stream_binding << config_file.rdbuf();
	return (stream_binding.str());
}

void errorHolder(const string &err)
{
	throw invalid_argument("Error: " + err);
}

bool _isspace(char c) 
{
    return c == ' ' || c == '\t';
}

string spaceRemover(string _target)
{
    string result = _target;
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

int onlyCharInLine(string &line, char c)
{
	size_t count = 0;
	size_t i = 0;
	for(; i < line.size(); i++)
		if(line[i] == c)
			count++;
	if(count == line.size())
		return 1;
	return 0;
}

// int Config::findBlock(string line, string _target, int i)
// {
// 	size_t pos = line.find(_target);
// 	if(pos != string::npos)
// 	{
// 		int start  = pos + _target.length();
// 		if(i == 0)
// 			_listen = line.substr(start, line.find(";") - start),spaceRemover(_listen);
// 		else if(i == 1)
// 			_server_name = line.substr(start, line.find(";") - start),spaceRemover(_server_name);
// 		else if(i == 2)
// 			_host = line.substr(start, line.find(";") - start), spaceRemover(_host);
// 		else if(i == 3)
// 			_root = line.substr(start, line.find(";") - start),spaceRemover(_root);
// 		return 0;
// 	}
// 	errorHolder(" Missing/invalid/duplicated Conf block");
// 	return 1;
// }

const ostream& operator<<(ostream& out, Server serv)
{
	out << "[ " << serv.getListen() << " ]            " ;
	out << "[ " << serv.getServername() << " ]            " ;
	out << "[ " << serv.getHost() << " ]            " ;
	out << "[ " << serv.getRoot() << " ]            " ;
	out << "[ ";
	for (vector<string>::iterator it = serv.getErrorPages().begin(); it != serv.getErrorPages().end(); ++it)
		out << *it << " " ;
	out << " ]    " ;
	out << "[ " << serv.getMaxBdSize() << " ]            \n" << endl;
	return out;
}

const ostream& operator<<(ostream& out, Location loc)
{
	out << "[ " << loc.getPattern() << " ]    " ;
	out << "[ ";
	for (vector<string>::iterator it = loc.getAllowedMethods().begin(); it != loc.getAllowedMethods().end(); ++it)
		out << *it << " " ;
	out << "]    " ;
	out << "[ " << loc.getRoot() << " ]    " ;
	out << "[ " << loc.getIndex() << " ]    " ;
	out << "[ " << loc.getAutoindex() << " ]    " ;
	out << "[ " << loc.getRedirection() << " ]    " ;
	out << "[ ";
	for (vector<string>::iterator it = loc.getUpload().begin(); it != loc.getUpload().end(); ++it)
		out << *it << " " ;
	out << "]    " ;
	out << "[ " << loc.getCgi() << " ]    " ;
	out << "[ ";
	for (vector<string>::iterator it = loc.getCGI_PHP().begin(); it != loc.getCGI_PHP().end(); ++it)
		out << *it << " " ;
	out << "]    " ;
	out << "[ ";
	for (vector<string>::iterator it = loc.getCGI_PY().begin(); it != loc.getCGI_PY().end(); ++it)
		out << *it << " " ;
	out << "]    ";
	out << "[ ";
	for (vector<string>::iterator it = loc.getCGI_SH().begin(); it != loc.getCGI_SH().end(); ++it)
		out << *it << " " ;
	out << "]    \n" << endl;
	
	return out;
}

void Config::print()
{
	int x = 0;
	int y = 0;

	vector<Server>::iterator sv;
	for(sv = _servers.begin(); sv != _servers.end(); ++sv)
	{
		cout << "                                 -------------                       " << endl;
		cout << "              __________________|  Server: " << x << "  |__________________" << endl;
		cout << "                                 -------------                       " << endl;
		cout << *sv;

		vector<Location>::iterator lt;
		y = 0;
		for(lt = _servers[x].getLocs().begin(); lt !=  _servers[x].getLocs().end(); ++lt)
		{
			cout << "                                 -------------                       " << endl;
			cout << "              __________________| Location: " << y << " |__________________" << endl;
			cout << "                                 -------------                       " << endl;
			cout << *lt;
			y++;
		}
		x++;
	}

}

int commentFound(string &line)
{
	int i = 0;
	while(_isspace(line[i]))
		i++;
	if(line[i]== '#')
		return 1;
	return 0;
}

int lineCheck(string &line, int &flag, int &flagg)
{
	if(line.empty() || onlyCharInLine(line, 32) || commentFound(line))
		return 1;
	if(line.find("server {") != string::npos || line.find("location {") != string::npos)
	{
		if(line.find("server {") != string::npos)
			flag = 1;
		if(line.find("location {") != string::npos)
			flagg = 1;
		return 1;
	}
	if(line[line.size() - 1] != ';' && spaceRemover(line).compare("}"))
	{
		errorHolder("semicolumn required at the end of line!");
	}
	return 0;
}

bool checkBrackets(const string &conf_file)
{
	stack<char> stack;
    for (string::const_iterator it = conf_file.begin(); it != conf_file.end(); ++it) 
	{
        char ch = *it;
        if (ch == '{') {
            stack.push(ch);
        } 
		else if (ch == '}') {
            if (stack.empty()) {
                return false;
            }
            stack.pop();
        }
    }
    return stack.empty(); // If stack is empty, all brackets are valid
}

void validateLocation(Location &loc)
{
	
	if(loc.getPattern()[0] == '\0' || loc.getAllowedMethods().size() == 0)
		errorHolder(" Location pattern or allowed methods required in " + loc.getPattern());
	
	//should parse the pattern path

	/* Allowed method */

	vector<string>::iterator it = loc.getAllowedMethods().begin();
	for(;it != loc.getAllowedMethods().end(); it++)
	{
		if(it->compare("GET") && it->compare("POST") && it->compare("DELETE"))
			errorHolder("Invalid method given of the location " + loc.getPattern());
	}

	/* Autoindex */
	if(loc.getAutoindex().compare("on") && loc.getAutoindex().compare("off"))
		errorHolder("Invalid autoindex value!");

	/* Upload */
	if(loc.getUpload().size() == 1 || loc.getUpload().size() == 2)
	{
		if(loc.getUpload().size() == 1)
		{
			if(loc.getUpload()[0].compare("off"))
				errorHolder("Invalid Upload status of the location " + loc.getPattern());
		}
		else if(loc.getUpload().size() == 2)
		{
			if(loc.getUpload()[0] != "on" && loc.getUpload()[0] != "off")
				errorHolder("upload in " + loc.getPattern() + " location is not ON nor OFF");
			if((loc.getUpload()[0] == "off" && !loc.getUpload()[1].empty()))
				errorHolder("useless Upload path for " + loc.getPattern() + " when is OFF!");
			else if(loc.getUpload()[0] == "on" && loc.getUpload()[1].empty())
				errorHolder("upload path for " + loc.getPattern() + " can't be empty!");
		}
	}
	else if(loc.getUpload().size() > 2)
		errorHolder("Invalid upload attribute in the loc " + loc.getPattern());

	/* Cgi */

	if(loc.getCgi().compare("on") && loc.getCgi().compare("off"))
		errorHolder("Invalid Cgi status of the location " + loc.getPattern());
	if((loc.getCgi() == "off") && (!loc.getCGI_PY().empty() || !loc.getCGI_PHP().empty() || !loc.getCGI_SH().empty())) //!loc.getCgiPY().empty() || !loc.getCgiPHP().empty() || !loc.getCgiSH().empty()
		errorHolder("Useless Cgi path for " + loc.getPattern() + " when CGI is OFF");

	if(!loc.getCgi().compare("on"))
	{
		if(loc.getCGI_PY().empty() && loc.getCGI_PHP().empty() && loc.getCGI_SH().empty())
			errorHolder("at least provide one CGI in " + loc.getPattern());
		// if(loc.getCGI_PY().size() != 2 || loc.getCGI_PHP().size() != 2)
		// 	errorHolder("invalid CGI path given in " + loc.getPattern());
		if(!loc.getCGI_PY().empty())
		{
			if(loc.getCGI_PY()[0].empty() || loc.getCGI_PY()[1].empty())
				errorHolder("path or extention for CGI is missed!");
			if(loc.getCGI_PY().size() != 2)
				errorHolder("invalid CGI values in " + loc.getPattern());
			if(loc.getCGI_PY()[1].compare(".py"))
				errorHolder("invalid CGI extention in " + loc.getPattern());
		}

		if(!loc.getCGI_PHP().empty())
		{
			if(loc.getCGI_PHP()[0].empty() || loc.getCGI_PHP()[1].empty())
				errorHolder("path or extention for CGI is missed!");
			if(loc.getCGI_PHP().size() != 2)
				errorHolder("invalid CGI values in " + loc.getPattern());
			if(loc.getCGI_PHP()[1].compare(".php"))
				errorHolder("invalid CGI extention in " + loc.getPattern());
		}

		if(!loc.getCGI_SH().empty())
		{
			if(loc.getCGI_SH()[0].empty() || loc.getCGI_SH()[1].empty())
				errorHolder("path or extention for CGI is missed!");
			if(loc.getCGI_SH().size() != 2)
				errorHolder("invalid CGI values in " + loc.getPattern());
			if(loc.getCGI_SH()[1].compare(".sh"))
				errorHolder("invalid CGI extention in " + loc.getPattern());
		}

	}
	// if ((access(loc.getRoot().c_str(), F_OK | R_OK | X_OK ) == -1) || (access(loc.getPattern().c_str(), F_OK | R_OK | X_OK ) == -1))
	// ||  (access(loc.getUploadPath().c_str(), F_OK | R_OK | X_OK ) == -1)
	// 	errorHolder(" Path not accessible!");


	// indexFile.close();
}

int _stoi(string str)
{
	istringstream ss(str);
	int nb;
	ss >> nb;
	return nb;
}

unsigned long _stoul(string str)
{
	istringstream ss(str);
	unsigned long nb;
	ss >> nb;
	return nb;
}

bool isNumber(string str)
{
	for(size_t i = 0; i < str.size(); i++)
		if(!isdigit(str[i]))
			return false;
	return true;
}

bool isValidPort(int port) 
{
	/* 1024-49551 is the valid range to personnal uses, 0-1023 are already reserver
	   and 49152-65535 are dynamic or private ports*/
    return port >= 1024 && port <= 49151;
}

void Config::validServerBlocks(Server serv)
{
	int hostParts = 0;
	string hostByte;
	size_t i = 0;
	int range = 0;

	if(serv.getRoot().empty())
		errorHolder("root not provided");
	if(serv.getListen()[0] == '\0' || serv.getServername()[0] == '\0' || serv.getHost()[0] == '\0')
		errorHolder("Server block required!");
	if(serv.getRoot()[0] == '\0')
	{
		_hasRoot = true;
	}
	// if(!isDirectory(serv.getRoot().c_str()))
	// 	errorHolder("invalid server root!");
	if(!isNumber(serv.getListen()) || !isValidPort(_stoi(serv.getListen())))
			errorHolder("Server port is not valid!");
	for(i = 0; i < serv.getHost().size(); i++)
	{
		if((!isdigit(serv.getHost()[i]) && serv.getHost()[i] != '.') || (serv.getHost()[i] == '.' && isdigit(serv.getHost()[i + 1]) && i == 0))
			errorHolder("Invalid host!");
		if(isdigit(serv.getHost()[i]))
			hostByte += serv.getHost()[i];
		if(serv.getHost()[i] == '.')
		{
			range = _stoi(hostByte);
			if(range > 255)
				errorHolder("Invalid host range!");
			hostByte.clear();
			hostParts++;
		}
	}
	if(!serv.getHost()[i])
	{
		range = _stoi(hostByte);
		if(range > 255)
			errorHolder("Invalid host range!");
		hostByte.clear();
		hostParts++;
	}
	if(hostParts != 4)
		errorHolder("More/Less than 4 bytes in host!");
	// if (access(serv.getRoot().c_str(), F_OK | R_OK | X_OK ) == -1)
	// 	errorHolder("server root pattern not accessible!");
}

void checkDuplicatedLocs(vector<Location> _locs)
{
	vector<Location>::iterator it = _locs.begin();
	for(; it + 1 != _locs.end(); it++)
	{
		vector<Location>::iterator itt = it + 1;
		for(; itt != _locs.end(); itt++)
		{
			if(!it->getPattern().compare(itt->getPattern()))
				return errorHolder("Duplicated locations!");
		}
	}
}

void checkDuplicatedServs(vector<Server> servs)
{
	vector<Server>::iterator it = servs.begin();
	for(; it + 1 != servs.end(); it++)
	{
		vector<Server>::iterator itt = it + 1;
		for(; itt != servs.end(); itt++)
		{
			if(!it->getListen().compare(itt->getListen()) && !it->getHost().compare(itt->getHost()) && !it->getServername().compare(itt->getServername()))
				return errorHolder("Duplicated Servers!");
		}
	}
}

void consecutiveSlashsFinder(string path)
{
	bool prevSlash = false;
	for (size_t i = 0; i < path.length(); ++i) 
	{
		// Check for consecutive slashes
		if (path[i] == '/') {
			if (prevSlash) {
				errorHolder("consecutive SLASH (/) found in " + path);
			}
			prevSlash = true;
		} 
		else {
			prevSlash = false;
		}
	}
}

void fetchingLocBLocks(istringstream &iss, Location &loc, vector<string> &DupsVec)
{
	vector<string> vec;
	string token;
	string holder;
	iss >> token;

	DupsVec.push_back(token);
	if (token == "pattern") {
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		// if(holder[0] != '/' || holder[holder.size() - 1] != '/')
		// 	errorHolder("pattern name in " + holder + " is missing a SLASH!");
		consecutiveSlashsFinder(holder);
		loc.setPattern(holder);
	}
	else if (token == "root") {
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		if(holder[holder.size() - 1] != '/')
			holder += "/";
		consecutiveSlashsFinder(holder);
		loc.setRoot(holder);
	}
	else if (token == "autoindex") {
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		loc.setAutoindex(holder);
	}
	else if (token == "index") {
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		if(holder[0] != '/' || holder[holder.size() - 1] == '/')
			errorHolder("index file in " + holder + " has error with SLASH!");
		consecutiveSlashsFinder(holder);
		loc.setIndex(holder);
	}
	else if (token == "return") {
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		// if(holder[0] != '/' || holder[holder.size() - 1] != '/')
		// 	errorHolder("return value in " + holder + " is missing a SLASH!");
		consecutiveSlashsFinder(holder);
		loc.setRedirection(holder);
	}
	else if (token == "upload") {
		while (iss >> token) {
			if(token[token.size() - 1] == ';')
				token.erase(token.size() - 1);
			vec.push_back(token);
		}
		loc.setUpload(vec);
	}
	else if (token == "cgi") {
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		loc.setCgi(holder);
	}
	else if (token == "allow_methods") {
		while (iss >> token) {
			if(token[token.size() - 1] == ';')
				token.erase(token.size() - 1);
			vec.push_back(token);
		}
		loc.setAllowedMethods(vec);
	}
	else if (token == "cgi_php") {
		while (iss >> token) {
			if(token[token.size() - 1] == ';')
				token.erase(token.size() - 1);
			vec.push_back(token);
		}
		loc.setCGI_PHP(vec);
	}
	else if (token == "cgi_py") {
		while (iss >> token) {
			if(token[token.size() - 1] == ';')
				token.erase(token.size() - 1);
			vec.push_back(token);
		}
		loc.setCGI_PY(vec);
	}
	else if (token == "cgi_sh") {
		while (iss >> token) {
			if(token[token.size() - 1] == ';')
				token.erase(token.size() - 1);
			vec.push_back(token);
		}
		loc.setCGI_SH(vec);
	}
	else
		errorHolder("stranger attribute found as " + iss.str());
	if(iss.good())
		errorHolder("attribute [" + iss.str() + " ] got an issue");
	
}

unsigned long long _stoull(string &str)
{
	istringstream ss(str);
	unsigned long long nb;
	ss >> nb;
	return nb;
}

bool isValueOverflowingULLONG_MAX(const std::string& valueStr) {
    errno = 0; // Reset errno to 0 before the call
    char* end;
    unsigned long long val = strtoull(valueStr.c_str(), &end, 10);
	(void)val;
    if (*end != '\0' || errno == ERANGE) {
        return true;
    }
    return false;
}

void fetchingServBLocks(istringstream &iss, Server &serv, vector<string> &DupsVec)
{
	string token;
	string holder;
	iss >> token;
	DupsVec.push_back(token);
	if (token == "listen") 
	{
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		serv.setListen(holder);
	}
	else if (token == "server_name") 
	{
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		serv.setServername(holder);
	}
	else if (token == "host") 
	{
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		serv.setHost(holder);
	}
	else if (token == "root") 
	{
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		if(holder[holder.size() - 1] != '/')
			holder += "/";
		consecutiveSlashsFinder(holder);
		serv.setRoot(holder);
    }
	else if (token == "max_body_size") 
	{
		iss >> holder;
		if(holder[holder.size() - 1] == ';')
			holder.erase(holder.size() - 1);
		if(holder[0] == '-' || !isNumber(holder))
			errorHolder("invalid Body Size!");
		if(isValueOverflowingULLONG_MAX(holder))
			errorHolder("body size overflowed!");

		serv.setMaxBdSize(_stoull(holder));
	}
	else if (token == "error_pages") 
	{
		vector<string> vec;
		while(iss >> token)
		{
			if(token[token.size() - 1] == ';')
				token.erase(token.size() - 1);
			vec.push_back(token);
		}
		serv.setErrorPages(vec);
	}
	else
		errorHolder("stranger attribute found as " + iss.str());

	if(iss.good())
		errorHolder("attribute [" + iss.str() + " ] got an issue");
}

void checkDuplicatedForAttributes(vector<string> Attrs)
{
	vector<string>::iterator it = Attrs.begin();
	for(; it + 1 != Attrs.end(); it++)
	{
		vector<string>::iterator itt = it + 1;
		for(; itt != Attrs.end(); itt++)
		{
			if(*it == *itt)
			{
				return errorHolder("Duplicated attributes in `" + *it + "`");
			}
		}
	}
}

void Config::catchConfig(const string &conf_file)
{
	string line;
	vector<Location> _locations;
	ifstream conf(conf_file.c_str());

	int serverNbr = -1;
	int servFlag = 0;
	int locFlag = 0;

	if (!conf.is_open())
        errorHolder("Config file can't be opened.");

	string readed = readFile(conf_file);

	if(readed.empty())
		errorHolder("empty config file!");
 
	if(!checkBrackets(readed))
		errorHolder("Brackets not even!");

	while(getline(conf, line))
	{
		if(lineCheck(line, servFlag, locFlag))
			continue;

		/* Servers */
		if(servFlag)
		{
			Server serv;
			while(spaceRemover(line).compare("location{") != 0)
			{
				if(lineCheck(line, servFlag, locFlag))
				{
					getline(conf, line);
					continue;
				}
				istringstream issObj(line);
				fetchingServBLocks(issObj, serv, duplicatesVecServ);
				getline(conf, line);
			}
			if(!spaceRemover(line).compare("location{"))
			{
				checkDuplicatedForAttributes(duplicatesVecServ);
				duplicatesVecServ.clear();
				validServerBlocks(serv);
				_servers.push_back(serv);
				serv = Server();
				if(_servers.size() > 1)
					checkDuplicatedServs(_servers);
				servFlag = 0;
				locFlag = 1;
				serverNbr++; // servers counter
				_locations.clear(); // clearing locations vector for the new server
				continue;
			}
		}

		/* Locations */
		if(locFlag)
		{
			Location loc;
			while(spaceRemover(line).compare("}") != 0)
			{
				if(lineCheck(line, servFlag, locFlag))
				{
					getline(conf, line);
					continue;
				}
				istringstream iss(line);
				fetchingLocBLocks(iss, loc, duplicatesVecLoc);
				getline(conf, line);

			}
			
			if(_hasRoot && loc.getRoot().empty())                 // if not server root and no location root exist
				errorHolder("Location needs a root path!");
			if(!spaceRemover(line).compare("}"))
			{
				checkDuplicatedForAttributes(duplicatesVecLoc);
				duplicatesVecLoc.clear();
				validateLocation(loc);
				_locations.push_back(loc);
				loc = Location(); //reset
				if(_locations.size() > 1)
					checkDuplicatedLocs(_locations);
				_servers[serverNbr].setLocs(_locations);
				locFlag = 0;
				continue;
			}
		}
	}

	// print();
	// exit(0);
	conf.close();
}

int Config::checkSocket(int fd)
{
    for (vector<Socket>::iterator it = _sockets.begin(); it != _sockets.end(); ++it)
    {
        if (it->getSocketFd() == fd)
            return fd;
    }
    return -1;
}

void Config::handle_requests()
{
    struct epoll_event events[MAX_EVENTS];
    struct epoll_event event;
	int epoll_fd, newsockfd;

	// init all servers
	
	for(size_t i = 0; i < _servers.size(); i++)
	{
		Socket soc;
		soc.init_serv(_servers[i]);
		_servers[i].setSocket(soc.getSocketFd());
		_map_servers[soc.getSocketFd()] = _servers[i];
		_sockets.push_back(soc);
	}

	// Create an epoll instance
    epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) {
        cout << "epoll create -> " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }

    // Register server sockets with epoll
    for (size_t i = 0; i < _sockets.size(); i++) 
	{
        event.events = EPOLLIN;
        event.data.fd = _sockets[i].getSocketFd();
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, _sockets[i].getSocketFd(), &event) == -1) 
		{
            // close(epoll_fd);
            cout << "epoll add -> " << strerror(errno) << endl;
        }
    }
	static size_t incrementer;
	map<int,Request> req;
    for (;;) 
	{
		signal(SIGPIPE, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
        // Wait for events on registered sockets
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) 
		{
            cout << "epoll wait -> " << strerror(errno) << endl;
            // break;
        }

		//if the call timed out before any file descriptor in the interest list became ready
		if(num_events == 0)
			continue;

        for (int i = 0; i < num_events; i++)
		{
			int index = checkSocket(events[i].data.fd);
            if (index > 0) 
			{
                // Handle incoming connection on the socket
                newsockfd = accept(events[i].data.fd, NULL, NULL);
				incrementer++;

				//add all clients accepted to a conta
                if (newsockfd == -1) {
                    break;
                }
				
				// struct epoll_event event;
				event.events = EPOLLIN | EPOLLOUT;
				event.data.fd = newsockfd;

				// adding the new client to the instance
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, newsockfd, &event) == -1) 
				{
					close(epoll_fd);
					break;
				}

				// This step is to link every request with the appropriate config file it cames from.
				Request rr;
				rr.setServConfig(_map_servers[index]);
				rr.setServersMap(_map_servers);
				req[newsockfd] = rr;
				req[newsockfd].cgiFileN = incrementer;
				req[newsockfd].startTime = clock();
            }
			else
			{
				if (events[i].events & EPOLLIN && !req[events[i].data.fd].getRequestCatch()) //Request
				{
					req[events[i].data.fd].startTime = clock();
					req[events[i].data.fd].Requesting(events[i].data.fd);
				}
				else if(events[i].events & EPOLLOUT && req[events[i].data.fd].getRequestCatch()) // response
				{
					req[events[i].data.fd].startTime = clock();
					if (((!req[events[i].data.fd].getResponseCode() || req[events[i].data.fd].getResponseCode() == 201)
						&& (req[events[i].data.fd].getMethode() == "GET" || req[events[i].data.fd].getMethode() == "POST")
						&& req[events[i].data.fd].getlocIndex() != -1 && !req[events[i].data.fd].getCgiDone()
						&& !req[events[i].data.fd].getServConfig().getLocs()[req[events[i].data.fd].getlocIndex()].getCgi().compare("on")))
					{
						Location loc = req[events[i].data.fd].getServConfig().getLocs()[req[events[i].data.fd].getlocIndex()];
						if(loc.isIndexed() && !loc.isRedirected() && !req[events[i].data.fd].getcgiTrue())
						{
							req[events[i].data.fd].old_url = req[events[i].data.fd]._url;
							string urlToServ = req[events[i].data.fd]._url + loc.getIndex();
							req[events[i].data.fd].setUrl(urlToServ);
						}
						// std::cout << "===CGI===" << std::endl;
						int Code = 0;
						Code = req[events[i].data.fd].cgi_obj.cgi_handler(req[events[i].data.fd]);
						if (!req[events[i].data.fd].getcgiTrue() && loc.isIndexed() && !loc.isRedirected())
						{
							req[events[i].data.fd].setUrl(req[events[i].data.fd].old_url);
							std::cout << "eywaa ==> " << req[events[i].data.fd]._url << std::endl;
						}
						if (req[events[i].data.fd].getcgiTrue() && !Code)
							continue;
						if (req[events[i].data.fd].getcgiTrue())
							req[events[i].data.fd].setResponseCode(Code);
					}
					if (!req[events[i].data.fd].getResponseSent())
						req[events[i].data.fd].handleContentRequest(events[i].data.fd);

					/* close finished socket */
					if(req[events[i].data.fd].getResponseSent())
					{
						std::cout << "-----DELETED-----" << std::endl;
						if (req[events[i].data.fd].infile.is_open())
							req[events[i].data.fd].infile.close();
						if (req[events[i].data.fd].outfile.is_open())
							req[events[i].data.fd].outfile.close();
						epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
						req.erase(events[i].data.fd);
						close(events[i].data.fd);
					}
				}

			}
			if (req.find(events[i].data.fd) != req.end())
			{
				req[events[i].data.fd].endTime = clock();
				if ((((double)req[events[i].data.fd].endTime - req[events[i].data.fd].startTime) / CLOCKS_PER_SEC > 7) && req[events[i].data.fd].startTime > 0)
				{
					if (req[events[i].data.fd].infile.is_open())
						req[events[i].data.fd].infile.close();
					if (req[events[i].data.fd].outfile.is_open())
						req[events[i].data.fd].outfile.close();
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
					req[events[i].data.fd].generateErrorResponse(events[i].data.fd, 408, " Request Timeout");
					req.erase(events[i].data.fd);
					close(events[i].data.fd);
					continue;
				}
			}
        }
    }

    // Cleanup: close epoll instance
    close(epoll_fd);
}
