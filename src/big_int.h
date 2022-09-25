#include <iostream>
#include "smart_vector.h"

class BigInt{
private:
    bool is_positive;
    SmartVector vector;

    int compare(const BigInt&) const;
public:
    BigInt();
    explicit BigInt(int);
    explicit BigInt(const std::string&);
    BigInt(const BigInt&);
    BigInt(BigInt&&) noexcept;
    ~BigInt();

    BigInt& operator=(const BigInt&);
    BigInt& operator=(BigInt&&) noexcept;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);

    BigInt operator+() const;
    BigInt operator-();
    BigInt& operator~();

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    BigInt& operator^=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    explicit operator int() const;
    explicit operator std::string() const;

    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool is_zero() const;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream&, const BigInt&);
std::istream& operator>>(std::istream&, BigInt&);
