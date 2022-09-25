#include "big_int.h"

int main() {
    auto a = std::make_tuple(4, 5);

    std::cout << std::get<1>(a);

    return 0;
}
