// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/optimizer/types.hpp>
#include <jln/mp/algorithm/fold_xs.hpp>
#include <jln/mp/algorithm/replace.hpp>
#include <jln/mp/list/at.hpp>

#include <initializer_list>
#include <type_traits>
#include <utility>

namespace jln::mp::optimizer
{
  using types::uncallable;

  template<class F, class input>
  struct optimizer_impl
  {
    using type = optimized_result_t<types::unknown, F>;
  };

  namespace opti_detail
  {
    template<class F, class params>
    struct optimizer_wrap_impl
    {
      using type = typename optimizer_impl<F, params>::type;
    };
  }

  template<class F, class params>
  using optimize = typename opti_detail::optimizer_wrap_impl<F, params>::type;

  template<class F, class input>
  using optimized_function = typename optimize<F, input>::function;

  template<class F, class input>
  using output_result = typename optimize<F, input>::output_result;

  template<class F, class... params>
  using optimized_for = optimize<F, seq<params...>>;

  template<class F, class... params>
  using optimized_function_for = typename optimize<F, seq<params...>>::function;

  template<class F, class... params>
  using output_result_for = typename optimize<F, seq<params...>>::output_result;

  template<class>
  struct number_as_bool_selector;

  template<class C>
  struct add_uncallable_output
  {
    template<class... xs>
    using f = add_uncallable_output_t<JLN_MP_DCALL_TRACE_XS(xs, C, xs...)>;
  };

  struct uncallable_union
  {
    template<class... xs>
    using f = union_<uncallable, xs...>;
  };

  template<class params>
  struct wrap_optimize_with_params
  {
    template<class C, class...>
    using f = optimize<C, params>;
  };

  template<class F, class params>
  struct wrap_optimize_with_function
  {
    template<class C, class...>
    using f = optimized_result<
      typename optimize<C, params>::output_result,
      typename F::template f<typename optimize<C, params>::function>
    >;
  };
}

namespace jln::mp::optimizer::opti_detail
{
  struct wrap_uncallable_type_member
  {
    using type = optimized_result_t<uncallable, uncallable_function>;
  };

  template<class F>
  struct optimizer_wrap_impl<F, types::uncallable>
  : wrap_uncallable_type_member
  {};

  template<class F, class... xs>
  struct optimizer_wrap_impl<F, types::basic_union<types::uncallable, xs...>>
  {
    using _opti = typename optimizer_impl<F, union_<xs...>>::type;

    using type = optimized_result_t<
      union_<types::uncallable, typename _opti::output_result>,
      typename _opti::function
    >;
  };


  constexpr int_ umin(std::initializer_list<int_> l)
  {
    int_ r = *l.begin();
    for (int_ i : l)
      r = r < i ? r : i;
    return r;
  }

  constexpr int_ umax(std::initializer_list<int_> l)
  {
    int_ r = 0;
    for (int_ i : l)
      r = r < i ? i : r;
    return r;
  }
}

namespace jln::mp::optimizer
{
  template<class>
  struct count_min_param : number<1>
  {};

  template<>
  struct count_min_param<types::uncallable> : number<0>
  {};

  template<class... xs>
  struct count_min_param<types::basic_seq<xs...>>
  : number<(0 + ... + count_min_param<xs>::value)>
  {};

  template<class... xs>
  struct count_min_param<types::basic_union<xs...>>
  : number<opti_detail::umin({count_min_param<xs>::value...})>
  {};

  template<class... xs>
  struct count_min_param<types::basic_union<types::uncallable, xs...>>
  : number<opti_detail::umin({count_min_param<xs>::value...})>
  {};

  template<class x>
  struct count_min_param<types::basic_pack<x>>
  : number<0>
  {};


  template<class>
  struct is_varlen_param : false_
  {};

  template<> struct is_varlen_param<types::uncallable> : true_ {};

  template<> struct is_varlen_param<types::boolean> : false_ {};
  template<> struct is_varlen_param<types::any> : false_ {};
  template<> struct is_varlen_param<types::number> : false_ {};
  template<> struct is_varlen_param<types::na> : false_ {};

  template<class... xs>
  struct is_varlen_param<types::basic_seq<xs...>>
  : number<(... || is_varlen_param<xs>::value)>
  {};

  template<class x, class... xs>
  struct is_varlen_param<types::basic_union<x, xs...>>
  : number<(is_varlen_param<x>::value || ... || is_varlen_param<xs>::value)
    || !std::is_same<
        std::integer_sequence<int_, count_min_param<x>::value, count_min_param<xs>::value...>,
        std::integer_sequence<int_, count_min_param<xs>::value..., count_min_param<x>::value>
      >::value>
  {};

  template<class... xs>
  struct is_varlen_param<types::basic_union<types::uncallable, xs...>>
  : true_
  {};

  template<class x>
  struct is_varlen_param<types::basic_pack<x>>
  : true_
  {};
}

namespace jln::mp::optimizer::opti_detail
{
  template<class params>
  struct extract_all_types_impl
  {
    using type = params;
  };

  template<class x>
  struct extract_all_types_impl<types::basic_pack<x>>
  {
    using type = union_<x, types::basic_seq<>>;
  };

  template<class... xs>
  struct extract_all_types_impl<types::basic_seq<xs...>>
  {
    using type = union_<xs...>;
  };

  template<class... xs>
  struct extract_all_types_impl<types::basic_union<xs...>>
  {
    using type = union_<typename extract_all_types_impl<xs>::type...>;
  };


  template<class params>
  struct remove_empty_seq_from_union_impl
  {
    using type = params;
  };

  template<class... xs>
  struct remove_empty_seq_from_union_impl<types::basic_union<xs...>>
  {
    using type = typename detail::_join_select<sizeof...(xs)>
      ::template f<
        union_or_identity_t,
        typename wrap_in_list_c<!std::is_same<types::basic_seq<>, xs>::value>::template f<xs>...
      >::type;
  };


  // ::f<always, maybe = add_uncallable_output<always>, never = uncallable>
  template<bool always_or_never, bool force_maybe>
  struct always_maybe_never_impl;

  template<> struct always_maybe_never_impl<true, false>
  {
    template<class always, class maybe = void, class never = uncallable>
    using f = always;
  };

  template<> struct always_maybe_never_impl<true, true>
  {
    template<class always, class maybe = add_uncallable_output<always>, class never = uncallable>
    using f = maybe;
  };

  template<> struct always_maybe_never_impl<false, true>
  {
    template<class always, class maybe = add_uncallable_output<always>, class never = uncallable>
    using f = maybe;
  };

  template<> struct always_maybe_never_impl<false, false>
  {
    template<class always, class maybe = void, class never = uncallable>
    using f = never;
  };


#define JLN_SELECT_NUMBER_AS_BOOL_TRUE 0
#define JLN_SELECT_NUMBER_AS_BOOL_FALSE 1
#define JLN_SELECT_NUMBER_AS_BOOL_MAYBE_TRUE 2
#define JLN_SELECT_NUMBER_AS_BOOL_MAYBE_FALSE 3
#define JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER 4
#define JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER 5
#define JLN_SELECT_NUMBER_AS_BOOL_NEVER 6

