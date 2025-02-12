#include "auth/crypto/StringEncoder.hpp"
#include "StringEncoder.hpp"

StringEncoder::StringEncoder(/* args */)
{
}

StringEncoder::~StringEncoder()
{
}

inline byte *StringEncoder::stringToBytes(const std::string &str)
{
    return reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));
}

std::string StringEncoder::bytesToString(const byte *bytes, size_t length)
{
    return std::string(reinterpret_cast<const char*>(bytes), length);
}