#include <iostream>
#include <cmath>

#define BLOCK_SIZE 256 // bits
#define GET_BIT_8(N, I) ((1 << (I) & (N)) >> (I))

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

std::string uint_to_str(unsigned int number){
    if (!number){
        return "0";
    }

    std::string result;
    while (number){
        result.insert(0, 1, (char)(number % 10 + '0'));
        number /= 10;
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

    std::string abs_decimal_representation;

    unsigned char* blocks;
    unsigned long long blocks_count;
public:
    BigInt(){
        is_positive = true;

        abs_decimal_representation = "0";

        blocks_count = 1;

        blocks = new unsigned char[1];
        blocks[0] = 0;
    }
    explicit BigInt(int number){
        is_positive = (number >= 0);

        unsigned int abs_number = abs(number);

        blocks_count = ceil_log(BLOCK_SIZE, abs_number);

        blocks = new unsigned char[blocks_count];

        for (unsigned int i = blocks_count; i > 0; i--){
            blocks[i - 1] = abs_number % BLOCK_SIZE;
            abs_number /= BLOCK_SIZE;
        }

        abs_decimal_representation = uint_to_str(abs(number));
    }
    BigInt(std::string str){
        if (!is_numerical(str)){
            throw std::invalid_argument("String isn't numerical");
        }




        char a = str[0];
    }
    BigInt(const BigInt&);
    ~BigInt(){
        delete blocks;
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
        return sizeof(is_positive) + abs_decimal_representation.length() + sizeof(blocks_count) + blocks_count;
    }

    [[nodiscard]] std::string decimal_representation() const{
        return is_positive ? abs_decimal_representation : '-' + abs_decimal_representation;
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
    BigInt c = BigInt("01");

    //std::cout << is_numerical("");


    //BigInt b = BigInt("-12345678901234567890");

    //std::cout << b;

    return 0;
}