  using select_number_as_bool_true = at_c<0>;
  using select_number_as_bool_false = at_c<1>;
  using select_number_as_bool_maybe_true = at_c<2>;
  using select_number_as_bool_maybe_false = at_c<3>;
  using select_number_as_bool_as_number = at_c<4>;
  using select_number_as_bool_maybe_number = at_c<5>;
  using select_number_as_bool_never = at_c<6>;

  template<class x>
  using number_as_bool_selector_from_union = typename number_as_bool_selector<x>
    ::template f<
      number<0b0000001>,
      number<0b0000010>,
      number<0b0000100>,
      number<0b0001000>,
      number<0b0010000>,
      number<0b0100000>,
      number<0b1000000>
    >;

  constexpr int number_as_bool_from_union_table[] {
    -1,
    // 0bxx
    JLN_SELECT_NUMBER_AS_BOOL_TRUE,
    JLN_SELECT_NUMBER_AS_BOOL_FALSE,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    // 0b1xx
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_TRUE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_TRUE,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    // 0b10xx
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_FALSE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_FALSE,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    // 0b11xx
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    // 0b1xxxx (as_number)
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER,
    // 0b1xxxxx (maybe_number)
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    // 0b1xxxxxx (never_number)
    JLN_SELECT_NUMBER_AS_BOOL_NEVER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_TRUE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_FALSE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    // 0b1xx
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_TRUE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_TRUE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    // 0b10xx
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_FALSE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_FALSE,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    // 0b11xx
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    // 0b101xxxx (never_number + as_number)
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    // 0b11xxxxx (never_number + maybe_number)
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
    JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER,
  };


  template<class F, class params>
  struct transform_from_params_impl
  {
    using type = output_result<F, params>;
  };

  template<class F, class x>
  struct transform_from_params_impl<F, types::basic_pack<x>>
  {
    using type = pack<output_result<F, x>>;
  };

  template<class F, class... xs>
  struct transform_from_params_impl<F, types::basic_seq<xs...>>
  {
    using type = seq<output_result<F, xs>...>;
  };

  template<class F, class... xs>
  struct transform_from_params_impl<F, types::basic_union<xs...>>
  {
    using type = union_<typename transform_from_params_impl<F, xs>::type...>;
  };
}

namespace jln::mp::optimizer
{
  template<class params>
  using extract_all_types_t = typename opti_detail::extract_all_types_impl<params>::type;


  template<class params>
  using remove_empty_seq_from_union_t =
    typename opti_detail::remove_empty_seq_from_union_impl<params>::type;


  template<class C>
  struct extract_one_param_as_union
  {
    template<class R, class... xs>
    using f = typename C
      ::template f<remove_empty_seq_from_union_t<extract_all_types_t<R>>, xs...>;
  };


  // TODO rename
  // ::f<always, maybe = add_uncallable_output<always>, never = uncallable>
  template<class params, int n>
  using count_param_always_maybe_never_selector = opti_detail::always_maybe_never_impl<
    count_min_param<params>::value == n,
    is_varlen_param<params>::value
  >;


  // ::f<always, maybe, never>
  template<class, int i>
  struct has_index_selector : at_c<i == 0 ? 0 : 2>
  {};

  template<int i>
  struct has_index_selector<types::uncallable, i> : at_c<2>
  {};

  template<class... xs, int i>
  struct has_index_selector<types::basic_seq<xs...>, i>
  : at_c<i < sizeof...(xs) ? 0 : 2>
  {};

  namespace opti_detail
  {
    template<int_ i>
    using has_index_union_selector = at_c<i == 0b100 ? 0 : i == 0b001 ? 2 : 1>;
  }

  template<class... xs, int i>
  struct has_index_selector<types::basic_union<xs...>, i>
  : opti_detail::has_index_union_selector<(... | has_index_selector<xs, i>
    ::template f<number<0b100>, number<0b010>, number<0b001>>::value
  )>
  {};

  template<class x, int i>
  struct has_index_selector<types::basic_pack<x>, i>
  : at_c<1>
  {};


  using remove_empty_seq_from_identity = detail::_wrap_in_list_if_not<is<types::basic_seq<>>>;


  // ::f<all_values,
  //     params_without_out_of_range = add_uncallable_output<all_values>,
  //     out_of_range_for_all = uncallable>
  // all_values::f<xs...>
  // params_without_out_of_range::f<xs...>
  // out_of_range_for_all::f<x>
  template<class params, int i>
  struct dispatch_param_at_c
  {
    template<class all_values,
             class params_without_out_of_range = void,
             class out_of_range_for_all = uncallable>
    using f = typename conditional_c<i != 0 || std::is_same<types::uncallable, params>::value>
      ::template f<out_of_range_for_all, all_values>
      ::template f<params>;
  };

  template<class... xs, int i>
  struct dispatch_param_at_c<types::basic_seq<xs...>, i>
  {
    template<class all_values,
             class params_without_out_of_range = void,
             class out_of_range_for_all = uncallable>
    using f = typename conditional_c<i < sizeof...(xs)>
      ::template f<at_c<i, all_values>, lift<types::basic_seq, out_of_range_for_all>>
      ::template f<xs...>;
  };

  namespace opti_detail
  {
    template<int i>
    struct dispatch_param_at_from_union
    {
      template<class... xs>
      using f = typename detail::_join_select<sizeof...(xs)>::template f<
        union_,
        typename remove_empty_seq_from_identity::template f<
          typename dispatch_param_at_c<xs, i>::template f<
            identity, identity, always<types::basic_seq<>>
          >
        >...
      >::type;
    };
  }

  template<class... xs, int i>
  struct dispatch_param_at_c<types::basic_union<xs...>, i>
  {
    template<class all_values,
             class params_without_out_of_range = add_uncallable_output<all_values>,
             class out_of_range_for_all = uncallable>
    using f = typename has_index_selector<types::basic_union<xs...>, i>
      ::template f<
        tee<opti_detail::dispatch_param_at_from_union<i>, all_values>,
        tee<opti_detail::dispatch_param_at_from_union<i>, params_without_out_of_range>,
        lift<types::basic_union, out_of_range_for_all>>
      ::template f<xs...>;
  };

  template<class x, int i>
  struct dispatch_param_at_c<types::basic_pack<x>, i>
  {
    template<class all_values,
             class params_without_out_of_range = add_uncallable_output<all_values>,
             class out_of_range_for_all = uncallable>
    using f = typename params_without_out_of_range::template f<x>;
  };


  template<class params, int i>
  using param_at_c = typename dispatch_param_at_c<params, i>
    ::template f<identity, uncallable_union, always<uncallable>>;


  template<class x>
  struct select_cond
  {
    template<class True, class False, class nobool = uncallable>
    using f = typename conditional_c<std::is_scalar<x>::value || std::is_array<x>::value>
      ::template f<nobool, union_<nobool, True, False>>;
  };

  template<>
  struct select_cond<true_>
  {
    template<class True, class False, class nobool = uncallable>
    using f = True;
  };

  template<class Int>
  struct select_cond<std::integral_constant<Int, 1>>
  : select_cond<true_>
  {};

  template<>
  struct select_cond<false_>
  {
    template<class True, class False, class nobool = uncallable>
    using f = False;
  };

  template<class Int>
  struct select_cond<std::integral_constant<Int, 0>>
  : select_cond<false_>
  {};

