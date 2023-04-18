#ifdef __linux__
#include <arpa/inet.h>
#endif
#include <protocols/ip/v6.h>
#include <string.h>

namespace bro::net::proto::ip::v6 {

address::address(std::string const &addr) noexcept {
  string_to_address(addr, *this);
}

#ifdef __linux__
address::address(in6_addr const &addr) noexcept {
  memcpy(_bytes, &addr, ip::v6::address::e_bytes_size);
}

address &address::operator=(in6_addr const &addr) noexcept {
  memcpy(_bytes, &addr, ip::v6::address::e_bytes_size);
  return *this;
}

in6_addr address::to_native() const noexcept {
  in6_addr addr;
  memcpy(&addr, _bytes, ip::v6::address::e_bytes_size);
  return addr;
}

#endif // __linux__

address::address(uint8_t const (&addr)[e_bytes_size]) noexcept {
  memcpy(_bytes, addr, e_bytes_size);
}

std::string address::to_string() const {
  return address_to_string(_bytes);
}

address address::reverse_order() const noexcept {
  return address(__builtin_bswap64(_qword[1]), __builtin_bswap64(_qword[0]));
}

std::string address_to_string(uint8_t const (&addr)[address::e_bytes_size]) {
  char buffer[256] = {0};
#ifdef __linux__
  inet_ntop(AF_INET6, addr, buffer, sizeof(buffer));
#endif //__linux__
  return buffer;
}

bool string_to_address(std::string const &str_address, uint8_t const (&addr)[address::e_bytes_size]) noexcept {
  bool rc{false};
#ifdef __linux__
  rc = 1 == inet_pton(AF_INET6, str_address.c_str(), (void *) addr);
#endif // __linux__
  return rc;
}

std::ostream &operator<<(std::ostream &strm, address const &address) {
  return strm << address_to_string(address);
}

} // namespace bro::net::proto::ip::v6
