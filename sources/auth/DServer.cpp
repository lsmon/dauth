#include "auth/DServer.hpp"
#include "auth/crypto/AuthIdentity.hpp"
#include "auth/EndpointHandlers.hpp"
#include "auth/crypto/AuthCrypto.hpp"
#include "util/logging/Log.hpp"
#include <future>

ApiAuthDServer::ApiAuthDServer() : server(std::make_unique<HttpServer>("localhost", "8080", 1024, 8))
{
    AuthIdentity* authId = AuthIdentity::getInstance();
    authId->getServerIdAuthCrypto()->loadPublicKey();
    std::string publicfn = authId->getServerIdAuthCrypto()->getPublicKeyFilename();

    if ( !publicfn.empty() ) {
        LOG_INFO << "Public key file found: " << publicfn;
        authId->getServerIdAuthCrypto()->loadPublicKey();
        LOG_INFO << "Server listening on port 8080";
    }
    else {
        LOG_INFO << "No public key file found";
    }
    
}

void ApiAuthDServer::init()
{
    server->setHttpHandler(HttpMethod::GET, "/keys", Endpoint::generateRsaKeys);
    server->setHttpHandler(HttpMethod::POST, "/chk", Endpoint::handleAuthentication);
    server->setHttpHandler(HttpMethod::GET, "/dl/{tok}/{ktype}", Endpoint::retrieveRsaKeys);
    server->setHttpHandler(HttpMethod::GET, "/dauth/pub", Endpoint::retrieveDauthPub);

    auto serverFuture = std::async(std::launch::async, [this]() mutable { server->run();} );

    serverFuture.wait();
}

void ApiAuthDServer::stop()
{
    server->stop();
}