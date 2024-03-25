#include"../includes/Location.hpp"

Location::Location()
{
	_pattern = "";
	_index = "";
	_autoindex = "off";
	_redirection = "";
	_root = "";
	_cgi = "off";
	// vector<string> vec(2);
	// vec[0] = "";
	// vec[1] = "";
	// _cgiPHP = vec;
	// _cgiPY = vec;
}

Location::Location(const Location& obj)
{
	*this = obj;
}

Location &Location::operator=(const Location& obj)
{
	_pattern = obj._pattern;
	_root = obj._root;
	_autoindex = obj._autoindex;
	_index = obj._index;
	_redirection = obj._redirection;
	_upload = obj._upload;
	_allowMethods = obj._allowMethods;
	_cgi = obj._cgi;
	_cgiPY = obj._cgiPY;
	_cgiPHP = obj._cgiPHP;
	_cgiSH = obj._cgiSH;
	return *this;
}

Location::~Location()
{
}

/* Location Setters */
void Location::setPattern(const string &pattern)
{
	_pattern = pattern;
}
void Location::setAutoindex(const string &autoIndex)
{
	_autoindex = autoIndex;
}
void Location::setIndex(const string &index)
{
	_index = index;
}
void Location::setRoot(const string &root)
{
	_root = root;
}
void Location::setRedirection(const string &redir)
{
	_redirection = redir;
}
void Location::setUpload(vector<string> upload)
{
	_upload = upload;
}
void Location::setCgi(string &cgi)
{
	_cgi = cgi;
}
void Location::setCGI_PY(vector<string> cgiPY)
{
	_cgiPY = cgiPY;
}
void Location::setCGI_PHP(vector<string> cgiPHP)
{
	_cgiPHP = cgiPHP;
}
void Location::setCGI_SH(vector<string> cgi_SH)
{
	_cgiSH = cgi_SH;
}
void Location::setAllowedMethods(vector<string> allow_methds)
{
	_allowMethods = allow_methds;
}

/* Location Getters */
string &Location::getPattern(void)
{
	return _pattern;
}
string &Location::getAutoindex(void)
{
	return _autoindex;
}
string &Location::getRoot(void)
{
	return _root;
}
string Location::getIndex(void)
{
	return _index;
}
string &Location::getRedirection(void)
{
	return _redirection;
}
vector<string> &Location::getUpload(void)
{
	return _upload;
}
string &Location::getCgi(void)
{
	return _cgi;
}
vector<string> &Location::getCGI_PY(void)
{
	return _cgiPY;
}
vector<string> &Location::getCGI_PHP(void)
{
	return _cgiPHP;
}
vector<string> &Location::getCGI_SH(void)
{
	return _cgiSH;
}
vector<string> &Location::getAllowedMethods(void)
{
	return _allowMethods;
}

bool Location::isIndexed()
{
    return (getIndex().empty() == 0);
}

bool Location::isRedirected()
{
    return (!getRedirection().empty());
}

bool Location::isAutoindexed()
{
    return (!getAutoindex().compare("on"));
}

bool Location::locHasGETallowed()
{
	vector<string>::iterator it = getAllowedMethods().begin();
    for(; it != getAllowedMethods().end(); it++)
	{
		if(!it->compare("GET"))
			return true;
	}
	return false;
}

bool Location::locHasPOSTallowed()
{
	vector<string>::iterator it = getAllowedMethods().begin();
    for(; it != getAllowedMethods().end(); it++)
	{
		if(!it->compare("POST"))
			return true;
	}
	return false;
}

bool Location::locHasDELETEallowed()
{
	vector<string>::iterator it = getAllowedMethods().begin();
    for(; it != getAllowedMethods().end(); it++)
	{
		if(!it->compare("DELETE"))
			return true;
	}
	return false;
}