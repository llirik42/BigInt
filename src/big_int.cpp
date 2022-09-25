#include "big_int.h"
#include "utils.h"
#include <climits>

BigInt::BigInt(): is_positive(true), vector(SmartVector()) {}
BigInt::BigInt(int number): is_positive(number >= 0), vector(SmartVector(abs(number))) {}
BigInt::BigInt(const std::string& str) {
    if (!is_string_numeric(str)){
        throw std::invalid_argument("Invalid string for BigInt");
    }

    is_positive = str[0] != '-';

    std::string tmp = str;

    if (!is_positive){
        tmp.erase(0, 1);
    }

    this->vector = SmartVector(tmp);
}
BigInt::BigInt(const BigInt& b)=default;
BigInt::BigInt(BigInt&& b) noexcept: is_positive(b.is_positive), vector(std::move(b.vector)) {}
BigInt::~BigInt()=default;

BigInt& BigInt::operator=(const BigInt& b)=default;
BigInt& BigInt::operator=(BigInt&& b) noexcept{
    this->is_positive = b.is_positive;
    this->vector = std::move(b.vector);
    return *this;
}

BigInt& BigInt::operator+=(const BigInt& b){
    BigInt result;

    if (this->is_positive != b.is_positive){
        result.is_positive = this->vector > b.vector ? this->is_positive : b.is_positive;
        result.vector = this->vector > b.vector ? this->vector - b.vector : b.vector - this->vector;
    }
    else{
        result.is_positive = this->is_positive;
        result.vector = this->vector + b.vector;
    }

    *this = result;
    this->is_positive = this->is_positive || this->is_zero();
    return *this;
}
BigInt& BigInt::operator*=(const BigInt& b){
    if (!b.is_positive){
        this->is_positive = !this->is_positive;
    }
    this->vector *= b.vector;

    this->is_positive = this->is_positive || this->is_zero();
    return *this;
}
BigInt& BigInt::operator-=(const BigInt& b){
    BigInt tmp = b;
    tmp.is_positive = !tmp.is_positive;
    *this += tmp;
    this->is_positive = this->is_positive || this->is_zero();
    return *this;
}
BigInt& BigInt::operator/=(const BigInt& b){
    if (b.is_zero()){
        throw std::invalid_argument("Division by zero");
    }
    this->is_positive = this->is_positive == b.is_positive;
    this->vector /= b.vector;
    this->is_positive = this->is_positive || this->is_zero();

    return *this;
}
BigInt& BigInt::operator%=(const BigInt& b){
    if (b.is_zero()){
        throw std::invalid_argument("Division by zero");
    }
    if (!b.is_positive){
        throw std::invalid_argument("Attempt of getting reminded for division by a negative number");
    }

    while(!this->is_positive){
        *this += b;
    }
    this->vector %= b.vector;

    return *this;
}

BigInt BigInt::operator+() const{
    return *this;
}
BigInt BigInt::operator-(){
    this->is_positive = !this->is_positive;
    return *this;
}
BigInt& BigInt::operator~(){
    this->vector = ~this->vector;
    return *this;
}

BigInt& BigInt::operator++(){
    *this += BigInt(1);
    return *this;
}
const BigInt BigInt::operator++(int){
    BigInt result = *this;
    *this += BigInt(1);
    return result;
}
BigInt& BigInt::operator--(){
    *this -= BigInt(1);
    return *this;
}
const BigInt BigInt::operator--(int){
    BigInt result = *this;
    *this -= BigInt(1);
    return result;
}

bool BigInt::operator==(const BigInt& b) const{
    return !compare(b);
}
bool BigInt::operator!=(const BigInt& b) const{
    return compare(b);
}
bool BigInt::operator>(const BigInt& b) const{
    return compare(b) == 1;
}
bool BigInt::operator<(const BigInt& b) const{
    return compare(b) == -1;
}
bool BigInt::operator>=(const BigInt& b) const{
    return compare(b) >= 0;
}
bool BigInt::operator<=(const BigInt& b) const{
    return compare(b) <= 0;
}

BigInt& BigInt::operator^=(const BigInt& b){
    BigInt result;
    result.is_positive = this->is_positive == b.is_positive;
    result.vector = this->vector ^ b.vector;
    *this = result;
    return *this;
}
BigInt& BigInt::operator&=(const BigInt& b){
    BigInt result;
    result.is_positive = this->is_positive == b.is_positive;
    result.vector = this->vector & b.vector;
    *this = result;
    return *this;
}
BigInt& BigInt::operator|=(const BigInt& b){
    BigInt result;
    result.is_positive = this->is_positive == b.is_positive;
    result.vector = this->vector | b.vector;
    *this = result;
    return *this;
}

BigInt::operator int() const{
    if (this->is_positive && this->vector > SmartVector(INT_MAX)){
        return INT_MAX;
    }
    if (!this->is_positive && this->vector > SmartVector(-(long long)(INT_MIN))){
        return INT_MIN;
    }

    int abs_value = int(this->vector);

    return this->is_positive ? abs_value : -abs_value;
}
BigInt::operator std::string() const{
    std::string result = std::string(this->vector);

    if (!this->is_positive && !this->is_zero()){
        result.insert(0, 1, '-');
    }
    return result;
}

size_t BigInt::size() const{
    return sizeof(this->is_positive) + this->vector.size();
}
bool BigInt::is_zero() const{
    return (int(*this)) == 0;
}

int BigInt::compare(const BigInt& b) const{
    if (this->is_positive != b.is_positive){
        return this->is_positive ? 1: -1;
    }

    if (this->vector == b.vector){
        return 0;
    }

    return ((this->vector > b.vector) == this->is_positive) ? 1 : -1;
}

BigInt operator+(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result += b;
    return result;
}
BigInt operator-(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result -= b;
    return result;
}
BigInt operator*(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result *= b;
    return result;
}
BigInt operator/(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result /= b;
    return result;
}
BigInt operator%(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result %= b;
    return result;
}
BigInt operator^(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result ^= b;
    return result;
}
BigInt operator&(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result &= b;
    return result;
}
BigInt operator|(const BigInt& a, const BigInt& b){
    BigInt result = a;
    result |= b;
    return result;
}

std::ostream& operator<<(std::ostream& out, const BigInt &b){
    out << std::string(b);
    return out;
}
std::istream& operator>>(std::istream& in, BigInt& b){
    std::string in_str;

    in >> in_str;

    if (!is_string_numeric(in_str)){
        throw std::invalid_argument("Invalid string for BigInt");
    }

    b = BigInt(in_str);

    return in;
}