  template<int_ i>
  struct select_cond<number<i>>
  {
    template<class True, class False, class nobool = uncallable>
    using f = nobool;
  };

  template<class Int, Int i>
  struct select_cond<std::integral_constant<Int, i>>
  : select_cond<number<2>>
  {};

  template<>
  struct select_cond<types::boolean>
  {
    template<class True, class False, class nobool = uncallable>
    using f = union_<True, False>;
  };

  template<>
  struct select_cond<types::number>
  {
    template<class True, class False, class nobool = uncallable>
    using f = union_<nobool, True, False>;
  };

  template<>
  struct select_cond<types::na>
  {
    template<class True, class False, class nobool = uncallable>
    using f = nobool;
  };

  template<>
  struct select_cond<types::uncallable>
  {
    template<class True, class False, class nobool = uncallable>
    using f = nobool;
  };

  template<>
  struct select_cond<types::any>
  {
    template<class True, class False, class nobool = uncallable>
    using f = union_<True, False>;
  };

  template<class... xs>
  struct select_cond<types::basic_seq<xs...>>
  {
    template<class True, class False, class nobool = uncallable>
    using f = nobool;
  };

  template<class... xs>
  struct select_cond<types::basic_list<xs...>>
  {
    template<class True, class False, class nobool = uncallable>
    using f = nobool;
  };

  template<class... xs>
  struct select_cond<list<xs...>>
  {
    template<class True, class False, class nobool = uncallable>
    using f = nobool;
  };

  template<class x>
  struct select_cond<types::basic_pack<x>>
  {
    template<class True, class False, class nobool = uncallable>
    using f = union_<nobool, typename select_cond<x>::template f<True, False, nobool>>;
  };

  template<class... xs>
  struct select_cond<types::basic_union<xs...>>
  {
    template<class True, class False, class nobool = uncallable>
    using f = union_<typename select_cond<xs>::template f<True, False, nobool>...>;
  };


  // ::f<F,
  //     all_i_params,
  //     params_without_out_of_range = add_uncallable_output<all_values>,
  //     out_of_range_for_all_params = uncallable>
  // all_i_params<F<left, right>, ...>
  // params_without_out_of_range<F<left, right>, ...>
  // out_of_range_for_all_params<params>
  template<class params>
  struct dispatch_split_param_at_1
  {
    template<class F,
             class all_values,
             class params_without_out_of_range = void,
             class out_of_range_for_all = uncallable>
    using f = typename all_values::template f<typename F::template f<params, types::basic_seq<>>>;
  };

  template<>
  struct dispatch_split_param_at_1<uncallable>
  {
    template<class F,
             class all_values,
             class params_without_out_of_range = void,
             class out_of_range_for_all = uncallable>
    using f = typename out_of_range_for_all::template f<uncallable>;
  };

  template<>
  struct dispatch_split_param_at_1<types::basic_seq<>>
  {
    template<class F,
             class all_values,
             class params_without_out_of_range = void,
             class out_of_range_for_all = uncallable>
    using f = typename out_of_range_for_all::template f<types::basic_seq<>>;
  };

  template<class x, class... xs>
  struct dispatch_split_param_at_1<types::basic_seq<x, xs...>>
  {
    template<class F,
             class all_values,
             class params_without_out_of_range = void,
             class out_of_range_for_all = uncallable>
    using f = typename all_values::template f<typename F::template f<x, seq<xs...>>>;
  };

  namespace opti_detail
  {
    template<class... ps>
    struct dispatch_split_param_at_1_from_seq_pack_state1
    {
      template<class...>
      using f = dispatch_split_param_at_1_from_seq_pack_state1;

      using type = dispatch_split_param_at_1_from_seq_pack_state1;

      template<class C>
      using g = typename C::template f<ps...>;
    };

    template<class F, class... ps>
    struct dispatch_split_param_at_1_from_seq_pack_state0
    {
      template<class x, class... xs>
      struct f
      {
        using type = dispatch_split_param_at_1_from_seq_pack_state1<
          ps..., typename F::template f<x, seq<xs...>>
        >;
      };

      template<class x, class... xs>
      struct f<types::basic_pack<x>, xs...>
      {
        using type = dispatch_split_param_at_1_from_seq_pack_state0<
          F, ps..., typename F::template f<x, seq<types::basic_pack<x>, xs...>>
        >;
      };

      template<class C>
      using g = typename C::template f<ps...>;
    };

    template<class state, class... xs>
    using dispatch_split_param_at_1_from_seq_pack = typename state::template f<xs...>::type;
  }

  template<class x, class... xs>
  struct dispatch_split_param_at_1<types::basic_seq<types::basic_pack<x>, xs...>>
  {
    template<class F,
             class all_values,
             class params_without_out_of_range = void,
             class out_of_range_for_all = uncallable>
    using f = typename detail::fold_xs_impl<sizeof...(xs)>
      ::template f<
        opti_detail::dispatch_split_param_at_1_from_seq_pack,
        sizeof...(xs),
        opti_detail::dispatch_split_param_at_1_from_seq_pack_state0<
          F, typename F::template f<x, types::basic_seq<types::basic_pack<x>, xs...>>>,
        xs...>
      ::template g<all_values>;
  };

  template<class x>
  struct dispatch_split_param_at_1<types::basic_pack<x>>
  {
    template<class F,
             class all_values,
             class params_without_out_of_range = add_uncallable_output<all_values>,
             class out_of_range_for_all = uncallable>
    using f = typename params_without_out_of_range::template f<
      typename F::template f<x, types::basic_pack<x>>
    >;
  };

  template<class... xs>
  struct dispatch_split_param_at_1<types::basic_union<xs...>>
  {
    template<class F,
             class all_values,
             class params_without_out_of_range = add_uncallable_output<all_values>,
             class out_of_range_for_all = uncallable>
    using f = typename detail::_join_select<sizeof...(xs)>::template f<
      has_index_selector<types::basic_union<xs...>, 0>
        ::template f<all_values, params_without_out_of_range, out_of_range_for_all>
        ::template f,
      typename dispatch_split_param_at_1<xs>::template f<
        F, listify, listify, always<list<>>
      >...
    >::type;
  };


