#pragma once

#include <jln/mp/functional/memoize.hpp> // uncallable_function
#include <jln/mp/functional/try.hpp> // na

namespace jln::mp::optimizer
{
  using mp::detail::uncallable_function;

  template<class R, class F>
  struct optimized_result_t
  {
    using output_result = R;
    using function = F;
  };

  namespace types
  {
    struct uncallable
    {
      template<class...>
      using f = optimized_result_t<uncallable, uncallable_function>;
    };

    using mp::na;
    class any {};
    class number {};
    class boolean {};
    // fized len pack
    template<class...> class basic_seq {};
    // mp::list of
    template<class...> class basic_list {};
    // pack with 0 or more element
    template<class>    class basic_pack {};
    template<class...> class basic_union {};

    using unknown = basic_union<uncallable, basic_pack<any>>;
    using any_list = basic_list<basic_pack<any>>;

    // uncallable always single or first parameter of basic_union

    // union_<x> -> x
    // union_<x, x, y> -> basic_union<x, y>
    // union_<x, union_<y>> -> basic_union<x, y>
    // union_<x, y, uncallable, z> -> basic_union<uncallable, x, y, z>
    // union_<pack<x>, x> -> basic_pack<x>
    // union_<pack<union_<x, y>>, y> -> basic_union<pack<x>, pack<y>>
    // union_<x, any, seq<...>> -> basic_union<any, seq<...>>
    // union_<x, pack<any>, seq<...>> -> basic_pack<any>
    // union_<x, any, pack<any>, z> -> basic_pack<any>
    // union_<boolean, number> -> number
    // union_<true_, boolean> -> boolean
    // union_<true_, false_> -> boolean
    // union_<true_, mp::number<2>> -> basic_union<true_, number<2>>
    // union_<true_, mp::number<2>, number> -> basic_union<true_, number>

    // pack<uncallable> -> uncallable
    // pack<seq<>> -> basic_seq<>
    // pack<pack<x>> -> basic_pack<x>
    // pack<union_<uncallable, x>> -> basic_union<uncallable, basic_pack<x>>
    // pack<union_<pack<x>, pack<y>, z>> -> basic_union<basic_pack<x>, basic_pack<y>, basic_pack<z>>

    // seq<x> -> x
    // seq<x, uncallable, x> -> uncallable
    // seq<x, x, seq<y, y>, x, x> -> basic_seq<x, x, y, y, x, x>
    // seq<pack<x>, pack<x>, x, pack<x>> -> basic_seq<pack<x>, x, pack<x>>
    // seq<x, x, uncallable, x, x> -> basic_union<uncallable, basic_seq<x, x, x, x>>
    // seq<x, union_<uncallable, x, y>, z>
    //  -> basic_union<uncallable, basic_seq<x, basic_union<x, y>, z>>
    // seq<x, union_<uncallable, x>, union_<uncallable, y, z>>
    //  -> basic_union<uncallable, basic_seq<x, basic_union<y, z>>

    // basic_list<types::...> -> basic_list<types::...>
    // basic_list<not types::...> -> list<...>
  }

  namespace opti_detail
  {
    template<class x> struct pack_impl;
    template<class seq> struct post_normalize_seq;
    template<class seq> struct post_normalize_list;
    template<class... xs> struct union_impl;
    template<class... xs> struct pre_seq_impl;

    template<class x> struct is_real_type_impl;

    template<class R>
    struct optimized_result_impl;
  }

  template<class R, class F>
  using optimized_result = typename opti_detail::optimized_result_impl<R>
    ::template f<F>;

  template<class... xs>
  using pack = typename opti_detail::pack_impl<xs...>::type;

  template<class... xs>
  using union_ = typename opti_detail::union_impl<xs...>::type;

  template<class... xs>
  using seq = typename opti_detail::post_normalize_seq<
    typename opti_detail::pre_seq_impl<xs...>::type
  >::type;

  template<class... xs>
  using list_t = typename opti_detail::post_normalize_list<
    typename opti_detail::pre_seq_impl<xs...>::type
  >::type;

  template<class x>
  inline constexpr bool is_real_type_v = opti_detail::is_real_type_impl<x>::value;

  template<class OptimizerResult>
  using add_uncallable_output_t = optimized_result_t<
    union_<types::uncallable, typename OptimizerResult::output_result>,
    typename OptimizerResult::function
  >;
}


