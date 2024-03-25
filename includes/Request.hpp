#ifndef REQUEST_HPP
#define REQUEST_HPP

#define PATH 2048

#include "include.hpp"
#include "Server.hpp"
#include "Config_parser.hpp"
// #include "Request.hpp"
#include "cgi.hpp"

class CGI;

class Request : public Server
{
    private:

        map<string, string>  _req_header;
        map<string, string>  _contentType;
        map<int, string> _errorStatus;
        map<int, string> _errorPath;
        string _methode;
        string _httpVersion;
        string initialBody;
        Server _serv_conf;
        string _postBody;
        size_t endOfHeaders;
        map<int, Server> servers_map;
        size_t      _buffer_size;
        char        _buffer[SIZE];
        string myBuff;

        // string        _bufferHelper;
        // bool headersLimitReached;


        bool    epollFlag;
        bool    readFlag;
        bool    doneRead;
        bool    RequestCatch;
        // bool    postFirstImposter;

        bool headersParsed;
        int contentLength;
        int bodyRead;
        bool bodyDone;
        bool cgiDone;
        bool cgiTrue;
        // bool ResponseSent;
        size_t chunkedBytesReaded;
        bool _isContentLength;
        bool _isContentLength1stTime;
        bool _isChunked;
        bool _chunkedDone;
        long _chunkSize;
        int rootLocIndex;
        bool _isChunked1stTime;
        int totalBytesRead;
        string fileName;


        // ifstream infile;
        // ofstream outfile;
        string postCreatedFileName;
        int locIndex;
        int     bytesRead;
        bool  _expectCRLF;
        string _partialChunkSize;
        string firstDirInPath;
        string pureLoc;
        bool stopReadinginHeaderSection;
        int ResponseCode;
        bool _isRedirected;
        std::string filePathstr;
        
        size_t      immediateResponse;
        std::string uploadPath;

        // chunk things
        std::string chunkString;
        size_t      chunkSize;
        size_t      counter;
        bool        BoundaryFlag;
        bool        BoundaryFlag2;

        /* boundary */
        bool _isBoundary1stTime;
        std::string BoundaryDelimiter;
        std::string BoundaryString;
        std::string BoundaryCtype;
        size_t      BoundaryDelimiterSize;
        std::string BoundaryLeftOver;


    public:
        string _url;
        size_t cgiFileN;
        ifstream infile;
        ofstream outfile;
        std::string old_url;
        std::string indexFileOnly;
        string pathToLocation;
        bool ResponseSent;
        CGI cgi_obj;
        pid_t	    cgiPid;
        std::string cgiOUT;
        // int Valx;
        bool cgiFlag;
        bool cgiIsPhp;
        bool    deleted;
        clock_t startTime;
        clock_t endTime;
        size_t  locationIndex;
        char        _toRead[SIZE];
        bool _firstReadedtry;
        Request();
        Request(const Request& obj);
        Request &operator=(const Request& obj);
        ~Request();
        
        /* Getters */
        string &getMethode(void);
        string getUrl(void);
        string &getHttpVers(void);
        Server &getServConfig(void);
        bool getEpollFlag();
        bool getdoneRead();
        bool getResponseSent();
        bool getReadFlag();
        bool getcgiTrue();
        Server  getServer();
        map<std::string, std::string> getReqHeader();
        int getlocIndex();
        std::string getfileName();
        bool    getRequestCatch();
        int     getResponseCode();

        /* Setters */
        void setMethode(string &meth);
        void setUrl(string &url);
        void setCgiDone(bool flag);
        void setHttp(string &http);
        void setServConfig(Server &ser_conf);
        void setEpollFlag(bool flag);
        void setRequestCatch(bool f);
        void setcgiTrue(bool ff);
        void setResponseCode(int Code);
        void setServersMap(map<int, Server> &servs_map);

        /* Methods */

        string getContentType(string reference);
        string getErrorPath(int pageCode);
        bool getCgiDone();
        string getErrorStatus(int pageCode);
        void Requesting(int _socFd);
        void parse_firstline(string &fst_line);
        void catchRequestForHeaders(string& myBuff, int len);
        void catchRequest(int sock_fd);
        // bool checkingLocation();
        int _locationPatternMatcher(string pattern);
        void handleContentRequest(int clientSocket);
        string readFile(int clientSocket, const string& filePath);
        void sendHtmlResponseFile(int clientSocket, int errCode ,string status, string filePath, string cnttype);
        string generateDirectoryListing(string directoryPath, string locName) ;

        void sendDirResponse(int clientSocket, const string content, int errCode);
        int isLocation(string &_url);
        void fileReqHandling(int clientSocket);
        void dirReqHandling(int clientSocket);
        void handleDeleteRequest(int clientSocket, const string& resourcePath) ;
        bool checkingRequestGivenPath(string requestPath, string &path);
        void generateErrorResponse(int clientFd, int error_code, const std::string& status);

        void catchingPost(string _buff);
        void processHeaders(const string& headerStr);
        void firstComingRequest(string& myBuff, int len);
        void contentLengthHandler(int sock_fd);
        void GetSize();
        void locationMatcher();
        void chunkedHandler(int sock_fd);
        int serverIndexFinder(string servName, string port);
        // int serverIndexFinderByListen(string port);
        // void boundaryHandler();
        // void boundaryFileOpener(size_t FileN);
        void encode_url();
        void sendMovedPermanently(int clientfd, string moveTo);

        // DELETE
        bool isFile(const char* path);
        int isDirectoryCheck(const char *path);
        bool CheckPermissions(const char *path);
        bool RemoveDirectory(const char *path);
        int Check_Path(const char* path);
        bool RemoveFile(const char* path);
        void DeleteMethod(const char* path);
        void uploadCheckers();
};

std::string mimetypes();

#endif