  // // ::f<all_i_params, params_without_out_of_range, out_of_range_for_all_params>
  // // all_i_params<list<left, right>, ...>
  // // params_without_out_of_range<list<left, right>, ...>
  // // out_of_range_for_all_params<params>
  // template<class params, int i>
  // struct dispatch_split_param_at_c
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename out_of_range_for_all::template f<params>;
  // };
  //
  // template<>
  // struct dispatch_split_param_at_c<uncallable, 0>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename out_of_range_for_all::template f<uncallable>;
  // };
  //
  // template<>
  // struct dispatch_split_param_at_c<uncallable, 1>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename out_of_range_for_all::template f<uncallable>;
  // };
  //
  // template<class params>
  // struct dispatch_split_param_at_c<params, 0>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename all_values::template f<list<types::basic_seq<>, params>>;
  // };
  //
  // template<class params>
  // struct dispatch_split_param_at_c<params, 1>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename all_values::template f<list<params, types::basic_seq<>>>;
  // };
  //
  // template<>
  // struct dispatch_split_param_at_c<types::basic_seq<>, 0>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename all_values::template f<list<types::basic_seq<>, types::basic_seq<>>>;
  // };
  //
  // template<>
  // struct dispatch_split_param_at_c<types::basic_seq<>, 1>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename out_of_range_for_all::template f<types::basic_seq<>>;
  // };
  //
  // template<class x, class... xs>
  // struct dispatch_split_param_at_c<types::basic_seq<x, xs...>, 0>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename all_values::template f<list<types::basic_seq<>, types::basic_seq<x, xs...>>>;
  // };
  //
  // template<class x, class... xs>
  // struct dispatch_split_param_at_c<types::basic_seq<x, xs...>, 1>
  // {
  //   // TODO pack
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename all_values::template f<list<x, seq<xs...>>>;
  // };
  //
  // template<class x, class... xs, int i>
  // struct dispatch_split_param_at_c<types::basic_seq<x, xs...>, i>
  // {
  //   // TODO
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename all_values::template f<list<x, seq<xs...>>>;
  // };
  //
  // template<class x>
  // struct dispatch_split_param_at_c<types::basic_pack<x>>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename all_values::template f<list<types::basic_pack<x>, types::basic_pack<x>>>;
  // };
  //
  // template<class... xs>
  // struct dispatch_split_param_at_c<types::basic_union<xs...>>
  // {
  //   template<class all_values, class params_without_out_of_range, class out_of_range_for_all>
  //   using f = typename detail::_join_select<sizeof...(xs)>::template f<
  //     typename has_index_selector<types::basic_union<xs...>, 0>
  //       ::template f<all_values, params_without_out_of_range, out_of_range_for_all>
  //       ::f,
  //     typename dispatch_split_param_at_c<xs>::template f<
  //       listify, listify, always<list<>>
  //     >...
  //   >::type;
  // };


  template<class x>
  struct type_is_number : false_ {};

  template<> struct type_is_number<types::number> : true_ {};
  template<> struct type_is_number<types::boolean> : true_ {};


  template<class>
  struct is_list_t_or_list : false_ {};

  template<class... xs>
  struct is_list_t_or_list<types::basic_union<xs...>>
  : number<(... && is_list_t_or_list<xs>::value)>
  {};

  template<class... xs> struct is_list_t_or_list<list<xs...>> : true_ {};
  template<class... xs> struct is_list_t_or_list<types::basic_list<xs...>> : true_ {};


  // ::f<uncallable, uncallable_union, callable>
  template<class x>
  struct dispatch_uncallable : at_c<2> {};

  template<> struct dispatch_uncallable<types::uncallable> : at_c<0> {};
  template<class x> struct dispatch_uncallable<types::basic_union<types::uncallable, x>> : at_c<1> {};


  namespace opti_detail
  {
    template<class>
    struct is_list_like_impl
    {
      using type = false_;
    };

    template<class... xs>
    struct is_list_like_impl<types::basic_seq<xs...>>
    {
      using type = false_;
    };

    template<class... xs>
    struct is_list_like_impl<types::basic_union<xs...>>
    {
      using type = false_;
    };

    template<class x>
    struct is_list_like_impl<types::basic_pack<x>>
    {
      using type = false_;
    };

    template<template<class...> class Tpl, class... xs>
    struct is_list_like_impl<Tpl<xs...>>
    {
      using type = true_;
    };
  }


  // f<F, always, maybe = add_uncallable_output<always>, never = uncallable>
  // always::f<F::f<xs...>...>
  // maybe::f<F::f<xs...>...>
  // never::f<params>
  template<class params>
  struct dispatch_unpack
  {
    template<class F,
             class always,
             class maybe = void,
             class never = uncallable>
    using f = typename never::template f<params>;
  };

  template<>
  struct dispatch_unpack<types::any>
  {
    template<class F,
             class always,
             class maybe = add_uncallable_output<always>,
             class never = uncallable>
    using f = typename maybe::template f<
      typename F::template f<types::basic_pack<types::any>>
    >;
  };

  template<class... xs>
  struct dispatch_unpack<types::basic_seq<xs...>>
  {
    template<class F,
             class always,
             class maybe = void,
             class never = uncallable>
    using f = typename never::template f<types::basic_seq<xs...>>;
  };

  template<class x>
  struct dispatch_unpack<types::basic_pack<x>>
  {
    template<class F,
             class always,
             class maybe = void,
             class never = uncallable>
    using f = typename never::template f<types::basic_pack<x>>;
  };

  template<>
  struct dispatch_unpack<types::basic_pack<types::any>>
  {
    template<class F,
             class always,
             class maybe = add_uncallable_output<always>,
             class never = uncallable>
    using f = typename maybe::template f<
      typename F::template f<types::basic_pack<types::any>>
    >;
  };

  template<template<class...> class Tpl, class... xs>
  struct dispatch_unpack<Tpl<xs...>>
  {
    template<class F,
             class always,
             class maybe = void,
             class never = uncallable>
    using f = typename always::template f<JLN_MP_DCALL_TRACE_XS(xs, F, xs...)>;
  };

  template<template<class...> class Tpl, class... xs>
  struct dispatch_unpack<types::basic_pack<Tpl<xs...>>>
  {
    template<class F,
             class always,
             class maybe = void,
             class never = uncallable>
    using f = typename always::template f<JLN_MP_DCALL_TRACE_XS(xs, F, xs...)>;
  };

  namespace opti_detail
  {
    template<int>
    struct dispatch_unpack_from_union_impl;

    template<>
    struct dispatch_unpack_from_union_impl<0>
    {
      template<class always, class maybe, class never, class... xs>
      using f = mp::always<typename always::template f<xs...>>;
    };

    template<>
    struct dispatch_unpack_from_union_impl<1>
    {
      template<class always, class maybe, class never, class... xs>
      using f = mp::always<typename maybe::template f<xs...>>;
    };

    template<>
    struct dispatch_unpack_from_union_impl<2>
    {
      template<class always, class maybe, class never, class... xs>
      using f = never;
    };

    template<std::size_t n, class always, class maybe, class never>
    struct dispatch_unpack_from_union
    {
      template<class... xs>
      using f = typename dispatch_unpack_from_union_impl<
        n == sizeof...(xs) ? 0 : sizeof...(xs) ? 1 : 2
      >::template f<always, maybe, never, xs...>;
    };
  }

  template<class... xs>
  struct dispatch_unpack<types::basic_union<xs...>>
  {
    template<class F,
             class always,
             class maybe = add_uncallable_output<always>,
             class never = uncallable>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<
        opti_detail::dispatch_unpack_from_union<sizeof...(xs), always, maybe, never>
          ::template f,
        typename dispatch_unpack<xs>
          ::template f<F, listify, listify, mp::always<list<>>>
        ...
      >::type
      ::template f<types::basic_union<xs...>>;
  };


  // template<class x>
  // struct number_as_bool_selector
  // {
  //   template<class always_true, class always_false,
  //            class maybe_true, class maybe_false,
  //            class as_number, class maybe_number, class never_number>
  //   using f = ...;
  // };

  template<class x>
  struct number_as_bool_selector
  : at_c<((std::is_class<x>::value && !std::is_null_pointer<x>::value)
        || std::is_union<x>::value
    ) ? JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER : JLN_SELECT_NUMBER_AS_BOOL_NEVER>
  {};

  template<>
  struct number_as_bool_selector<false_>
  : opti_detail::select_number_as_bool_false
  {};

