#include"../includes/Request.hpp"
#include"../includes/cgi.hpp"


Request::Request()
{
    // std::string typ = mimetypes();
    std::string typ;
	std::string	s1;
	std::string	s2;
    std::ifstream file("./config/mime.types");
    if (file.is_open())
    {
        for (; std::getline(file, typ); )
        {
            s1 = typ.substr(0, typ.find(":"));
            s2 = typ.substr(typ.find(":") + 1, typ.find("\n") - 1);
            _contentType[s2] = s1;
            // std::cout << "s1==>" << s1 << " s2==> " << s2 << std::endl;
        }
    }
    else
    {
        std::cerr << "MIMEtypes file cannot be opened!" << std::endl;
    }
    // exit (0);
	// for (; !typ.empty(); )
	// {
	// 	s1 = typ.substr(0, typ.find(' '));
	// 	typ.erase(0, typ.find(' ') + 1);
	// 	s2 = typ.substr(0, typ.find('$'));
	// 	typ.erase(0, typ.find('$') + 1);
	// 	_contentType[s2] = s1;
	// }
    
    _errorPath[201] =  "./error_pages/201.html";
    _errorPath[204] =  "./error_pages/204.html";
    _errorPath[301] =  "./error_pages/301.html";
    _errorPath[400] =  "./error_pages/400.html";
    _errorPath[403] =  "./error_pages/403.html";
    _errorPath[404] =  "./error_pages/404.html";
    _errorPath[405] =  "./error_pages/405.html";
    _errorPath[413] =  "./error_pages/413.html";
    _errorPath[414] =  "./error_pages/414.html";
    _errorPath[500] =  "./error_pages/500.html";
    _errorPath[501] =  "./error_pages/501.html";
    _errorPath[505] =  "./error_pages/505.html";

    _errorStatus[200] = " OK";
    _errorStatus[201] = " Created";
    _errorStatus[204] = " No Content";
    _errorStatus[301] = " Moved Permanently";
    _errorStatus[400] = " Bad Request";
    _errorStatus[403] = " Forbidden";
    _errorStatus[404] = " Not Found";
    _errorStatus[405] = " Method Not Allowed";
    _errorStatus[408] = " Timeout";
    _errorStatus[411] = " Length Required";
    _errorStatus[413] = " Entity Too Large";
    _errorStatus[414] = " Request-URI Too Long";
    _errorStatus[500] = " Internal Server Error";
    _errorStatus[501] = " Not Implemented";
    _errorStatus[505] = " HTTP Version Not Supported";
    _errorStatus[504] = " Gateaway Timeout";

    _firstReadedtry = false;
    epollFlag = false; 
    readFlag = false;
    doneRead = false;
    ResponseSent = false;

    _partialChunkSize = "";
    old_url = "";
    immediateResponse = 0;
    bytesRead = 0;
    chunkSize = 0;
    ResponseCode = 0;
    counter = 0;
    endOfHeaders = 0;
    cgiFileN = 0;
    headersParsed = false;
    chunkedBytesReaded = 0;
    contentLength = 0;
    bodyRead = 0;
    locIndex = 0;
    bodyDone = false;
    rootLocIndex = -1;
    cgiDone = false;
    cgiTrue = false;
    RequestCatch = false;
    BoundaryFlag = false;
    BoundaryFlag2 = false;
    cgiIsPhp = false;
    cgiFlag = false;
	deleted = false;

    stopReadinginHeaderSection = false;
    _isContentLength = false;
    _isContentLength1stTime = false;
    _isChunked1stTime = false;
    _isRedirected = false;
    _isChunked = false;

    _chunkSize = 0;
    totalBytesRead = 0;
    BoundaryDelimiterSize = 0;

    postCreatedFileName = "";
    pathToLocation = "";
    initialBody = "";
    firstDirInPath = "";

    /* boundary */
}

Request::Request(const Request& obj) : Server(obj)
{
    *this = obj;
}

Request &Request::operator=(const Request& obj)
{
     _contentType = obj._contentType;
    _errorPath = obj._errorPath;
    _errorStatus = obj._errorStatus;
    _serv_conf = obj._serv_conf;
    cgi_obj = obj.cgi_obj;
    _firstReadedtry = false;
    servers_map = obj.servers_map;
    epollFlag = false;
    readFlag = false;
    doneRead = false;
    ResponseSent = false;
    headersParsed = false;
    contentLength = 0;
    bodyRead = 0;
    bodyDone = false;
    BoundaryFlag = false;
    BoundaryFlag2 = false;
    startTime = 0;
    endTime = 0;

    _expectCRLF = false;
    _partialChunkSize = "";
    old_url = "";

    
    _isContentLength = false;
    _isChunked = false;
    _postBody = "";
    _isChunked1stTime = false;
    _isBoundary1stTime = false;
    ResponseCode = 0;
    endOfHeaders = 0;
    cgiFileN = 0;
    rootLocIndex = -1;
    _chunkSize = 0;
    _isRedirected = false;
    cgiIsPhp = false;
    cgiFlag = false;
    locIndex = 0;
    cgiDone = false;
    cgiTrue = false;
	deleted = false;
    RequestCatch = false;
    immediateResponse = 0;
    totalBytesRead = 0;
    chunkedBytesReaded = 0;
    stopReadinginHeaderSection = false;
    initialBody = "";
    _chunkedDone = false;
    postCreatedFileName = "";

    _req_header = obj._req_header;
    _methode = obj._methode;
    _url = obj._url;
    _httpVersion = obj._httpVersion;
    firstDirInPath = "";
    pathToLocation = "";

    /* boundary */

    return *this;
}

Request::~Request()
{

}
/* Getters */

string &Request::getMethode(void)
{
    return _methode;
}
string Request::getUrl(void)
{
    return _url;
}
string &Request::getHttpVers(void)
{
    return _httpVersion;
}
Server &Request::getServConfig(void)
{
    return _serv_conf;
}
bool Request::getEpollFlag()
{
    return epollFlag;
}
bool Request::getdoneRead()
{
    return doneRead;
}
bool Request::getReadFlag()
{
    return readFlag;
}
int  Request::getlocIndex()
{
    return locIndex;
}
bool Request::getCgiDone()
{
    return cgiDone;
}
bool Request::getcgiTrue()
{
    return cgiTrue;
}
bool Request::getResponseSent()
{
    return ResponseSent;
}
Server  Request::getServer()
{
    return _serv_conf;
}
std::string Request::getfileName()
{
    return fileName;
}

map<std::string, std::string> Request::getReqHeader()
{
    return _req_header;
}

bool Request::getRequestCatch()
{
    return RequestCatch;
}

int Request::getResponseCode()
{
    return ResponseCode;
}

/* Setters */

