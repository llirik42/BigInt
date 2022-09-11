#include <iostream>
#include "big_int.h"

#define SIZE_OF_BYTE 8

// 0 ... 7
#define GET_BIT_8(N, I) ((1 << (SIZE_OF_BYTE - (I) - 1) & (N)) >> (SIZE_OF_BYTE - (I) - 1))
#define SET_BIT_8(N, I, V) N = (V) ? ((1 << (SIZE_OF_BYTE - (I) - 1)) | (N)) : (~(1 << (SIZE_OF_BYTE - (I) - 1)) & (N));



unsigned int ceil_div(unsigned a, unsigned b){
    if (b == 0){
        return 0;
    }

    unsigned int result = 0;
    while (a){
        result++;
        if (a < b){
            break;
        }

        a -= b;
    }

    return result;
}

bool t(std::string str){
    const unsigned int length = str.length();

    if (!length){
        return false;
    }

    if (length == 1 && !std::isdigit(str[0])){
        return false;
    }

    if ((length != 1 && str[0] == '0') || (length != 2 && str[0] == '-' && str[1] == '0')){
        return false;
    }

    for (unsigned int i = 1; i < length; i++){
        if (!std::isdigit(str[i])){
            return false;
        }
    }

    return true;
}

int main() {
    Big


    std::cout << t("");

    return 0;
}
