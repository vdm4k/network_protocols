#include <protocols/ip/full_address.h>

namespace jkl {
namespace proto {
namespace ip {

std::ostream& operator<<(std::ostream& strm, const full_address& address) {
  return strm << address.to_string();
}

}  // namespace ip
}  // namespace proto
}  // namespace jkl
