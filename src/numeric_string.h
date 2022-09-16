#include <iostream>

class NumericString{
private:
    char* string;

    unsigned int length;

    void append(char, unsigned int);
    void insert_front(char);
    void add_zero();
    void erase_front();
    void reduce_zeroes();
public:
    NumericString();
    explicit NumericString(unsigned long long);
    explicit NumericString(const std::string&);
    NumericString(NumericString&&) noexcept;
    NumericString(const NumericString&);
    ~NumericString();

    NumericString& operator=(const NumericString&);
    NumericString& operator=(NumericString&&) noexcept;

    NumericString operator+(const NumericString&) const;
    NumericString operator*(const NumericString&) const;
    NumericString operator/(unsigned long long) const;
    unsigned long long operator%(unsigned long long) const;

    NumericString& operator+=(const NumericString&);
    NumericString& operator/=(unsigned long long);

    bool operator==(const std::string&) const;
    bool operator==(const NumericString&) const;
    bool operator!=(const std::string&) const;
    bool operator!=(const NumericString&) const;
    bool operator>(const NumericString&) const;

    explicit operator unsigned long long() const;
    explicit operator std::string() const;

    [[nodiscard]] bool is_zero() const;

    [[nodiscard]] unsigned int get_length() const;
};

unsigned int ceil_log_numerical_str(unsigned long long, const NumericString&);
