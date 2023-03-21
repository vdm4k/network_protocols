#pragma once
#include <string>
#ifdef __linux__
#include <netinet/in.h>
#endif

namespace bro::net::proto::ip::v4 {

/** @defgroup proto
 *  @{
 */

/**
 * \brief ip v4 address wrapper
 */
class address {
 public:
  enum {
    e_bytes_size = 4  ///< address size in bytes
  };

  /**
   * default constructor
   */
  address() = default;

  /**
   * copy ctor
   */
  address(address const& addr) = default;

  /**
   * ctor from string representation
   *
   * ctor from string for example "127.0.0.1"
   */
  explicit address(std::string const& addr);

  /**
   * ctor from uint32_t
   */
  explicit address(uint32_t addr) noexcept : _data(addr) {}

  /**
   * ctor from byte array
   */
  explicit address(uint8_t const (&bytes)[e_bytes_size]) noexcept
      : _byte1(bytes[0]),
        _byte2(bytes[1]),
        _byte3(bytes[2]),
        _byte4(bytes[3]) {}

#ifdef __linux__
  address(in_addr const& addr) noexcept : _data(addr.s_addr) {}
#endif

  /**
   * ctor from bytes
   *
   * to build like 192,168,0,1
   */
  address(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) noexcept
      : _byte1(byte1), _byte2(byte2), _byte3(byte3), _byte4(byte4) {}

  /**
   * get current address in reverse order
   */
  address reverse_order() const noexcept {
    return address(__builtin_bswap32(_data));
  }

  /**
   * assign operator
   */
  address& operator=(address const& r) noexcept {
    _data = r._data;
    return *this;
  }

  /**
   * operator less
   */
  bool operator<(address const& r) const noexcept { return _data < r._data; }

  /**
   * operator equal
   */
  bool operator==(address const& r) const noexcept { return _data == r._data; }

  /**
   * operator not equal
   */
  bool operator!=(address const& r) const noexcept {
    return !(_data == r._data);
  }

  /**
   * operator&
   */
  address operator&(address const& r) const noexcept {
    return address(_data & r._data);
  }

#ifdef __linux__
  /**
   * get native discriptor
   */
  in_addr to_native() const noexcept { return {_data}; }
#endif

  /**
   * get address as uint32_t
   */
  uint32_t get_data() const noexcept { return _data; }

  /**
   * convert address to string representation
   *
   * @return string (ex. "192.168.0.1")
   */
  std::string to_string() const;

 private:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#pragma GCC diagnostic ignored "-Wnested-anon-types"
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
#pragma GCC diagnostic pop

  friend bool string_to_address(std::string const& str_address,
                                address& address) noexcept;
};

/**
 * convert address to string representation
 *
 * @param filled address
 * @return string (ex. "192.168.0.1")
 */
std::string address_to_string(uint32_t addr);

/**
 * convert address to string representation
 *
 * @param filled address
 * @return string (ex. "192.168.0.1")
 */
inline std::string address_to_string(address const& address) {
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
                              address& address) noexcept {
  return string_to_address(str_address, address._data);
}

/**
 * put in ostream string address
 *
 * @param strm ostream value
 * @param address
 */
std::ostream& operator<<(std::ostream& strm, address const& address);
/** @} */  // end of proto

}  // namespace bro::net::proto::ip::v4
