#include <iostream>
#include <cmath>

#define BASE 256
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



class BigInt {
private:
    unsigned char* data;
    unsigned long long data_length;
    bool is_positive;
public:
    BigInt(){
        data_length = 1;

        data = new unsigned char[1];
        data[0] = 0;

        is_positive = true;

        //std::cout << "Positive=" << is_positive << " data_length=" << data_length << "\n";

        //for (unsigned int i = 0; i < data_length; i++){
          //  std::cout << int(data[i]) << " ";
        //}
    }
    explicit BigInt(int number){
        is_positive = (number >= 0);

        unsigned int abs_number = abs(number);

        data_length = ceil_log(BASE, abs_number);

        data = new unsigned char[data_length];

        for (unsigned int i = data_length; i > 0; i--){
            data[i - 1] = abs_number % BASE;
            abs_number /= BASE;
        }


    }
    BigInt(std::string){

    }
    BigInt(const BigInt&);
    ~BigInt(){
        delete data;
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
        return sizeof(data_length) + sizeof(is_positive) + data_length;
    }

    [[nodiscard]] std::string representation() const{
        std::string binary_representation;

        for (unsigned long long i = data_length; i > 0; i--){
            const unsigned char current_block = data[i - 1];

            for (unsigned char j = 0; j < 8; j++){
                binary_representation.insert(0, 1, GET_BIT_8(current_block, j) + '0');
            }
        }

        std::string representation;
        const unsigned long long binary_representation_length = binary_representation.length();

        unsigned char carry = 0;
        for (unsigned long long i = binary_representation_length; i > 0; i--){
            const unsigned char current_binary_digit = binary_representation[i - 1];
            const unsigned long long



            carry = binary_representation[i - 1] / 10;
            representation.insert(0, 1, binary_representation[i - 1] % 10);
        }






        return representation;
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
    out << i.representation();
    return out;
}
std::istream& operator>>(std::istream& o, BigInt& i);



int main() {
    //BigInt a = BigInt(1234567890);
    BigInt b = BigInt(2);

    std::cout << b;

    return 0;
}