  template<int_ value>
  struct number_as_bool_selector<number<value>>
  : opti_detail::select_number_as_bool_true
  {};

  template<>
  struct number_as_bool_selector<std::true_type>
  : opti_detail::select_number_as_bool_true
  {};

  template<>
  struct number_as_bool_selector<std::false_type>
  : opti_detail::select_number_as_bool_false
  {};

  template<class Int>
  struct number_as_bool_selector<std::integral_constant<Int, 0>>
  : opti_detail::select_number_as_bool_false
  {};

  template<std::size_t value>
  struct number_as_bool_selector<std::integral_constant<std::size_t, value>>
  : opti_detail::select_number_as_bool_true
  {};

  template<>
  struct number_as_bool_selector<types::na>
  : opti_detail::select_number_as_bool_never
  {};

  template<>
  struct number_as_bool_selector<types::uncallable>
  : opti_detail::select_number_as_bool_never
  {};

  template<>
  struct number_as_bool_selector<types::boolean>
  : opti_detail::select_number_as_bool_as_number
  {};

  template<>
  struct number_as_bool_selector<types::number>
  : opti_detail::select_number_as_bool_as_number
  {};

  template<class... xs>
  struct number_as_bool_selector<types::basic_list<xs...>>
  : opti_detail::select_number_as_bool_never
  {};

  template<class... xs>
  struct number_as_bool_selector<types::basic_seq<xs...>>
  : opti_detail::select_number_as_bool_never
  {};

  template<class x>
  struct number_as_bool_selector<types::basic_pack<x>>
  : number_as_bool_selector<x>
    ::template f<
      opti_detail::select_number_as_bool_maybe_true,
      opti_detail::select_number_as_bool_maybe_false,
      opti_detail::select_number_as_bool_maybe_true,
      opti_detail::select_number_as_bool_maybe_false,
      opti_detail::select_number_as_bool_maybe_number,
      opti_detail::select_number_as_bool_maybe_number,
      opti_detail::select_number_as_bool_never
    >
  {};

  template<class... xs>
  struct number_as_bool_selector<types::basic_union<xs...>>
  : at_c<opti_detail::number_as_bool_from_union_table[
    (... | opti_detail::number_as_bool_selector_from_union<xs>::value)
  ]>
  {};


  namespace opti_detail
  {
    template<class F>
    using dispatch_idx_3 = typename F::template f<
      always<number<0b001>>,
      always<number<0b010>>,
      always<number<0b100>>
    >;

    constexpr int dispatch_idx_3_union_table[]{
      // 0b00x
      0, 0,
      // 0b01x
      1, 1,
      // 0b100
      2,
      // 0b1xx
      1, 1, 1,
    };

    constexpr int dispatch_idx_3_seq_table[]{
      // 0b00x
      0, 0,
      // 0b01x
      1, 1,
      // 0b1xx
      2, 2, 2, 2,
    };

    template<template<class> class F, class... xs>
    using dispatch_3_union_selector = at_c<dispatch_idx_3_union_table[
      (... | dispatch_idx_3<F<xs>>::value)
    ]>;

    template<template<class> class F, class... xs>
    using dispatch_3_seq_selector = at_c<dispatch_idx_3_seq_table[
      (0 | ... | dispatch_idx_3<F<xs>>::value)
    ]>;

    template<template<class> class F, class C>
    struct dispatch_3_filter
    {
      template<class... xs>
      using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<
        C::template f,
        typename F<xs>::template f<listify, listify, always<list<>>>...
      >::type;
    };
  }


  template<class C>
  struct to_creator
  {
    template<class all,
             class partial = tee<all, lift<add_uncallable_output>>,
             class never = always<uncallable>>
    using f = typename C::template f<all, partial, never>;
  };


  template<class C>
  struct to_selector
  {
    template<class all,
             class partial = add_uncallable_output<all>,
             class never = uncallable>
    using f = typename C::template f<always<all>, always<partial>, always<never>>;
  };

  template<class C,
           class all,
           class partial = add_uncallable_output<all>,
           class never = uncallable>
  using selector = typename C::template f<always<all>, always<partial>, always<never>>;


