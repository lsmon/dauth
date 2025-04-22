#ifndef __DCLIENT_HPP__
#define __DCLIENT_HPP__

#include <memory>
#include "api/Client.hpp"
#include "auth/crypto/AuthCrypto.hpp"

class DClient {
private:
    std::shared_ptr<ApiClient> client;
    std::string clientname;
    std::string password;
    std::shared_ptr<AuthCrypto>  clientRsa;
    std::shared_ptr<AuthCrypto>  serverRsa;

public:
    explicit DClient(const std::string& clientname, const std::string& password);

    ~DClient() = default;

    void requestDauthPublicKey(const std::string& addr);

    void requestRsaKeysGeneration(const std::string& addr, std::string &clientName, std::string& password);

    void requestClientPublicKey(const std::string& addr, const std::string& token);

    void requestClientPrivateKey(const std::string& addr, const std::string& token);
};

#endif // __DCLIENT_HPP__