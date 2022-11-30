#pragma once
#include "ipv4.h"
#include "ipv6.h"

namespace jkl {
namespace proto {
/** @addtogroup proto
 *  @{
 */

/**
 * \brief ip v4/v6 address wrapper
 */
class ip_addr {
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
  ip_addr() = default;

  /**
   * ctor from string representation
   *
   * ctor from string for example "127.0.0.1" or "fe80::23a1:b152")
   */
  explicit ip_addr(std::string const& addr) noexcept;

  /**
   * ctor from ipv4
   */
  explicit ip_addr(ipv4 const& addr) noexcept
      : _dword{addr.get_data(), 0, 0, 0}, _version(version::e_v4) {}

  /**
   * ctor from ipv6
   */
  explicit ip_addr(ipv6 const& addr) noexcept;

  /**
   * ctor from ip_addr
   */
  ip_addr(ip_addr const& addr) noexcept
      : _qword{addr._qword[0], addr._qword[1]}, _version{addr._version} {}

  /**
   * assign operator from ipv4
   */
  ip_addr& operator=(ipv4 const& addr) noexcept {
    _dword[0] = addr.get_data();
    _dword[1] = _dword[2] = _dword[3] = 0;
    _version = version::e_v4;
    return *this;
  }

  /**
   * assign operator from ipv6
   */
  ip_addr& operator=(ipv6 const& addr) noexcept;

  /**
   * assign operator from ip_addr
   */
  ip_addr& operator=(ip_addr const& addr) noexcept;

  /**
   * operator less
   */
  bool operator<(ip_addr const& addr) const noexcept {
    return _qword[0] < addr._qword[0] ||
           (!(addr._qword[0] < _qword[0]) && _qword[1] < addr._qword[1]);
  }

  /**
   * operator equal
   */
  bool operator==(ip_addr const& addr) const noexcept {
    return _version == addr._version && _qword[0] == addr._qword[0] &&
           _qword[1] == addr._qword[1];
  }

  /**
   * operator not equal
   */
  bool operator!=(ip_addr const& addr) const noexcept {
    return !(*this == addr);
  }

  /**
   * operator&
   */
  ip_addr operator&(ip_addr const& addr) const noexcept;

  /**
   * create ipv4 address from current address
   */
  ipv4 to_v4() const noexcept { return ipv4(_dword[0]); }

  /**
   * create ipv6 address from current address
   */
  ipv6 to_v6() const noexcept { return ipv6(_qword[0], _qword[1]); }

  /**
   * get current address in reverse order
   */
  ip_addr reverse_order() const noexcept;

  /**
   * get address version
   *
   * @return address version
   */
  version get_version() const noexcept { return _version; }

  /**
   * get address as uint8_t *
   */
  uint8_t const* get_data() const noexcept { return _bytes; }

 private:
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
    uint64_t _qword[ipv6::e_qword_size];  ///< uint64_t array
    uint32_t _dword[ipv6::e_dword_size];  ///< uint32_t array
    uint8_t _bytes[ipv6::e_bytes_size];   ///< bytes array
  };
  version _version = version::e_none;  ///< address type
};

/**
 * convert address to string representation
 *
 * @param filled address
 * @return string (ex. "192.168.0.1" or "fe80::23a1:b152")
 */
std::string address_to_string(ip_addr const& address) noexcept;

/**
 * build address from string representation
 *
 * @param str_address string filled with address (ex. "192.168.0.1" or
 * "fe80::23a1:b152")
 * @param address to fill
 * @return true if operation succeed
 */
bool string_to_address(std::string const& str_address,
                       ip_addr& address) noexcept;

/**
 * put in ostream string address
 *
 * @param strm ostream value
 * @param address
 */
std::ostream& operator<<(std::ostream& strm, ip_addr const& address);

/** @} */  // end of proto

}  // namespace proto
}  // namespace jkl