  template<class params>
  struct dispatch_list
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void /*add_uncallable_output<all_is_list>*/,
             class never_list = uncallable>
    using f = typename never_list::template f<params>;
  };

  template<class... xs>
  struct dispatch_list<list<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<list<xs...>>;
  };

  template<class... xs>
  struct dispatch_list<types::basic_list<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<types::basic_list<xs...>>;
  };

  template<>
  struct dispatch_list<types::any>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = void>
    using f = typename possibly_list_without_nolist::template f<types::any_list>;
  };

  template<class x>
  struct dispatch_list<types::basic_pack<x>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = uncallable>
    using f = typename dispatch_list<x>
      ::template f<
        possibly_list_without_nolist,
        possibly_list_without_nolist,
        lift<types::basic_pack, never_list>
      >;
  };

  template<class... xs>
  struct dispatch_list<types::basic_union<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = uncallable>
    using f = typename opti_detail::dispatch_3_union_selector<dispatch_list, xs...>
      ::template f<
        all_is_list,
        opti_detail::dispatch_3_filter<dispatch_list, possibly_list_without_nolist>,
        lift<types::basic_union, never_list>>
      ::template f<xs...>;
  };


  template<class params>
  struct dispatch_lists
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void /*add_uncallable_output<all_is_list>*/,
             class never_list = uncallable>
    using f = typename never_list::template f<params>;
  };

  template<class... xs>
  struct dispatch_lists<list<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<list<xs...>>;
  };

  template<class... xs>
  struct dispatch_lists<types::basic_list<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<types::basic_list<xs...>>;
  };

  template<>
  struct dispatch_lists<types::any>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = void>
    using f = typename possibly_list_without_nolist::template f<types::any_list>;
  };

  template<class x>
  struct dispatch_lists<types::basic_pack<x>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = uncallable>
    using f = typename dispatch_lists<x>
      ::template f<
        lift<types::basic_pack, all_is_list>,
        lift<types::basic_pack, possibly_list_without_nolist>,
        lift<types::basic_pack, never_list>
      >;
  };

  template<class... xs>
  struct dispatch_lists<types::basic_seq<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = uncallable>
    using f = typename opti_detail::dispatch_3_seq_selector<dispatch_lists, xs...>
      ::template f<
        all_is_list,
        opti_detail::dispatch_3_filter<dispatch_lists, possibly_list_without_nolist>,
        lift<types::basic_seq, never_list>>
      ::template f<xs...>;
  };

  template<class... xs>
  struct dispatch_lists<types::basic_union<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = uncallable>
    using f = typename opti_detail::dispatch_3_union_selector<dispatch_lists, xs...>
      ::template f<
        lift<types::basic_union, all_is_list>,
        opti_detail::dispatch_3_filter<dispatch_lists,
          lift<opti_detail::union_or_identity_t, possibly_list_without_nolist>>,
        lift<types::basic_union, never_list>>
      ::template f<xs...>;
  };


  template<class params>
  struct dispatch_join_list
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void /*add_uncallable_output<all_is_list>*/,
             class never_list = uncallable>
    using f = typename never_list::template f<params>;
  };

  template<class... xs>
  struct dispatch_join_list<list<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<xs...>;
  };

  template<class... xs>
  struct dispatch_join_list<types::basic_list<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<xs...>;
  };

  template<>
  struct dispatch_join_list<types::any>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = void>
    using f = typename possibly_list_without_nolist::template f<types::basic_pack<types::any>>;
  };

  template<>
  struct dispatch_join_list<types::basic_pack<types::any>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = void>
    using f = typename possibly_list_without_nolist::template f<types::basic_pack<types::any>>;
  };

  template<>
  struct dispatch_join_list<types::basic_pack<list<>>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<>;
  };

  template<class x>
  struct dispatch_join_list<types::basic_pack<list<x>>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<types::basic_pack<x>>;
  };

  template<class... xs>
  struct dispatch_join_list<types::basic_pack<list<xs...>>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<types::basic_pack<types::basic_seq<xs...>>>;
  };

  template<class x>
  struct dispatch_join_list<types::basic_pack<types::basic_list<x>>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<types::basic_pack<x>>;
  };

  template<class... xs>
  struct dispatch_join_list<types::basic_pack<types::basic_list<xs...>>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<types::basic_pack<types::basic_seq<xs...>>>;
  };

  template<class... xs>
  struct dispatch_join_list<types::basic_pack<types::basic_union<xs...>>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = uncallable>
    using f = typename dispatch_join_list<types::basic_union<xs...>>
      ::template f<
        lift<types::basic_pack, all_is_list>,
        lift<types::basic_pack, possibly_list_without_nolist>,
        lift<types::basic_pack, never_list>
      >;
  };

  template<class x>
  struct dispatch_join_list<types::basic_pack<x>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = uncallable>
    using f = typename never_list::template f<types::basic_pack<x>>;
  };

  template<>
  struct dispatch_join_list<types::basic_seq<>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = void,
             class never_list = void>
    using f = typename all_is_list::template f<>;
  };

  namespace opti_detail
  {
    template<class x>
    struct dispatch_seq_or_x
    {
      template<class C>
      using f = typename C::template f<x>;
    };

    template<class... xs>
    struct dispatch_seq_or_x<types::basic_seq<xs...>>
    {
      template<class C>
      using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
    };

    template<class C>
    struct dispatch_as_seq
    {
      template<class... xs>
      using f = typename dispatch_seq_or_x<seq<xs...>>::template f<C>;
    };
  }

  template<class... xs>
  struct dispatch_join_list<types::basic_seq<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = uncallable>
    using f = typename opti_detail::dispatch_3_seq_selector<dispatch_join_list, xs...>
      ::template f<
        opti_detail::dispatch_3_filter<dispatch_join_list,
          opti_detail::dispatch_as_seq<all_is_list>>,
        opti_detail::dispatch_3_filter<dispatch_join_list,
          opti_detail::dispatch_as_seq<possibly_list_without_nolist>>,
        lift<types::basic_seq, never_list>>
      ::template f<xs...>;
  };

  template<class... xs>
  struct dispatch_join_list<types::basic_union<xs...>>
  {
    template<class all_is_list,
             class possibly_list_without_nolist = add_uncallable_output<all_is_list>,
             class never_list = uncallable>
    using f = typename opti_detail::dispatch_3_union_selector<dispatch_join_list, xs...>
      ::template f<
        lift<types::basic_union, all_is_list>,
        replace<types::basic_seq<>, list<types::basic_seq<>>,
          opti_detail::dispatch_3_filter<dispatch_join_list,
            lift<opti_detail::union_or_identity_t, possibly_list_without_nolist>>>,
        lift<types::basic_union, never_list>>
      ::template f<xs...>;
  };


  template<class x>
  struct dispatch_bool
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = add_uncallable_output<all_is_bool>,
             class never_bool = uncallable>
    using f = typename conditional_c<std::is_scalar<x>::value || std::is_array<x>::value>
      ::template f<never_bool, possibly_bool_without_nobool>
      ::template f<x>;
  };

  template<>
  struct dispatch_bool<false_>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = void>
    using f = typename all_is_bool::template f<false_>;
  };

  template<>
  struct dispatch_bool<true_>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = void>
    using f = typename all_is_bool::template f<true_>;
  };

  template<int_ i>
  struct dispatch_bool<number<i>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = uncallable>
    using f = typename never_bool::template f<number<i>>;
  };

  template<class Int>
  struct dispatch_bool<std::integral_constant<Int, 0>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = void>
    using f = typename all_is_bool::template f<std::integral_constant<Int, 0>>;
  };

  template<class Int>
  struct dispatch_bool<std::integral_constant<Int, 1>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = void>
    using f = typename all_is_bool::template f<std::integral_constant<Int, 1>>;
  };

  template<class Int, Int n>
  struct dispatch_bool<std::integral_constant<Int, n>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = uncallable>
    using f = typename never_bool::template f<std::integral_constant<Int, n>>;
  };

  template<>
  struct dispatch_bool<types::boolean>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = void>
    using f = typename all_is_bool::template f<types::boolean>;
  };

  template<>
  struct dispatch_bool<types::number>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = add_uncallable_output<all_is_bool>,
             class never_bool = void>
    using f = typename possibly_bool_without_nobool::template f<types::number>;
  };

  template<>
  struct dispatch_bool<types::any>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = add_uncallable_output<all_is_bool>,
             class never_bool = void>
    using f = typename possibly_bool_without_nobool::template f<types::any>;
  };

  template<class x>
  struct dispatch_bool<types::basic_pack<x>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = add_uncallable_output<all_is_bool>,
             class never_bool = uncallable>
    using f = typename dispatch_bool<x>
      ::template f<
        possibly_bool_without_nobool,
        possibly_bool_without_nobool,
        lift<types::basic_pack, never_bool>
      >;
  };
  template<>
  struct dispatch_bool<types::uncallable>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = uncallable>
    using f = typename never_bool::template f<types::uncallable>;
  };

  template<>
  struct dispatch_bool<types::na>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = uncallable>
    using f = typename never_bool::template f<types::na>;
  };

  template<class... xs>
  struct dispatch_bool<list<xs...>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = uncallable>
    using f = typename never_bool::template f<list<xs...>>;
  };

  template<class... xs>
  struct dispatch_bool<types::basic_list<xs...>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = uncallable>
    using f = typename never_bool::template f<types::basic_list<xs...>>;
  };

  template<class... xs>
  struct dispatch_bool<types::basic_seq<xs...>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = void,
             class never_bool = uncallable>
    using f = typename never_bool::template f<types::basic_seq<xs...>>;
  };

  template<class... xs>
  struct dispatch_bool<types::basic_union<xs...>>
  {
    template<class all_is_bool,
             class possibly_bool_without_nobool = add_uncallable_output<all_is_bool>,
             class never_bool = uncallable>
    using f = typename opti_detail::dispatch_3_union_selector<dispatch_bool, xs...>
      ::template f<
        all_is_bool,
        opti_detail::dispatch_3_filter<dispatch_bool, possibly_bool_without_nobool>,
        lift<types::basic_union, never_bool>>
      ::template f<xs...>;
  };


  template<class>
  struct callable_selector
  {
    template <class Callable, class MaybeCallable = void, class Uncallable = uncallable>
    using f = Callable;
  };

  template<class... xs>
  struct callable_selector<types::basic_union<types::uncallable, xs...>>
  {
    template <class Callable, class MaybeCallable = add_uncallable_output<Callable>, class Uncallable = uncallable>
    using f = MaybeCallable;
  };

  template<> struct callable_selector<types::uncallable>
  {
    template <class Callable, class MaybeCallable = add_uncallable_output<Callable>, class Uncallable = uncallable>
    using f = Uncallable;
  };


  template<class C>
  struct dispatch_optimizer
  {
    template<class F, class params, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      output_result<F, params>,
      optimized_function<F, params>,
      xs...
    );
  };


  template<class TC, class FC = uncallable>
  struct dispatch_if_not_uncallable
  {
    template<class F, class params, class... xs>
    using f = typename callable_selector<output_result<F, params>>
      ::template f<TC, TC, FC>
      ::template f<
        output_result<F, params>,
        optimized_function<F, params>,
        xs...
      >;
  };


  template<class TC, class FC = uncallable>
  struct if_not_uncallable
  {
    template<class Params, class... xs>
    using f = typename callable_selector<Params>
      ::template f<TC, TC, FC>
      ::template f<Params, xs...>;
  };


  template<class C>
  struct add_uncallable_result
  {
    template<class R, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, union_<uncallable, R>, xs...);
  };


  template<class Callable, class Uncallable = uncallable>
  struct propagate_uncallable
  {
    template<class params, class R, class... xs>
    using f = typename callable_selector<params>
      ::template f<Callable, add_uncallable_output<Callable>, Uncallable>
      ::template f<R, xs...>;
  };


  namespace opti_detail
  {
    template<class params>
    struct remove_uncallable_union_impl
    {
      using type = params;
    };

    template<class x>
    struct remove_uncallable_union_impl<types::basic_union<uncallable, x>>
    {
      using type = x;
    };

    template<class... xs>
    struct remove_uncallable_union_impl<types::basic_union<uncallable, xs...>>
    {
      using type = types::basic_union<xs...>;
    };
  }


  template<class C>
  struct remove_uncallable_union
  {
    template<class params, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      typename opti_detail::remove_uncallable_union_impl<params>::type,
      xs...
    );
  };


  template<class C>
  struct rewrap_uncallable
  {
    template<class params, class... xs>
    using f = typename callable_selector<params>
      ::template f<C, add_uncallable_output<remove_uncallable_union<C>>>
      ::template f<params, xs...>;
  };


  template<class F, class params>
  using transform_from_params_t = typename opti_detail::transform_from_params_impl<F, params>::type;
}


