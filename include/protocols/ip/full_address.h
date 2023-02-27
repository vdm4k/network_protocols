#pragma once
#include <tuple>

#include "address.h"

namespace jkl {
namespace proto {
namespace ip {

/** @addtogroup proto
 *  @{
 */

/*! \class faddress
 *  \brief full address (ip address + port)
 */
class full_address {
 public:
  /**
   * default constructor
   */
  full_address() = default;

  /**
   * ctor from address and port
   */
  full_address(address const& addr, uint16_t port)
      : _address(addr), _port(port) {}

  /**
   * copy ctor
   */
  full_address(full_address const& faddr)
      : _address(faddr._address), _port(faddr._port) {}

  /**
   * move ctor
   */
  full_address(full_address&& faddr)
      : _address(faddr._address), _port(faddr._port) {}

  /**
   * assign operator
   */
  full_address& operator=(full_address const& faddr) {
    _address = faddr._address;
    _port = faddr._port;
    return *this;
  }

  /**
   * move assign operator
   */
  full_address& operator=(full_address&& faddr) {
    _address = faddr._address;
    _port = faddr._port;
    return *this;
  }

  /**
   * operator less
   */
  bool operator<(full_address const& faddr) const noexcept {
    return std::tie(_address, _port) < std::tie(faddr._address, faddr._port);
  }

  /**
   * operator equal
   */
  bool operator==(full_address const& faddr) const noexcept {
    return _address == faddr._address && _port == faddr._port;
  }

  /**
   * operator not equal
   */
  bool operator!=(full_address const& fss) const noexcept {
    return !(*this == fss);
  }

  /**
   * generate string representation
   */
  std::string to_string() const {
    return address_to_string(_address) + ":" + std::to_string(_port);
  }

  /**
   * get address
   */
  address const& get_address() const noexcept { return _address; }

  /**
   * get address
   */
  uint16_t get_port() const noexcept { return _port; }

 private:
  address _address;    ///< address
  uint16_t _port = 0;  ///< port
};

/**
 * put in ostream string address
 *
 * @param strm ostream value
 * @param address
 */
std::ostream& operator<<(std::ostream& strm, full_address const& address);

/** @} */  // end of proto

}  // namespace ip
}  // namespace proto
}  // namespace jkl
