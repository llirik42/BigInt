#include <iostream>
#include "smart_vector.h"
#include "numeric_string.h"
#include <cassert>
#include <climits>

void test_numeric_string(){
    assert(NumericString(0) == "0");
    assert(NumericString("0") == "0");
    assert(NumericString(123) == "123");
    assert(NumericString("123") == "123");
    assert(NumericString("1111111111111111111111111111111") == "1111111111111111111111111111111");
    assert(NumericString(42) == NumericString("42"));
    assert(NumericString(0) + NumericString(111) == NumericString(111));
    assert(NumericString(999) + NumericString(1) == NumericString(1000));
    assert(NumericString(42) * NumericString(1) == NumericString(42));
    assert(NumericString(1) * NumericString(42) == NumericString(42));
    assert(NumericString(0) * NumericString(1) == NumericString(0));
    assert(NumericString(0) * NumericString(0) == NumericString(0));
    assert(NumericString(1) * NumericString(1) == "1");
    assert(NumericString(11) * NumericString(12) == "132");
    assert(NumericString(0) / 42 == "0");
    assert(NumericString(42) / 5 == "8");
    assert(NumericString(0) % 5 == 0);
    assert(NumericString(0) % 42 == 0);
    assert(NumericString(13) % 6 == 1);
    assert(NumericString(3) % 10 == 3);
    assert(NumericString(1234567890).get_length() == 10);
    assert(NumericString(123456798) > NumericString(123456789));
    assert((unsigned long long)NumericString(123456789) == 123456789);
    assert((unsigned long long)NumericString("11111111111111111111111111111111111111111111") == ULLONG_MAX);
    assert(std::string(NumericString(123456789)) == "123456789");
    std::cout << "All tests of NumericString passed\n";
}
void test_smart_vector(){
    assert(std::string(SmartVector()) == "0");
    assert(std::string(SmartVector("0")) == "0");
    assert(std::string(SmartVector(0)) == "0");
    assert(std::string(SmartVector(1)) == "1");
    assert(std::string(SmartVector("1")) == "1");
    assert(std::string(SmartVector(123456789)) == "123456789");
    assert(std::string(SmartVector("123456789")) == "123456789");
    assert(std::string(SmartVector("111111111111111111111111111111111111111111")) == "111111111111111111111111111111111111111111");
    assert(SmartVector(0) + SmartVector(0) == SmartVector(0));
    assert(SmartVector(1) + SmartVector(1) == SmartVector(2));
    assert(SmartVector(999) + SmartVector(1) == SmartVector(1000));
    assert(SmartVector("1111111111111111111111111") + SmartVector("1111111111111111111111111") == SmartVector("2222222222222222222222222"));
    assert(SmartVector("11111") + SmartVector("111") == SmartVector("11222"));
    assert(SmartVector(42) * SmartVector(2) == SmartVector(84));
    assert(SmartVector(0) * SmartVector(111) == SmartVector(0));
    assert(SmartVector(0) * SmartVector(0) == SmartVector(0));
    assert(SmartVector(1) * SmartVector(123) == SmartVector(123));
    assert(SmartVector(11) * SmartVector(12) == SmartVector(132));
    assert(SmartVector(42) * SmartVector(4294967296) == SmartVector(180388626432));
    assert(SmartVector("123456789") * SmartVector("987654321") == SmartVector("121932631112635269"));
    assert(SmartVector("1111111111111111111111111111111111111111111111111111111111111") * SmartVector("1111111111111111111111111111111111111111111111111111111111111") == SmartVector("1234567901234567901234567901234567901234567901234567901234567654320987654320987654320987654320987654320987654320987654321"));
    assert(SmartVector(1) - SmartVector(0) == SmartVector(1));
    assert(SmartVector(100000000000001) - SmartVector(1) == SmartVector(100000000000000));
    assert(SmartVector(0) - SmartVector(0) == SmartVector(0));
    assert(SmartVector(10) - SmartVector(1) == SmartVector(9));
    assert(SmartVector(100000000000000) - SmartVector(1) == SmartVector(99999999999999));
    assert(SmartVector(1010101010101010) - SmartVector(101010101010101) == SmartVector(909090909090909));
    assert(SmartVector(123456789) - SmartVector(123456) == SmartVector(123333333));
    assert(SmartVector("1111111111111111111111111112") - SmartVector("1111111111111111111111111111") == SmartVector(1));
    assert(SmartVector("99999999999999999999999999999999") - SmartVector("11111111111111111111111111111111") == SmartVector("88888888888888888888888888888888"));
    assert(SmartVector(123) % SmartVector(1) == SmartVector(123));
    assert(SmartVector(123) % SmartVector(10) == SmartVector(3));
    assert(SmartVector(123) / SmartVector(10) == SmartVector(12));
    assert(SmartVector(0) % SmartVector(5) == SmartVector(0));
    assert(SmartVector(0) / SmartVector(111) == SmartVector(0));
    assert(SmartVector("11111111111111111111111111111111111111111111111") / SmartVector(42) == SmartVector("264550264550264550264550264550264550264550264"));
    assert(SmartVector("11111111111111111111111111111111111111111111111") % SmartVector(42) == SmartVector(23));
    std::cout << "All tests of SmartVector passed\n";
}



int main() {
    test_smart_vector();


    //SmartVector v1 = SmartVector("111111111111111111111");
    //SmartVector v2 = SmartVector("2");

    //std::cout << v1 * v2;

    //test_numeric_string();

    //SmartVector v1 = SmartVector("11111111111111111111111111111111111111111111111");

    //std::cout << v1;

    return 0;
}
