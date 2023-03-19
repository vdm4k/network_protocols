#include <protocols/ip/full_address.h>

namespace bro {
namespace net {
namespace proto {
namespace ip {

std::ostream& operator<<(std::ostream& strm, const full_address& address) {
  return strm << address.to_string();
}

}  // namespace ip
}  // namespace proto
}  // namespace net
}  // namespace bro
