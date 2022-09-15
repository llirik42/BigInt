inline unsigned int get_max(unsigned int a, unsigned int b){
    return a > b ? a : b;
}
inline unsigned int char_to_digit(unsigned char c){
    return c - '0';
}
inline char digit_to_char(unsigned int d){
    return d + '0';
}


#define CHAR_TO_DIGIT(C) (int((C) - '0'))
#define DIGIT_TO_CHAR(D) (char((D) + '0'))

#define SIZE_OF_BYTE 8
#define TWO_TO_THE_POWER_OF_BYTE_SIZE 256
