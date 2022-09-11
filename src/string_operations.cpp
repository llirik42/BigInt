#include <iostream>

#define CHAR_TO_DIGIT(C) (int((C) - '0'))
#define DIGIT_TO_CHAR(D) (char(D + '0'))

std::string sub(std::string s1, std::string s2){
    if (s1 == s2){
        return "0";
    }

    std::string result;

    const unsigned int length = s1.length();

    while (s2.length() < s1.length()){
        s2.insert(0, 1, '0');
    }

    unsigned char carry = 0;
    for (unsigned int i = length; i > 0; i--){
        const int cur_digit_1 = CHAR_TO_DIGIT(s1[i - 1]);
        const int cur_digit_2 = CHAR_TO_DIGIT(s2[i - 1]) + carry;

        carry = cur_digit_1 < cur_digit_2;

        const int digit_of_result = 10 * carry + cur_digit_1 - cur_digit_2;

        result.insert(0, 1, DIGIT_TO_CHAR(digit_of_result));
    }

    while (result[0] == '0'){
        result.erase(0, 1);
    }

    return result;
}

bool compare_numerical_strings(std::string s1, std::string s2){
    // s1 > s2

    const unsigned int l1 = s1.length();
    const unsigned int l2 = s2.length();

    if (l1 != l2){
        return l1 > l2;
    }

    for (unsigned int i = 0; i < l1; i++){
        if (s1[i] != s2[i]){
            return s1 > s2;
        }
    }

    return false;
}

void increment_str(std::string& str){
    std::string result;

    const unsigned int length = str.length();

    unsigned int carry = 1;
    for (unsigned int i = length; i > 0; i--){
        const unsigned char cur_digit = CHAR_TO_DIGIT(str[i - 1]);

        const unsigned char tmp = carry + cur_digit;

        result.insert(0, 1, DIGIT_TO_CHAR(tmp % 10));

        carry = tmp / 10;
    }

    if (carry){
        result.insert(0, 1, DIGIT_TO_CHAR(carry));
    }

    str = result;
}

void str_division(std::string a, const std::string& b, std::string& q, std::string& r){
    std::string result = "0";

    while (true){
        if (compare_numerical_strings(b, a)){
            q = result;
            r = a;
            break;
        }

        increment_str(result);
        a = sub(a, b);
    }
}
