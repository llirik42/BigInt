#include <iostream>

class NumericString{
private:
    std::string string;

    void add_zero();
    void reduce_zeroes();
    [[nodiscard]] unsigned int length() const;
public:
    NumericString();
    explicit NumericString(unsigned long long);
    explicit NumericString(const std::string&);

    NumericString operator+(const NumericString&) const;
    NumericString operator*(const NumericString&) const;
    NumericString operator/(unsigned long long) const;
    unsigned long long operator%(unsigned long long) const;

    NumericString& operator+=(const NumericString&);
    NumericString& operator/=(unsigned long long);

    bool operator!=(const std::string&) const;
    bool operator>(const NumericString&) const;

    explicit operator unsigned long long() const;
    explicit operator std::string() const;

    [[nodiscard]] bool is_zero() const;
};

unsigned int ceil_log_numerical_str(unsigned long long, const NumericString&);
