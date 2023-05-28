// SPDX-License-Identifier: BSD-3-Clause
#include <gtest/gtest.h>
#include <protocols/ip/address.h>
#include <protocols/ip/v4.h>
#include <protocols/ip/v6.h>

namespace bro::protocols::test {

TEST(ipv4, ctor) {
  std::string addr_str{"192.168.0.1"};
  {
    bro::net::proto::ip::v4::address addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
  {
    uint32_t add = 192;
    add |= (168 << 8);
    add |= (1 << 24);
    bro::net::proto::ip::v4::address addr(add);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
  {
    uint8_t add[] = {192, 168, 0, 1};
    bro::net::proto::ip::v4::address addr(add);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
  {
   bro::net::proto::ip::v4::address addr(192, 168, 0, 1);
    EXPECT_EQ(addr_str, address_to_string(addr));
  }
}

TEST(ipv4, eq) {
  std::string addr_str{"192.168.0.1"};
  bro::net::proto::ip::v4::address addr(addr_str);
  bro::net::proto::ip::v4::address addr2(addr_str);
  EXPECT_EQ(addr, addr2);
}

TEST(ipv4, not_eq) {
  bro::net::proto::ip::v4::address addr("192.168.0.1");
  bro::net::proto::ip::v4::address addr2("192.168.0.2");
  EXPECT_NE(addr, addr2);
}

TEST(ipv4, operator_less) {
  bro::net::proto::ip::v4::address addr("192.168.0.1");
  bro::net::proto::ip::v4::address addr2("192.168.0.2");
  EXPECT_TRUE(addr < addr2);
}

TEST(ipv4, operator_and) {
  bro::net::proto::ip::v4::address addr("192.168.0.1");
  bro::net::proto::ip::v4::address addr2("255.255.0.0");
  bro::net::proto::ip::v4::address addr3 = addr & addr2;
  EXPECT_EQ("192.168.0.0", address_to_string(addr3));
}

TEST(ipv4, assign_operator) {
  std::string addr_str{"192.168.0.1"};
  auto addr = bro::net::proto::ip::v4::address(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));
}

TEST(ipv4, reverse_order) {
  std::string addr_str{"1.0.168.192"};
  bro::net::proto::ip::v4::address addr(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));
  EXPECT_EQ("192.168.0.1", address_to_string(addr.reverse_order()));
}

TEST(ipv6, ctor) {
  std::string addr_str{"fe80::23a1:b152"};
  bro::net::proto::ip::v6::address addr(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));

  {
    uint8_t add[] = {0x26, 0x07, 0xf2, 0xc0, 0xf0, 0x0f, 0xb0, 0x01,
                     0x00, 0x00, 0x00, 0x00, 0xfa, 0xce, 0xb0, 0x0c};
    bro::net::proto::ip::v6::address addr(add);
    EXPECT_EQ("2607:f2c0:f00f:b001::face:b00c", address_to_string(addr));
  }
}

TEST(ipv6, reverse_order) {
  std::string addr_str{"fe80::23a1:b152"};
  bro::net::proto::ip::v6::address addr(addr_str);
  EXPECT_EQ(addr_str, address_to_string(addr));
  EXPECT_EQ("52b1:a123::80fe", address_to_string(addr.reverse_order()));
}

TEST(ipv6, eq) {
  std::string addr_str{"fe80::23a1:b152"};
  bro::net::proto::ip::v6::address addr(addr_str);
  bro::net::proto::ip::v6::address addr2(addr_str);
  EXPECT_EQ(addr, addr2);
}

TEST(ipv6, not_eq) {
  bro::net::proto::ip::v6::address addr("fe80::23a1:b152");
  bro::net::proto::ip::v6::address addr2("fe80::23a1:b153");
  EXPECT_NE(addr, addr2);
}

TEST(ipv6, operator_less) {
  bro::net::proto::ip::v6::address addr("fe80::23a1:b152");
  bro::net::proto::ip::v6::address addr2("fe80::23a1:b153");
  EXPECT_TRUE(addr < addr2);
}

TEST(ipv6, assign_operator) {
  std::string addr_str{"fe80::23a1:b152"};
  bro::net::proto::ip::v6::address addr = bro::net::proto::ip::v6::address(addr_str);
  EXPECT_EQ(addr_str, bro::net::proto::ip::v6::address_to_string(addr));
}

TEST(address, ctor) {
  {
    std::string addr_str{"192.168.0.1"};
    bro::net::proto::ip::address addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"192.168.0.1"};
    bro::net::proto::ip::v4::address v4addr(addr_str);
    bro::net::proto::ip::address addr(v4addr);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    bro::net::proto::ip::address addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v6, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    bro::net::proto::ip::v6::address v6addr(addr_str);
    bro::net::proto::ip::address addr(v6addr);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v6, addr.get_version());
  }
}

TEST(address, reverse_order) {
  {
    std::string addr_str{"1.0.168.192"};
    bro::net::proto::ip::address addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ("192.168.0.1", address_to_string(addr.reverse_order()));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    bro::net::proto::ip::address addr(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ("52b1:a123::80fe", address_to_string(addr.reverse_order()));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v6, addr.get_version());
  }
}

TEST(address, assign_operator) {
  {
    std::string addr_str{"fe80::23a1:b152"};
    bro::net::proto::ip::address addr = bro::net::proto::ip::address(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v6, addr.get_version());
  }
  {
    std::string addr_str{"192.168.0.1"};
    bro::net::proto::ip::address addr;
    addr = bro::net::proto::ip::v4::address(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"192.168.0.1"};
    bro::net::proto::ip::address addr = bro::net::proto::ip::address(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v4, addr.get_version());
  }
  {
    std::string addr_str{"fe80::23a1:b152"};
    bro::net::proto::ip::address addr;
    addr = bro::net::proto::ip::v6::address(addr_str);
    EXPECT_EQ(addr_str, address_to_string(addr));
    EXPECT_EQ(bro::net::proto::ip::address::version::e_v6, addr.get_version());
  }
}

TEST(address, operator_less) {
  {
    bro::net::proto::ip::address addr("192.168.0.1");
    bro::net::proto::ip::address addr2("192.168.0.2");
    EXPECT_TRUE(addr < addr2);
  }
  {
    bro::net::proto::ip::address addr("fe80::23a1:b152");
    bro::net::proto::ip::address addr2("fe80::23a1:b153");
    EXPECT_TRUE(addr < addr2);
  }
}

TEST(address, convert_to) {
  {
    std::string addr_str{"192.168.0.1"};
    bro::net::proto::ip::v4::address addr_v4{addr_str};
    bro::net::proto::ip::address addr(addr_str);
    EXPECT_EQ(addr_v4, addr.to_v4());
  }
  {
    std::string addr_str{"fe80::23a1:b153"};
    bro::net::proto::ip::v6::address addr_v6{addr_str};
    bro::net::proto::ip::address addr(addr_str);
    EXPECT_EQ(addr_v6, addr.to_v6());
  }
}

}  // namespace bro::protocols::test
