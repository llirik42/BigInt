#include "strings_operations.h"
#include "utils.h"

bool compare_strings(std::string s1, std::string s2){
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

std::string add_strings(std::string s1, std::string s2){
    const unsigned int length = s1.length() > s2.length() ? s1.length() : s2.length();

    std::string result;
    result.resize(length);

    while(s1.length() < length){
        s1.insert(0, 1, '0');
    }
    while(s2.length() < length){
        s2.insert(0, 1, '0');
    }

    unsigned char carry = 0;
    for (unsigned int i = length; i > 0; i--){
        const unsigned char current_sum = CHAR_TO_DIGIT(s1[i - 1]) + CHAR_TO_DIGIT(s2[i - 1]) + carry;

        result[i - 1] = DIGIT_TO_CHAR(current_sum % 10);
        carry = current_sum / 10;
    }

    if (carry){
        result.insert(0, 1, '1');
    }

    return result;
}

void divide_string_by_number(std::string a, unsigned int b, std::string& q, unsigned int& r){
    if (compare_strings(std::to_string(b), a)){
        q = "0";
        r = std::strtoull(a.c_str(), nullptr, 10);
        return;
    }

    r = 0;

    unsigned int current_index = 0;

    while(r < b){
        r = r * 10 + CHAR_TO_DIGIT(a[current_index++]);
    }

    const unsigned int length = a.length();

    while(true){
        q.append(1, DIGIT_TO_CHAR(r / b));
        r %= b;

        if (current_index == length){
            break;
        }

        r = r * 10 + CHAR_TO_DIGIT(a[current_index++]);

        while(r < b){
            if (current_index == length){
                break;
            }

            q.append(1, '0');
            r = r * 10 + CHAR_TO_DIGIT(a[current_index++]);
        }
    }
}

std::string multiply_strings(std::string a, std::string b){
    if (b.length() == 1){
        std::string result;

        unsigned int carry = 0;
        const unsigned int length = a.length();

        for (unsigned int i = length; i > 0; i--){
            const unsigned char product = CHAR_TO_DIGIT(a[i - 1]) * CHAR_TO_DIGIT(b[0]) + carry;

            result.insert(0, 1, DIGIT_TO_CHAR(product % 10));
            carry = product / 10;
        }

        if (carry){
            result.insert(0, 1, DIGIT_TO_CHAR(carry));
        }

        return result;
    }
    else{
        std::string result = "0";

        unsigned long long index = 0;
        while(b != "0"){
            std::string current_product = multiply_strings(a, std::to_string(b.back()));

            current_product.append(index, '0');

            result = add_strings(result, current_product);

            std::string tmp1;
            unsigned int tmp2;
            divide_string_by_number(a, 10, tmp1, tmp2);

            a = tmp1;
        }
        return result;
    }
}

unsigned int ceil_log_str(unsigned int base, std::string a){
    if (a == "0"){
        return 1;
    }

    unsigned int result = 0;
    while (a != "0"){
        std::string tmp1;
        unsigned int tmp2;

        result++;
        divide_string_by_number(a, base, tmp1, tmp2);

        a = tmp1;
    }

    return result;
}
