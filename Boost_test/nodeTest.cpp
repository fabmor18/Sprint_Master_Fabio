#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "../include/map_objects.h"
#include "../include/primitives.h"

BOOST_AUTO_TEST_SUITE(NodeTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
  auto a = Node(
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );


  BOOST_CHECK_EQUAL(a.data.position[0], 1.0);
}

BOOST_AUTO_TEST_CASE(HashNe)
{
    auto a = Node(
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    auto b = Node(
      {1.0,2.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    constexpr NodeDataHash hasher;
    BOOST_CHECK_NE(hasher(a), hasher(b));
}

BOOST_AUTO_TEST_CASE(HashEq)
{
    auto a = Node(
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    auto b = Node(
      {1.0,1.0003,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    constexpr NodeDataHash hasher;
    BOOST_CHECK_EQUAL(hasher(a), hasher(b));
}

BOOST_AUTO_TEST_CASE(TestHashNePrim)
{
    auto a = Node(
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    auto b = Node(
      {1.0,2.0,1.0},
      {1.0,1.0,1.0},
      {32.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    constexpr PrimDataHash hasher;
    BOOST_CHECK_NE(hasher(a), hasher(b));
}

BOOST_AUTO_TEST_CASE(TestHashEqPrim)
{
    auto a = Node(
      {1.0,1.0,34451.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    auto b = Node(
      {1.0,1.0003,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );

    constexpr PrimDataHash hasher;
    BOOST_CHECK_EQUAL(hasher(a), hasher(b));
}

BOOST_AUTO_TEST_CASE(EqualNodes)
{
    auto a = Node(
        {1.0,1.0,1.0},
        {1.0,1.0,1.0},
        {1.0,1.0,1.0},
        {1.0,1.0,1.0}
    );

    auto b = Node(
      {1.0,1.0003,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0}
  );


  BOOST_CHECK(a.compare_nodes(b, TEST));
}
BOOST_AUTO_TEST_SUITE_END()