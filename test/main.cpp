#include <iostream>
#include <vector>
#include <cassert>
#include <memory>
#include "auth/crypto/AuthCrypto.hpp"
#include "auth/crypto/Hash.hpp"
#include "auth/crypto/StringEncoder.hpp"
#include "util/logging/Log.hpp"
#include "config.h"

static std::string originalText = R"(The quick brown fox jumps over the lazy dog, showcasing a classic pangram used for typing practice and font display.
The quick brown fox jumps over the lazy dog, showcasing a classic pangram used for typing practice and font display.
The quick brown fox jumps over the lazy dog, showcasing a classic pangram used for typing practice and font display.
The quick brown fox jumps over the lazy dog, showcasing a classic pangram used for typing practice and font display.
12345678890
12345678890
12345678)";

void testEncryptionDecryption() {
    std::unique_ptr<AuthCrypto> authCrypto = std::make_unique<AuthCrypto>();
    authCrypto->generateKeyPair("");

    std::vector<byte> data = StringEncoder::stringToBytes(originalText);
    byte* encryptedData = nullptr;
    byte* decryptedData = nullptr;

    std::cout << "Original length: " << originalText.size() << std::endl;
    size_t encryptedSize = authCrypto->encrypt(data.data(), encryptedData);
    size_t decryptedSize = authCrypto->decrypt(encryptedData, encryptedSize, decryptedData);

    std::string decryptedText = StringEncoder::bytesToString(decryptedData, decryptedSize);

    std::cout << "Original text: " << originalText << std::endl;
    std::cout << "Encrypted text (hex): " << StringEncoder::bytesToHex(encryptedData, encryptedSize) << std::endl;
    std::cout << "Encrypted text (base64): " << StringEncoder::base64Encode(encryptedData, encryptedSize) << std::endl;
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    std::cout << ((originalText == decryptedText)?"TRUE":"FALSE") << std::endl;
    assert(originalText == decryptedText && "Decrypted text matches the original text");
    
    std::cout << "Test passed: Decrypted text matches the original text." << std::endl;

    // Clean up
    delete[] encryptedData;
    delete[] decryptedData;
}

void testHashing() {
    std::vector<byte> data = StringEncoder::stringToBytes(originalText);
    byte* md5Hash = Hash::md5(data.data());
    byte* sha1Hash = Hash::sha1(data.data());
    byte* sha256Hash = Hash::sha256(data.data());

    std::string md5Hex = StringEncoder::bytesToHex(md5Hash, EVP_MAX_MD_SIZE);
    std::string sha1Hex = StringEncoder::bytesToHex(sha1Hash, SHA_DIGEST_LENGTH);
    std::string sha256Hex = StringEncoder::bytesToHex(sha256Hash, SHA256_DIGEST_LENGTH);

    unsigned long long md5Int = StringEncoder::hexToInteger(md5Hex);
    unsigned long long sha1Int = StringEncoder::hexToInteger(sha1Hex);
    unsigned long long sha256Int = StringEncoder::hexToInteger(sha256Hex);

    std::cout << "MD5 hash (Hex): " << md5Hex << std::endl;
    std::cout << "SHA1 hash (Hex): " << sha1Hex << std::endl;
    std::cout << "SHA256 hash (Hex): " << sha256Hex << std::endl;

    std::cout << "MD5 hash (Integer): " << md5Int << std::endl;
    std::cout << "SHA1 hash (Integer): " << sha1Int << std::endl;
    std::cout << "SHA256 hash (Integer): " << sha256Int << std::endl;

    assert("0443281202a5e0d36e93555b9f7ecacc000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" 
        == md5Hex && "Md5 Hash value matches");
    assert("1fa12ea69db5bf081751a175d64dd6e358baa8f3" 
        == sha1Hex && "SHA1 Hash value matches");
    assert("2f8869fca97f9b637c201208aeb581e9452875e713112d438084233b9089c304" 
        == sha256Hex && "SHA256 Hash value matches");

    std::string hashValueStr = "18446744073709551615";
    unsigned long long hashValue = std::stoul(hashValueStr, nullptr, 10);
    assert(hashValue == md5Int);
    assert(hashValue == sha1Int);
    assert(hashValue == sha256Int);
}

int main(int argc, char* argv[]) {
    testEncryptionDecryption();
    testHashing();
    return EXIT_SUCCESS;
}