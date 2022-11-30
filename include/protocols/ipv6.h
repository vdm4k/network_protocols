#pragma once
#include <string>

namespace jkl {
namespace proto {

/** @addtogroup proto
 *  @{
 */
/**
 * \brief ip v6 address wrapper
 */
class ipv6 {
 public:
  enum {
    e_bytes_size = 16,  ///< address size in bytes
    e_dword_size = 4,   ///< address size in dword
    e_qword_size = 2    ///< address size in qword
  };

  /**
   * default constructor
   */
  ipv6() = default;

  /**
   * copy ctor
   */
  ipv6(ipv6 const& addr) = default;

  /**
   * ctor from string representation
   *
   * ctor from string for example "fe80::23a1:b152"
   */
  explicit ipv6(std::string const& addr) noexcept;

  /**
   * ctor from uint64_t array
   */
  explicit ipv6(uint64_t const (&addr)[e_qword_size]) noexcept
      : ipv6(addr[0], addr[1]) {}

  /**
   * ctor from uint32_t array
   */
  explicit ipv6(uint32_t const (&addr)[e_dword_size]) noexcept
      : ipv6(addr[0], addr[1], addr[2], addr[3]) {}

  /**
   * ctor from byte array
   */
  explicit ipv6(uint8_t const (&addr)[e_bytes_size]) noexcept;

  /**
   * ctor from uint64_t's
   */
  ipv6(uint64_t qword1, uint64_t qword2) noexcept : _qword{qword1, qword2} {}

  /**
   * ctor from uint32_t's
   */
  ipv6(uint32_t dword1, uint32_t dword2, uint32_t dword3,
       uint32_t dword4) noexcept
      : _dword{dword1, dword2, dword3, dword4} {}

  /**
   * ctor from bytes
   */
  ipv6(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4,
       uint8_t byte5, uint8_t byte6, uint8_t byte7, uint8_t byte8,
       uint8_t byte9, uint8_t byte10, uint8_t byte11, uint8_t byte12,
       uint8_t byte13, uint8_t byte14, uint8_t byte15, uint8_t byte16) noexcept
      : _byte1(byte1),
        _byte2(byte2),
        _byte3(byte3),
        _byte4(byte4),
        _byte5(byte5),
        _byte6(byte6),
        _byte7(byte7),
        _byte8(byte8),
        _byte9(byte9),
        _byte10(byte10),
        _byte11(byte11),
        _byte12(byte12),
        _byte13(byte13),
        _byte14(byte14),
        _byte15(byte15),
        _byte16(byte16) {}

  /**
   * assign operator
   */
  ipv6& operator=(ipv6 const& r) noexcept {
    _qword[0] = r._qword[0];
    _qword[1] = r._qword[1];
    return *this;
  }

  /**
   * operator less
   */
  bool operator<(ipv6 const& r) const noexcept {
    return _qword[0] < r._qword[0] ||
           (!(r._qword[0] < _qword[0]) && _qword[1] < r._qword[1]);
  }

  /**
   * operator equal
   */
  bool operator==(ipv6 const& r) const noexcept {
    return _qword[0] == r._qword[0] && _qword[1] == r._qword[1];
  }

  /**
   * operator not equal
   */
  bool operator!=(ipv6 const& r) const noexcept { return !(*this == r); }

  /**
   * operator&
   */
  ipv6 operator&(ipv6 const& r) const noexcept {
    return ipv6(_qword[0] & r._qword[0], _qword[1] & r._qword[1]);
  }

  /**
   * get current address in reverse order
   */
  ipv6 reverse_order() const noexcept {
    return ipv6(__builtin_bswap64(_qword[1]), __builtin_bswap64(_qword[0]));
  }

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
    uint64_t _qword[e_qword_size];  ///< uint64_t array
    uint32_t _dword[e_dword_size];  ///< uint32_t array
    uint8_t _bytes[e_bytes_size];   ///< bytes array
  };

  friend std::string address_to_string(ipv6 const& address) noexcept;
  friend bool string_to_address(std::string const& str_address,
                                ipv6& address) noexcept;
};

/**
 * convert address to string representation
 *
 * @param filled address
 * @return string (ex. "fe80::23a1:b152")
 */
std::string address_to_string(
    uint8_t const (&addr)[ipv6::e_bytes_size]) noexcept;

/**
 * convert address to string representation
 *
 * @param address
 * @return string (ex. "fe80::23a1:b152")
 */
inline std::string address_to_string(ipv6 const& address) noexcept {
  return address_to_string(address._bytes);
}

/**
 * build address from string representation
 *
 * @param str_address string filled with address
 * @param address to fill
 * @return true if operation succeed
 */
bool string_to_address(std::string const& str_address,
                       uint8_t const (&addr)[ipv6::e_bytes_size]) noexcept;

/**
 * build address from string representation
 *
 * @param str_address string filled with address
 * @param address to fill
 * @return true if operation succeed
 */
inline bool string_to_address(std::string const& str_address,
                              ipv6& address) noexcept {
  return string_to_address(str_address, address._bytes);
}

/**
 * put in ostream string address
 *
 * @param strm ostream value
 * @param address
 */
std::ostream& operator<<(std::ostream& strm, ipv6 const& address);
/** @} */  // end of proto

}  // namespace proto
}  // namespace jkl