#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/detail/unpack.hpp>

namespace jln::mp::optimizer
{
  struct optimized_for_regular_optimizer
  {
    template<class R, class C, class F, class... xs>
    using f = optimized_result<R, typename F::template f<xs..., C>>;
  };


#define JLN_MP_OPTIMIZER_CREATE_REGULAR_OPTIMIZER_0(func, arity, output) \
  namespace jln::mp::optimizer                                           \
  {                                                                      \
    template<class C, class params>                                      \
    struct optimizer_impl<func<C>, params>                               \
    {                                                                    \
      using type = optimized_for_regular<arity, output>                  \
        ::f<params, func, C>;                                            \
    };                                                                   \
  }

#define JLN_MP_OPTIMIZER_CREATE_REGULAR_OPTIMIZER_1(func, arity, output) \
  namespace jln::mp::optimizer                                           \
  {                                                                      \
    template<class x, class C, class params>                             \
    struct optimizer_impl<func<x, C>, params>                            \
    {                                                                    \
      using type = optimized_for_regular<arity, output>                  \
        ::f<params, func, C, x>;                                         \
    };                                                                   \
  }

#define JLN_MP_OPTIMIZER_CREATE_REGULAR_OPTIMIZER_2(func, arity, output) \
  namespace jln::mp::optimizer                                           \
  {                                                                      \
    template<class x, class y, class C, class params>                    \
    struct optimizer_impl<func<x, y, C>, params>                         \
    {                                                                    \
      using type = optimized_for_regular<arity, output>                  \
        ::f<params, func, C, x, y>;                                      \
    };                                                                   \
  }

  // TODO move output to ::f<output, ...>
  template<int arity, class output>
  struct optimized_for_regular;

  namespace opti_detail
  {
    template<class params>
    struct optimized_for_regular_get_output
    {
      template<class F, class output>
      using f = typename conditional_c<is_real_type_v<params>>
        ::template f<F, always<output>>
        ::template f<params>;
    };

    template<class... xs>
    struct optimized_for_regular_get_output<types::basic_union<xs...>>
    {
      template<class F, class output>
      using f = typename conditional_c<(... && is_real_type_v<xs>)>
        ::template f<transform<F, lift<union_>>, always<output>>
        ::template f<xs...>;
    };
  }

  template<class output>
  struct optimized_for_regular<-1, output>
  {
    template<class params, template<class...> class Tpl, class C, class... xs>
    using f = dispatch_optimizer<optimized_for_regular_optimizer>
      ::template f<
        C,
        typename opti_detail::optimized_for_regular_get_output<params>
          ::template f<Tpl<xs...>, output>,
        typename conditional_c<is_real_type_v<params>>
          ::template f<lift<always>, lift<Tpl>>,
        xs...
      >;
  };

  template<class output>
  struct optimized_for_regular<1, output>
  {
    template<class params, template<class...> class Tpl, class C, class... xs>
    using f = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<dispatch_optimizer<optimized_for_regular_optimizer>>
      ::template f<
        C,
        typename opti_detail::optimized_for_regular_get_output<params>
          ::template f<Tpl<xs...>, output>,
        typename conditional_c<is_real_type_v<params>>
          ::template f<lift<always>, lift<Tpl>>,
        xs...
      >;
  };

  namespace opti_detail
  {
    template<class params>
    struct optimized_for_regular2_selector
    {
      template<class output, template<class...> class Tpl, class C, class... xs>
      using f = typename count_param_always_maybe_never_selector<params, 2>
        ::template f<dispatch_optimizer<optimized_for_regular_optimizer>>
        ::template f<C, output, lift<Tpl>, xs...>;
    };

    template<bool>
    struct optimized_for_regular2_selector_impl;

    template<>
    struct optimized_for_regular2_selector_impl<false>
    {
      template<class x, class y, class output, template<class...> class Tpl, class C, class... xs>
      using f = typename count_param_always_maybe_never_selector<types::basic_seq<x, y>, 2>
        ::template f<dispatch_optimizer<optimized_for_regular_optimizer>>
        ::template f<C, output, lift<Tpl>, xs...>;
    };

    template<>
    struct optimized_for_regular2_selector_impl<true>
    {
      template<class x, class y, class output, template<class...> class Tpl, class C, class... xs>
      using f = dispatch_optimizer<optimized_for_regular_optimizer>
        ::template f<C, typename Tpl<xs...>::template f<x, y>, lift<always>>;
    };

    template<class x, class y>
    struct optimized_for_regular2_selector<types::basic_seq<x, y>>
    {
      template<class output, template<class...> class Tpl, class C, class... xs>
      using f = typename optimized_for_regular2_selector_impl<is_real_type_v<x>
                                                           && is_real_type_v<y>>
        ::template f<x, y, output, Tpl, C, xs...>;
    };

    template<bool>
    struct optimized_for_regular2_with_uncallable_selector_impl;

