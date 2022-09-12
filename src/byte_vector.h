#pragma once

#include <iostream>

typedef unsigned char Byte;

class ByteVector{
private:
    Byte* data;
    unsigned int length;
public:
    ByteVector();
    explicit ByteVector(unsigned long long);
    explicit ByteVector(std::string);
    ~ByteVector();

    explicit operator std::string() const;
};
