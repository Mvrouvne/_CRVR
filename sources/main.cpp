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
        {
            conf.catchConfig(av[1]);
            conf.handle_requests();
            return 0;
        }
        else if (ac == 1)
        {
            conf.catchConfig("config/server.conf");
            conf.handle_requests();
            return 0;
        }
        cerr << "Bad Args given!" << endl;
    }
    catch(exception &e)
    {
        cout << RED << e.what() << NONE << endl;
    }
    return 1;
}