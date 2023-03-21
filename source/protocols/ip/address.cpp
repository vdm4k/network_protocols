#include <arpa/inet.h>
#include <protocols/ip/address.h>
#include <string.h>

namespace bro::net::proto::ip {

address::address(std::string const& addr) noexcept {
  if (addr.find(':') == std::string::npos) {
    if (ip::v4::string_to_address(addr, _dword[0])) {
      _version = version::e_v4;
    }
  } else {
    if (ip::v6::string_to_address(addr, _bytes)) {
      _version = version::e_v6;
    }
  }
}

#ifdef __linux__
address::address(in6_addr const& addr) noexcept : _version(version::e_v6) {
  memcpy(_bytes, &addr, ip::v6::address::e_bytes_size);
}

in6_addr address::to_native_v6() const noexcept {
  in6_addr addr;
  memcpy(&addr, _bytes, ip::v6::address::e_bytes_size);
  return addr;
}

#endif

address::address(ip::v6::address const& addr) noexcept
    : _version(version::e_v6) {
  memcpy(_bytes, addr.get_data(), ip::v6::address::e_bytes_size);
}

address& address::operator=(ip::v6::address const& addr) noexcept {
  memcpy(_bytes, addr.get_data(), ip::v6::address::e_bytes_size);
  _version = version::e_v6;
  return *this;
}

address& address::operator=(address const& addr) noexcept {
  memcpy(_bytes, addr.get_data(), ip::v6::address::e_bytes_size);
  _version = addr.get_version();
  return *this;
}

address address::operator&(address const& addr) const noexcept {
  switch (_version) {
    case version::e_v4:
      return address(ip::v4::address(_dword[0] & addr._dword[0]));
    case version::e_v6:
      return address(ip::v6::address(_qword[0] & addr._qword[0],
                                     _qword[1] & addr._qword[1]));
    default:
      break;
  }
  return {};
}

address address::reverse_order() const noexcept {
  switch (_version) {
    case version::e_v4:
      return address(to_v4().reverse_order());
    case version::e_v6:
      return address(to_v6().reverse_order());
    default:
      break;
  }
  return {};
}

std::string address::to_string() const {
  switch (get_version()) {
    case version::e_v4:
      return address_to_string(to_v4());
    case address::version::e_v6:
      return address_to_string(to_v6());
    default:
      break;
  }
  return {};
}

bool string_to_address(std::string const& str_addr, address& addr) noexcept {
  addr = address(str_addr);
  return addr.get_version() != address::version::e_none;
}

std::ostream& operator<<(std::ostream& strm, address const& address) {
  switch (address.get_version()) {
    case address::version::e_v4:
      strm << address.to_v4();
      break;
    case address::version::e_v6:
      strm << address.to_v6();
      break;
    default:
      break;
  }
  return strm;
}
}  // namespace bro::net::proto::ip
