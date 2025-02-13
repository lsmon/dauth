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
    std::cout << "Encrypted text: " << StringEncoder::bytesToString(encryptedData, encryptedSize) << std::endl;
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    assert(originalText == decryptedText);
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

    std::cout << "MD5 hash: " << StringEncoder::bytesToString(md5Hash, EVP_MAX_MD_SIZE) << std::endl;
    std::cout << "SHA1 hash: " << StringEncoder::bytesToString(sha1Hash, SHA_DIGEST_LENGTH) << std::endl;
    std::cout << "SHA256 hash: " << StringEncoder::bytesToString(sha256Hash, SHA256_DIGEST_LENGTH) << std::endl;
}

int main(int argc, char* argv[]) {
    testEncryptionDecryption();
    testHashing();
    return EXIT_SUCCESS;
}