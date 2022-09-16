#include "byte_vector.h"
#include "numeric_string.h"

inline const unsigned long long BASE = 4294967296;

unsigned int ceil_log(unsigned long long base, unsigned long long number){
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
    this->length = 1;

    this->data = new Block[1];
    this->data[0] = 0;
}
ByteVector::ByteVector(unsigned long long number){
    this->length = ceil_log(BASE, number);

    this->data = new Block[length];

    for (unsigned int i = length; i > 0; i--){
        this->data[i - 1] = number % BASE;
        number /= BASE;
    }
}
ByteVector::ByteVector(const std::string& str){
    NumericString numerical_str = NumericString(str);

    this->length = ceil_log_numerical_str(BASE, numerical_str);

    this->data = new Block[length];

    for (unsigned int i = this->length; i > 0; i--){
        data[i - 1] = numerical_str % BASE;
        numerical_str /= BASE;
    }
}
ByteVector::~ByteVector(){
    delete[] this->data;
}

ByteVector::operator std::string() const{
    NumericString result = NumericString(0);

    NumericString m = NumericString(BASE);
    NumericString current_m = NumericString(1);

    for (unsigned int i = this->length; i > 0; i--){
        result += current_m * NumericString(this->data[i - 1]);

        current_m = current_m * m;
    }

    return std::string(result);
}

std::ostream& operator<<(std::ostream& out, const ByteVector &b){
    out << std::string(b);

    return out;
}
