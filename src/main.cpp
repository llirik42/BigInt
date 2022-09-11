#include <iostream>
#include <cmath>
#include <cstdlib>
#include "string_operations.h"

typedef unsigned char Byte;

#define SIZE_OF_BYTE 8

// 0 ... 7
#define GET_BIT_8(N, I) ((1 << (SIZE_OF_BYTE - (I) - 1) & (N)) >> (SIZE_OF_BYTE - (I) - 1))
#define SET_BIT_8(N, I, V) N = (V) ? ((1 << (SIZE_OF_BYTE - (I) - 1)) | (N)) : (~(1 << (SIZE_OF_BYTE - (I) - 1)) & (N));


unsigned int ceil_log(unsigned int base, unsigned int number){
    if (!number){
        return 1;
    }

    unsigned long long result = 0;

    while (number){
        result++;
        number /= base;
    }

    return result;
}
unsigned int ceil_div(unsigned a, unsigned b){
    if (b == 0){
        return 0;
    }

    unsigned int result = 0;
    while (a){
        result++;
        if (a < b){
            break;
        }

        a -= b;
    }

    return result;
}

bool is_numerical(std::string str){
    const unsigned int length = str.length();

    if (!length){
        return false;
    }

    if (length == 1 && !std::isdigit(str[0])){
        return false;
    }

    if ((length != 1 && str[0] == '0') || (length != 2 && str[0] == '-' && str[1] == '0')){
        return false;
    }

    for (unsigned int i = 1; i < length; i++){
        if (!std::isdigit(str[i])){
            return false;
        }
    }

    return true;
}

class BigInt {
private:
    bool is_positive;

    unsigned long long decimal_digits_count;
    unsigned long long binary_digits_count;

    unsigned long long binary_blocks_count;

    Byte* abs_decimal_representation;
    Byte* abs_binary_compact_representation;
public:
    BigInt(){
        is_positive = true;

        decimal_digits_count = 1;
        binary_digits_count = 1;

        binary_blocks_count = 1;

        abs_decimal_representation = new Byte[1];
        abs_binary_compact_representation = new Byte[1];

        abs_decimal_representation[0] = 0;
        abs_binary_compact_representation[0] = 0;
    }
    explicit BigInt(int number){
        is_positive = (number >= 0);

        const unsigned int abs_number = abs(number);

        decimal_digits_count = ceil_log(10, abs_number);
        binary_digits_count = ceil_log(2, abs_number);

        binary_blocks_count = ceil_div(binary_digits_count, 8); // log(256, x) = log(2, x) * 8

        abs_decimal_representation = new Byte[decimal_digits_count];
        abs_binary_compact_representation = new Byte[binary_blocks_count];

        unsigned int tmp1 = abs_number;
        for (unsigned int i = decimal_digits_count; i > 0; i--){
            abs_decimal_representation[i - 1] = tmp1 % 10;
            tmp1 /= 10;
        }

        unsigned int tmp2 = abs_number;
        for (unsigned int i = binary_blocks_count; i > 0; i--){
            abs_binary_compact_representation[i - 1] = tmp2 % 256;
            tmp2 /= 256;
        }
    }
    BigInt(std::string str){
        if (!is_numerical(str)){
            throw std::invalid_argument("String isn't numerical");
        }

        is_positive = str[0] != '-';

        decimal_digits_count = str.length();




        //decimal_digits_count

        //abs_decimal_representation = str;
        //if (str[0] == '-'){
          //  abs_decimal_representation.erase(0, 1);
        //}



    }
    BigInt(const BigInt&);
    ~BigInt(){
        delete abs_decimal_representation;
        delete abs_binary_compact_representation;
    }

    BigInt(BigInt&&);
    BigInt& operator=(BigInt&&);


    BigInt& operator=(const BigInt&);

    BigInt operator~();

    BigInt& operator++();
    const BigInt operator++(int) const;
    BigInt& operator--();
    const BigInt operator--(int) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;

    [[nodiscard]] size_t size() const{
        return sizeof(is_positive) + sizeof(decimal_digits_count) + sizeof(binary_digits_count) +
        sizeof(binary_blocks_count) + decimal_digits_count + binary_blocks_count;
    }

    [[nodiscard]] std::string decimal_representation() const{
        //return is_positive ? abs_decimal_representation : '-' + abs_decimal_representation;
    }
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& out, const BigInt& i){
    out << i.decimal_representation();
    return out;
}
std::istream& operator>>(std::istream& o, BigInt& i);



int main() {
    char* a = new char[3];
    a[0] = '1';
    a[1] = '2';
    a[2] = '3';

    ltoa(1024, a, 2);

    std::cout << a;

    delete[] a;


    /*
    for (unsigned int a = 0; a < 16; a++){
        for (unsigned int b = 0; b < 16; b++){
            std::cout << (a + b - 15) << " " << (a & b) << "\n";
        }
    }*/


    //BigInt a = BigInt(312321321);

    //std::cout << a.size();

    return 0;
}
