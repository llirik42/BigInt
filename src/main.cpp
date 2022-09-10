#include <iostream>
#include <cmath>

#define SIZE_OF_BYTE 8
#define POW_2_SIZE_OF_BYTE 256
#define GET_BIT_8(N, I) ((1 << (SIZE_OF_BYTE - (I) - 1) & (N)) >> (SIZE_OF_BYTE - (I) - 1))

unsigned int ceil_log8(unsigned int number){
    if (!number){
        return 1;
    }

    unsigned long long result = 0;

    while (number){
        result++;
        number /= POW_2_SIZE_OF_BYTE;
    }

    return result;
}



class BigInt {
private:
    unsigned char* data;
    unsigned long long data_length;
    bool is_positive;
public:
    BigInt();
    explicit BigInt(int number){
        is_positive = (number >= 0);

        unsigned int abs_number = abs(number);

        data_length = ceil_log8(abs_number);

        data = new unsigned char[data_length];

        for (unsigned int i = data_length; i > 0; i--){
            data[i - 1] = abs_number % POW_2_SIZE_OF_BYTE;
            abs_number /= POW_2_SIZE_OF_BYTE;
        }

        std::cout << "Positive=" << is_positive << " data_length=" << data_length << "\n";

        for (unsigned int i = 0; i < data_length; i++){
            std::cout << int(data[i]) << " ";
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

    size_t size() const;  // size in bytes


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


    return out;
}
std::istream& operator>>(std::istream& o, BigInt& i);



int main() {
    BigInt b = BigInt(3123213);

    return 0;
}
