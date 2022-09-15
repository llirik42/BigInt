#include <iostream>
#include "numeric_string.h"

//#include "byte_vector.h"

int main() {
    NumericString s = NumericString("32132132132132132132132193820130291");

    std::cout << ceil_log_numerical_str(256, s);

    //NumericString s3 = s1 + s2;

    //ByteVector a = ByteVector("0");
    //ByteVector b = ByteVector("1");
    //ByteVector c = ByteVector("2");
    //ByteVector d = ByteVector("2570");
    //ByteVector e = ByteVector("111111111111111111111");
    //ByteVector f = ByteVector("256");
    //ByteVector g = ByteVector("65536");
    //ByteVector h = ByteVector("1111111111111111111111111111111111111111");
    //ByteVector i = ByteVector("111111111111111111111111111111111111111111111111111111111111");
    //ByteVector j = ByteVector("1111111111111111111111111111111111111111111111111111111111111111111111111111111");


    //std::cout << std::string(a) << "\n";
    //std::cout << std::string(b) << "\n";
    //std::cout << std::string(c) << "\n";
    //std::cout << std::string(d) << "\n";
    //std::cout << std::string(e) << "\n";
    //std::cout << std::string(f) << "\n";
    //std::cout << std::string(g) << "\n";
    //std::cout << std::string(h) << "\n";
    //std::cout << std::string(i) << "\n";
    //std::cout << std::string(j) << "\n";

    return 0;
}
