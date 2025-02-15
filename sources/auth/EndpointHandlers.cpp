#include "auth/crypto/AuthCrypto.hpp"
#include "auth/EndpointHandlers.hpp"
#include "util/logging/Log.hpp"
#include "util/UUID.hpp"
#include "http/Status.hpp"
#include <fstream>

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
    {
        uname = uname.substr(0, uname.size()-1);
        authCrypto = std::make_unique<AuthCrypto>(uname.c_str());
    }
    LOG_DEBUG << "filename: " << uname;
    LOG_DEBUG << "password: " << keyPassword;

    authCrypto->generateKeyPair(keyPassword.c_str());
    
    response.setStatus(200);
    response.setBody(uname);
}

void Endpoint::handleAuthentication(const HttpRequest& request, HttpResponse& response, Path* path)
{
    LOG << "Authoentication";
}

void Endpoint::retrieveRsaKeys(const HttpRequest& request, HttpResponse& response, Path* path) 
{
    auto token = path->getPathParamMap().find("tok");
    auto ktype = path->getPathParamMap().find("ktype");
    if (token != path->getPathParamMap().end() && token != path->getPathParamMap().end())
    {
        std::string tok = token->second;
        std::string keyType = ktype->second;
        
        if (keyType == "pem" || keyType == "pub")
        {
            std::unique_ptr<AuthCrypto> keyPair = std::make_unique<AuthCrypto>(tok.c_str());
            std::string filename;
            if (keyType == "pem")
                filename = keyPair->getPrivateKeyFilename();
            else
                filename = keyPair->getPublicKeyFilename();

            std::ifstream file(filename, std::ios::binary);
            if (file)
            {
                std::string filecontent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                response.addHeader("content-type", "application/octet-stream");
                response.addHeader("content-length", std::to_string(filecontent.size()));
                response.setBody(filecontent);
                response.setStatus(200);
            }
            else
            {
                response.setStatus(NOT_FOUND);
                response.setBody(Status(NOT_FOUND).ss.str());
            }
        }
        else
        {
            response.setStatus(CONFLICT);
            response.setBody(Status(CONFLICT).ss.str());
        }
    }
    else 
    {
        response.setStatus(GONE);
        response.setBody(Status(GONE).ss.str());
    }
}