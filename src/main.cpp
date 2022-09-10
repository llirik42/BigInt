#include <iostream>
#include <cmath>

#define SIZE_OF_BYTE 8
#define SET_BIT_8(N, I, V) N = (V) ? ((1 << (SIZE_OF_BYTE - (I) - 1)) | (N)) : (~(1 << (SIZE_OF_BYTE - (I) - 1)) & (N));
#define GET_BIT_8(N, I) ((1 << (SIZE_OF_BYTE - (I) - 1) & (N)) >> (SIZE_OF_BYTE - (I) - 1))


class BigInt {
private:
    std::string binaryRepresentation;
public:
    BigInt();
    explicit BigInt(int number){
        binaryRepresentation = "";

        while (number){
            binaryRepresentation.insert(0, 1, 0);
            for (unsigned char j = 0; j < 8; j++){
                SET_BIT_8(binaryRepresentation[0], 8 - j - 1, number % 2);
                number /= 2;
            }
        }

        const unsigned int length = binaryRepresentation.length();
        for (unsigned int l = 0; l < length; l++){
            for (int i = 0; i < 8; i++){
                std::cout << GET_BIT_8(binaryRepresentation[l], i);
            }
            std::cout << " ";
        }
    }
    BigInt(std::string); // ??????? ?????????? std::invalid_argument ??? ??????
    BigInt(const BigInt&);
    ~BigInt()= default;

    BigInt(BigInt&&);
    BigInt& operator=(BigInt&&);


    BigInt& operator=(const BigInt&);  //???????? ???????????? ?????? ????!

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
    out << "123";

    return out;
}
std::istream& operator>>(std::istream& o, BigInt& i);



int main() {
    BigInt b = BigInt(473829473);

    return 0;
}
