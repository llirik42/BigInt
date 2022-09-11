#include "big_int.h"
#include "string_operations.h"
#include "utils.h"

bool is_str_numerical(std::string str){
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

    is_positive = (str[0] != '-');

    abs_decimal_representation = str;
    if (!is_positive){
        abs_decimal_representation.erase(0, 1);
    }

    while (str != "0"){
        unsigned char current_block_value = 0;

        unsigned char current_m = 1;
        for (unsigned char i = 0; i < SIZE_OF_BYTE; i++){
            std::string r;

            str_division(str, "2", str, r);

            current_block_value += current_m * CHAR_TO_DIGIT(r[0]);
            current_m *= 2;
        }
        abs_binary_compact_representation.insert(0, 1, char(current_block_value));
    }



}
BigInt::BigInt(const BigInt& b) {
    is_positive = b.is_positive;

    abs_decimal_representation = b.abs_decimal_representation;

    abs_binary_compact_representation = b.abs_binary_compact_representation;
}
BigInt::~BigInt()= default;

size_t BigInt::size() const {
    return sizeof(is_positive) + abs_decimal_representation.length() + abs_binary_compact_representation.length();
}
std::string BigInt::decimal_representation() {
    std::string result = abs_decimal_representation;

    if (!is_positive){
        result.insert(0, 1, '-');
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const BigInt& b);
    out << b.decimal_representation();

    return out;
}
