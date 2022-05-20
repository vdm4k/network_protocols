#pragma once
#include <string>

namespace jkl {
namespace protocols {

/** @defgroup protocols
 *  @{
 */

/**
 * \brief ip v4 address wrapper
 */
class ipv4 {
 public:
  enum {
    e_bytes_size = 4  ///< address size in bytes
  };

  /**
   * default constructor
   */
  ipv4() = default;

  /**
   * copy ctor
   */
  ipv4(ipv4 const& addr) = default;

  /**
   * ctor from string representation
   *
   * ctor from string for example "127.0.0.1"
   */
  explicit ipv4(std::string const& addr) noexcept;

  /**
   * ctor from uint32_t
   */
  explicit ipv4(uint32_t addr) noexcept : _data(addr) {}

  /**
   * ctor from byte array
   */
  explicit ipv4(uint8_t const (&bytes)[e_bytes_size]) noexcept
      : _byte1(bytes[0]),
        _byte2(bytes[1]),
        _byte3(bytes[2]),
        _byte4(bytes[3]) {}

  /**
   * ctor from bytes
   *
   * to build like 192,168,0,1
   */
  ipv4(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) noexcept
      : _byte1(byte1), _byte2(byte2), _byte3(byte3), _byte4(byte4) {}

  /**
   * get current address in reverse order
   */
  ipv4 reverse_order() const noexcept { return ipv4(__builtin_bswap32(_data)); }

  /**
   * assign operator
   */
  ipv4& operator=(ipv4 const& r) noexcept {
    _data = r._data;
    return *this;
  }

  /**
   * operator less
   */
  bool operator<(ipv4 const& r) const noexcept { return _data < r._data; }

  /**
   * operator equal
   */
  bool operator==(ipv4 const& r) const noexcept { return _data == r._data; }

  /**
   * operator not equal
   */
  bool operator!=(ipv4 const& r) const noexcept { return !(_data == r._data); }

  /**
   * operator&
   */
  ipv4 operator&(ipv4 const& r) const noexcept { return ipv4(_data & r._data); }

  /**
   * get address as uint32_t
   */
  uint32_t get_data() const noexcept { return _data; }

 private:
  union {
    struct {
      uint8_t _byte1;  ///< 1 byte
      uint8_t _byte2;  ///< 2 byte
      uint8_t _byte3;  ///< 3 byte
      uint8_t _byte4;  ///< 4 byte
    };
    uint8_t _bytes[e_bytes_size];  ///< bytes array
    uint32_t _data = 0;            ///< address as 32 bit
  };

  friend bool string_to_address(std::string const& str_address,
                                ipv4& address) noexcept;
};

/**
 * convert address to string representation
 *
 * @param filled address
 * @return string (ex. "192.168.0.1")
 */
std::string address_to_string(uint32_t addr) noexcept;

/**
 * convert address to string representation
 *
 * @param filled address
 * @return string (ex. "192.168.0.1")
 */
inline std::string address_to_string(ipv4 const& address) noexcept {
  return address_to_string(address.get_data());
}

/**
 * build address from string representation
 *
 * @param str_address string filled with address
 * @param address to fill
 * @return true if operation succeed
 */
bool string_to_address(std::string const& str_address,
                       uint32_t& address) noexcept;

/**
 * build address from string representation
 *
 * @param str_address string filled with address
 * @param address to fill
 * @return true if operation succeed
 */
inline bool string_to_address(std::string const& str_address,
                              ipv4& address) noexcept {
  return string_to_address(str_address, address._data);
}

/**
 * put in ostream string address
 *
 * @param strm ostream value
 * @param address
 */
std::ostream& operator<<(std::ostream& strm, ipv4 const& address);
/** @} */  // end of protocols

}  // namespace protocols
}  // namespace jkl
