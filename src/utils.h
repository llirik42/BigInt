inline unsigned int get_max(unsigned int a, unsigned int b){
    return a > b ? a : b;
}
inline unsigned int get_min(unsigned int a, unsigned int b){
    return a > b ? b : a;
}
inline unsigned int char_to_digit(unsigned char c){
    return c - '0';
}
inline char digit_to_char(unsigned int d){
    return char(d + '0');
}

static unsigned int ceil_log(unsigned long long base, unsigned long long number){
    if (!number){
        return 1;
    }

    unsigned int result = 0;

    while (number){
        result++;
        number /= base;
    }

    return result;
}
