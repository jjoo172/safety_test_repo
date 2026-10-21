#pragma once

#include <cstdint>
#include <vector>

namespace app {

int mean(const std::vector<int>& values);

double median(std::vector<int> values);

// Returns a mask with the low `bits` bits set, e.g. mask_for(4) == 0xF.
std::uint32_t mask_for(unsigned bits);

}  // namespace app
