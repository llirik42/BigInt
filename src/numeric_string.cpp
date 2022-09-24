#include "numeric_string.h"
#include "utils.h"
#include <climits>

void copy_into_the_end(const char* from, unsigned int from_length, char* to, unsigned int to_length){
    const unsigned int length = get_min(from_length, to_length);

    for (unsigned int i = length; i > 0; i--){
        to[to_length - (length - i) - 1] = from[from_length - (length - i) - 1];
    }
}

void NumericString::append(char c, unsigned int count){
    char* tmp = new char[this->length + count];

    for (unsigned int i = this->length; i > 0; i--){
        tmp[i - 1] = this->string[i - 1];
    }
    for (unsigned int i = 0; i < count; i++){
        tmp[i + this->length] = c;
    }

    delete[] this->string;
    this->length += count;

    this->string = new char[this->length];

    copy_into_the_end(tmp, this->length, this->string, this->length);

    delete[] tmp;

}
void NumericString::insert_front(char c){
    NumericString tmp = (*this);

    delete[] this->string;

    this->string = new char[++this->length];

    copy_into_the_end(tmp.string, this->length - 1, this->string, this->length);

    this->string[0] = c;
}
void NumericString::add_zero(){
    this->insert_front('0');
}
void NumericString::erase_front(){
    NumericString tmp = (*this);

    delete[] this->string;

    this->string = new char[--this->length];

    copy_into_the_end(tmp.string, this->length, this->string, this->length);
}
void NumericString::reduce_zeroes(){
    while(this->get_length() > 1 && this->string[0] == '0'){
        this->erase_front();
    }
}

NumericString::NumericString(){
    this->string = nullptr;
    this->length = 0;
}
NumericString::NumericString(unsigned long long n){
    if (!n){
        this->length = 1;
        this->string = new char[1];
        this->string[0] = '0';
        return;
    }

    this->length = 0;
    this->string = nullptr;

    while(n){
        this->insert_front(digit_to_char(n % 10));
        n /= 10;
    }
}
NumericString::NumericString(const std::string& s){
    this->length = 0;
    this->string = nullptr;

    for (unsigned int i = s.length(); i > 0; i--){
        this->insert_front(s[i - 1]);
    }
}
NumericString::NumericString(NumericString&& s) noexcept{
    this->length = s.length;
    this->string = s.string;
    s.string = nullptr;
}
NumericString::NumericString(const NumericString &s){
    this->length = s.length;

    this->string = this->length ? new char[this->length] : nullptr;

    if (this->length){
        copy_into_the_end(s.string, s.length, this->string, this->length);
    }
}
NumericString::~NumericString(){
    delete[] this->string;
}

NumericString& NumericString::operator=(const NumericString& s){
    if (&s == this){
        return (*this);
    }

    this->length = 0;
    delete[] this->string;
    this->string = nullptr;

    for (unsigned int i = s.length; i > 0; i--){
        this->insert_front(s.string[i - 1]);
    }

    return (*this);
}
NumericString& NumericString::operator=(NumericString&& s) noexcept {
    this->length = s.length;
    this->string = s.string;

    s.string = nullptr;

    return (*this);
}

