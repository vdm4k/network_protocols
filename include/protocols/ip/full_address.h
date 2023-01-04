#pragma once
#include <tuple>

#include "address.h"

namespace jkl {
namespace proto {
namespace ip {

/** @addtogroup proto
 *  @{
 */

/*! \class faddress (ip address + port)
 *  \brief full address
 */
class full_address {
 public:
  full_address() = default;
  full_address(address const& addr, uint16_t port)
      : _address(addr), _port(port) {}
  full_address(full_address const& faddr)
      : _address(faddr._address), _port(faddr._port) {}
  full_address(full_address&& faddr)
      : _address(faddr._address), _port(faddr._port) {}
  full_address& operator=(full_address const& faddr) {
    _address = faddr._address;
    _port = faddr._port;
    return *this;
  }
  full_address& operator=(full_address&& faddr) {
    _address = faddr._address;
    _port = faddr._port;
    return *this;
  }
  bool operator<(full_address const& faddr) const noexcept {
    return std::tie(_address, _port) < std::tie(faddr._address, faddr._port);
  }
  bool operator==(full_address const& faddr) const noexcept {
    return _address == faddr._address && _port == faddr._port;
  }
  bool operator!=(full_address const& fss) const noexcept {
    return !(*this == fss);
  }
  std::string to_string() const {
    return address_to_string(_address) + ":" + std::to_string(_port);
  }

  address const& get_address() const noexcept { return _address; }
  uint16_t get_port() const noexcept { return _port; }

 private:
  address _address;
  uint16_t _port = 0;
};

/** @} */  // end of proto

}  // namespace ip
}  // namespace proto
}  // namespace jkl
