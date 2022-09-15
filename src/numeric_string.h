#include <iostream>

class NumericString{
private:
    std::string string;

    void add_zero();
    void reduce_zeroes();
    [[nodiscard]] unsigned int length() const;
public:
    NumericString();
    explicit NumericString(char);
    explicit NumericString(unsigned long long);
    explicit NumericString(const std::string&);

    NumericString& operator+=(const char);

    NumericString operator+(const NumericString&) const;
    NumericString operator*(const NumericString&) const;
    NumericString operator/(unsigned long long) const;
    unsigned long long operator%(unsigned long long) const;

    bool operator!=(const std::string&) const;
    bool operator>(const NumericString&) const;

    explicit operator unsigned long long() const;

    std::string representation() const;
};

std::ostream& operator<<(std::ostream&, const NumericString&);
