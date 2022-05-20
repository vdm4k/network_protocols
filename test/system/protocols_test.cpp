// SPDX-License-Identifier: BSD-3-Clause
#include <gtest/gtest.h>
#include <protocols/ip_addr.h>
#include <protocols/ipv4.h>
#include <protocols/ipv6.h>

namespace jkl::protocols::test {

TEST(ipv4, ctor) {
  std::string addr_str{"192.168.0.1"};
  {
    ipv4 addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
  {
    uint32_t add = 192;
    add |= (168 << 8);
    add |= (1 << 24);
    ipv4 addr(add);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
  {
    uint8_t add[] = {192, 168, 0, 1};
    ipv4 addr(add);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
  {
    ipv4 addr(192, 168, 0, 1);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
}

TEST(ipv4, eq) {
  std::string addr_str{"192.168.0.1"};
  ipv4 addr(addr_str);
  ipv4 addr2(addr_str);
  EXPECT_EQ(addr, addr2);
}

TEST(ipv4, not_eq) {
  ipv4 addr("192.168.0.1");
  ipv4 addr2("192.168.0.2");
  EXPECT_NE(addr, addr2);
}

TEST(ipv4, operator_less) {
  ipv4 addr("192.168.0.1");
  ipv4 addr2("192.168.0.2");
  EXPECT_TRUE(addr < addr2);
}

TEST(ipv4, operator_and) {
  ipv4 addr("192.168.0.1");
  ipv4 addr2("255.255.0.0");
  ipv4 addr3 = addr & addr2;
  EXPECT_EQ("192.168.0.0", address_to_string(addr3));
}

TEST(ipv4, assign_operator) {
  std::string addr_str{"192.168.0.1"};
  ipv4 addr = ipv4(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));
}

TEST(ipv4, reverse_order) {
  std::string addr_str{"1.0.168.192"};
  ipv4 addr(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));
  EXPECT_EQ("192.168.0.1", address_to_string(addr.reverse_order()));
}

TEST(ipv6, ctor) {
  std::string addr_str{"fe80::23a1:b152"};
  ipv6 addr(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));

  {
    uint8_t add[] = {0x26, 0x07, 0xf2, 0xc0, 0xf0, 0x0f, 0xb0, 0x01,
                     0x00, 0x00, 0x00, 0x00, 0xfa, 0xce, 0xb0, 0x0c};
    ipv6 addr(add);
    EXPECT_EQ("2607:f2c0:f00f:b001::face:b00c", address_to_string(addr));
  }
}

TEST(ipv6, reverse_order) {
  std::string addr_str{"fe80::23a1:b152"};
  ipv6 addr(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));
  EXPECT_EQ("52b1:a123::80fe", address_to_string(addr.reverse_order()));
}

TEST(ipv6, eq) {
  std::string addr_str{"fe80::23a1:b152"};
  ipv6 addr(addr_str);
  ipv6 addr2(addr_str);
  EXPECT_EQ(addr, addr2);
}

TEST(ipv6, not_eq) {
  ipv6 addr("fe80::23a1:b152");
  ipv6 addr2("fe80::23a1:b153");
  EXPECT_NE(addr, addr2);
}

TEST(ipv6, operator_less) {
  ipv6 addr("fe80::23a1:b152");
  ipv6 addr2("fe80::23a1:b153");
  EXPECT_TRUE(addr < addr2);
}

TEST(ipv6, assign_operator) {
  std::string addr_str{"fe80::23a1:b152"};
  ipv6 addr = ipv6(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));
}

TEST(ip_addr, ctor) {
  {
    std::string addr_str{"192.168.0.1"};
    ip_addr addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"192.168.0.1"};
    ipv4 v4addr(addr_str);
    ip_addr addr(v4addr);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    ip_addr addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v6, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    ipv6 v6addr(addr_str);
    ip_addr addr(v6addr);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v6, addr.get_version());
  }
}

TEST(ip_addr, reverse_order) {
  {
    std::string addr_str{"1.0.168.192"};
    ip_addr addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ("192.168.0.1", address_to_string(addr.reverse_order()));
    EXPECT_EQ(ip_addr::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    ip_addr addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ("52b1:a123::80fe", address_to_string(addr.reverse_order()));
    EXPECT_EQ(ip_addr::version::e_v6, addr.get_version());
  }
}

TEST(ip_addr, assign_operator) {
  {
    std::string addr_str{"fe80::23a1:b152"};
    ip_addr addr = ip_addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v6, addr.get_version());
  }
  {
    std::string addr_str{"192.168.0.1"};
    ip_addr addr;
    addr = ipv4(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"192.168.0.1"};
    ip_addr addr = ip_addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    ip_addr addr;
    addr = ipv6(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(ip_addr::version::e_v6, addr.get_version());
  }
}

TEST(ip_addr, operator_less) {
  {
    ip_addr addr("192.168.0.1");
    ip_addr addr2("192.168.0.2");
    EXPECT_TRUE(addr < addr2);
  }
  {
    ip_addr addr("fe80::23a1:b152");
    ip_addr addr2("fe80::23a1:b153");
    EXPECT_TRUE(addr < addr2);
  }
}

TEST(ip_addr, convert_to) {
  {
    std::string addr_str{"192.168.0.1"};
    ipv4 addr_v4{addr_str};
    ip_addr addr(addr_str);
    EXPECT_EQ(addr_v4, addr.to_v4());
  }
  {
    std::string addr_str{"fe80::23a1:b153"};
    ipv6 addr_v6{addr_str};
    ip_addr addr(addr_str);
    EXPECT_EQ(addr_v6, addr.to_v6());
  }
}

}  // namespace jkl::protocols::test
