#ifndef __DAUTH_SERVER_HPP__
#define __DAUTH_SERVER_HPP__

#include <memory>
#include "http/Server.hpp"

class ApiAuthDServer {
private:
    std::unique_ptr<HttpServer> server;

public:
    explicit ApiAuthDServer();

    void init();

    void stop();
};

#endif // __DAUTH_SERVER_HPP__