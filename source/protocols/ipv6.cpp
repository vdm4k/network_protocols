#include <arpa/inet.h>
#include <protocols/ipv6.h>
#include <string.h>

namespace jkl {
namespace protocols {

ipv6::ipv6(std::string const& addr) noexcept { string_to_address(addr, *this); }

ipv6::ipv6(uint8_t const (&addr)[e_bytes_size]) noexcept {
  memcpy(_bytes, addr, e_bytes_size);
}

std::string address_to_string(
    uint8_t const (&addr)[ipv6::e_bytes_size]) noexcept {
  char buffer[256] = {0};
  inet_ntop(AF_INET6, addr, buffer, sizeof(buffer));
  return buffer;
}

bool string_to_address(std::string const& str_address,
                       uint8_t const (&addr)[ipv6::e_bytes_size]) noexcept {
  return 1 == inet_pton(AF_INET6, str_address.c_str(), (void*)addr);
}

std::ostream& operator<<(std::ostream& strm, ipv6 const& address) {
  return strm << address_to_string(address);
}
}  // namespace protocols
}  // namespace jkl
