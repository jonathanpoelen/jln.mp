#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/make_id.hpp"

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<detail::sfinae<make_id<>>, smp::make_id<>>();

  number<id_of<int>::value>() = _0();
  number<id_of_v<int>>() = _0();
  id_of_t<int>() = _0();

  number<id_of_v<long>>() = _1();
  number<id_of<long>::value>() = _1();
  id_of_t<long>() = _1();

  id_of_t<char>() = _2();
  number<id_of_v<char>>() = _2();
  number<id_of<char>::value>() = _2();

  id_of_t<int>() = _0();
  number<id_of<int>::value>() = _0();
  number<id_of_v<int>>() = _0();


  class tag1;

  make_id_for<tag1>::f<int>() = _0();
  make_id_for<tag1>::f<int>() = _0();
  smp::make_id_for<tag1>::f<int>() = _0();
  smp::make_id_for<tag1>::f<int>() = _0();

  make_id_for<tag1>::f<long>() = _1();
  make_id_for<tag1>::f<long>() = _1();
  smp::make_id_for<tag1>::f<long>() = _1();
  smp::make_id_for<tag1>::f<long>() = _1();

  make_id_for<tag1>::f<void>() = _2();
  make_id_for<tag1>::f<void>() = _2();
  smp::make_id_for<tag1>::f<void>() = _2();
  smp::make_id_for<tag1>::f<void>() = _2();


  make_id<>::f<long>() = _1();
  make_id<>::f<long>() = _1();
  smp::make_id<>::f<long>() = _1();
  smp::make_id<>::f<long>() = _1();

  make_id<>::f<int>() = _0();
  make_id<>::f<int>() = _0();
  smp::make_id<>::f<int>() = _0();
  smp::make_id<>::f<int>() = _0();

  make_id<>::f<void>() = _3();
  make_id<>::f<void>() = _3();
  smp::make_id<>::f<void>() = _3();
  smp::make_id<>::f<void>() = _3();


  ut::not_invocable<make_id_for<tag1>, int, int>();
}

TEST_SUITE_END()

#endif
#endif
