#include <iostream>

typedef unsigned int Block;

class ByteVector{
private:
    Block* data;
    unsigned int length;
public:
    ByteVector();
    explicit ByteVector(unsigned long long);
    explicit ByteVector(const std::string&);
    ~ByteVector();

    explicit operator std::string() const;
};

std::ostream& operator<<(std::ostream&, const ByteVector&);
