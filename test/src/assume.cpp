#include "test/is_same.hpp"
#include "test/test_case.hpp"

#include "jln/mp/smp/assume.hpp"

#define DECL_ASSUME(name)               \
  namespace assume_test { class name; } \
  namespace jln::mp::detail {           \
    JLN_MP_MAKE_EXPECTED_ARGUMENT(      \
      argument_category::name,          \
      (), (::assume_test::name)         \
    );                                  \
  }

DECL_ASSUME(lists)
DECL_ASSUME(numbers)
DECL_ASSUME(number)
DECL_ASSUME(positive_number)
DECL_ASSUME(unary)
DECL_ASSUME(binary)
DECL_ASSUME(binary_list)
DECL_ASSUME(unary_or_more)
DECL_ASSUME(binary_or_more)

#undef DECL_ASSUME

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  ut::same<assume_test::lists, assume_lists<assume_test::lists>>();
  ut::same<try_<assume_test::lists>, assume_numbers<assume_test::lists>>();
  ut::same<try_<assume_test::lists>, assume_number<assume_test::lists>>();
  ut::same<try_<assume_test::lists>, assume_positive_number<assume_test::lists>>();
  ut::same<try_<assume_test::lists>, assume_unary<assume_test::lists>>();
  ut::same<try_<assume_test::lists>, assume_binary<assume_test::lists>>();
  ut::same<assume_test::lists, assume_binary_list<assume_test::lists>>();
  ut::same<try_<assume_test::lists>, assume_unary_or_more<assume_test::lists>>();
  ut::same<try_<assume_test::lists>, assume_binary_or_more<assume_test::lists>>();

  ut::same<try_<assume_test::numbers>, assume_lists<assume_test::numbers>>();
  ut::same<assume_test::numbers, assume_numbers<assume_test::numbers>>();
  ut::same<assume_test::numbers, assume_number<assume_test::numbers>>();
  ut::same<assume_test::numbers, assume_positive_number<assume_test::numbers>>();
  ut::same<try_<assume_test::numbers>, assume_unary<assume_test::numbers>>();
  ut::same<try_<assume_test::numbers>, assume_binary<assume_test::numbers>>();
  ut::same<try_<assume_test::numbers>, assume_binary_list<assume_test::numbers>>();
  ut::same<try_<assume_test::numbers>, assume_unary_or_more<assume_test::numbers>>();
  ut::same<try_<assume_test::numbers>, assume_binary_or_more<assume_test::numbers>>();

  ut::same<try_<assume_test::number>, assume_lists<assume_test::number>>();
  ut::same<try_<assume_test::number>, assume_numbers<assume_test::number>>();
  ut::same<assume_test::number, assume_number<assume_test::number>>();
  ut::same<assume_test::number, assume_positive_number<assume_test::number>>();
  ut::same<try_<assume_test::number>, assume_unary<assume_test::number>>();
  ut::same<try_<assume_test::number>, assume_binary<assume_test::number>>();
  ut::same<try_<assume_test::number>, assume_binary_list<assume_test::number>>();
  ut::same<try_<assume_test::number>, assume_unary_or_more<assume_test::number>>();
  ut::same<try_<assume_test::number>, assume_binary_or_more<assume_test::number>>();

  ut::same<try_<assume_test::positive_number>, assume_lists<assume_test::positive_number>>();
  ut::same<try_<assume_test::positive_number>, assume_numbers<assume_test::positive_number>>();
  ut::same<try_<assume_test::positive_number>, assume_number<assume_test::positive_number>>();
  ut::same<assume_test::positive_number, assume_positive_number<assume_test::positive_number>>();
  ut::same<try_<assume_test::positive_number>, assume_unary<assume_test::positive_number>>();
  ut::same<try_<assume_test::positive_number>, assume_binary<assume_test::positive_number>>();
  ut::same<try_<assume_test::positive_number>, assume_binary_list<assume_test::positive_number>>();
  ut::same<try_<assume_test::positive_number>, assume_unary_or_more<assume_test::positive_number>>();
  ut::same<try_<assume_test::positive_number>, assume_binary_or_more<assume_test::positive_number>>();

  ut::same<try_<assume_test::unary>, assume_lists<assume_test::unary>>();
  ut::same<try_<assume_test::unary>, assume_numbers<assume_test::unary>>();
  ut::same<assume_test::unary, assume_number<assume_test::unary>>();
  ut::same<assume_test::unary, assume_positive_number<assume_test::unary>>();
  ut::same<assume_test::unary, assume_unary<assume_test::unary>>();
  ut::same<try_<assume_test::unary>, assume_binary<assume_test::unary>>();
  ut::same<try_<assume_test::unary>, assume_binary_list<assume_test::unary>>();
  ut::same<try_<assume_test::unary>, assume_unary_or_more<assume_test::unary>>();
  ut::same<try_<assume_test::unary>, assume_binary_or_more<assume_test::unary>>();

  ut::same<try_<assume_test::binary>, assume_lists<assume_test::binary>>();
  ut::same<try_<assume_test::binary>, assume_numbers<assume_test::binary>>();
  ut::same<try_<assume_test::binary>, assume_number<assume_test::binary>>();
  ut::same<try_<assume_test::binary>, assume_positive_number<assume_test::binary>>();
  ut::same<try_<assume_test::binary>, assume_unary<assume_test::binary>>();
  ut::same<assume_test::binary, assume_binary<assume_test::binary>>();
  ut::same<assume_test::binary, assume_binary_list<assume_test::binary>>();
  ut::same<try_<assume_test::binary>, assume_unary_or_more<assume_test::binary>>();
  ut::same<try_<assume_test::binary>, assume_binary_or_more<assume_test::binary>>();

  ut::same<try_<assume_test::binary_list>, assume_lists<assume_test::binary_list>>();
  ut::same<try_<assume_test::binary_list>, assume_numbers<assume_test::binary_list>>();
  ut::same<try_<assume_test::binary_list>, assume_number<assume_test::binary_list>>();
  ut::same<try_<assume_test::binary_list>, assume_positive_number<assume_test::binary_list>>();
  ut::same<try_<assume_test::binary_list>, assume_unary<assume_test::binary_list>>();
  ut::same<try_<assume_test::binary_list>, assume_binary<assume_test::binary_list>>();
  ut::same<assume_test::binary_list, assume_binary_list<assume_test::binary_list>>();
  ut::same<try_<assume_test::binary_list>, assume_unary_or_more<assume_test::binary_list>>();
  ut::same<try_<assume_test::binary_list>, assume_binary_or_more<assume_test::binary_list>>();

  ut::same<try_<assume_test::unary_or_more>, assume_lists<assume_test::unary_or_more>>();
  ut::same<try_<assume_test::unary_or_more>, assume_numbers<assume_test::unary_or_more>>();
  ut::same<assume_test::unary_or_more, assume_number<assume_test::unary_or_more>>();
  ut::same<assume_test::unary_or_more, assume_positive_number<assume_test::unary_or_more>>();
  ut::same<assume_test::unary_or_more, assume_unary<assume_test::unary_or_more>>();
  ut::same<assume_test::unary_or_more, assume_binary<assume_test::unary_or_more>>();
  ut::same<assume_test::unary_or_more, assume_binary_list<assume_test::unary_or_more>>();
  ut::same<assume_test::unary_or_more, assume_unary_or_more<assume_test::unary_or_more>>();
  ut::same<assume_test::unary_or_more, assume_binary_or_more<assume_test::unary_or_more>>();

  ut::same<try_<assume_test::binary_or_more>, assume_lists<assume_test::binary_or_more>>();
  ut::same<try_<assume_test::binary_or_more>, assume_numbers<assume_test::binary_or_more>>();
  ut::same<try_<assume_test::binary_or_more>, assume_number<assume_test::binary_or_more>>();
  ut::same<try_<assume_test::binary_or_more>, assume_positive_number<assume_test::binary_or_more>>();
  ut::same<try_<assume_test::binary_or_more>, assume_unary<assume_test::binary_or_more>>();
  ut::same<assume_test::binary_or_more, assume_binary<assume_test::binary_or_more>>();
  ut::same<assume_test::binary_or_more, assume_binary_list<assume_test::binary_or_more>>();
  ut::same<try_<assume_test::binary_or_more>, assume_unary_or_more<assume_test::binary_or_more>>();
  ut::same<assume_test::binary_or_more, assume_binary_or_more<assume_test::binary_or_more>>();
}

TEST_SUITE_END()
