#include "big_int.h"
#include "utils.h"

bool is_str_numerical(std::string str){
    const unsigned int length = str.length();

    if (!length){
        return false;
    }

    if (length == 1){
        return std::isdigit(str[0]);
    }

    if (!std::isdigit(str[0]) && str[0] != '-'){
        return false;
    }

    if (str[0] == '0' || (str[0] == '-' && str[1] == '0')){
        return false;
    }

    for (unsigned int i = 1; i < length; i++){
        if (!std::isdigit(str[i])){
            return false;
        }
    }

    return true;
}

BigInt::BigInt() {
    is_positive = true;

    abs_decimal_representation = "0";
    abs_binary_compact_representation = {0};
}
BigInt::BigInt(int number) {
    is_positive = (number >= 0);

    unsigned int abs_number = is_positive ? number : (-number);

    abs_decimal_representation = std::to_string(abs_number);

    while (abs_number){
        abs_binary_compact_representation.insert(0, 1, char(abs_number % TWO_TO_THE_POWER_OF_BYTE_SIZE));
        abs_number /= TWO_TO_THE_POWER_OF_BYTE_SIZE;
    }
}
BigInt::BigInt(std::string str) {
    if (!is_str_numerical(str)){
        throw std::invalid_argument("Invalid string for BigInt");
    }

    is_positive = str[0] != '-';

    if (!is_positive){
        str.erase(0, 1);
    }

    abs_decimal_representation = str;

    while (str != "0"){
        unsigned char current_block_value = 0;

        unsigned int current_m = 1;
        for (unsigned char i = 0; i < SIZE_OF_BYTE; i++){
            std::string r;

            current_block_value += current_m * CHAR_TO_DIGIT(r[0]);
            current_m *= 2;
        }
        abs_binary_compact_representation.insert(0, 1, (char)(current_block_value));
    }
}
BigInt::BigInt(const BigInt& b) {
    is_positive = b.is_positive;

    abs_decimal_representation = b.abs_decimal_representation;

    abs_binary_compact_representation = b.abs_binary_compact_representation;
}
BigInt::~BigInt()= default;

BigInt& BigInt::operator=(BigInt&&) noexcept{
    return *this;
}

BigInt& BigInt::operator=(const BigInt& b){
    return *this;
}

BigInt::operator std::string() const{
    return decimal_representation();
}

size_t BigInt::size() const {
    return sizeof(is_positive) + abs_decimal_representation.length() + abs_binary_compact_representation.length();
}
std::string BigInt::decimal_representation() const{
    std::string result = abs_decimal_representation;

    if (!is_positive){
        result.insert(0, 1, '-');
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const BigInt &b){
    out << b.decimal_representation();

    return out;
}
std::istream& operator>>(std::istream& in, BigInt& b){
    std::string in_str;

    in >> in_str;

    b = BigInt(in_str);

    return in;
}
