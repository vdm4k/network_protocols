#include <arpa/inet.h>
#include <protocols/ipv4.h>

namespace jkl {
namespace protocols {

ipv4::ipv4(std::string const& addr) noexcept { string_to_address(addr, *this); }

std::string address_to_string(uint32_t addr) noexcept {
  return inet_ntoa({addr});
}

bool string_to_address(std::string const& str_address,
                       uint32_t& address) noexcept {
  bool rc = (1 == inet_pton(AF_INET, str_address.c_str(), &address));
  return rc;
}

std::ostream& operator<<(std::ostream& strm, ipv4 const& address) {
  return strm << address_to_string(address);
}
}  // namespace protocols
}  // namespace jkl
