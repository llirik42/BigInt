#pragma once

#include <iostream>

typedef unsigned int Block;

inline const unsigned long long BASE = 4294967296; // must be power of 2 for binary operations

class SmartVector{
private:
    Block* data;
    unsigned int length;

    void extend_and_copy(unsigned int);
    void append_zero_blocks(unsigned int);
    void reduce_first_block();
    void reduce_first_zero_blocks();
public:
    SmartVector();
    explicit SmartVector(unsigned long long);
    explicit SmartVector(const std::string&);
    SmartVector(SmartVector&&) noexcept;
    SmartVector(const SmartVector&);
    ~SmartVector();

    SmartVector& operator=(SmartVector&&) noexcept;
    SmartVector& operator=(const SmartVector&);

    SmartVector& operator+=(const SmartVector&);
    SmartVector& operator*=(const SmartVector&);
    SmartVector& operator-=(const SmartVector&);
    SmartVector& operator/=(const SmartVector&);
    SmartVector& operator%=(const SmartVector&);
    SmartVector& operator^=(const SmartVector&);
    SmartVector& operator&=(const SmartVector&);
    SmartVector& operator|=(const SmartVector&);
    SmartVector& operator~();

    bool operator==(const SmartVector&) const;
    bool operator!=(const SmartVector&) const;
    bool operator>(const SmartVector&) const;
    bool operator>=(const SmartVector&) const;

    explicit operator int() const;
    explicit operator std::string() const;

    [[nodiscard]] size_t size() const;
};

SmartVector operator+(const SmartVector&, const SmartVector&);
SmartVector operator-(const SmartVector&, const SmartVector&);
SmartVector operator*(const SmartVector&, const SmartVector&);
SmartVector operator/(const SmartVector&, const SmartVector&);
SmartVector operator%(const SmartVector&, const SmartVector&);
SmartVector operator^(const SmartVector&, const SmartVector&);
SmartVector operator&(const SmartVector&, const SmartVector&);
SmartVector operator|(const SmartVector&, const SmartVector&);


std::ostream& operator<<(std::ostream&, const SmartVector&);