#include <jln/mp/detail/unpack.hpp>
#include <jln/mp/algorithm/unique.hpp>
#include <jln/mp/algorithm/flatten.hpp>
#include <jln/mp/algorithm/remove.hpp>
#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/number/is_number.hpp>

namespace jln::mp::optimizer::opti_detail
{
  template<class> struct is_real_type_impl : true_ {};
  template<> struct is_real_type_impl<types::uncallable> : false_ {};
  template<> struct is_real_type_impl<types::any> : false_ {};
  template<> struct is_real_type_impl<types::number> : false_ {};
  template<> struct is_real_type_impl<types::boolean> : false_ {};
  template<class... xs> struct is_real_type_impl<types::basic_seq<xs...>> : false_ {};
  template<class... xs> struct is_real_type_impl<types::basic_list<xs...>> : false_ {};
  template<class... xs> struct is_real_type_impl<types::basic_pack<xs...>> : false_ {};
  template<class... xs> struct is_real_type_impl<types::basic_union<xs...>> : false_ {};


  template<class R>
  struct optimized_result_impl
  {
    template<class F>
    using f = optimized_result_t<R, always<R>>;
  };

  template<>
  struct optimized_result_impl<types::uncallable>
  : types::uncallable
  {};

#define JLN_MP_OPTIMIZER_TYPE_IMPL(t_param, tpl_param) \
  template<tpl_param>                                  \
  struct optimized_result_impl<t_param>                \
  {                                                    \
    template<class F>                                  \
    using f = optimized_result_t<t_param, F>;          \
  }

  JLN_MP_OPTIMIZER_TYPE_IMPL(types::any, JLN_MP_NIL);
  JLN_MP_OPTIMIZER_TYPE_IMPL(types::number, JLN_MP_NIL);
  JLN_MP_OPTIMIZER_TYPE_IMPL(types::boolean, JLN_MP_NIL);
  JLN_MP_OPTIMIZER_TYPE_IMPL(types::basic_seq<xs...>, class... xs);
  JLN_MP_OPTIMIZER_TYPE_IMPL(types::basic_list<xs...>, class... xs);
  JLN_MP_OPTIMIZER_TYPE_IMPL(types::basic_pack<x>, class x);
  JLN_MP_OPTIMIZER_TYPE_IMPL(types::basic_union<xs...>, class... xs);

#undef JLN_MP_OPTIMIZER_TYPE_IMPL

  // basic_pack

  template<class x>
  struct pack_impl
  {
    using type = types::basic_pack<x>;
  };

  template<class x>
  struct pack_impl<types::basic_pack<x>>
  {
    using type = types::basic_pack<x>;
  };

  template<>
  struct pack_impl<types::basic_seq<>>
  {
    using type = types::basic_seq<>;
  };

  template<>
  struct pack_impl<types::uncallable>
  {
    using type = types::uncallable;
  };

  template<>
  struct pack_impl<types::basic_union<types::uncallable, types::basic_seq<>>>
  {
    using type = types::basic_union<types::uncallable, types::basic_seq<>>;
  };

  template<class x>
  struct pack_impl<types::basic_union<types::uncallable, x>>
  {
    using type = types::basic_union<types::uncallable, types::basic_pack<x>>;
  };

  using pack_from_union = remove<types::basic_seq<>, lift<union_impl>>;

  template<class... xs>
  struct pack_impl<types::basic_union<xs...>>
  {
    using type = typename pack_from_union::f<typename pack_impl<xs>::type...>::type;
  };

  template<class... xs>
  struct pack_impl<types::basic_union<types::uncallable, xs...>>
  {
    using type = typename pack_from_union::f<
      types::uncallable, typename pack_impl<xs>::type...
    >::type;
  };

  // misc

  template<bool>
  struct tpl_or_identity_impl;

  template<>
  struct tpl_or_identity_impl<false>
  {
    template<template<class...> class Tpl, class... xs>
    using f = Tpl<xs...>;
  };

  template<>
  struct tpl_or_identity_impl<true>
  {
    template<template<class...> class Tpl, class x>
    using f = x;
  };

