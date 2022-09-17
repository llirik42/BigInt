#include "smart_vector.h"
#include "numeric_string.h"
#include "utils.h"

inline const unsigned long long BASE = 4294967296;

SmartVector::SmartVector(){
    this->length = 1;

    this->data = new Block[1];
    this->data[0] = 0;
}
SmartVector::SmartVector(unsigned long long number){
    this->length = ceil_log(BASE, number);

    this->data = new Block[length];

    for (unsigned int i = length; i > 0; i--){
        this->data[i - 1] = number % BASE;
        number /= BASE;
    }
}
SmartVector::SmartVector(const std::string& str){
    NumericString numerical_str = NumericString(str);

    this->length = ceil_log_numerical_str(BASE, numerical_str);

    this->data = new Block[length];

    for (unsigned int i = this->length; i > 0; i--){
        data[i - 1] = numerical_str % BASE;
        numerical_str /= BASE;
    }
}
SmartVector::SmartVector(SmartVector&& v) noexcept{
    this->data = v.data;
    this->length = v.length;
    v.data = nullptr;
}
SmartVector::SmartVector(const SmartVector& v){
    this->length = v.length;
    this->data = new Block[this->length];

    for (unsigned int i = 0; i < this->length; i++){
        this->data[i] = v.data[i];
    }
}
SmartVector::~SmartVector(){
    delete[] this->data;
}

SmartVector& SmartVector::operator=(const SmartVector& v){
    if (&v == this){
        return (*this);
    }

    this->length = v.length;
    delete[] this->data;

    this->data = new Block[this->length];

    for (unsigned int i = 0; i < this->length; i++){
        this->data[i] = v.data[i];
    }

    return (*this);
}
SmartVector& SmartVector::operator=(SmartVector&& v) noexcept{
    this->data = v.data;
    this->length = v.length;
    v.data = nullptr;

    return (*this);
}

SmartVector& SmartVector::operator+=(const SmartVector& v){
    const unsigned int max_length = get_max(this->length, v.length);

    this->extend_and_copy(max_length - this->length);

    unsigned int carry = 0;
    for (unsigned int i = 0; i < max_length; i++){
        unsigned long long current_sum = this->data[this->length - i - 1] + carry;

        if (v.length > i){
            current_sum += v.data[v.length - i - 1];
        }

        this->data[this->length - i - 1] = current_sum % BASE;
        carry = current_sum / BASE;
    }

    if (carry){
        this->extend_and_copy(1);
        this->data[0] = carry;
    }

    return (*this);
}
SmartVector& SmartVector::operator*=(const SmartVector& v){
    if (SmartVector(0) == v){
        *this = SmartVector(0);
        return (*this);
    }

    SmartVector result = *this;

    if (v.length == 1){
        unsigned int carry = 0;

        const unsigned long long operand_only_digit = v.data[0];
        for (unsigned int i = this->length; i > 0; i--){
            const unsigned long long current_digit = this->data[i - 1];

            const unsigned long long product = current_digit * operand_only_digit + carry;

            result.data[i - 1] = product % BASE;

            carry = product / BASE;
        }

        if (carry){
            result.extend_and_copy(1);
            result.data[0] = carry;
        }

    }
    else{
        result = SmartVector(0);

        for (unsigned int i = v.length; i > 0; i--){
            SmartVector current_digit = SmartVector(v.data[i - 1]);

            SmartVector current_product = (*this) * current_digit;

            if (current_product != SmartVector(0)){
                current_product.append_zero_blocks(v.length - i);
            }


            result += current_product;
        }
    }


    *this = result;
    return *this;
}
SmartVector& SmartVector::operator-=(const SmartVector& v){
    SmartVector operand = v;

    operand.extend_and_copy(this->length - operand.length);

    SmartVector result = *this;

    unsigned int carry = 0;
    bool f = false;
    for (unsigned int i = this->length; i > 0; i--){
        unsigned long long digit1 = this->data[i - 1];

        if (carry){
            f = digit1 == 0;

            if (digit1 == 0){
                digit1 = BASE;
            }

            digit1 -= carry;
            carry = 0;
        }
        else{
            f = false;
        }

        const unsigned long long digit2 = operand.data[i - 1];

        if (digit1 < digit2){
            digit1 += BASE;
            carry = 1;
        }

        if (f){
            carry = 1;
        }

        const unsigned long long current_difference = digit1 - digit2;

        result.data[i - 1] = current_difference;
    }

    result.reduce_first_zero_blocks();

    *this = result;
    return *this;
}
SmartVector& SmartVector::operator/=(const SmartVector& v){
    if (v > *this){
        *this = SmartVector(0);
        return *this;
    }

    SmartVector r = SmartVector(0);

    unsigned int current_index = 0;

    SmartVector result;

    while(v > r){
        r = r * SmartVector(BASE) + SmartVector(this->data[current_index++]); //TODO SmartVector(BASE)
    }
    while(true){
        unsigned long long current_digit = 0;
        while(r >= v){
            r -= v;
            current_digit++;
        }

        result = result * SmartVector(BASE) + SmartVector(current_digit);

        if (current_index == this->length){
            break;
        }

        r = r * SmartVector(BASE) + SmartVector(this->data[current_index++]); //TODO SmartVector(BASE)

        while(v > r){
            if (current_index == this->length){
                break;
            }
            result.append_zero_blocks(1);
            r = r * SmartVector(BASE) + SmartVector(this->data[current_index++]); //TODO SmartVector(BASE)
        }
    }

    *this = result;
    return *this;
}
SmartVector& SmartVector::operator%=(const SmartVector& v){
    if (v > *this){
        return *this;
    }

    SmartVector result = SmartVector(0);

    unsigned int current_index = 0;

    while(v > result){
        result = result * SmartVector(BASE) + SmartVector(this->data[current_index++]); //TODO SmartVector(BASE)
    }

    while(true){
        while(result >= v){
            result -= v;
        }

        if (current_index == this->length){
            break;
        }

        result = result * SmartVector(BASE) + SmartVector(this->data[current_index++]); //TODO SmartVector(BASE)

        while(v > result){
            if (current_index == this->length){
                break;
            }
            result = result * SmartVector(BASE) + SmartVector(this->data[current_index++]); //TODO SmartVector(BASE)
        }
    }

    *this = result;
    return *this;
}
SmartVector& SmartVector::operator^=(const SmartVector& v){

}
SmartVector& SmartVector::operator&=(const SmartVector& v){

}
SmartVector& SmartVector::operator|=(const SmartVector& v){
    SmartVector result = *this;

}

