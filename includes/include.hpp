#ifndef INCLUDE_HPP
#define INCLUDE_HPP

// Headers
#include <cstring>
#include <string>
#include <ctime>
#include <list>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <sys/stat.h> 
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <dirent.h>
#include <climits>
#include <limits>
#include <cstdio>
#include <sys/wait.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <iomanip>
// Typedefs
typedef int _sockFD;

//defines
#define FAIL -1;
#define MAX_EVENTS 10
#define SIZE 3096

using namespace std;

// extern size_t cgiFileN;


int _stoi(string str);
void errorHolder(const string &err);
string spaceRemover(string _target);
bool _isspace(char c);
int onlyCharInLine(string &line, char c);
int commentFound(string &line);
vector<string> split(const string& input, char delimiter);
string extractFileExtension(const string& urlPath);
bool isDirectory(const char *path);
bool _isFile(const char* path);
string intToString(int value);
// void generateErrorResponse(int clientFd, int error_code, const std::string& status);
string	readFileForCGi(string path);
#endif
