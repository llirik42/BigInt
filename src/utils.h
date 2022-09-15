inline unsigned int get_max(unsigned int a, unsigned int b){
    return a > b ? a : b;
}
inline unsigned int char_to_digit(unsigned char c){
    return c - '0';
}
inline char digit_to_char(unsigned int d){
    return char(d + '0');
}