bool SmartVector::operator==(const SmartVector& v) const{
    if (this->length != v.length){
        return false;
    }

    for (unsigned int i = v.length; i > 0; i--){
        if (this->data[i - 1] != v.data[i - 1]){
            return false;
        }
    }

    return true;
}
bool SmartVector::operator!=(const SmartVector& v) const{
    return !(*this == v);
}
bool SmartVector::operator>(const SmartVector& v) const{
    if (this->length != v.length){
        return this->length > v.length;
    }
    for (unsigned int i = 0; i < v.length; i++){
        if (this->data[i] != v.data[i]){
            return this->data[i] > v.data[i];
        }
    }

    return false;
}
bool SmartVector::operator>=(const SmartVector& v) const{
    return *this == v || *this > v;
}

void SmartVector::extend_and_copy(unsigned int delta){
    SmartVector tmp = (*this);

    this->length += delta;
    this->data = new Block[this->length];

    for (unsigned int i = 0; i < delta; i++){
        this->data[i] = 0;
    }

    for (unsigned int i = 0; i < tmp.length; i++){
        this->data[this->length - i - 1] = tmp.data[tmp.length - i - 1];
    }
}
void SmartVector::append_zero_blocks(unsigned int count){
    SmartVector tmp = *this;

    delete[] this->data;
    this->data = new Block[this->length + count];

    for (unsigned int i = 0; i < this->length; i++){
        this->data[i] = tmp.data[i];
    }
    for (unsigned int i = 0; i < count; i++){
        this->data[this->length + i] = 0;
    }

    this->length += count;
}
void SmartVector::reduce_first_block(){
    SmartVector tmp = *this;

    this->length--;
    delete[] this->data;
    this->data = new Block[this->length];

    for (unsigned int i = this->length; i > 0; i--){
        this->data[i - 1] = tmp.data[i];
    }
}
void SmartVector::reduce_first_zero_blocks(){
    while(this->length > 1 && this->data[0] == 0){
        this->reduce_first_block();
    }
}

SmartVector::operator std::string() const{
    NumericString result = NumericString(0);

    NumericString m = NumericString(BASE);
    NumericString current_m = NumericString(1);

    for (unsigned int i = this->length; i > 0; i--){
        result += current_m * NumericString(this->data[i - 1]);

        current_m = current_m * m;
    }

    return std::string(result);
}

SmartVector operator+(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = SmartVector(0);

    result += v1;
    result += v2;

    return result;
}
SmartVector operator-(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = v1;
    result -= v2;
    return result;
}
SmartVector operator*(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = v1;
    result *= v2;
    return result;
}
SmartVector operator/(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = v1;
    result /= v2;
    return result;
}
SmartVector operator%(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = v1;
    result %= v2;
    return result;
}
SmartVector operator^(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = v1;
    result ^= v2;
    return result;
}
SmartVector operator&(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = v1;
    result &= v2;
    return result;
}
SmartVector operator|(const SmartVector& v1, const SmartVector& v2){
    SmartVector result = v1;
    result |= v2;
    return result;
}

std::ostream& operator<<(std::ostream& out, const SmartVector &b){
    out << std::string(b);

    return out;
}
