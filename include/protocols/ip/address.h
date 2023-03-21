#pragma once
#include "v4.h"
#include "v6.h"
#ifdef __linux__
#include <netinet/in.h>
#endif

namespace bro::net::proto::ip {
/** @addtogroup proto
 *  @{
 */

/**
 * \brief ip v4/v6 address wrapper
 */
class address {
 public:
  /**
   * ip address version
   */
  enum class version : uint16_t {
    e_v4,   ///< ipv4 address
    e_v6,   ///< ipv6 address
    e_none  ///< address not set
  };

  /**
   * default constructor
   */
  address() = default;

  /**
   * ctor from string representation
   *
   * ctor from string for example "127.0.0.1" or "fe80::23a1:b152")
   */
  explicit address(std::string const& addr) noexcept;

#ifdef __linux__
  /**
   * ctor from ipv4 native linux
   */
  address(in_addr const& addr) noexcept
      : _dword{addr.s_addr, 0, 0, 0}, _version(version::e_v4) {}

  /**
   * ctor from ipv6 native linux
   */
  address(in6_addr const& addr) noexcept;
#endif

  /**
   * ctor from ipv4
   */
  address(ip::v4::address const& addr) noexcept
      : _dword{addr.get_data(), 0, 0, 0}, _version(version::e_v4) {}

  /**
   * ctor from ipv6
   */
  address(ip::v6::address const& addr) noexcept;

  /**
   * ctor from address
   */
  address(address const& addr) noexcept
      : _qword{addr._qword[0], addr._qword[1]}, _version{addr._version} {}

  /**
   * assign operator from ipv4
   */
  address& operator=(ip::v4::address const& addr) noexcept {
    _dword[0] = addr.get_data();
    _dword[1] = _dword[2] = _dword[3] = 0;
    _version = version::e_v4;
    return *this;
  }

  /**
   * assign operator from ipv6
   */
  address& operator=(ip::v6::address const& addr) noexcept;

  /**
   * assign operator from ip_addr
   */
  address& operator=(address const& addr) noexcept;

  /**
   * operator less
   */
  bool operator<(address const& addr) const noexcept {
    return _qword[0] < addr._qword[0] ||
           (!(addr._qword[0] < _qword[0]) && _qword[1] < addr._qword[1]);
  }

  /**
   * operator equal
   */
  bool operator==(address const& addr) const noexcept {
    return _version == addr._version && _qword[0] == addr._qword[0] &&
           _qword[1] == addr._qword[1];
  }

  /**
   * operator not equal
   */
  bool operator!=(address const& addr) const noexcept {
    return !(*this == addr);
  }

  /**
   * operator&
   */
  address operator&(address const& addr) const noexcept;

  /**
   * create ipv4 address from current address
   */
  ip::v4::address to_v4() const noexcept { return ip::v4::address(_dword[0]); }

  /**
   * create ipv6 address from current address
   */
  ip::v6::address to_v6() const noexcept {
    return ip::v6::address(_qword[0], _qword[1]);
  }

#ifdef __linux__
  /**
   * get native discriptor
   */
  in_addr to_native_v4() const noexcept { return {_dword[0]}; }

  /**
   * get native discriptor
   */
  in6_addr to_native_v6() const noexcept;
#endif

  /**
   * get current address in reverse order
   */
  address reverse_order() const noexcept;

  /**
   * get address version
   *
   * @return address version
   */
  version get_version() const noexcept { return _version; }

  /**
   * convert address to string representation
   *
   * @return string (ex. "192.168.0.1" or "fe80::23a1:b152")
   */
  std::string to_string() const;

  /**
   * get address as uint8_t *
   */
  uint8_t const* get_data() const noexcept { return _bytes; }

 private:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#pragma GCC diagnostic ignored "-Wnested-anon-types"
  union {
    struct {
      uint8_t _byte1;   ///< byte 1
      uint8_t _byte2;   ///< byte 2
      uint8_t _byte3;   ///< byte 3
      uint8_t _byte4;   ///< byte 4
      uint8_t _byte5;   ///< byte 5
      uint8_t _byte6;   ///< byte 6
      uint8_t _byte7;   ///< byte 7
      uint8_t _byte8;   ///< byte 8
      uint8_t _byte9;   ///< byte 9
      uint8_t _byte10;  ///< byte 10
      uint8_t _byte11;  ///< byte 11
      uint8_t _byte12;  ///< byte 12
      uint8_t _byte13;  ///< byte 13
      uint8_t _byte14;  ///< byte 14
      uint8_t _byte15;  ///< byte 15
      uint8_t _byte16;  ///< byte 16
    };
    uint64_t _qword[ip::v6::address::e_qword_size];  ///< uint64_t array
    uint32_t _dword[ip::v6::address::e_dword_size];  ///< uint32_t array
    uint8_t _bytes[ip::v6::address::e_bytes_size];   ///< bytes array
  };
#pragma GCC diagnostic pop
  version _version = version::e_none;  ///< address type
};

/**
 * convert address to string representation
 *
 * @param filled address
 * @return string (ex. "192.168.0.1" or "fe80::23a1:b152")
 */
inline std::string address_to_string(address const& address) {
  return address.to_string();
}

/**
 * build address from string representation
 *
 * @param str_address string filled with address (ex. "192.168.0.1" or
 * "fe80::23a1:b152")
 * @param address to fill
 * @return true if operation succeed
 */
bool string_to_address(std::string const& str_address,
                       address& address) noexcept;

/**
 * put in ostream string address
 *
 * @param strm ostream value
 * @param address
 */
std::ostream& operator<<(std::ostream& strm, address const& address);

/** @} */  // end of proto

}  // namespace bro::net::proto::ip
