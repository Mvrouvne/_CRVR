#include"../includes/Config_parser.hpp"
#include"../includes/cgi.hpp"


int main(int ac, char **av)
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    try
    {
        Config conf;
 
        if(ac == 2)
            conf.catchConfig(av[1]);
        else if (ac == 1)
            conf.catchConfig("config/server.conf");
        else 
        {
            cerr << "Bad Args given!" << endl;
            return 0;
        }
        conf.handle_requests();
    }
    catch(exception &e)
    {
        cout << RED << e.what() << NONE << endl;
    }
    return 1;
}