    template<>
    struct optimized_for_regular2_with_uncallable_selector_impl<false>
    {
      template<class x, class y, class output, template<class...> class Tpl, class C, class... xs>
      using f = typename count_param_always_maybe_never_selector<
        types::basic_union<uncallable, types::basic_seq<x, y>>, 2
      >
        ::template f<dispatch_optimizer<optimized_for_regular_optimizer>>
        ::template f<C, output, lift<Tpl>, xs...>;
    };

    template<>
    struct optimized_for_regular2_with_uncallable_selector_impl<true>
    {
      template<class x, class y, class output, template<class...> class Tpl, class C, class... xs>
      using f = dispatch_optimizer<optimized_for_regular_optimizer>
        ::template f<
          C,
          types::basic_union<uncallable, typename Tpl<xs...>::template f<x, y>>,
          lift<always>
      >;
    };

    template<class x, class y>
    struct optimized_for_regular2_selector<types::basic_union<uncallable, types::basic_seq<x, y>>>
    {
      template<class output, template<class...> class Tpl, class C, class... xs>
      using f = typename optimized_for_regular2_with_uncallable_selector_impl<is_real_type_v<x>
                                                                           && is_real_type_v<y>>
        ::template f<x, y, output, Tpl, C, xs...>;
    };
  }

  template<class output>
  struct optimized_for_regular<2, output>
  {
    template<class params, template<class...> class Tpl, class C, class... xs>
    using f = typename opti_detail::optimized_for_regular2_selector<params>
      ::template f<output, Tpl, C, xs...>;
  };


  template<class R>
  using optimized_for_identity = optimized_result<R, identity>;

  template<class params>
  struct optimizer_impl<identity, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<
        lift<optimized_for_identity>,
        extract_one_param_as_union<add_uncallable_result<lift<optimized_for_identity>>>,
        uncallable>
      ::template f<params>;
  };


  struct optimized_for_transform0
  {
    template<class F, class R, class C>
    using f = optimize<C, types::basic_seq<>>;
  };

  struct optimized_for_transform
  {
    template<class R, class C, class F>
    using f = optimized_result<R, transform<F, C>>;
  };

  struct optimized_for_transform1_or_more
  {
    template<class R, class F, class C>
    using f = typename dispatch_optimizer<optimized_for_transform>
      ::f<C, R, F>;
  };

  struct optimized_for_transform0_or_more
  {
    template<class R, class F, class C>
    using f = typename dispatch_optimizer<optimized_for_transform>
      ::f<C, union_<R, types::basic_seq<>>, F>;
  };

  template<class F, class C, class params>
  struct optimizer_impl<transform<F, C>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 0>
      ::template f<
        optimized_for_transform0,
        optimized_for_transform0_or_more,
        if_not_uncallable<optimized_for_transform1_or_more>>
      ::template f<
        transform_from_params_t<F, params>,
        optimized_function<F, remove_empty_seq_from_union_t<extract_all_types_t<params>>>,
        C
      >;
  };


  struct optimized_if_pred_true
  {
    template<class Pred, class OTC, class OFC>
    using f = OTC;
  };

  struct optimized_if_pred_false
  {
    template<class Pred, class OTC, class OFC>
    using f = OFC;
  };

  struct optimized_for_if
  {
    template<class R, class Pred, class OTC, class OFC>
    using f = optimized_result<R, if_<Pred, OTC, OFC>>;
  };

  struct optimized_if_pred_maybe_true
  {
    template<class Pred, class OTC, class OFC>
    using f = typename optimized_for_if
    ::template f<
      union_<types::uncallable, typename OTC::output_result>,
      Pred, OTC, uncallable_function
    >;
  };

  struct optimized_if_pred_maybe_false
  {
    template<class Pred, class OTC, class OFC>
    using f = typename optimized_for_if
    ::template f<
      union_<types::uncallable, typename OFC::output_result>,
      Pred, uncallable_function, OFC
    >;
  };

  struct optimized_if_pred_number
  {
    template<class Pred, class OTC, class OFC>
    using f = typename optimized_for_if
    ::template f<
      union_<
        typename OTC::output_result,
        typename OFC::output_result
      >,
      Pred,
      typename OTC::function,
      typename OFC::function
    >;
  };

  struct optimized_if_pred_maybe_number
  {
    template<class Pred, class OTC, class OFC>
    using f = typename optimized_for_if
    ::template f<
      union_<
        types::uncallable,
        typename OTC::output_result,
        typename OFC::output_result
      >,
      Pred,
      typename OTC::function,
      typename OFC::function
    >;
  };

  struct optimized_if_pred_nerver_number
  {
    template<class Pred, class TC, class FC, class params>
    using f = types::uncallable;
  };

  template<class Pred, class TC, class FC, class params>
  struct optimizer_impl<if_<Pred, TC, FC>, params>
  {
    using type = typename number_as_bool_selector<output_result<Pred, params>>
      ::template f<
        optimized_if_pred_true,
        optimized_if_pred_false,
        optimized_if_pred_maybe_true,
        optimized_if_pred_maybe_false,
        optimized_if_pred_number,
        optimized_if_pred_maybe_number,
        uncallable>
      ::template f<
        optimized_function<Pred, params>,
        optimize<TC, params>,
        optimize<FC, params>
      >;
  };


  template<class F, class params>
  struct optimizer_impl<tee<F, identity>, params>
  {
    using type = optimize<F, params>;
  };


  struct optimized_for_try_callable
  {
    template<class OptiF, class TC, class FC, class params>
    using f = optimize<
      transform<typename OptiF::function, TC>,
      typename OptiF::output_result
    >;
  };

  struct optimized_for_try_uncallable
  {
    template<class OptiF, class TC, class FC, class params>
    using f = optimize<FC, params>;
  };

  template<class R, class F, class TC, class FC>
  using optimized_for_try_maybe_callable_impl = optimized_result<R, try_<F, TC, FC>>;

  struct optimized_for_try_maybe_callable
  {
    template<class OptiF, class TC, class FC, class params>
    using f = optimized_for_try_maybe_callable_impl<
      union_<
        output_result<TC, typename OptiF::output_result>,
        output_result<FC, params>
      >,
      typename OptiF::function,
      optimized_function<TC, typename OptiF::output_result>,
      optimized_function<FC, params>
    >;
  };

  template<class F, class TC, class FC, class params>
  struct optimizer_impl<try_<F, TC, FC>, params>
  {
    using type = typename callable_selector<output_result<F, params>>
      ::template f<optimized_for_try_callable,
                   optimized_for_try_maybe_callable,
                   optimized_for_try_uncallable>
      ::template f<optimize<F, params>, TC, FC, params>
      ;
  };
}


#undef JLN_SELECT_NUMBER_AS_BOOL_TRUE
#undef JLN_SELECT_NUMBER_AS_BOOL_FALSE
#undef JLN_SELECT_NUMBER_AS_BOOL_MAYBE_TRUE
#undef JLN_SELECT_NUMBER_AS_BOOL_MAYBE_FALSE
#undef JLN_SELECT_NUMBER_AS_BOOL_AS_NUMBER
#undef JLN_SELECT_NUMBER_AS_BOOL_MAYBE_NUMBER
#undef JLN_SELECT_NUMBER_AS_BOOL_NEVER
