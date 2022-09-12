#include "byte_vector.h"
#include "strings_operations.h"

#define BASE 256

unsigned int ceil_log(unsigned int base, unsigned long long number){
    if (!number){
        return 1;
    }

    unsigned int result = 0;

    while (number){
        result++;
        number /= base;
    }

    return result;
}


ByteVector::ByteVector(){
    length = 1;

    data = new Byte[1];
    data[0] = 0;
}
ByteVector::ByteVector(unsigned long long number){
    length = ceil_log(BASE, number);

    data = new Byte[length];

    for (unsigned int i = length; i > 0; i--){
        data[i - 1] = number % BASE;
        number /= BASE;
    }
}
ByteVector::ByteVector(std::string str){
    length = ceil_log_str(BASE, str);

    data = new Byte[length];

    for (unsigned int i = length; i > 0; i--){
        std::string tmp1;
        unsigned int tmp2;

        divide_string_by_number(str, BASE, tmp1, tmp2);

        data[i - 1] = tmp2;

        str = tmp1;
    }
}
ByteVector::~ByteVector(){
    delete[] data;
}

ByteVector::operator std::string() const{
    std::string result = "0";

    const std::string k = "256";
    std::string current_m = "1";
    for (unsigned int i = length; i > 0; i--){
        result = add_strings(result, multiply_strings(std::to_string(data[i - 1]), current_m));
        current_m = multiply_strings(current_m, k);
    }

    return result;
}
