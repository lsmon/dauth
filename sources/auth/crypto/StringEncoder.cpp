#include "auth/crypto/StringEncoder.hpp"

// inline byte *StringEncoder::stringToBytes(const std::string &str)
// {
//     return reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));
// }

std::vector<byte> StringEncoder::stringToBytes(const std::string& str) {
    return std::vector<unsigned char>(str.begin(), str.end());
}

std::string StringEncoder::bytesToString(const byte *bytes, size_t length)
{
    return std::string(reinterpret_cast<const char*>(bytes), length);
}