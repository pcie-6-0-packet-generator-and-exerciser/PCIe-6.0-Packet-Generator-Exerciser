#pragma once
#include <boost/dynamic_bitset.hpp>

boost::dynamic_bitset<> get_bits(const boost::dynamic_bitset<>& bits, size_t start_index, size_t end_index);
