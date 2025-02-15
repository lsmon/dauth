#include "auth/DServer.hpp"
#include "auth/EndpointHandlers.hpp"
#include "util/logging/Log.hpp"
#include <future>

ApiAuthDServer::ApiAuthDServer() : server(std::make_unique<HttpServer>("localhost", "8080", 1024, 8))
{
    LOG_INFO << "Server listening on port 8080";
}

void ApiAuthDServer::init()
{
    server->setHttpHandler(HttpMethod::GET, "/keys", Endpoint::generateRsaKeys);
    server->setHttpHandler(HttpMethod::POST, "/chk", Endpoint::handleAuthentication);
    server->setHttpHandler(HttpMethod::GET, "/dl/{tok}/{ktype}", Endpoint::retrieveRsaKeys);

    auto serverFuture = std::async(std::launch::async, [this]() mutable { server->run();} );

    serverFuture.wait();
}

void ApiAuthDServer::stop()
{
    server->stop();
}