#include <arpa/inet.h>
#include <protocols/ip_addr.h>
#include <string.h>

namespace jkl {
namespace proto {

ip_addr::ip_addr(std::string const& addr) noexcept {
  if (addr.find(':') == std::string::npos) {
    if (string_to_address(addr, _dword[0])) {
      _version = version::e_v4;
    }
  } else {
    if (string_to_address(addr, _bytes)) {
      _version = version::e_v6;
    }
  }
}

ip_addr::ip_addr(ipv6 const& addr) noexcept : _version(version::e_v6) {
  memcpy(_bytes, addr.get_data(), ipv6::e_bytes_size);
}

ip_addr& ip_addr::operator=(ipv6 const& addr) noexcept {
  memcpy(_bytes, addr.get_data(), ipv6::e_bytes_size);
  _version = version::e_v6;
  return *this;
}

ip_addr& ip_addr::operator=(ip_addr const& addr) noexcept {
  memcpy(_bytes, addr.get_data(), ipv6::e_bytes_size);
  _version = addr.get_version();
  return *this;
}

ip_addr ip_addr::operator&(ip_addr const& addr) const noexcept {
  switch (_version) {
    case version::e_v4:
      return ip_addr(ipv4(_dword[0] & addr._dword[0]));
    case version::e_v6:
      return ip_addr(
          ipv6(_qword[0] & addr._qword[0], _qword[1] & addr._qword[1]));
    default:
      break;
  }
  return {};
}

ip_addr ip_addr::reverse_order() const noexcept {
  switch (_version) {
    case version::e_v4:
      return ip_addr(to_v4().reverse_order());
    case version::e_v6:
      return ip_addr(to_v6().reverse_order());
    default:
      break;
  }
  return {};
}

std::string address_to_string(ip_addr const& address) noexcept {
  switch (address.get_version()) {
    case ip_addr::version::e_v4:
      return address_to_string(address.to_v4());
    case ip_addr::version::e_v6:
      return address_to_string(address.to_v6());
    default:
      break;
  }
  return {};
}

bool string_to_address(std::string const& str_addr, ip_addr& addr) noexcept {
  addr = ip_addr(str_addr);
  return addr.get_version() != ip_addr::version::e_none;
}

std::ostream& operator<<(std::ostream& strm, ip_addr const& address) {
  switch (address.get_version()) {
    case ip_addr::version::e_v4:
      strm << address.to_v4();
      break;
    case ip_addr::version::e_v6:
      strm << address.to_v6();
      break;
    default:
      break;
  }
  return strm;
}
}  // namespace proto
}  // namespace jkl