NumericString NumericString::operator+(const NumericString& operand) const{
    const unsigned int max_operand_length = get_max(this->get_length(), operand.get_length());

    NumericString result = NumericString();

    NumericString tmp1; tmp1 = (*this);
    NumericString tmp2; tmp2 = operand;

    while(tmp1.get_length() < max_operand_length){
        tmp1.add_zero();
    }
    while(tmp2.get_length() < max_operand_length){
        tmp2.add_zero();
    }

    unsigned int carry = 0;
    for (unsigned int i = max_operand_length; i > 0; i--){
        const unsigned int current_digit1 = char_to_digit(tmp1.string[i - 1]);
        const unsigned int current_digit2 = char_to_digit(tmp2.string[i - 1]);

        const unsigned int current_sum = current_digit1 + current_digit2 + carry;

        result.insert_front(digit_to_char(current_sum % 10));

        carry = current_sum / 10;
    }

    if (carry){
        result.insert_front('1');
    }

    return result;
}
NumericString NumericString::operator*(const NumericString& operand) const{
    NumericString result = NumericString();

    const unsigned int operand_length = operand.get_length();

    if (this->is_zero()){
        return NumericString(0);
    }

    if (operand_length == 1){
        unsigned char carry = 0;

        const unsigned char operand_only_digit = char_to_digit(operand.string[0]);
        for (unsigned int i = this->get_length(); i > 0; i--){
            const unsigned char current_digit1 = char_to_digit(this->string[i - 1]);

            const unsigned char product = current_digit1 * operand_only_digit + carry;

            result.insert_front(digit_to_char(product % 10));

            carry = product / 10;
        }

        if (carry){
            result.insert_front(digit_to_char(carry));
        }

        result.reduce_zeroes();
    }
    else{
        result = NumericString(0);

        for (unsigned int i = operand_length; i > 0; i--){
            NumericString current_digit = NumericString(char_to_digit(operand.string[i - 1]));

            NumericString current_product = (*this) * current_digit;

            current_product.append('0', operand_length - i);

            result += current_product;
        }
    }

    return result;
}
NumericString NumericString::operator/(unsigned long long operand) const{
    NumericString tmp = NumericString(operand);

    if (tmp > *this){
        return NumericString(0);
    }

    unsigned long long r = 0;
    unsigned int current_index = 0;

    NumericString result;

    while(r < operand){
        r = r * 10 + char_to_digit(this->string[current_index++]);
    }

    while(true){
        result.append(digit_to_char((unsigned char) (r / operand)), 1);
        r %= operand;

        if (current_index == this->length){
            break;
        }

        r = r * 10 + char_to_digit(this->string[current_index++]);

        while(r < operand){
            if (current_index == this->length){
                break;
            }
            result.append('0', 1);
            r = r * 10 + char_to_digit(this->string[current_index++]);
        }
    }

    return result;
}
unsigned long long NumericString::operator%(unsigned long long operand) const{
    NumericString tmp = NumericString(operand);

    if (tmp > *this){
        return (unsigned long long)(*this);
    }

    unsigned long long r = 0;
    unsigned int current_index = 0;

    while(r < operand){
        r = r * 10 + char_to_digit(this->string[current_index++]);
    }

    while(true){
        r %= operand;

        if (current_index == this->length){
            break;
        }

        r = r * 10 + char_to_digit(this->string[current_index++]);

        while(r < operand){
            if (current_index == this->length){
                break;
            }
            r = r * 10 + char_to_digit(this->string[current_index++]);
        }
    }

    return r;
}

NumericString& NumericString::operator+=(const NumericString& operand){
    (*this) = (*this) + operand;
    return (*this);
}
NumericString& NumericString::operator/=(const unsigned long long operand){
    (*this) = (*this) / operand;
    return (*this);
}

bool NumericString::operator==(const std::string& s) const{
    if (this->length != s.length()){
        return false;
    }

    for (unsigned int i = 0; i < s.length(); i++){
        if (this->string[i] != s[i]){
            return false;
        }
    }

    return true;
}
bool NumericString::operator==(const NumericString& s) const{
    if (this->length != s.length){
        return false;
    }

    for (unsigned int i = 0; i < s.length; i++){
        if (this->string[i] != s.string[i]){
            return false;
        }
    }

    return true;
}
bool NumericString::operator!=(const std::string& s) const{
    return this->string != s;
}
bool NumericString::operator!=(const NumericString& s) const{
    return !(s == (*this));
}
bool NumericString::operator>(const NumericString& operand) const{
    const unsigned int length1 = this->get_length();
    const unsigned int length2 = operand.get_length();

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
    const NumericString ullong_max_numeric = NumericString(ULLONG_MAX);

    if ((*this) > ullong_max_numeric){
        return ULLONG_MAX;
    }

    unsigned long long result = 0;

    unsigned long current_m = 1;
    for (unsigned int i = this->length; i > 0; i--, current_m *= 10){
        result += current_m * char_to_digit(this->string[i - 1]);
    }

    return result;
}
NumericString::operator std::string() const{
    std::string result;

    for (unsigned int i = 0; i < this->length; i++){
        result.append(1, this->string[i]);
    }

    return result;
}

unsigned int NumericString::get_length() const{
    return this->length;
}
bool NumericString::is_zero() const{
    return this->length == 1 && this->string[0] == '0';
}

unsigned int ceil_log_numerical_str(unsigned long long base, const NumericString& s){
    if (s.is_zero()){
        return 1;
    }

    unsigned int result = 0;

    NumericString tmp = s;
    while (!tmp.is_zero()){
        result++;

        tmp /= base;
    }

    return result;
}
