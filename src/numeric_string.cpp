#include "numeric_string.h"
#include "utils.h"

void NumericString::add_zero(){
    this->string.insert(0, 1, '0');
}
void NumericString::reduce_zeroes(){
    while(this->length() > 1 && this->string[0] == '0'){
        this->string.erase(0, 1);
    }
}
unsigned int NumericString::length() const{
    return this->string.length();
}

NumericString::NumericString()= default;
NumericString::NumericString(char c){
    this->string.insert(0, 1, c);
}
NumericString::NumericString(unsigned long long n){
    this->string = std::to_string(n);
}
NumericString::NumericString(const std::string& s){
    this->string = s;

    this->reduce_zeroes();
}

NumericString& NumericString::operator+=(const char operand){
    *this = (*this) + NumericString(operand);

    return *this;
}

NumericString NumericString::operator+(const NumericString& operand) const{
    const unsigned int length = get_max(this->length(), operand.length());

    std::string result;
    result.resize(length);

    NumericString tmp1 = *this;
    NumericString tmp2 = operand;

    while(tmp1.length() < length){
        tmp1.add_zero();
    }
    while(tmp2.length() < length){
        tmp2.add_zero();
    }

    unsigned int carry = 0;
    for (unsigned int i = length; i > 0; i--){
        const unsigned int current_digit1 = char_to_digit(this->string[i - 1]);
        const unsigned int current_digit2 = char_to_digit(operand.string[i - 1]);

        const unsigned int current_sum = current_digit1 + current_digit2 + carry;

        result[i - 1] = digit_to_char(current_sum % 10);

        carry = current_sum / 10;
    }

    if (carry){
        result.insert(0, 1, '1');
    }

    return NumericString(result);
}
NumericString NumericString::operator*(const NumericString& operand) const{
    NumericString result = NumericString("0");

    if (operand.length() == 1){
        unsigned int carry = 0;
        const unsigned int length = this->length();

        const unsigned int operand_only_digit = char_to_digit(operand.string[0]);
        for (unsigned int i = length; i > 0; i--){
            const unsigned int current_digit1 = char_to_digit(this->string[i - 1]);

            const unsigned int product = current_digit1 * operand_only_digit + carry;

            result.string = digit_to_char(product % 10) + result;

            carry = product / 10;
        }

        if (carry){
            result.string.insert(0, 1, digit_to_char(carry));
        }
    }
    else{
        unsigned long long index = 0;
        while(operand != "0"){
            NumericString current_product = (*this) * NumericString(operand.string.back());
            current_product.string.append(index, 0);

            result = result + current_product;;

            //NumericString q

            //std::string tmp1;
            unsigned int tmp2;
            //divide_string_by_number(a, 10, tmp1, tmp2);

            //a = tmp1;
        }
    }

    return result;
}
NumericString NumericString::operator/(unsigned long long operand) const{
    NumericString tmp = NumericString(operand);

    if (tmp > *this){
        return NumericString("0");
    }

    const unsigned int length = this->length();
    unsigned long long r = 0;
    unsigned int current_index = 0;
    std::string result;

    while(r < operand){
        r = r * 10 + char_to_digit(this->string[current_index++]);
    }

    while(true){
        result.append(1, digit_to_char(r / operand));
        r %= operand;

        if (current_index == length){
            break;
        }

        r = r * 10 + char_to_digit(this->string[current_index++]);

        while(r < operand){
            if (current_index == length){
                break;
            }
            result.append(1, '0');
            r = r * 10 + char_to_digit(this->string[current_index++]);
        }
    }

    return NumericString(result);
}
unsigned long long NumericString::operator%(unsigned long long operand) const{
    NumericString tmp = NumericString(operand);

    if (tmp > *this){
        return (unsigned long long)(*this);
    }

    const unsigned int length = this->length();
    unsigned long long r = 0;
    unsigned int current_index = 0;

    while(r < operand){
        r = r * 10 + char_to_digit(this->string[current_index++]);
    }

    while(true){
        r %= operand;

        if (current_index == length){
            break;
        }

        r = r * 10 + char_to_digit(this->string[current_index++]);

        while(r < operand){
            if (current_index == length){
                break;
            }
            r = r * 10 + char_to_digit(this->string[current_index++]);
        }
    }

    return r;
}

bool NumericString::operator!=(const std::string& s) const{
    return this->string != s;
}
bool NumericString::operator>(const NumericString& operand) const{
    const unsigned int length1 = this->length();
    const unsigned int length2 = operand.length();

    if (length1 != length2){
        return length1 > length2;
    }

    for (unsigned int i = 0; i < length1; i++){
        const char current_digit1 = this->string[i];
        const char current_digit2 = operand.string[i];

        if (current_digit1 != current_digit2){
            return current_digit1 > current_digit2;
        }
    }

    return false;
}

NumericString::operator unsigned long long() const{
    return std::strtoull(this->string.c_str(), nullptr, 10);
}

std::string NumericString::representation() const{
    return this->string;
}

std::ostream& operator<<(std::ostream& out, const NumericString& s){
    out << s.representation();
    return out;
}
