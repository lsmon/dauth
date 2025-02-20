#include "auth/DClient.hpp"
#include "util/logging/Log.hpp"
#include "config.h"
#include <fstream>
#include <iostream>

DClient::DClient(const std::string& clientname, const std::string& password) : clientname(clientname), password(password)
{
    this->client = std::make_shared<ApiClient>();

}

void DClient::requestDauthPublicKey(const std::string &addr)
{
    try {
        std::string url = "http://";
        url.append(addr);
        url.append(":8080/dauth/pub");
        auto response = client->get(url, "");
        LOG_DEBUG << "Response STATUS: " << response.getStatus();
        LOG_DEBUG << "Response BODY: " << response.getBody();
        std::ofstream file;
        std::string filename = "./key/pub/dauth.pub";
        // filename = PUB_KEY_ARCHIVE;
        // filename.append("/dauth.pub");
        file.open(filename);
        file << response.getBody();
        file.close();
    } catch (const std::exception& e) {
        LOG_ERROR << "Exception caught in requestDauthPublicKey(): " << e.what();
    }
}

void DClient::requestRsaKeysGeneration(const std::string &addr, std::string &clientName, std::string& password)
{
    std::string url = "http://";
    url.append(addr);
    url.append(":8080/keys");
    // encrypt client name
    // sign the string pub
    // encrypt the password

    std::unordered_map<std::string, std::string> headers = {
        {"Content-Type", "application/json"},
        {"Authorization", password},
        {"X-User", clientName}
    };
    
    

    auto response = client->get(url, "");
    LOG_DEBUG << "Response STATUS: " << response.getStatus();
    LOG_DEBUG << "Response BODY: " << response.getBody();
}

void DClient::requestClientPublicKey(const std::string &addr, const std::string &token)
{
}

void DClient::requestClientPrivateKey(const std::string &addr, const std::string &token)
{
}
