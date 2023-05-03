#include "get_bits.h"

boost::dynamic_bitset<> get_bits(const boost::dynamic_bitset<>& bits, size_t start_index, size_t end_index) {
    size_t length = end_index - start_index + 1;
    boost::dynamic_bitset<> result(length);
    for (size_t i = 0; i < length; ++i) {
        result[i] = bits[start_index + i];
    }
    return result;
}