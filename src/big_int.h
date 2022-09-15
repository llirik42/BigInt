#include <iostream>

class BigInt{
private:
    bool is_positive;

    std::string abs_decimal_representation;
    std::string abs_binary_compact_representation;
public:
    BigInt();
    explicit BigInt(int);
    explicit BigInt(std::string);
    BigInt(const BigInt&);
    ~BigInt();

    BigInt(BigInt&&);
    BigInt& operator=(BigInt&&) noexcept ;

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

    BigInt operator+() const;
    BigInt operator-() const;

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    explicit operator std::string() const;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] std::string decimal_representation() const;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream&, const BigInt&);
std::istream& operator>>(std::istream&, BigInt&);