  template<template<class...> class Tpl>
  struct tpl_or_identity
  {
    template<class... xs>
    using f = typename tpl_or_identity_impl<sizeof...(xs) == 1>
      ::template f<Tpl, xs...>;
  };

  // basic_union

  class true_and_false;

  template<class> // any
  inline constexpr int union_num_level = 0;

  template<>
  inline constexpr int union_num_level<true_> = 1;

  template<>
  inline constexpr int union_num_level<false_> = 2;

  template<>
  inline constexpr int union_num_level<true_and_false> = 3;

  template<>
  inline constexpr int union_num_level<types::boolean> = 4;

  template<>
  inline constexpr int union_num_level<types::number> = 5;

  template<int>
  struct union_num_impl;

  template<> struct union_num_impl<1> { using type = true_; };
  template<> struct union_num_impl<2> { using type = false_; };
  template<> struct union_num_impl<3> { using type = true_and_false; };
  template<> struct union_num_impl<4> { using type = types::boolean; };
  template<> struct union_num_impl<5> { using type = types::number; };

  template<class state, int lvl>
  using union_num_t = typename union_num_impl<
    union_num_level<state> < lvl ? lvl : union_num_level<state>
  >::type;


  template<class seq, class item>
  struct pre_normalize_union_impl;

  template<class seq, class item>
  using pre_normalize_union = typename pre_normalize_union_impl<seq, item>::type;

  using union_state = types::basic_seq<
    types::any /* or uncallable */,
    types::any /* or true_ | false_ | true_and_false | boolean | number */
  >;

  template<class u, class n, class... xs, class item>
  struct pre_normalize_union_impl<types::basic_seq<u, n, xs...>, item>
  {
    using type = types::basic_seq<u, n, xs..., item>;
  };

  template<class u, class n, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, n, xs...>, types::uncallable>
  {
    using type = types::basic_seq<types::uncallable, n, xs...>;
  };

  template<class u, class n, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, n, xs...>, true_>
  {
    using type = types::basic_seq<u, union_num_t<n, 1>, xs...>;
  };

  template<class u, class n, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, n, xs...>, false_>
  {
    using type = types::basic_seq<u, union_num_t<n, 2>, xs...>;
  };

  template<class u, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, false_, xs...>, true_>
  {
    using type = types::basic_seq<u, true_and_false, xs...>;
  };

  template<class u, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, true_, xs...>, false_>
  {
    using type = types::basic_seq<u, true_and_false, xs...>;
  };

  template<class u, class n, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, n, xs...>, types::boolean>
  {
    using type = types::basic_seq<u, union_num_t<n, 4>, xs...>;
  };

  template<class u, class n, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, n, xs...>, types::number>
  {
    using type = types::basic_seq<u, types::number, xs...>;
  };

  template<class u, int_ n, class... xs>
  struct pre_normalize_union_impl<types::basic_seq<u, types::number, xs...>, number<n>>
  {
    using type = types::basic_seq<u, types::number, xs...>;
  };


  template<class>
  struct wrap_seq_or_empty_list
  {
    using type = list<>;
  };

  template<class... xs>
  struct wrap_seq_or_empty_list<types::basic_seq<xs...>>
  {
    using type = list<types::basic_seq<xs...>>;
  };


  template<class x>
  struct wrap_non_pack_or_empty_list
  {
    using type = list<x>;
  };

  template<class x>
  struct wrap_non_pack_or_empty_list<types::basic_pack<x>>
  {
    using type = list<>;
  };


  using unpack_for_pre_normalize_union = unpack<fold_left<lift<pre_normalize_union>>>;


  template<bool>
  struct normalize_union_has_any;

