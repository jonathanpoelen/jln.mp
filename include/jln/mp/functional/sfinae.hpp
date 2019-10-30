#pragma once

#include "sfinaefwd.hpp"
// TODO include smp/* ?

// TODO mp::unsafe_sfinae / mp::unsafe_sfinae_once ? for sfinae<F> without specialization on F
namespace jln::mp
{
  template<class x>
  using sfinae = typename detail::_sfinae<detail::_recursive_sfinae, x>::type;

  template<class x>
  using sfinae_once = typename detail::_sfinae<detail::_sfinae_once, x>::type;
}

// #include "../smp/traits.hpp"
#include "../smp/utility/always.hpp"
#include "../smp/utility/has_value.hpp"
#include "../smp/utility/same_as.hpp"
#include "../smp/utility/unpack.hpp"
// #include "../smp/algorithm/all_of.hpp"
#include "../smp/algorithm/rotate.hpp"
#include "../smp/algorithm/transform.hpp"
// #include "../smp/algorithm/same.hpp"
#include "../smp/algorithm/fold_left.hpp"
// #include "../smp/algorithm/make_int_sequence.hpp"
// #include "../smp/algorithm/reduce.hpp"
// #include "../smp/functional/capture.hpp"
#include "../smp/functional/bind.hpp"
#include "../smp/functional/flip.hpp"
#include "../smp/functional/is_invocable.hpp"
#include "../smp/functional/if.hpp"
// #include "../smp/functional/invoke.hpp"
// #include "../smp/functional/values.hpp"
#include "../smp/functional/identity.hpp"
// #include "../smp/functional/fork_front.hpp"
// #include "../smp/functional/monadic_invoke.hpp"
// #include "../smp/functional/bind.hpp"
// #include "../smp/functional/conditional.hpp"
#include "../smp/functional/fork.hpp"
// #include "../smp/functional/packed.hpp"
// #include "../smp/functional/invoke_or.hpp"
// #include "../smp/functional/call.hpp"
#include "../smp/number/is_number.hpp"
#include "../smp/number/numbers.hpp"
#include "../smp/number/as_number.hpp"
#include "../smp/number/operators.hpp"
#include "../smp/number/math.hpp"
// #include "../smp/list/iota.hpp"
// #include "../smp/list/is_list.hpp"
#include "../smp/list/push_back.hpp"
#include "../smp/list/list.hpp"
// #include "../smp/list/pop_front.hpp"
#include "../smp/list/push_front.hpp"
// #include "../smp/list/join.hpp"
// #include "../smp/list/as_list.hpp"
#include "../smp/list/drop_front.hpp"
#include "../smp/list/size.hpp"
#include "../smp/list/front.hpp"
// #include "../smp/list/at.hpp"
