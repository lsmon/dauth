#ifndef __STRING_ENCODER_HPP__
#define __STRING_ENCODER_HPP__

#include <string>
#include "config.h"

class StringEncoder
{
private:
    /* data */
public:
    StringEncoder(/* args */);
    ~StringEncoder();

    static byte* stringToBytes(const std::string& str);
    
    static std::string bytesToString(const byte* bytes, size_t length);
};

#endif // __STRING_ENCODER_HPP__