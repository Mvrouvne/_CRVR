#include "../includes/cgi.hpp"
#include "../includes/webserver.hpp"

CGI::CGI()
{
    isPy = false;
    isPHP = false;
    isSh = false;
    cgiRoot = "";
    _url = "";
    cgiStartTime = 0;
    cgiEndTime = 0;
    status = -1;
}

CGI::~CGI()
{

}

bool    CGI::checkPathExtension(Request& reqObj)
{
    if (_url.find_last_of(".") == std::string::npos)
        return false;
    extension = _url.substr(_url.find_last_of("."));
    if (extension == ".php")
    {
        isPHP = true;
        reqObj.cgiIsPhp = true;
        if (!reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_PHP().size())
            return false;
        else if (reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_PHP()[1] == ".php")
            return true;
    }
    else if (extension == ".py")
    {
        isPy = true;
        if (!reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_PY().size())
            return false;
        else if (reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_PY()[1] == ".py")
            return true;
    }
    else if (extension == ".sh")
    {
        isSh = true;
        if (!reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_SH().size())
            return false;
        else if (reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_SH()[1] == ".sh")
            return true;
    }
    return false;
}

int	CGI::cgi_handler(Request& reqObj)
{
    if (!reqObj.cgiFlag)
    {
        reqObj.cgiFlag = true;
        _url = reqObj.getUrl();

        if(!reqObj.getServer().getLocs()[reqObj.getlocIndex()].getRoot().empty())
            cgiRoot = reqObj.getServer().getLocs()[reqObj.getlocIndex()].getRoot();
        else if(reqObj.getServer().getLocs()[reqObj.getlocIndex()].getRoot().empty())
            cgiRoot = reqObj.getServer().getRoot();
        size_t x = _url.find("?");
        if(x != std::string::npos)
        {
            queryString = _url.substr(x + 1);
            _url.erase(x);
            realPath = cgiRoot + _url;
        }
        else
        {
            realPath = cgiRoot + _url;
        }
        if (!checkPathExtension(reqObj))
        {
            reqObj.cgiFlag = false;
            return 0;
        }
        reqObj.setcgiTrue(true);
        reqObj.setResponseCode(0);
        std::string request_method = "REQUEST_METHOD=" + reqObj.getMethode();
        env[0] = const_cast<char*>(request_method.c_str());
        std::string query_string = "QUERY_STRING=" + queryString;
        env[1] = const_cast<char*>(query_string.c_str());
        env[2] = const_cast<char*>("REDIRECT_STATUS=200");
        std::string script_name = "SCRIPT_FILENAME=" + realPath;
        env[3] = const_cast<char*>(script_name.c_str());
        std::string content_type = "CONTENT_TYPE=" + reqObj.getReqHeader()["Content-Type"];
        env[4] = const_cast<char*>(content_type.c_str());
        std::string content_length = "CONTENT_LENGTH=" + reqObj.getReqHeader()["Content-Length"];
        env[5] = const_cast<char*>(content_length.c_str());
        std::string http_cookie = "HTTP_COOKIE=" + reqObj.getReqHeader()["Cookie"];
        env[6] = const_cast<char*>(http_cookie.c_str());
        env[7] = NULL;

        if (isPHP)
            args[0] = const_cast<char*>(reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_PHP()[0].c_str());
        else if (isPy)
            args[0] = const_cast<char*>(reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_PY()[0].c_str());
        else if (isSh)
            args[0] = const_cast<char*>(reqObj.getServConfig().getLocs()[reqObj.getlocIndex()].getCGI_SH()[0].c_str());
        args[1] = const_cast<char*>(realPath.c_str());
        args[2] = NULL;

        cgiStartTime = clock();
        pid = fork();
        reqObj.cgiPid = pid;
        if (pid == -1)
        {
            reqObj.setCgiDone(true);
            return 500;
        }
        if (pid == 0)
        {
            if (reqObj.getMethode() == "POST")
            {
                if (realpath(reqObj.getfileName().c_str(), uploadPath) == NULL)
                    kill(getpid(), SIGKILL);
            }
            std::string dirPath = realPath.substr(0, realPath.find_last_of('/') + 1);
            if (chdir(dirPath.c_str()) < 0)
                kill(getpid(), SIGKILL);
            std::string cgiOUT = dirPath + "cgi-output-" + intToString(reqObj.cgiFileN);
            file = std::freopen(cgiOUT.c_str(), "w+", stdout);
            if (!file)
                kill(getpid(), SIGKILL);
            if (reqObj.getMethode() == "POST")
            {
                file_in = std::freopen(uploadPath, "r", stdin);
                if (!file_in)
                    kill(getpid(), SIGKILL);
            }
            errFile = std::freopen("/dev/null", "rw", stderr);
            if (!errFile)
                kill(getpid(), SIGKILL);
            if (execve(args[0], args, env) < 0)
                kill(getpid(), SIGKILL);
            kill(getpid(), SIGKILL);
        }
    }
    pid_t waitStat = waitpid(pid, &status, WNOHANG);
    if (waitStat < 0)
    {
        reqObj.setCgiDone(true);
        toUnlink = realPath.substr(0, realPath.find_last_of('/') + 1) + "/cgi-output-" + intToString(reqObj.cgiFileN);
        unlink(toUnlink.c_str());
        return 500;
    }
    if (WIFSIGNALED(status))
    {
        reqObj.setCgiDone(true);
        toUnlink = realPath.substr(0, realPath.find_last_of('/') + 1) + "/cgi-output-" + intToString(reqObj.cgiFileN);
        unlink(toUnlink.c_str());
        return 500;
    }
    cgiEndTime = clock();

    if (((double)cgiEndTime - cgiStartTime) / CLOCKS_PER_SEC > 7)
    {
        reqObj.setCgiDone(true);
        kill (pid, SIGKILL);
        waitpid(pid, NULL, 0);
        toUnlink = realPath.substr(0, realPath.find_last_of('/') + 1) + "/cgi-output-" + intToString(reqObj.cgiFileN);
        unlink(toUnlink.c_str());
        return 504;
    }
    if (waitStat == 0)
    {
        reqObj.setRequestCatch(true);
        return 0;
    }
    if (waitStat == pid)
    {
        reqObj.setCgiDone(true);
        reqObj.setRequestCatch(true);
        return 0;
    }
    return 0;
}
