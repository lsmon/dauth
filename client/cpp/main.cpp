#include <iostream>
#include "config.h"
#include "auth/DClient.hpp"

int main(int argc, char** argv)
{
    std::string username;
    std::string password = "";

    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <client_id> <password | opt>" << std::endl;
        return -1;
    } 
    else if(argc == 3)
    {   
        password = argv[2];
    }
    username = argv[1];

    std::shared_ptr<DClient> client = std::make_shared<DClient>(username, password);
    client->requestDauthPublicKey("localhost");
    return 0;
}