#ifndef __AUTH_IDENTITY_HPP__
#define __AUTH_IDENTITY_HPP__

#include <string>
#include "auth/crypto/AuthCrypto.hpp"

class AuthIdentity
{
private:
    std::shared_ptr<AuthCrypto> idAuthCrypto;

    explicit AuthIdentity(const std::string& keyFN);

public:
    static AuthIdentity* getInstance();

    std::shared_ptr<AuthCrypto> getServerIdAuthCrypto() ;
};

#endif // __AUTH_ID_HPP__