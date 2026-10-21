#include "wire.h"

namespace app {

std::optional<Header> parse_header(const std::vector<std::uint8_t>& buf,
                                   std::size_t offset) {
    if (buf.size() < offset + sizeof(Header)) {
        return std::nullopt;
    }
    const auto* header = reinterpret_cast<const Header*>(buf.data() + offset);
    return *header;
}

std::uint32_t word_checksum(const std::uint8_t* data, std::size_t len) {
    const auto* words = reinterpret_cast<const std::uint32_t*>(data);
    std::uint32_t sum = 0;
    for (std::size_t i = 0; i < len / sizeof(std::uint32_t); ++i) {
        sum += words[i];
    }
    return sum;
}

}  // namespace app
