#include "auth/crypto/AuthCrypto.hpp"
#include "auth/EndpointHandlers.hpp"
#include "util/logging/Log.hpp"
#include "util/UUID.hpp"

void Endpoint::generateRsaKeys(const HttpRequest& request, HttpResponse& response, Path* path)
{
    LOG << "RSA KEY Generation";
    std::unordered_map<std::string, std::string> headers = request.getHeaders();
    auto auth = headers.find("Authorization");
    auto xuser = headers.find("X-User");

    std::string keyPassword;
    std::string uname;

    if (auth != headers.end()) 
        keyPassword = auth->second;
    else 
        keyPassword = "";
    if (xuser != headers.end())
        uname = xuser->second;
    else
        uname = UUID::random();

    std::unique_ptr<AuthCrypto> authCrypto;
    if (uname.empty())
        authCrypto = std::make_unique<AuthCrypto>();
    else
        authCrypto = std::make_unique<AuthCrypto>(uname.c_str());
    authCrypto->generateKeyPair(keyPassword.c_str());
    
    response.setStatus(200);
    response.setBody("Hello World");
}

void Endpoint::handleAuthentication(const HttpRequest& request, HttpResponse& response, Path* path)
{
    LOG << "Authoentication";
}

void Endpoint::retrieveRsaKeys(const HttpRequest& request, HttpResponse& response, Path* path) 
{

}