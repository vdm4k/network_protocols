#include <arpa/inet.h>
#include <protocols/ip/v4.h>

namespace bro::net::proto::ip::v4 {

address::address(std::string const &addr) { string_to_address(addr, *this); }

std::string address::to_string() const { return address_to_string(_data); }

std::string address_to_string(uint32_t addr) { return inet_ntoa({addr}); }

bool string_to_address(std::string const &str_address,
                       uint32_t &address) noexcept {
  bool rc = (1 == inet_pton(AF_INET, str_address.c_str(), &address));
  return rc;
}

std::ostream &operator<<(std::ostream &strm, address const &address) {
  return strm << address_to_string(address);
}

} // namespace bro::net::proto::ip::v4