void Request::setMethode(string &meth)
{
    _methode = meth;
}
void Request::setUrl(string &url)
{
    _url = url;
}
void Request::setHttp(string &http)
{
    _httpVersion = http;
}
void Request::setCgiDone(bool flag)
{
    cgiDone = flag;
}
void Request::setEpollFlag(bool flag)
{
    epollFlag = flag;
}
void Request::setServConfig(Server &serv_conf)
{
    _serv_conf = serv_conf;
}
void Request::setServersMap(map<int, Server> &servs_map)
{
    servers_map = servs_map;
}

void Request::setRequestCatch(bool f)
{
    RequestCatch = f;
}

void Request::setcgiTrue(bool ff)
{
    cgiTrue = ff;
}

void Request::setResponseCode(int Code)
{
    ResponseCode = Code;
}

/* Methods */

bool isDirectory(const char *path)
{
    struct stat fileInfo;
    stat(path, &fileInfo);
    return S_ISDIR(fileInfo.st_mode) != 0;
}

vector<string> split(const string& input, char delimiter) 
{
    vector<string> tokens;
    istringstream tokenStream(input);
    string token;

    while (getline(tokenStream, token, delimiter)) 
    {
        if(!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

bool _isFile(const char* path) 
{
    struct stat fileInfo;
    if(stat(path, &fileInfo) == -1)
        return 0;
    return S_ISREG(fileInfo.st_mode) != 0;
}

bool isUserPermitted(const string& path) 
{
    struct stat fileInfo;
    stat(path.c_str(), &fileInfo);
    return (fileInfo.st_mode & S_IRUSR) != 0;
}

bool hasDirectoryAccess(const std::string& directoryPath) {
    struct stat statbuf;

    if (stat(directoryPath.c_str(), &statbuf) == 0) 
    {
        // Check for read (S_IRUSR) and execute (S_IXUSR) permissions for the user
        return ((statbuf.st_mode & S_IRUSR) && (statbuf.st_mode & S_IXUSR)) != 0;
    }
    return false;
}

void Request::parse_firstline(string &fst_line)
{
    vector<string> firstline_params;

    firstline_params = split(fst_line, 32);
    if(!firstline_params[0].empty())
        _methode = firstline_params[0];
    else 
        _methode = "";
    if(!firstline_params[1].empty())
        _url = firstline_params[1];
    else
        _url = "";
    if(!firstline_params[2].empty())
        _httpVersion = firstline_params[2];
    else
        _httpVersion = "";
}

int findChar(string &str, char c)
{
    for(size_t i = 0; i < str.size(); i++)
        if(str[i] == c)
            return i;
    return -1;
}

const string nameGenerator() 
{
    // Get the current time
    time_t now = time(NULL);
    
    // Convert time_t to tm struct for local time
    struct tm *localTime = localtime(&now);
    
    // Use a stringstream to format the time into a string
    ostringstream nameStream;
    
    // You can format the time as you wish; here's a basic YYYYMMDD_HHMMSS format
    nameStream << (1900 + localTime->tm_year) << "-";
    
    // Ensure month, day, hour, minute, and second are two digits
    nameStream << (localTime->tm_mon < 9 ? "0" : "") << (localTime->tm_mon + 1) << "-";
    nameStream << (localTime->tm_mday < 10 ? "0" : "") << localTime->tm_mday << "_";
    nameStream << (localTime->tm_hour < 10 ? "0" : "") << localTime->tm_hour << ".";
    nameStream << (localTime->tm_min < 10 ? "0" : "") << localTime->tm_min << ".";
    nameStream << (localTime->tm_sec < 10 ? "0" : "") << localTime->tm_sec;
    
    return nameStream.str() + ".";
}

string extractFileExtension(const string& urlPath) 
{
    size_t lastDotPos = urlPath.rfind('.');

    return (lastDotPos != string::npos && lastDotPos < urlPath.length() - 1) ? urlPath.substr(lastDotPos + 1) : "";
}

string errorTemplate(int error_code, string status)
{
    stringstream response;

    response << "<!DOCTYPE html>\n";
    response << "<html lang=\"en\">\n";
    response << "<head>\n";
    response << "<meta charset=\"UTF-8\">\n";
    response << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    response << "<title>" + intToString(error_code) + " :" + status + "</title>\n";
    response << "<style>\n";
    response << "html { height: 100%; }\n";
    response << "body { min-height: 100%; background-color: #111111; font-family: \"Roboto Condensed\"; text-transform: uppercase; overflow: hidden; }\n";
    response << ".police-tape { background-color: #C7C8CC; background: linear-gradient(180deg, lighten(#e2bb2d, 20%) 0%, #e2bb2d 5%, #e2bb2d 90%, lighten(#e2bb2d, 5%) 95%, darken(#e2bb2d, 50%) 100%); padding: 0.125em; font-size: 3em; text-align: center; white-space: nowrap; }\n";
    response << ".police-tape--1 { transform: rotate(10deg); position: absolute; top: 40%; left: -5%; right: -5%; z-index: 2; margin-top: 0; }\n";
    response << ".police-tape--2 { transform: rotate(-8deg); position: absolute; top: 50%; left: -5%; right: -5%; }\n";
    response << ".ghost { display: flex; justify-content: stretch; flex-direction: column; height: 100vh; }\n";
    response << ".ghost--columns { display: flex; flex-grow: 1; flex-basis: 200px; align-content: stretch; }\n";
    response << ".ghost--navbar { flex: 0 0 60px; background: linear-gradient(0deg, #27292d 0px, #27292d 10px, transparent 10px); border-bottom: 2px solid #111111; }\n";
    response << ".ghost--column { flex: 1 0 30%; border-width: 0px; border-style: solid; border-color: #27292d; border-left-width: 10px; background-color: darken(#27292d, 6%); }\n";
    response << ".ghost--main { background-color: #111111; border-top: 15px solid lighten(#27292d, 4%); flex: 1 0 100px; }\n";
    response << ".code { display: block; width: 100px; background-color: #27292d; height: 1em; margin: 1em; }\n";
    response << ".ghost--main .code { height: 2em; width: 200px; }\n";
    response << "</style>\n";
    response << "</head>\n";
    response << "<body>\n";
    response << "<div class=\"ghost\">\n";
    response << "<div class=\"ghost--navbar\"></div>\n";
    response << "<div class=\"ghost--columns\">\n";
    response << "<div class=\"ghost--column\">\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "</div>\n";
    response << "<div class=\"ghost--column\">\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "</div>\n";
    response << "<div class=\"ghost--column\">\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "</div>\n";
    response << "</div>\n";
    response << "<div class=\"ghost--main\">\n";
    response << "<div class=\"code\"></div>\n";
    response << "<div class=\"code\"></div>\n";
    response << "</div>\n";
    response << "</div>\n";
    response << "<h1 class=\"police-tape police-tape--1\">\n";
    response << "&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "\n";
    response << "</h1>\n";
    response << "<h1 class=\"police-tape police-tape--2\">" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + status + " : " + intToString(error_code) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n";
    response << "</h1>\n";
    response << "</body>\n";
    response << "</html>\n";
    
    return response.str();
}

void Request::generateErrorResponse(int cli_fd, int error_code, const std::string& status) 
{
    bool flag = true;
    string fullPth;
    // exit (0);

    if(cgiDone && ResponseCode == 200)
    {
        sendHtmlResponseFile(cli_fd, 200, " OK", fullPth, "text/html");
        
        // if(ResponseSent)
        //     unlink(fullPth.c_str()); // remove output file after reading the content for CGI
    }
    else if(_serv_conf.getErrorPages().size() == 2 && _isFile(_serv_conf.getErrorPages()[1].c_str()) && intToString(error_code) == _serv_conf.getErrorPages()[0])
    {
        if(_serv_conf.getErrorPages()[1].substr(_serv_conf.getErrorPages()[1].find_last_of('.')) != ".html")
            flag = false;
        else
        {
            sendHtmlResponseFile(cli_fd, error_code, status, _serv_conf.getErrorPages()[1], "text/html");
        }
    }
    if(!flag || (flag && ResponseCode != 200))
    {
        string response = errorTemplate(error_code, status);
        stringstream responseFinale;
        if(_methode == "HEAD")
        {
            responseFinale << "HTTP/1.1 " + intToString(error_code) + status + "\r\n";
            responseFinale << "Content-Type: text/html\r\n";
            responseFinale << "Content-Length: 0\r\n";
            responseFinale << "\r\n";
        }
        else
        {
            responseFinale << "HTTP/1.1 " + intToString(error_code) + status + "\r\n";
            responseFinale << "Content-Type: text/html\r\n";
            responseFinale << "Content-Length: " + intToString(response.size()) + "\r\n";
            responseFinale << "Connection: close\r\n";
            responseFinale << "\r\n";
            responseFinale << response;
        }
        
        if (send(cli_fd, responseFinale.str().c_str(), responseFinale.str().length(), 0) == -1)
        {
            std::cout << "Generate Error: " << strerror(errno) << std::endl;
        }
        // std::cout << ResponseCode << std::endl;
        // exit (0);
        ResponseSent = true;
        if(cgiDone)
            unlink(filePathstr.c_str());
    }
}

void Request::processHeaders(const string& headerStr) 
{
        istringstream headerStream(headerStr);
        string line;
        while (getline(headerStream, line) && line != "\r") 
        {
            size_t colonPos = line.find(":");
            if (colonPos != string::npos) {
                string key = line.substr(0, colonPos);
                string value = line.substr(colonPos + 2, line.size() - colonPos - 3); // Exclude the carriage return
                _req_header[key] = value;
                
                // If this is the Content-Length header, store its value
                    // cout << "--> " << key << endl;
                if(_methode == "POST")
                {
                    if (key == "Content-Length") 
                    {
                        contentLength = atoi(value.c_str());
                        if (!contentLength)
                        {
                            ResponseCode = 411;
                            throw ResponseCode;
                            // return ;
                        }
                        _isContentLength = true;
                    }
                    if(key == "Transfer-Encoding" && value == "chunked")
                        _isChunked = true;
                    else if (key == "Transfer-Encoding" && value != "chunked")
                    {
                        // _isContentLength = false;
                        ResponseCode = 501;
                        throw ResponseCode;
                        // return;
                    }
                }
                // add boundary check

            }
        }
        // add boundary check

        if (_methode == "POST" && !_isContentLength && !_isChunked)
        {
            ResponseCode = 400;
            throw ResponseCode;
        }
}

void Request::uploadCheckers()
{
    if (locIndex != -1 && !_serv_conf.getLocs()[locIndex].locHasPOSTallowed())
    {
        bodyDone = true;
        ResponseCode = 405;
        throw ResponseCode;
    }
    else if (locIndex != -1 && (!_serv_conf.getLocs()[locIndex].getUpload().size() || _serv_conf.getLocs()[locIndex].getUpload()[0] == "off"))
    {
        bodyDone = true;
        ResponseCode = 400;
        throw ResponseCode;
    }
    else if (locIndex != -1)
    {
        uploadPath = _serv_conf.getLocs()[locIndex].getUpload()[1];
        DIR*        dir = opendir(uploadPath.c_str());
        if (!dir)
        {
            bodyDone = true;
            ResponseCode = 400;
            throw ResponseCode;
        }
        closedir(dir);
    }
}

string removeConsecutiveSlashes(string str)
{
    string cleanPath;
    bool slashFound = false;
    for(size_t i = 0; i < str.size(); i++)
    { 
        if(str[i] == '/') 
        {
            if(!slashFound)
            {
                cleanPath += str[i];
                slashFound = true;
            }
        }
        else
        {
            cleanPath += str[i];
            slashFound = false;
        }
    }
    return cleanPath;
}

int Request::serverIndexFinder(string servName, string port)
{
    map<int, Server>::iterator it = servers_map.begin();
    if(!servName.empty())
    {
        for(; it != servers_map.end(); it++)
        {
            if(!it->second.getServername().compare(servName) || !it->second.getHost().compare(servName))
                return it->first;
        }
    }
    else if(!port.empty())
    {
        for(; it != servers_map.end(); it++)
        {
            if(!it->second.getListen().compare(port))
                return it->first;
        }
    }
	return -1;
}

int dupServerFound(map<int ,Server> servs)
{
    map<int ,Server>::iterator it = servs.begin();
	map<int ,Server>::iterator itt;
    int i = 0;
    for(; it != servs.end(); it++)
	{
        itt = it;
        itt++;
		for(; itt != servs.end(); itt++)
		{
			if(it->second.getListen() == itt->second.getListen() && it->second.getHost() == itt->second.getHost())
            {
				return i;
            }
		}
        i++;
	}
	return -1;
}

int dupServerFoundIndex(map<int ,Server> servs)
{
    map<int ,Server>::iterator it = servs.begin();
	map<int ,Server>::iterator itt;
    for(; it != servs.end(); it++)
	{
        itt = it;
        itt++;
		for(; itt != servs.end(); itt++)
		{
			if(it->second.getListen() == itt->second.getListen() && it->second.getHost() == itt->second.getHost())
				return it->first;
		}
	}
	return -1;
}

bool isServerExist(string host, map<int ,Server> servMap)
{
    map<int, Server>::iterator it = servMap.begin();
	for(; it != servMap.end(); it++)
	{
		if(!it->second.getServername().compare(host) || !it->second.getHost().compare(host))
			return true;
	}
	return false;
}

bool isListenExist(string listen, map<int ,Server> servMap)
{
    map<int, Server>::iterator it = servMap.begin();
	for(; it != servMap.end(); it++)
	{
		if(!it->second.getListen().compare(listen))
			return true;
	}
	return false;
}

void Request::encode_url()
{
    std::string AllowedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
    for (size_t x = 0; x < _url.size(); x++)
    {
        if (AllowedCharacters.find(_url[x]) == std::string::npos)
        {
            ResponseCode = 400;
            throw ResponseCode;
        }
        if (_url[x] == '%' && (x + 2) <= _url.size())
        {
            size_t  hexa = 0;
            std::string str;
            std::stringstream ss;
            str = _url.substr(x + 1, x + 3);
            ss << std::hex << str;
            ss >> hexa;
            if (AllowedCharacters.find(static_cast<char>(hexa)) == std::string::npos)
            {
                ResponseCode = 400;
                throw ResponseCode;
            }
        }
    }
}

void Request::firstComingRequest(string& myBuff, int len)
{
    bool flag = false;
    static size_t    FileNumber;
    (void)len;
    size_t endOfFirstLine = myBuff.find("\r\n");

    /* Parsing the first line of the request */
    if (endOfFirstLine != string::npos) 
    {
        string firstLine = myBuff.substr(0, endOfFirstLine);
        size_t firstSpace = firstLine.find(32);
        size_t secondSpace = firstLine.find(32, firstSpace + 1);
        if (firstSpace != string::npos && secondSpace != string::npos) 
        {
            flag = true;
            _methode = firstLine.substr(0, firstSpace);
            if (_methode != "GET" && _methode != "POST" && _methode != "DELETE")
            {
                ResponseCode = 501;
                // std::cout << ResponseCode << std::endl;
                throw ResponseCode;
            }
            _url = removeConsecutiveSlashes(firstLine.substr(firstSpace + 1, secondSpace - firstSpace - 1));
            if(!_url.compare("/favicon.ico"))
            {
                ResponseCode = 200;
                throw ResponseCode;
            }
            _httpVersion = firstLine.substr(secondSpace + 1);
            if (_httpVersion != "HTTP/1.1")
            {
                ResponseCode = 505;
                throw ResponseCode;
            }
        }
    }

    if (!flag)
    {
        ResponseCode = 400;
        throw ResponseCode;
    }
    encode_url();
    std::string AllowedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
    for (size_t x = 0; x < _url.length(); x++)
    {
        if (AllowedCharacters.find(_url[x]) == std::string::npos)
        {
            ResponseCode = 400;
            throw ResponseCode;
            // return;
        }
    }
    size_t PORTsize = _serv_conf.getListen().size();
    if (10 + PORTsize + _url.size() > 2048)
    {
        ResponseCode = 414;
        throw ResponseCode;
        // return;
    }
    // std::cout<< "OUT" << std::endl;
    // exit (0);
    // Find the start of the headers
    size_t startOfHeaders = endOfFirstLine + 2; // Skip '\r\n'

    // Find the end of headers (double '\r\n' marks the end of headers)
    endOfHeaders = myBuff.find("\r\n\r\n", startOfHeaders);

    if (endOfHeaders != string::npos) 
    {
        // Extract the headers section
        processHeaders(myBuff.substr(startOfHeaders, endOfHeaders));
        
        /* if host is given within headers */
        if(!getReqHeader()["Host"].empty() && dupServerFound(servers_map) != -1)
        {
            string hostt = getReqHeader()["Host"];
            // servername without :
            string hostVal;
            string port = "";
            if(hostt.find(":") != string::npos)
            {
                if(split(hostt, ':').size() == 0 || split(hostt, ':').size() > 2)
                {
                    ResponseCode = 400;
                    throw ResponseCode;
                }
                hostVal = hostt.substr(0, hostt.find(":"));
                port = hostt.substr(hostt.find(":") + 1);
            }
            else
                hostVal = hostt;
            
            if(isServerExist(hostVal, servers_map))
            {
                int dupIndex = dupServerFoundIndex(servers_map);
                if(serverIndexFinder(hostVal, ""))
                {
                    if(servers_map[serverIndexFinder(hostVal, "")].getListen() == _serv_conf.getListen())
                            _serv_conf = servers_map[serverIndexFinder(hostVal, "")];
                    else
                        _serv_conf = servers_map[dupIndex];
                }
                else
                    _serv_conf = servers_map[dupIndex];
            }

            else
                _serv_conf = servers_map[dupServerFoundIndex(servers_map)];
        }
        else if(getReqHeader()["Host"].empty() && dupServerFound(servers_map) != -1)
            _serv_conf = servers_map[dupServerFoundIndex(servers_map)];

        locationMatcher();
        if (_methode == "POST")
        {
            uploadCheckers();
            if(_isChunked || _isContentLength)
            {
                if (_isContentLength)
                {
                    if (static_cast<unsigned long>(contentLength) > _serv_conf.getMaxBdSize())
                    {
                        bodyDone = true;
                        ResponseCode = 413;
                        throw ResponseCode;
                    }
                }
                FileNumber++;
                std::stringstream y;
                y << FileNumber;
                std::string n;
                y >> n;
                std::string typo = _contentType[_req_header["Content-Type"]];
                if (typo.empty())
                    typo = "txt";
                fileName = uploadPath + "/file-number=" + n + "." + typo;
                if (_isFile(fileName.c_str()))
                {
                    while (_isFile(fileName.c_str()))
                    {
                        FileNumber++;
                        std::stringstream y;
                        y << FileNumber;
                        std::string n;
                        y >> n;
                        fileName = uploadPath + "/file-number=" + n + "." + typo;
                    }
                }
                outfile.open(fileName.c_str());
                if (!outfile)
                {
                    ResponseCode = 500;
                    throw ResponseCode;
                }
            }
            if (!myBuff.substr(endOfHeaders + 4).empty())
                initialBody = myBuff.substr(endOfHeaders + 4); //1024-end - 4
            // bodyRead += initialBody.size();
        }
        // Mark headers as parsed
        headersParsed = true;
        if(_methode == "GET" || _methode == "DELETE")
        {
            // exit (0);
            ResponseCode = 0;
            throw ResponseCode;
            // RequestCatch = true;
            // return;
        }
    }
}

void Request::contentLengthHandler(int sock_fd)
{
    (void)sock_fd;
    if(!_isContentLength1stTime)
    {
        size_t  iBodysize = initialBody.size();
        if (!iBodysize)
        {
            _isContentLength1stTime = true;
            return;
        }
        if (iBodysize > (size_t)contentLength)
        {
            outfile.write(initialBody.c_str(), contentLength);
            bodyRead = contentLength;
        }
        else
            outfile.write(initialBody.c_str(), iBodysize);
        if (outfile.fail())
        {
            // OPTIONAL !!!
            std::cerr << "write() failed to save body" << std::endl;
            exit (EXIT_FAILURE);
        }
        bodyRead += iBodysize;
        outfile.flush();
        initialBody.clear();
        _isContentLength1stTime = true;
    }
    else
    {
        if (bytesRead + bodyRead > contentLength)
        {
            outfile.write(_buffer, contentLength - bodyRead);
            bodyRead = contentLength;
        }
        else
            outfile.write(_buffer, bytesRead);
        if (outfile.fail())
        {
            // OPTIONAL !!!
            std::cerr << "write() failed to save body" << std::endl;
            exit (EXIT_FAILURE);
        }
        outfile.flush();
        bodyRead += bytesRead;
    }
    if(contentLength > 0 && bodyRead >= contentLength)
    {
        ResponseCode = 201;
        readFlag = true;
        outfile.close();
        throw ResponseCode;
    }
}

void Request::GetSize()
{
	std::string hexSize = chunkString.substr(0, chunkString.find("\r\n"));
	size_t	sub = hexSize.size() + 2;
	chunkString.erase(0, sub);
	counter -= sub;
	std::stringstream stream;
	stream << std::hex << hexSize;
	stream >> chunkSize;
}

void Request::chunkedHandler(int sock_fd)
{
    std::cout << "CHUUNKK" << std::endl;
    (void)sock_fd;
	if (!_isChunked1stTime)
	{
        size_t  iBodySize = initialBody.size();
        if (!iBodySize)
        {
            _isContentLength1stTime = true;
            return;
        }
		counter = iBodySize;
		chunkString.append(initialBody.c_str(), iBodySize);
		GetSize();
		_isChunked1stTime = true;
        //////
        while (chunkSize &&  chunkSize < iBodySize)
        {
            outfile.write(chunkString.c_str(), chunkSize);
            if (outfile.fail())
            {
                // OPTIONAL !!!
                std::cerr << "write() failed to save chunk" << std::endl;
                exit (EXIT_FAILURE);
            }
            chunkString.erase(0, chunkSize);
            chunkString.erase(0, 2);
            counter -= (chunkSize + 2);
            GetSize();
            std::cout << chunkSize << std::endl;
        }
	}
    else
    {
        chunkString.append(_buffer, bytesRead);
        counter += bytesRead;
    }
 
	while (counter > chunkSize && chunkString.find("\r\n", chunkSize + 2) != std::string::npos)
	{
		outfile.write(chunkString.c_str(), chunkSize);
		if (outfile.fail())
		{
			// OPTIONAL !!!
            std::cerr << "write() failed to save chunk" << std::endl;
            exit (EXIT_FAILURE);
		}
		chunkString.erase(0, chunkSize);
		chunkString.erase(0, 2);
		counter -= (chunkSize + 2);
		GetSize();
	}

	if (!chunkSize)
	{
        // bodyDone = true;
        ResponseCode = 201;
        readFlag = true;
        _chunkedDone = true;
        outfile.close();
        throw ResponseCode;
		// return;
	}
}

void Request::catchRequestForHeaders(string& myBuff, int len)
{
    /* First request that cames*/
    if(!headersParsed){
        firstComingRequest(myBuff, len);
    }
}

void Request::catchRequest(int sock_fd)
{
    if (_methode == "POST" && headersParsed)
    {
        if(_isChunked)
            chunkedHandler(sock_fd);
        else if(_isContentLength)
            contentLengthHandler(sock_fd);
    }
}

int Request::_locationPatternMatcher(string firsDirinPath)
{
    /* removing slashs*/
    if(firsDirinPath[0] == '/')
        firsDirinPath = firsDirinPath.substr(1);
    if(firsDirinPath[firsDirinPath.size() - 1] == '/')
        firsDirinPath = firsDirinPath.substr(0, firsDirinPath.size() - 1);

    for(size_t i = 0; i < _serv_conf.getLocs().size(); i++)
    {
        string pattern = _serv_conf.getLocs()[i].getPattern();
        if(pattern[0] == '/')
            pattern = pattern.substr(1);
        if(pattern[pattern.size() - 1] == '/')
            pattern = pattern.substr(0, pattern.size() - 1);
        
        if(!pattern.compare(firsDirinPath))
        {
            return i;
        }
    }
    return -1;
}

void Request::locationMatcher()
{
    rootLocIndex = _locationPatternMatcher("/");

    // override the old root by the new from the location /
    if(rootLocIndex >= 0 && !_serv_conf.getLocs()[rootLocIndex].getRoot().empty())
        _serv_conf.setRoot(_serv_conf.getLocs()[rootLocIndex].getRoot());

    // if(_methode == "DELETE")
    // {
    //     ResponseCode = 0;
    //     throw ResponseCode;
    // }
    // if DOT is found in url
    if(_url.find("/.") != string::npos && _url.find("/.") == 0 && _url[2] != '.')
        _url.erase(1,2);

    if(!_url.substr(0, _url.find('/', 1) + 1).empty() && _url.find("/..") != 0)
        firstDirInPath = _url.substr(0, _url.find('/', 1) + 1);
    else if(rootLocIndex >= 0)
        firstDirInPath = '/';
    else
        firstDirInPath = _url;

    
    if(rootLocIndex == -1)
    {
        if(firstDirInPath[firstDirInPath.size() - 1] == '/')
        {
            locIndex = _locationPatternMatcher(firstDirInPath.substr(0, firstDirInPath.size() - 1));
        }
        else
        {
            locIndex = _locationPatternMatcher(firstDirInPath);
        }

        if(locIndex == -1)
        {
            ResponseCode = 404;
            throw ResponseCode;
        }

        if(!_serv_conf.getLocs()[locIndex].getRoot().empty())
            pathToLocation = _serv_conf.getLocs()[locIndex].getRoot() + _url.substr(firstDirInPath.size());
        else if(_serv_conf.getLocs()[locIndex].getRoot().empty())
            pathToLocation = _serv_conf.getRoot() + _url.substr(firstDirInPath.size());
        
    }
    else
    {
        locIndex = rootLocIndex;
        if(!_serv_conf.getLocs()[locIndex].getRoot().empty())
            pathToLocation = _serv_conf.getLocs()[locIndex].getRoot() + _url.substr(1);
        else if(_serv_conf.getLocs()[locIndex].getRoot().empty())
            pathToLocation = _serv_conf.getRoot() + _url.substr(1);
    }

    if(pathToLocation.find("/..") != string::npos)
    {
        char rr[PATH_MAX];
        char *res = realpath(pathToLocation.c_str(), rr);
        if(!res)
        {
            ResponseCode = 404;
            throw ResponseCode;
            // return;
        }
        pathToLocation = rr;
        pathToLocation += "/";
        if(!_serv_conf.getLocs()[locIndex].getRoot().empty())
        {
            if(pathToLocation.find(_serv_conf.getLocs()[locIndex].getRoot()) == string::npos)
            {
                ResponseCode = 403;
                throw ResponseCode;
                // return;
            }
        }
        else if(_serv_conf.getLocs()[locIndex].getRoot().empty())
        {
            if(pathToLocation.find(_serv_conf.getRoot()) == string::npos)
            {
                ResponseCode = 403;
                throw ResponseCode;
                // return;
            }
        }
    }

    if(!isDirectory(pathToLocation.c_str()) && !_isFile(pathToLocation.c_str()) && _url != "/favicon.ico")
    {
        // if(_serv_conf.getLocs()[locIndex].isRedirected())
        // {
        //     _url = firstDirInPath;
        //     ResponseCode = 301;
        //     throw ResponseCode;
        // }
        std::string tmp = pathToLocation.substr(0, pathToLocation.find_last_of("?"));
        if (_serv_conf.getLocs()[locIndex].getCgi().compare("on") || !_isFile(tmp.c_str()))
        {
            cout << "-->" << firstDirInPath << endl;
            ResponseCode = 404;
            throw ResponseCode;
        }
    }

    if(firstDirInPath[firstDirInPath.size() - 1] != '/')
    {
        _url += '/';
        ResponseCode = 301;
        throw ResponseCode;
    }

    pureLoc = _url;
    if(!_serv_conf.getLocs()[locIndex].getRoot().empty())
        _url = pathToLocation.substr(_serv_conf.getLocs()[locIndex].getRoot().size());
    else if(_serv_conf.getLocs()[locIndex].getRoot().empty())
        _url = pathToLocation.substr(_serv_conf.getRoot().size());

    if (_serv_conf.getLocs()[locIndex].isIndexed() && !_serv_conf.getLocs()[locIndex].isRedirected())
        pathToLocation = pathToLocation + _serv_conf.getLocs()[locIndex].getIndex();
        // indexFullPath = pathToLocation + _serv_conf.getLocs()[locIndex].getIndex();
    // exit(0);
}

void Request::Requesting(int _socFd)
{
    try
    {
        memset(_buffer, 0, SIZE);
        bytesRead = read(_socFd, _buffer, SIZE);
        if (bytesRead < 0)
        {
            ResponseCode = 500;
            throw ResponseCode;
        }
        // if (bytesRead < 0)
        // {
        //     std::cout << "2" << strerror(errno) << std::endl;
        //     exit (EXIT_FAILURE);
        // }

        if(!headersParsed)
        {
            myBuff.append(_buffer, bytesRead);
            if (myBuff.find("\r\n\r\n") == std::string::npos)
                return;
            
            firstComingRequest(myBuff, bytesRead);
            catchRequest(_socFd);
        }
        else
        {
            catchRequest(_socFd);
        }
    }
    catch (...)
    {
        RequestCatch = true;
    }
}

string intToString(int value) 
{
    stringstream ss;
    ss << value;
    return ss.str();
}

string charToString(char buff[]) 
{
    stringstream ss;
    ss << buff;
    return ss.str();
}

void Request::sendHtmlResponseFile(int clientSocket, int errCode ,const string status, string filePath, string cnttype) 
{
    
    if(infile.is_open())
    {
        memset(_toRead, 0, SIZE);
        infile.read(_toRead, SIZE);
        // if (send(clientSocket, _toRead, infile.gcount(), 0) && filePath.compare("./favicon.ico"))
        if (send(clientSocket, _toRead, infile.gcount(), 0) < 0)
        {
            ResponseSent = true;
            return;
        }
        if(infile.eof())
        {
            unlink(filePathstr.c_str());
            infile.close();
            ResponseSent = true;
            return;
        }
        else if (infile.fail())
        {
            unlink(filePathstr.c_str());
            infile.close();
            ResponseSent = true;
            return;
        }
    }
    else if (!infile.is_open()) 
    {
        if(!_firstReadedtry && !cgiDone && !cgiTrue)
        {
            string response;
            infile.open(filePath.c_str());
            struct stat flstat;
            stat(filePath.c_str(), &flstat);

            response = "HTTP/1.1 " + intToString(errCode) + status + "\r\nContent-type: ";
            response += cnttype + "\r\nContent-Length: " + intToString(flstat.st_size) + "\r\n\r\n";
            _firstReadedtry = true;
            if (send(clientSocket, response.c_str(), response.length(), 0) < 0)
            {
                ResponseSent = true;
                return;
            }
        }
        else if(!_firstReadedtry && cgiDone)
        {
            string response;
            filePath = pathToLocation.substr(0, pathToLocation.find_last_of('/')) + "/cgi-output-" + intToString(cgiFileN++);
            filePathstr = filePath;
            infile.open(filePath.c_str());
            if(infile.fail())
            {
                ResponseSent = true; ///////////////////////////////////////////
                // throw ResponseCode;
                return ;
                cout << "******* >>" << filePath << endl;
                exit(0);
            }
            struct stat flstat;
            stat(filePath.c_str(), &flstat);
            _firstReadedtry = true;
            std::string rep;

            if (!cgiIsPhp)
                rep += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            else
                rep += "HTTP/1.1 200 OK\r\n";
            if (send(clientSocket, rep.c_str(), rep.length(), 0) == -1)
                std::cout << "8" << strerror(errno) << std::endl;
        }
    }
}

void Request::sendDirResponse(int clientSocket, const string content, int errCode)
{
    // Constructing the HTTP response
    ostringstream httpResponse;
    if(_isRedirected)
    {
        httpResponse << "HTTP/1.1 " << errCode << _errorStatus[errCode] << "\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                      << "Location: " << _serv_conf.getLocs()[locIndex].getRedirection() << "\r\n"
                    << "\r\n" << content;
        _isRedirected = false;
    }
    else
    {
        httpResponse << "HTTP/1.1 " << errCode << _errorStatus[errCode] << "\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                    << "\r\n" << content;
    }
    string response = httpResponse.str();

    // Send the HTTP response to the client
    if (send(clientSocket, response.c_str(), response.length(), 0) == -1)
        std::cout << "6" << strerror(errno) << std::endl;
    ResponseSent = true;
}

void sendDeleteResponse(int clientSocket, const string content) 
{
    // Constructing the HTTP response
    ostringstream httpResponse;
    httpResponse << content;

    string response = httpResponse.str();

    // Send the HTTP response to the client
    if (send(clientSocket, response.c_str(), response.length(), 0) == -1)
        std::cout << "7" << strerror(errno) << std::endl;
}

string Request::getErrorPath(int pageCode)
{
    // if(pageCode)                       check code validity
	map<int, string>::iterator it = _errorPath.begin();
	for(;it != _errorPath.end(); it++)
    {
        if(it->first == pageCode)
            return it->second;
    }
    return _errorPath[404];
}

string Request::getErrorStatus(int pageCode)
{
    // if(pageCode)                       check code validity
	map<int, string>::iterator it = _errorStatus.begin();
	for(;it != _errorStatus.end(); it++)
    {
        if(it->first == pageCode)
            return it->second;
    }
    return _errorStatus[404];
}

bool pathIncluded(string &path)
{
    char resolved[PATH_MAX];
    if (realpath(path.c_str(), resolved) == NULL && path.compare("/favicon.ico")) 
        return false;
    string pth = resolved;
    return pth.find("data") != string::npos;
}

string Request::generateDirectoryListing(string directoryPath, string locName)
{
    ostringstream listingStream;

    DIR* dir;
    struct dirent* entry;
    
    if ((dir = opendir(directoryPath.c_str())) != NULL)
    {
        listingStream << "<html><head><title>Directory Listing</title>";
        listingStream << "<style>";
        listingStream << "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; padding: 0; display: flex; flex-direction: column; align-items: center; justify-content: center; min-height: 100vh; background-color: #f4f4f4; }";
        listingStream << "h1 { color: #333; text-align: center; }";
        listingStream << ".directory-listing { text-align: center; }";
        listingStream << ".card { display: inline-block; width: 200px; padding: 10px; margin: 10px; background-color: #fff; border: 1px solid #ddd; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); transition: transform 0.3s; }";
        listingStream << ".card:hover { transform: scale(1.05); background-color: #f8c471; }";
        listingStream << ".card a { color: #3498db; text-decoration: none; }";
        listingStream << ".card a:hover { text-decoration: underline; }";
        listingStream << "</style>";
        listingStream << "</head><body><div class=\"directory-listing\">";
        listingStream << "<h1>Directory Listing for <span style=\"color: green;\">" << locName << "</span></h1>";

        while ((entry = readdir(dir)) != NULL) 
        {
            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && entry->d_name[0] != '.' && strcmp(entry->d_name, "favicon.ico")) 
            {
                listingStream << "<div class=\"card\">";
                string entryPath = directoryPath + entry->d_name;
                // Check if the entry is a directory
                struct stat fileInfo;
                if (stat(entryPath.c_str(), &fileInfo) == 0 && S_ISDIR(fileInfo.st_mode)) 
                {
                    entryPath += "/";
                    listingStream << "<a href=\"" << entryPath.substr(directoryPath.size()) << "\""
                        << " style=\"text-decoration: none; display: block; padding: 0px 2px; border: none; background-color: transparent; color: green;\""
                        << ">" << entry->d_name << "</a>";
                }
                else
                {
                    listingStream << "<a href=\"" << entryPath.substr(directoryPath.size()) << "\""
                        << " style=\"text-decoration: none; display: block; padding: 0px 2px; border: none; background-color: transparent; color: green;\""
                        << ">" << entry->d_name << "</a>";\
                }

                listingStream << "</div>";
            }
        }

        listingStream << "</div></body></html>";
        closedir(dir);
    } 
    else
    {
        listingStream << getErrorPath(404);
    }

    return listingStream.str();
}

string Request::getContentType(string reference)
{
	map<string, string>::iterator it = _contentType.begin();
	for(;it != _contentType.end(); it++)
		if(reference == it->second)
			return it->first;
	// errorHolder("invalid content type");
	return "";
}

bool indexFileAcces(string idxFile)
{
	ifstream indexFile;
	indexFile.open(idxFile.c_str());
	if(indexFile.fail())
        return false;
    indexFile.close();
    return true;
}

int Request::isLocation(string &_url)
{
    if(_url.compare("/"))
    {
        string url = _url.substr(_serv_conf.getRoot().size() - 1);
        if(url.empty())
            return _locationPatternMatcher("/");
        for(size_t i = 0; i < _serv_conf.getLocs().size(); i++)
        {
            if(!_serv_conf.getLocs()[i].getPattern().compare(url))
            {
                return i;
            }
        }
    }
    return -1;
}

//// delete
// DELETE METHOD NADYA CHAMA
bool Request::isFile(const char* path) 
{
    // tra mushkil fch knhyd perm lwhd direc katji hta ktlqa f_ok 
    struct stat file_stat;

    // Use stat to get information about the file
    if (stat(path, &file_stat) == 0) 
    {
        // Check if it's a regular file
        if (S_ISREG(file_stat.st_mode)) 
            return (true);
        else 
            return (false);
    }
    return (false);
}

int Request::isDirectoryCheck(const char *path)
{
    DIR *ptr_dir = opendir(path);

    if (ptr_dir)
    {
        closedir(ptr_dir);
        return (0);
    }
    else
    {
        int error_code = errno;

        // Si l'erreur est due à des problèmes de permissions
        if (error_code == EACCES)
        {
            closedir(ptr_dir);
            return (-1);
        }
        closedir(ptr_dir);
        return (1);
    }
    return (0);
}

bool Request::CheckPermissions(const char *path) 
{
    if (access(path, W_OK) == -1) 
        return (false);
    return (true);
}

bool Request::RemoveDirectory(const char *path) 
{
    DIR *ptr_dir = opendir(path);
    struct dirent *ptr_dirent;
    
    if (ptr_dir != NULL)
    {
        while((ptr_dirent = readdir(ptr_dir)) != NULL)
        {
            if (strcmp(ptr_dirent->d_name, ".") != 0 && strcmp(ptr_dirent->d_name, "..") != 0)
            {
                string path_name = string(path) + ptr_dirent->d_name;
                
                if (ptr_dirent->d_type == DT_DIR)
                {
                    if (CheckPermissions(path_name.c_str()) == true)
                        RemoveDirectory(path_name.c_str());
                    else
                    {
                        closedir(ptr_dir);
                        return(false);
                    }
                }
                else if(ptr_dirent->d_type == DT_REG)
                {
                    if (CheckPermissions(path_name.c_str()) ==  true)
                        remove(path_name.c_str());
                    else
                    {
                        closedir(ptr_dir);
                        return(false);
                    }
                }
            }
        }
    }   
    closedir(ptr_dir);

    rmdir(path);
    return (true);
}

bool Request::RemoveFile(const char* path) 
{
    if (remove(path) != 0) 
    {
        cerr << "ERROR IN DELETING THE FILE: " << path << endl;
        return (false);
    }
    
    return (true);
}

int Request::Check_Path(const char* path)
{
    if (!path)
        return (404);

    std::string pp = path;
    if(pp.find(_serv_conf.getRoot()) == string::npos)
        pp = _serv_conf.getRoot() + pp.substr(1);
    std::string root = _serv_conf.getRoot();
    if (root.empty())
        return (404);

    if(pp[pp.size() - 1] != '/')
    {
        struct stat path_stat;
        if (stat(pp.c_str(), &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
        {
            // Ajouter le slash seulement si c'est un répertoire
            pp += '/';
        }
    }

    char path_abso[PATH];
    char *resultat = realpath(pp.c_str(), path_abso);

    if (resultat != NULL) 
    {
        std::string str_path = path_abso;

        size_t findPath = str_path.find(root);

        if (findPath != std::string::npos)
        {
            std::string temp = str_path;
            std::string erasy = temp.erase(0,root.size());

            if (erasy.empty() == false)
            {
                return (204);
            }
            else
                return (403);
        }
        else
            return(403);
    }
    return (404);
}

void Request::DeleteMethod(const char* path)
{
    if(!_serv_conf.getLocs()[locIndex].locHasDELETEallowed())
    {
        ResponseCode = 405;
        throw ResponseCode;
    }
    if (Check_Path(path) == 204)
    {
        std::string pp = path;
        if (isDirectoryCheck(pp.c_str()) == 0)
        {
            if (CheckPermissions(pp.c_str()) == true)
            {
                if (RemoveDirectory(pp.c_str()) == true)
                    ResponseCode = 204;

                else
                    ResponseCode = 403;

            }
        }

        else if(isDirectoryCheck(pp.c_str()) == -1)
            ResponseCode = 403;

        else if(isFile(pp.c_str()))
        {
            if (CheckPermissions(pp.c_str()) == true)
            {
                if(RemoveFile(pp.c_str()) == true)
                    ResponseCode = 204;
            }
            else
                ResponseCode = 403;
        }
        else
            ResponseCode = 404;
    }
    else if(Check_Path(path) == 403)
        ResponseCode = 403;
    else if(Check_Path(path) == 404)
    {
        ResponseCode = 404;
    }
    throw ResponseCode;
}

void Request::sendMovedPermanently(int clientfd, string moveTo)
{
    stringstream httpResponse;
    httpResponse << "HTTP/1.1 " << 301 << _errorStatus[301] << "\r\n"
    << "Location: "<< moveTo << "\r\n"
    << "\r\n";
    send(clientfd, httpResponse.str().c_str(), httpResponse.str().length(), 0);
    ResponseSent = true;
    ResponseCode = 0;
}

void Request::dirReqHandling(int clientSocket)
{
    
    if(hasDirectoryAccess(pathToLocation))
    {
        Location mainLoc = _serv_conf.getLocs()[locIndex];

        // cheking it's return
        if(mainLoc.isRedirected())
        {   
            cout << "----cc----------->" << pathToLocation << endl;
            sendMovedPermanently(clientSocket, _serv_conf.getLocs()[locIndex].getRedirection());
            throw ResponseCode;
        }

        // cheking index
        else if(mainLoc.isIndexed() && !cgiDone)
        {
            std::cout << "DKHAAL NORMAL" << std::endl;
            pathToLocation += indexFileOnly;
            // string fullPath;
            // if(!mainLoc.getRoot().empty())
            //     fullPath = mainLoc.getRoot() + mainLoc.getIndex();
            // else if(mainLoc.getRoot().empty())
            //     fullPath = _serv_conf.getRoot() + mainLoc.getIndex();
            
            pathToLocation = removeConsecutiveSlashes(pathToLocation);
            string ext = pathToLocation.substr(pathToLocation.find_last_of('.') + 1);
            if(_isFile(pathToLocation.c_str()) && isUserPermitted(pathToLocation))
            {
                sendHtmlResponseFile(clientSocket, 200, " OK", pathToLocation, getContentType(ext));
                // ResponseCode = 200;
                // throw ResponseCode;
            }
            else if(_isFile(pathToLocation.c_str()) && !isUserPermitted(pathToLocation))
            {
                ResponseCode = 403;
                throw ResponseCode;
            }
            else
            {
                ResponseCode = 404;
                throw ResponseCode;
            }
        }

        //cheking autoindex
        else if(mainLoc.isAutoindexed() && mainLoc.locHasGETallowed())
        {
            sendDirResponse(clientSocket, generateDirectoryListing(pathToLocation, pureLoc), 200);
            ResponseCode = 0;
            throw ResponseCode;
        }

        else if(!mainLoc.locHasGETallowed())
        {
            ResponseCode = 405;
            throw ResponseCode;
        }

        else
        {
            ResponseCode = 403;
            throw ResponseCode;
        }
    }
    else
    {
        ResponseCode = 403;
        throw ResponseCode;
    }
}

void Request::fileReqHandling(int clientSocket)
{
    if(isUserPermitted(pathToLocation.c_str()))
    {
        string extent;
        if(!getContentType(_url.substr(_url.find('.') + 1)).empty())
            extent =  getContentType(_url.substr(_url.find('.') + 1));
        else
            extent = "text/plain";
        sendHtmlResponseFile(clientSocket, 200, _errorStatus[200], pathToLocation, extent);
        ResponseCode = 0;
        if(ResponseSent)
            throw ResponseCode;
    }
    else if(!isUserPermitted(pathToLocation.c_str()))
    {
        ResponseCode = 403;
        throw ResponseCode;
    }
    else
    {
        ResponseCode = 404;
        throw ResponseCode;
    }
}

bool findErrorCode(map<int, map<string, string> >  _errPages, int code)
{
    map<int, map<string,string> >::iterator it = _errPages.begin();
    for(;it != _errPages.end(); it++)
    {
        if(it->first == code)
            return true;
    }
    return false;
}

bool hasReadAndWritePermissions(const char *path) {
    // Check for read permission
    if (access(path, R_OK) == -1) {
        return false;
    }
    return true;
}

void Request::handleContentRequest(int clientSocket) 
{
    try
    {
        if(!_url.compare("/favicon.ico"))
        {
            sendHtmlResponseFile(clientSocket, 200, " OK", "." + _url, "image/x-icon");
            if(ResponseSent)
            {
                ResponseCode = 0;
                throw ResponseCode;
            }
        }

        else if (ResponseCode)
        {
            throw ResponseCode;
        }

        else if(cgiDone)
        {
            ResponseCode = 200;
            throw ResponseCode;
        }

        else if(!_methode.compare("GET"))
        {
            // exit(0);
            if (_serv_conf.getLocs()[locIndex].isIndexed() && !_serv_conf.getLocs()[locIndex].isRedirected()
                && _isFile(pathToLocation.c_str()))
            {
                indexFileOnly = pathToLocation.substr(pathToLocation.find_last_of("/") + 1);
                pathToLocation = pathToLocation.substr(0, pathToLocation.find_last_of("/") + 1);
            }
            if(isDirectory(pathToLocation.c_str()))
            {
                
                if(!hasReadAndWritePermissions(pathToLocation.c_str()))
                {
                    ResponseCode = 403;
                    throw ResponseCode;
                }
                dirReqHandling(clientSocket);
            }
            else if(_isFile(pathToLocation.c_str()))
            {
                // std::cout << pathToLocation << std::endl;
                // exit (0);
                fileReqHandling(clientSocket);
            }
            else if (!cgiDone)
            {
                ResponseCode = 404;
                throw ResponseCode;
            }
        }

        else if(!_methode.compare("DELETE"))
        {
            DeleteMethod(pathToLocation.c_str());
        }
    }
    catch(...)
    {
        cout << "->" << ResponseCode << " ---- " << boolalpha << ResponseSent << endl;
        // exit(0);
        if(ResponseCode == 301)
        {
            // cout << "---->" << pathToLocation << endl;
            // exit(0);
            sendMovedPermanently(clientSocket, _url);
            ResponseCode = 0;
        }
        if (ResponseCode)
        {
            // cout << "-->" << pathToLocation << endl;
            // exit(0);
            cout << "~~> ERROR CODE CATCHED = " << _errorStatus[ResponseCode] << "<~~" << endl;
            generateErrorResponse(clientSocket, ResponseCode, _errorStatus[ResponseCode]);
        }
        if (ResponseSent)
        {
            ResponseSent = true;
        }
    }
}