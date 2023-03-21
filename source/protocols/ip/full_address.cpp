#include <protocols/ip/full_address.h>

#include <cstring>
#ifdef __linux__
#include <arpa/inet.h>
#include <ifaddrs.h>
#endif

namespace bro::net::proto::ip {

#ifdef __linux__

full_address::full_address(sockaddr_in const& addr) noexcept
    : _address(addr.sin_addr), _port(htons(addr.sin_port)) {}

full_address::full_address(sockaddr_in6 const& addr) noexcept
    : _address(addr.sin6_addr), _port(htons(addr.sin6_port)) {}

uint32_t find_scope_id(const proto::ip::address& addr) {
  uint32_t scope_id{0};
  struct ifaddrs *ifap{nullptr}, *ifa{nullptr};
  getifaddrs(&ifap);

  for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
    if (ifa && ifa->ifa_addr && AF_INET6 == ifa->ifa_addr->sa_family) {
      struct sockaddr_in6* in6 =
          reinterpret_cast<struct sockaddr_in6*>(ifa->ifa_addr);
      char addr_buf[50];
      inet_ntop(AF_INET6, &in6->sin6_addr, addr_buf, sizeof(addr_buf));
      proto::ip::v6::address addr_s(addr_buf);
      if (addr == addr_s) {
        scope_id = in6->sin6_scope_id;
        break;
      }
    }
  }

  freeifaddrs(ifap);
  return scope_id;
}

sockaddr_in full_address::to_native_v4() const noexcept {
  sockaddr_in addr{0, 0, {0}, {0}};
  addr.sin_family = AF_INET;
  addr.sin_addr = _address.to_native_v4();
  addr.sin_port = htons(_port);
  return addr;
}

sockaddr_in6 full_address::to_native_v6() noexcept {
  sockaddr_in6 addr = {0, 0, 0, {{{0}}}, 0};
  addr.sin6_family = AF_INET6;
  addr.sin6_addr = _address.to_native_v6();
  addr.sin6_port = htons(_port);
  if (!_scope_id) _scope_id = find_scope_id(_address);
  if (!_scope_id) addr.sin6_scope_id = *_scope_id;
  return addr;
}

#endif

std::ostream& operator<<(std::ostream& strm, const full_address& address) {
  return strm << address.to_string();
}

}  // namespace bro::net::proto::ip
