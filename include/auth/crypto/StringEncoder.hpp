#ifndef __STRING_ENCODER_HPP__
#define __STRING_ENCODER_HPP__

#include "config.h"
#include <string>
#include <vector>

class StringEncoder {
public:
    static std::vector<byte> stringToBytes(const std::string& str);

    static std::string bytesToString(const byte* bytes, size_t length);
};

#endif // __STRING_ENCODER_HPP__