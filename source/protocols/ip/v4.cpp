#include <arpa/inet.h>
#include <protocols/ip/v4.h>

namespace bro {
namespace proto {
namespace ip {
namespace v4 {

address::address(std::string const& addr) noexcept {
  string_to_address(addr, *this);
}

std::string address_to_string(uint32_t addr) noexcept {
  return inet_ntoa({addr});
}

bool string_to_address(std::string const& str_address,
                       uint32_t& address) noexcept {
  bool rc = (1 == inet_pton(AF_INET, str_address.c_str(), &address));
  return rc;
}

std::ostream& operator<<(std::ostream& strm, address const& address) {
  return strm << address_to_string(address);
}

}  // namespace v4
}  // namespace ip
}  // namespace proto
}  // namespace bro
