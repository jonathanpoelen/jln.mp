#include "test/is_same.hpp"
#include "test/test_case.hpp"

#include "jln/mp/detail/to_predicate_not.hpp"
#include "jln/mp/utility/always.hpp"

#include <type_traits>

TEST_SUITE_BEGIN()

struct xxx
{
  template<class...>
  using f = jln::mp::true_;
};

TEST()
{
  using namespace jln::mp;
  using jln::mp::detail::to_predicate_not_t;

  using x_not = not_<>;
  using x_not_xxx = not_<xxx>;
  using x_not_not = not_<not_<>>;
  using x_not_not_xxx = not_<not_<xxx>>;
  using x_is = is<int>;
  using x_is_not = is<int, not_<>>;
  using x_same = same<>;
  using x_same_not = same<not_<>>;
  using x_lift = lift<std::is_same>;
  using x_lift_not = lift<std::is_same, not_<>>;
  using x_tee_not = tee<is<int>, not_<>>;
  using x_tee2_not = tee<x_tee_not, not_<>>;
  using x_tee3_not = tee<x_tee2_not, not_<>>;
  using x_tee_xxx_not = tee<xxx, not_<>>;
  using x_tee_xxx2_not = tee<x_tee_xxx_not, not_<>>;
  using x_tee_xxx3_not = tee<x_tee_xxx2_not, not_<>>;

  ut::invoke_r<x_not, lift<to_predicate_not_t>, identity>();
  ut::invoke_r<identity, lift<to_predicate_not_t>, x_not>();
  ut::invoke_r<tee<x_not_xxx, not_<>>, lift<to_predicate_not_t>, x_not_xxx>();
  ut::invoke_r<x_not, lift<to_predicate_not_t>, x_not_not>();
  ut::invoke_r<tee<x_not_not_xxx, not_<>>, lift<to_predicate_not_t>, x_not_not_xxx>();
  ut::invoke_r<x_is_not, lift<to_predicate_not_t>, x_is>();
  ut::invoke_r<x_is, lift<to_predicate_not_t>, x_is_not>();
  ut::invoke_r<x_same_not, lift<to_predicate_not_t>, x_same>();
  ut::invoke_r<x_same, lift<to_predicate_not_t>, x_same_not>();
  ut::invoke_r<x_lift_not, lift<to_predicate_not_t>, x_lift>();
  ut::invoke_r<x_lift, lift<to_predicate_not_t>, x_lift_not>();
  ut::invoke_r<x_is, lift<to_predicate_not_t>, x_tee_not>();
  ut::invoke_r<x_is_not, lift<to_predicate_not_t>, x_tee2_not>();
  ut::invoke_r<x_is, lift<to_predicate_not_t>, x_tee3_not>();
  ut::invoke_r<xxx, lift<to_predicate_not_t>, x_tee_xxx_not>();
  ut::invoke_r<x_tee_xxx_not, lift<to_predicate_not_t>, x_tee_xxx2_not>();
  ut::invoke_r<xxx, lift<to_predicate_not_t>, x_tee_xxx3_not>();
}

TEST_SUITE_END()
