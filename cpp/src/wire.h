#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace app {

struct Header {
    std::uint32_t magic;
    std::uint16_t version;
    std::uint16_t flags;
    std::uint32_t length;
};

// Reads a frame header that starts `offset` bytes into `buf`.
std::optional<Header> parse_header(const std::vector<std::uint8_t>& buf,
                                   std::size_t offset);

// Sums the payload as little 32-bit words; trailing bytes are ignored.
std::uint32_t word_checksum(const std::uint8_t* data, std::size_t len);

}  // namespace app
