#include "gtest/gtest.h"
#include "../big_int.h"

TEST(eq_test, eq_test1){
    BigInt a = BigInt("0");
    BigInt b = BigInt(0);

    EXPECT_TRUE(a == b);
}
TEST(eq_test, eq_test2){
    BigInt a = BigInt("123");
    BigInt b = BigInt(123);

    EXPECT_TRUE(a == b);
}
TEST(eq_test, eq_test3){
    BigInt a = BigInt("-987");
    BigInt b = BigInt(-987);

    EXPECT_TRUE(a == b);
}

TEST(neq_test, neq_test1){
    BigInt a = BigInt("0");
    BigInt b = BigInt(0);

    EXPECT_FALSE(a != b);
}
TEST(neq_test, neq_test2){
    BigInt a = BigInt("123");
    BigInt b = BigInt(123);

    EXPECT_FALSE(a != b);
}
TEST(neq_test, neq_test3){
    BigInt a = BigInt("-987");
    BigInt b = BigInt(-987);

    EXPECT_FALSE(a != b);
}

TEST(greater_test, greater_test1){
    BigInt a = BigInt(1);
    BigInt b = BigInt(0);
    EXPECT_TRUE(a > b);
}
TEST(greater_test, greater_test2){
    BigInt a = BigInt(0);
    BigInt b = BigInt(-1);

    EXPECT_TRUE(a > b);
}
TEST(greater_test, greater_test3){
    BigInt a = BigInt(-123);
    BigInt b = BigInt(-124);

    EXPECT_TRUE(a > b);
}
TEST(greater_test, greater_test4){
    BigInt a = BigInt(-1);
    BigInt b = BigInt(1);

    EXPECT_FALSE(a > b);
}

TEST(greater_or_equal_test, greater_or_equal_test1){
    BigInt a = BigInt(1);
    BigInt b = BigInt(0);
    EXPECT_TRUE(a >= b);
}
TEST(greater_or_equal_test, greater_or_equal_test2){
    BigInt a = BigInt(0);
    BigInt b = BigInt(-1);

    EXPECT_TRUE(a >= b);
}
TEST(greater_or_equal_test, greater_or_equal_test3){
    BigInt a = BigInt(-123);
    BigInt b = BigInt(-124);

    EXPECT_TRUE(a >= b);
}
TEST(greater_or_equal_test, greater_or_equal_test4){
    BigInt a = BigInt(-1);
    BigInt b = BigInt(1);

    EXPECT_FALSE(a >= b);
}
TEST(greater_or_equal_test, greater_or_equal_test5){
    BigInt a = BigInt(1);
    BigInt b = BigInt(1);

    EXPECT_TRUE(a >= b);
}
TEST(greater_or_equal_test, greater_or_equal_test6){
    BigInt a = BigInt(-1);
    BigInt b = BigInt(-1);

    EXPECT_TRUE(a >= b);
}