  template<>
  struct normalize_union_has_any<true>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs) + 1>
      ::template f<
        list,
        typename conditional_c<(false || ... || std::is_same<types::uncallable, xs>::value)>
        ::template f<
          list<types::uncallable, types::any>,
          list<types::any>
        >,
        typename wrap_seq_or_empty_list<xs>::type...
      >::type;
  };

  template<>
  struct normalize_union_has_any<false>
  {
    template<class... xs>
    using f = unpack_for_pre_normalize_union::f<
      typename detail::_join_select<sizeof...(xs)>
      ::template f<
        list,
        typename wrap_non_pack_or_empty_list<xs>::type...
      >::type,
      union_state
    >;
  };


  template<class x>
  struct pack_as_list_or_empty_list
  {
    using type = list<>;
  };

  template<class x>
  struct pack_as_list_or_empty_list<types::basic_pack<x>>
  {
    using type = list<x>;
  };

  template<bool>
  struct normalize_union_has_pack_any;

  template<class, class>
  struct normalize_union_merge;

  template<>
  struct normalize_union_has_pack_any<true>
  {
    template<class... xs>
    using f = typename conditional_c<(false || ... || std::is_same<types::uncallable, xs>::value)>
      ::template f<
        types::basic_union<types::uncallable, types::basic_pack<types::any>>,
        types::basic_pack<types::any>
      >;
  };

  struct normalize_union_has_pack_any_impl
  {
    template<class... xs>
    using f = typename normalize_union_merge<
      unpack_for_pre_normalize_union::f<
        typename detail::_join_select<sizeof...(xs)>
        ::template f<
          list,
          typename pack_as_list_or_empty_list<xs>::type...
        >::type,
        union_state
      >,
      typename normalize_union_has_any<(false || ... || std::is_same<types::any, xs>::value)>
      ::template f<xs...>
    >::type;
  };

  using unique_union_impl = fold_left<lift<emp::set_push_back>>;

  template<>
  struct normalize_union_has_pack_any<false>
  {
    template<class... xs>
    using f = typename detail::_unpack<
      normalize_union_has_pack_any_impl,
      unique_union_impl::f<list<>, xs...>
    >::type;
  };


  template<class>
  struct wrap_num_state_in_pack_in_list
  {
    using type = mp::list<>;
  };

  template<>
  struct wrap_num_state_in_pack_in_list<true_>
  {
    using type = mp::list<types::basic_pack<true_>>;
  };

  template<>
  struct wrap_num_state_in_pack_in_list<false_>
  {
    using type = mp::list<types::basic_pack<false_>>;
  };

  template<>
  struct wrap_num_state_in_pack_in_list<true_and_false>
  {
    using type = mp::list<types::basic_pack<false_>, types::basic_pack<true_>>;
  };

  template<>
  struct wrap_num_state_in_pack_in_list<types::boolean>
  {
    using type = mp::list<types::basic_pack<types::boolean>>;
  };

  template<>
  struct wrap_num_state_in_pack_in_list<types::number>
  {
    using type = mp::list<types::basic_pack<types::number>>;
  };


  template<class, bool, bool>
  struct wrap_num_state_in_list
  {
    using type = mp::list<>;
  };

  template<>
  struct wrap_num_state_in_list<true_, true, false>
  {
    using type = mp::list<true_>;
  };

  template<>
  struct wrap_num_state_in_list<true_, false, true>
  {
    using type = mp::list<true_>;
  };

  template<>
  struct wrap_num_state_in_list<false_, true, false>
  {
    using type = mp::list<false_>;
  };

  template<bool b>
  struct wrap_num_state_in_list<true_and_false, true, b>
  {
    using type = mp::list<types::boolean>;
  };

  template<bool b>
  struct wrap_num_state_in_list<types::boolean, true, b>
  {
    using type = mp::list<types::boolean>;
  };

  template<bool b>
  struct wrap_num_state_in_list<types::number, true, b>
  {
    using type = mp::list<types::number>;
  };


  template<bool>
  struct union_merge_pack_maybe_remove_number;

  template<>
  struct union_merge_pack_maybe_remove_number<false>
  {
    template<class... xs>
    using f = list<types::basic_pack<xs>...>;
  };

  template<class>
  struct wrap_in_pack_in_list;

  template<>
  struct wrap_in_pack_in_list<true_>
  {
    template<class x>
    using f = list<>;
  };

  template<>
  struct wrap_in_pack_in_list<false_>
  {
    template<class x>
    using f = list<types::basic_pack<x>>;
  };

  template<>
  struct union_merge_pack_maybe_remove_number<true>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<
        list,
        typename wrap_in_pack_in_list<typename detail::_is_number<xs>::type>
        ::template f<xs>...
      >::type;
  };


  template<bool>
  struct union_merge_maybe_remove_number;

  template<>
  struct union_merge_maybe_remove_number<false>
  {
    template<class y, class... xs>
    using f = typename wrap_in_list_c<none_of<is<y>>::template f<xs...>::value>::template f<y>;
  };

  template<>
  struct union_merge_maybe_remove_number<true>
  {
    template<class y, class... xs>
    using f = typename wrap_in_list_c<conditional_c<detail::_is_number<y>::type::value>
      ::template f<always<false_>, none_of<is<y>>>
      ::template f<xs...>
      ::value
    >::template f<y>;
  };


  template<class... xs>
  using union_or_identity_t = typename tpl_or_identity_impl<sizeof...(xs) == 1>
    ::template f<types::basic_union, xs...>;


  template<class... xs>
  using seq_or_identity_t = typename tpl_or_identity_impl<sizeof...(xs) == 1>
    ::template f<types::basic_seq, xs...>;


  template<class u1, class n1, class... xs, class u2, class n2, class... ys>
  struct normalize_union_merge<types::basic_seq<u1, n1, xs...>, types::basic_seq<u2, n2, ys...>>
  {
    using maybe_remove_number = union_merge_maybe_remove_number<
      union_num_level<n1> == 5 || union_num_level<n2> == 5
    >;

    using type = typename detail::_join_select<sizeof...(ys) + 4>
      ::template f<
        union_or_identity_t,
        typename conditional_c<std::is_same<types::uncallable, u1>::value
                            || std::is_same<types::uncallable, u2>::value>
          ::template f<list<types::uncallable>, list<>>,
        typename union_merge_pack_maybe_remove_number<union_num_level<n1> == 5>::template f<xs...>,
        typename wrap_num_state_in_pack_in_list<n1>::type,
        typename wrap_num_state_in_list<
          n2, union_num_level<n1> < union_num_level<n2>, union_num_level<n1> == 2>::type,
        typename maybe_remove_number::template f<ys, xs...>...
      >::type;
  };

  template<class u1, class n1, class... xs, class y, class... ys>
  struct normalize_union_merge<types::basic_seq<u1, n1, xs...>, list<y, ys...>>
  {
    using type = typename detail::_join_select<5>
      ::template f<
        union_or_identity_t,
        typename conditional_c<std::is_same<types::uncallable, u1>::value
                            || std::is_same<types::uncallable, y>::value>
          ::template f<list<types::uncallable>, list<>>,
        typename union_merge_pack_maybe_remove_number<union_num_level<n1> == 5>::template f<xs...>,
        typename wrap_num_state_in_pack_in_list<n1>::type,
        typename conditional_c<std::is_same<types::uncallable, y>::value>
          ::template f<list<>, list<y>>,
        list<ys...>
      >::type;
  };

  template<class... xs>
  using normalize_union_impl = typename normalize_union_has_pack_any<
    (false || ... || std::is_same<types::basic_pack<types::any>, xs>::value)
  >::template f<xs...>;

  using union_impl_f = flatten_once<lift<types::basic_union>, lift<normalize_union_impl>>;

  template<class... xs>
  struct union_impl
  {
    using type = typename union_impl_f::template f<xs...>;
  };

  // common case
  template<class... xs>
  struct union_impl<types::uncallable, types::basic_union<types::uncallable, xs...>>
  {
    using type = types::basic_union<types::uncallable, xs...>;
  };

  // common case
  template<class... xs>
  struct union_impl<types::uncallable, types::basic_union<xs...>>
  {
    using type = types::basic_union<types::uncallable, xs...>;
  };

  template<class x>
  struct union_impl<x>
  {
    using type = x;
  };

  template<>
  struct union_impl<>
  {
    using type = types::basic_seq<>;
  };

  // basic_seq

  template<class l, class item>
  struct pre_normalize_seq_impl
  {
    using type = types::uncallable;
  };

  using seq_state = types::basic_seq<
    types::number /* or uncallable */,
    types::number /* previous pack */
  >;

  template<class u, class p, class... xs, class item>
  struct pre_normalize_seq_impl<types::basic_seq<u, p, xs...>, item>
  {
    using type = types::basic_seq<u, types::number, xs..., item>;
  };

  template<class u, class p, class... xs, class... ys>
  struct pre_normalize_seq_impl<types::basic_seq<u, p, xs...>, types::basic_seq<ys...>>
  {
    using type = types::basic_seq<u, types::number, xs..., ys...>;
  };

  template<class u, class p, class... xs, class y>
  struct pre_normalize_seq_impl<types::basic_seq<u, p, xs...>, types::basic_pack<y>>
  {
    using type = types::basic_seq<u, types::basic_pack<y>, xs..., types::basic_pack<y>>;
  };

  template<class u, class... xs, class y>
  struct pre_normalize_seq_impl<types::basic_seq<u, types::basic_pack<y>, xs...>, types::basic_pack<y>>
  {
    using type = types::basic_seq<u, types::basic_pack<y>, xs...>;
  };

  // seq<..., pack<y>> + y -> seq<..., y, pack<y>>
  template<class u, class... xs, class y>
  struct pre_normalize_seq_impl<types::basic_seq<u, types::basic_pack<y>, xs...>, y>
  {
    using type = typename detail::_join_select<3>::template f<
      types::basic_seq,
      list<u, types::basic_pack<y>>,
      typename detail::rotate_impl<sizeof...(xs)-1>
        ::template f<sizeof...(xs)-1, drop_front_c<1>, xs...>,
      list<y, types::basic_pack<y>>
    >::type;
  };

  template<class u, class p, class... xs>
  struct pre_normalize_seq_impl<types::basic_seq<u, p, xs...>, types::uncallable>
  {
    using type = types::uncallable;
  };

  template<class u, class p, class... xs, class y>
  struct pre_normalize_seq_impl<
    types::basic_seq<u, p, xs...>, types::basic_union<types::uncallable, y>>
  {
    using type = types::basic_seq<types::uncallable, types::number, xs..., y>;
  };

  template<class u, class p, class... xs, class... ys>
  struct pre_normalize_seq_impl<
    types::basic_seq<u, p, xs...>, types::basic_union<types::uncallable, types::basic_seq<ys...>>>
  {
    using type = types::basic_seq<types::uncallable, types::number, xs..., ys...>;
  };

  template<class u, class p, class... xs, class... ys>
  struct pre_normalize_seq_impl<
    types::basic_seq<u, p, xs...>, types::basic_union<types::uncallable, ys...>>
  {
    using type = types::basic_seq<types::uncallable, types::number, xs..., types::basic_union<ys...>>;
  };

  template<class seq, class item>
  using pre_normalize_seq = typename pre_normalize_seq_impl<seq, item>::type;

  template<class seq>
  struct post_normalize_seq
  {
    using type = types::uncallable;
  };

  template<class p, class x>
  struct post_normalize_seq<types::basic_seq<types::number, p, x>>
  {
    using type = x;
  };

  template<class p, class... xs>
  struct post_normalize_seq<types::basic_seq<types::number, p, xs...>>
  {
    using type = types::basic_seq<xs...>;
  };

  template<class p, class x>
  struct post_normalize_seq<types::basic_seq<types::uncallable, p, x>>
  {
    using type = types::basic_union<types::uncallable, x>;
  };

  template<class p, class... xs>
  struct post_normalize_seq<types::basic_seq<types::uncallable, p, xs...>>
  {
    using type = types::basic_union<types::uncallable, types::basic_seq<xs...>>;
  };

  template<class... xs>
  struct pre_seq_impl
  {
    using type = typename detail::fold_left_impl<sizeof...(xs)>
      ::template f<pre_normalize_seq, seq_state, xs...>;
  };

  // basic_list

  template<class seq>
  struct post_normalize_list
  {
    using type = types::uncallable;
  };

  template<bool>
  struct post_normalize_list_or_strong_list;

  template<>
  struct post_normalize_list_or_strong_list<true>
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<>
  struct post_normalize_list_or_strong_list<false>
  {
    template<class... xs>
    using f = types::basic_list<xs...>;
  };

  template<class p, class... xs>
  struct post_normalize_list<types::basic_seq<types::number, p, xs...>>
  {
    using type = typename post_normalize_list_or_strong_list<
      (true && ... && is_real_type_impl<xs>::value)
    >::template f<xs...>;
  };

  template<class p, class... xs>
  struct post_normalize_list<types::basic_seq<types::uncallable, p, xs...>>
  {
    using type = types::basic_union<
      types::uncallable,
      typename post_normalize_list_or_strong_list<
        (true && ... && is_real_type_impl<xs>::value)
      >::template f<xs...>
    >;
  };
}
