#include <iostream>
#include "smart_vector.h"
#include "numeric_string.h"
#include <cassert>

void test_numeric_string(){
    assert(NumericString(0) == "0");
    assert(NumericString("0") == "0");
    assert(NumericString(123) == "123");
    assert(NumericString("123") == "123");
    assert(NumericString("1111111111111111111111111111111") == "1111111111111111111111111111111");
    assert(NumericString(42) == NumericString("42"));
    assert(NumericString(0) + NumericString(111) == NumericString(111));
    assert(NumericString(999) + NumericString(1) == NumericString(1000));
    assert(NumericString(1) * NumericString(42) == NumericString(42));
    assert(NumericString(0) * NumericString(1) == NumericString(0));
    assert(NumericString(0) * NumericString(0) == NumericString(0));
    assert(NumericString(1) * NumericString(1) == "1");
    assert(NumericString(11) * NumericString(12) == "132");
    assert(NumericString(0) / 42 == "0");
    assert(NumericString(42) / 5 == "8");
    assert(NumericString(0) % 5 == 0);
    assert(NumericString(0) % 42 == 0);
    assert(NumericString(1234567890).length() == 10);
    assert(NumericString(123456798) > NumericString(123456789));
    assert((unsigned long long)NumericString(123456789) == 123456789);
    assert(std::string(NumericString(123456789)) == "123456789");
    std::cout << "All tests of NumericString passed";
}

int main() {
    test_numeric_string();

    return 0;
}
