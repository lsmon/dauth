#include "auth/crypto/AuthIdentity.hpp"
#include "util/logging/Log.hpp"
#include "util/UUID.hpp"
#include "util/LogUtil.hpp"
#include "util/fio/DirectoryHelper.hpp"
#include "config.h"

AuthIdentity::AuthIdentity(const std::string& kfn) 
{
    idAuthCrypto = std::make_shared<AuthCrypto>(kfn.c_str());
    
    if (idAuthCrypto->getPublicKeyFilename().empty())
    {
        idAuthCrypto->generateKeyPair("");
    } else if (std::filesystem::exists(idAuthCrypto->getPublicKeyFilename()))
    {
        idAuthCrypto->loadPublicKey();
    }
    else
    {
        throw std::runtime_error("SERVER IDENTITY COMPROMISED");
    }
    if (idAuthCrypto->isPublicKeyRsa())
        LOG_INFO << "Server public key exists and is RSA";
    else
        throw std::runtime_error("SERVER IDENTITY COMPROMISED");
}

AuthIdentity* AuthIdentity::getInstance()
{
    // std::unique_ptr<DirectoryHelper> dirHelp = std::make_unique<DirectoryHelper>();
    // std::vector<std::string> idFiles = dirHelp->listFiles(IDENTITY_ARCHIVE);
    // std::string identification;
    // if (idFiles.empty())
    // {
    //     identification = UUID::random();
    // }
    // else 
    // {
    //     for (auto &id : idFiles)
    //     {
    //         if (identification.empty())
    //         {
    //             identification = LogUtil::disassembleFileName(id)[1];
    //         }
    //         else
    //         {
    //             identification = ((identification == LogUtil::disassembleFileName(id)[1])?identification:UUID::random());
    //         }
    //     }
    // }
    return new AuthIdentity(DEFAULT_KEY_FILE_NAME);
}

std::shared_ptr<AuthCrypto> AuthIdentity::getServerIdAuthCrypto() {
    return idAuthCrypto;
}