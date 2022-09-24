#include "gtest/gtest.h"
#include "../big_int.h"

TEST(constructors_test, empty_constructor_test){
    BigInt b = BigInt();
    EXPECT_EQ(std::string(b), "0");
}
TEST(constructors_test, constructors_test1){
    BigInt b = BigInt(0);
    EXPECT_EQ(std::string(b), "0");
}
TEST(constructors_test, constructors_test2){
    BigInt b = BigInt("0");
    EXPECT_EQ(std::string(b), "0");
}
TEST(constructors_test, constructors_test3){
    BigInt b = BigInt(1234);
    EXPECT_EQ(std::string(b), "1234");
}
TEST(constructors_test, constructors_test4){
    BigInt b = BigInt(-1235);
    EXPECT_EQ(std::string(b), "-1235");
}
TEST(constructors_test, constructors_test5){
    BigInt b = BigInt("12345678901234567890");
    EXPECT_EQ(std::string(b), "12345678901234567890");
}
TEST(constructors_test, constructors_test6){
    BigInt b = BigInt("-12345678901234567890");
    EXPECT_EQ(std::string(b), "-12345678901234567890");
}
TEST(constructors_test, constructors_test7){
    BigInt b = BigInt("111111111111111111111111111111111111111111111111111111111111");
    EXPECT_EQ(std::string(b), "111111111111111111111111111111111111111111111111111111111111");
}
TEST(constructors_test, constructors_test8){
    BigInt b = BigInt("-111111111111111111111111111111111111111111111111111111111111");
    EXPECT_EQ(std::string(b), "-111111111111111111111111111111111111111111111111111111111111");
}
