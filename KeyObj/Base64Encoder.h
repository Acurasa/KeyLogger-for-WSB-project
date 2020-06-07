#ifndef BASE_64_ENCODER_H
#define BASE_64_ENCODER_H
#include<string>
#include <vector>

namespace Base64Encoder
{
    std::string base64_encode(const std::string &s);
const    std::string &salty1 = "3412453///42";
const    std::string &salty2 = "port29ko";
const    std::string &salty3 = "rrerv#fff";

    std::string EncodeB64(std::string s)
    {
        s = salty1 + s + salty2 + salty3;
        s = base64_encode(s);
        s.insert(7,salty3);
        s+=salty1;
        s = salty2 + salty3 + salty1;
        s = base64_encode(s);
        s.insert(1,"L");
        s.insert(7,"M");
        return s;
    }
const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
std::string base64_encode(const std::string &s)
{
    std::string ret;
    int val = 0;
    int bits = -6;
    const unsigned int b63 = 0x3F;

    for(const auto &c : s)
    {
        val = (val<<8) + c;
        bits += 8;
        while(bits>= 0)
        {
            ret.push_back(BASE64_CODES[(val>>bits)&b63]);
            bits -= 6;
        }

    }
    if(bits > -6)
        ret.push_back(BASE64_CODES[((val<<8) >> (bits + 8))& b63]);

    while(ret.size() %4)
        ret.push_back('=');
    return ret;

    }
}





























#endif // BASE_64_ENCODER_H
