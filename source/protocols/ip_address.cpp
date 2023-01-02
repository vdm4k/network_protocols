#include <arpa/inet.h>
#include <protocols/ip_address.h>
#include <string.h>

namespace jkl {
namespace proto {

ip_address::ip_address(std::string const& addr) noexcept {
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

ip_address::ip_address(ipv6 const& addr) noexcept : _version(version::e_v6) {
  memcpy(_bytes, addr.get_data(), ipv6::e_bytes_size);
}

ip_address& ip_address::operator=(ipv6 const& addr) noexcept {
  memcpy(_bytes, addr.get_data(), ipv6::e_bytes_size);
  _version = version::e_v6;
  return *this;
}

ip_address& ip_address::operator=(ip_address const& addr) noexcept {
  memcpy(_bytes, addr.get_data(), ipv6::e_bytes_size);
  _version = addr.get_version();
  return *this;
}

ip_address ip_address::operator&(ip_address const& addr) const noexcept {
  switch (_version) {
    case version::e_v4:
      return ip_address(ipv4(_dword[0] & addr._dword[0]));
    case version::e_v6:
      return ip_address(
          ipv6(_qword[0] & addr._qword[0], _qword[1] & addr._qword[1]));
    default:
      break;
  }
  return {};
}

ip_address ip_address::reverse_order() const noexcept {
  switch (_version) {
    case version::e_v4:
      return ip_address(to_v4().reverse_order());
    case version::e_v6:
      return ip_address(to_v6().reverse_order());
    default:
      break;
  }
  return {};
}

std::string address_to_string(ip_address const& address) noexcept {
  switch (address.get_version()) {
    case ip_address::version::e_v4:
      return address_to_string(address.to_v4());
    case ip_address::version::e_v6:
      return address_to_string(address.to_v6());
    default:
      break;
  }
  return {};
}

bool string_to_address(std::string const& str_addr, ip_address& addr) noexcept {
  addr = ip_address(str_addr);
  return addr.get_version() != ip_address::version::e_none;
}

std::ostream& operator<<(std::ostream& strm, ip_address const& address) {
  switch (address.get_version()) {
    case ip_address::version::e_v4:
      strm << address.to_v4();
      break;
    case ip_address::version::e_v6:
      strm << address.to_v6();
      break;
    default:
      break;
  }
  return strm;
}
}  // namespace proto
}  // namespace jkl
