// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_context.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/optimizer/optimizer.hpp"
#include "jln/mp/functional/lift.hpp"

TEST_SUITE_BEGIN()

template<class... xs>
using U = mp::optimizer::types::basic_union<xs...>;

template<class... xs>
using S = mp::optimizer::types::basic_seq<xs...>;

template<class... xs>
using L = mp::optimizer::types::basic_list<xs...>;

template<class x>
using P = mp::optimizer::types::basic_pack<x>;

using n = mp::optimizer::types::number;
using b = mp::optimizer::types::boolean;

class always;
class maybe;
class never;

struct count_param_always_maybe_never_selector
{
  template<class params, class n>
  using f = typename mp::optimizer::count_param_always_maybe_never_selector<params, n::value>
    ::template f<always, maybe, never>;
};

class pred_true;
class pred_false;
class pred_maybe_true;
class pred_maybe_false;
class pred_number;
class pred_maybe_number;
class pred_uncallable;

struct number_as_bool_selector
{
  template<class params>
  using f = typename mp::optimizer::number_as_bool_selector<params>
    ::template f<
      pred_true,
      pred_false,
      pred_maybe_true,
      pred_maybe_false,
      pred_number,
      pred_maybe_number,
      pred_uncallable
    >;
};

struct has_index_selector
{
  template<class params, class n>
  using f = typename mp::optimizer::has_index_selector<params, n::value>
    ::template f<always, maybe, never>;
};

template<int i>
struct dispatch_param_at_c
{
  template<class params>
  using f = typename mp::optimizer::dispatch_param_at_c<params, i>
    ::template f<
      mp::push_front<always>,
      mp::push_front<maybe>,
      mp::push_front<never>>;
};

struct dispatch_split_param_at_1
{
  template<class params>
  using f = typename mp::optimizer::dispatch_split_param_at_1<params>
    ::template f<
      mp::listify,
      mp::push_front<always>,
      mp::push_front<maybe>,
      mp::push_front<never>>;
};

struct dispatch_unpack
{
  template<class params>
  using f = typename mp::optimizer::dispatch_unpack<params>
    ::template f<
      mp::listify,
      mp::push_front<always>,
      mp::push_front<maybe>,
      mp::push_front<never>>;
};

struct select_cond
{
  template<class params>
  using f = typename mp::optimizer::select_cond<params>
    ::template f<always, never>;
};

struct dispatch_bool
{
  template<class params>
  using f = typename mp::optimizer::dispatch_bool<params>
    ::template f<
      mp::push_front<always>,
      mp::push_front<maybe>,
      mp::push_front<never>>;
};

struct dispatch_list
{
  template<class params>
  using f = typename mp::optimizer::dispatch_list<params>
    ::template f<
      mp::push_front<always>,
      mp::push_front<maybe>,
      mp::push_front<never>>;
};

struct dispatch_lists
{
  template<class params>
  using f = typename mp::optimizer::dispatch_lists<params>
    ::template f<
      mp::push_front<always>,
      mp::push_front<maybe>,
      mp::push_front<never>>;
};

struct dispatch_join_list
{
  template<class params>
  using f = typename mp::optimizer::dispatch_join_list<params>
    ::template f<
      mp::push_front<always>,
      mp::push_front<maybe>,
      mp::push_front<never>>;
};


TEST()
{
  namespace mp = jln::mp;
  using namespace jln::mp::optimizer::types;
  using namespace ut::ints;

  test_context<count_param_always_maybe_never_selector, void>()
    .test<always, int, _1>()
    .test<never, S<>, _1>()
    .test<always, S<int>, _1>()
    .test<never, S<int, int>, _1>()
    .test<always, U<int, long>, _1>()
    .test<maybe, U<int, S<int, int>>, _1>()
    .test<maybe, P<int>, _1>()
    ;

  test_context<number_as_bool_selector, void>()
    .test<pred_false, _0>()
    .test<pred_true, _1>()
    .test<pred_true, _2>()
    .test<pred_number, number>()
    .test<pred_number, boolean>()
    .test<pred_uncallable, int>()
    .test<pred_maybe_false, P<_0>>()
    .test<pred_maybe_true, P<_1>>()
    .test<pred_maybe_true, P<_2>>()
    .test<pred_maybe_number, P<number>>()
    .test<pred_maybe_number, P<boolean>>()
    .test<pred_uncallable, P<int>>()
    .test<pred_true, U<_1, _2>>()
    .test<pred_number, U<_0, _2>>()
    .test<pred_number, U<_1, number>>()
    .test<pred_maybe_number, U<int, number>>()
    .test<pred_maybe_false, U<_0, int>>()
    .test<pred_maybe_true, U<_1, int>>()
    .test<pred_maybe_true, U<_2, int>>()
    .test<pred_maybe_number, U<number, int>>()
    .test<pred_uncallable, U<int, long>>()
    ;

  test_context<has_index_selector, void>()
    .test<never, uncallable, _0>()
    .test<never, uncallable, _1>()
    .test<never, S<>, _0>()
    .test<never, S<>, _1>()
    .test<never, S<int>, _1>()
    .test<always, S<int>, _0>()
    .test<never, int, _1>()
    .test<always, int, _0>()
    .test<maybe, P<int>, _0>()
    .test<maybe, P<int>, _1>()
    .test<never, U<int, long>, _1>()
    .test<always, U<int, long>, _0>()
    .test<maybe, U<int, P<long>>, _1>()
    .test<maybe, U<uncallable, int, long>, _0>()
    .test<never, U<uncallable, S<>>, _0>()
    ;

  test_context<dispatch_param_at_c<0>, void>()
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, S<>>, S<>>()
    .test<mp::list<always, int>, int>()
    .test<mp::list<always, int>, S<int, long>>()
    .test<mp::list<maybe, int>, P<int>>()
    .test<mp::list<always, U<int, long>>, U<int, long>>()
    .test<mp::list<always, U<int, long>>, U<int, S<long, double>>>()
    .test<mp::list<maybe, U<int, long>>, U<uncallable, int, long>>()
    .test<mp::list<maybe, long>, U<S<>, long>>()
    .test<mp::list<maybe, U<int, long>>, U<P<int>, long>>()
    .test<mp::list<maybe, int>, U<uncallable, S<>, int>>()
    .test<mp::list<never, U<uncallable, S<>>>, U<uncallable, S<>>>()
    .test<mp::list<always, any>, U<any, S<int, int>>>()
    ;

  test_context<dispatch_param_at_c<1>, void>()
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, S<>>, S<>>()
    .test<mp::list<never, int>, int>()
    .test<mp::list<always, long>, S<int, long>>()
    .test<mp::list<maybe, int>, P<int>>()
    .test<mp::list<never, U<int, long>>, U<int, long>>()
    .test<mp::list<never, U<S<>, long>>, U<S<>, long>>()
    .test<mp::list<maybe, double>, U<S<int, double>, long>>()
    .test<mp::list<maybe, int>, U<P<int>, long>>()
    ;

  test_context<dispatch_split_param_at_1, void>()
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, S<>>, S<>>()
    .test<mp::list<always, mp::list<int, S<>>>, int>()
    .test<mp::list<always, mp::list<int, long>>, S<int, long>>()
    .test<mp::list<maybe, mp::list<int, P<int>>>, P<int>>()
    .test<mp::list<always, mp::list<int, S<P<int>, P<long>>>,
                           mp::list<long, P<long>>>,
      S<P<int>, P<long>>>()
    .test<mp::list<always, mp::list<int, S<P<int>, P<long>, P<int>>>,
                           mp::list<long, S<P<long>, P<int>>>,
                           mp::list<int, P<int>>>,
      S<P<int>, P<long>, P<int>>>()
    .test<mp::list<always, mp::list<int, S<P<int>, P<long>, P<int>, void>>,
                           mp::list<long, S<P<long>, P<int>, void>>,
                           mp::list<int, S<P<int>, void>>,
                           mp::list<void, S<>>>,
      S<P<int>, P<long>, P<int>, void>>()
    .test<mp::list<always, mp::list<int, S<>>,
                           mp::list<long, S<>>>,
      U<int, long>>()
    .test<mp::list<maybe, mp::list<long, S<>>>, U<S<>, long>>()
    .test<mp::list<always, mp::list<int, double>,
                           mp::list<long, S<>>>,
      U<S<int, double>, long>>()
    .test<mp::list<maybe, mp::list<int, P<int>>,
                          mp::list<long, S<>>>,
      U<P<int>, long>>()
    ;

  test_context<dispatch_unpack, void>()
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, S<>>, S<>>()
    .test<mp::list<never, S<int, long>>, S<int, long>>()
    .test<mp::list<never, int>, int>()
    .test<mp::list<never, P<int>>, P<int>>()
    .test<mp::list<maybe, mp::list<P<any>>>, any>()
    .test<mp::list<maybe, mp::list<P<any>>>, P<any>>()
    .test<mp::list<always, mp::list<int>>, P<mp::list<int>>>()
    .test<mp::list<always, mp::list<n>>, P<L<n>>>()
    .test<mp::list<always, mp::list<int>>, L<int>>()
    .test<mp::list<always, mp::list<long, int>>, L<long, int>>()
    .test<mp::list<always, mp::list<n, int>>, L<n, int>>()
    .test<mp::list<always, mp::list<>>, mp::list<>>()
    .test<mp::list<always, mp::list<int>>, mp::list<int>>()
    .test<mp::list<always, mp::list<long, int>>, mp::list<long, int>>()
    .test<mp::list<never, U<int, long>>, U<int, long>>()
    .test<mp::list<maybe, mp::list<long>>, U<S<>, L<long>>>()
    .test<mp::list<maybe, mp::list<long, int>>, U<S<int, double>, long, L<long, int>>>()
    .test<mp::list<always, mp::list<int>, mp::list<long, int>>, U<L<int>, L<long, int>>>()
    ;

  test_context<select_cond, void>()
    .test<uncallable, uncallable>()
    .test<uncallable, int>()
    .test<U<always, never>, any>()
    .test<never, mp::false_>()
    .test<always, mp::true_>()
    .test<never, std::integral_constant<char, 0>>()
    .test<always, std::integral_constant<char, 1>>()
    .test<U<always, never>, boolean>()
    .test<U<uncallable, always, never>, number>()
    .test<uncallable, mp::list<>>()
    .test<U<uncallable, always>, P<mp::true_>>()
    .test<U<uncallable, never>, P<mp::false_>>()
    .test<U<uncallable, always, never>, P<number>>()
    .test<uncallable, P<int>>()
    .test<U<always, never>, U<mp::true_, mp::false_>>()
    .test<U<uncallable, always, never>, U<int, mp::true_, mp::false_, number>>()
    ;

  test_context<dispatch_bool, void>()
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, int>, int>()
    .test<mp::list<maybe, any>, any>()
    .test<mp::list<always, mp::true_>, mp::true_>()
    .test<mp::list<always, mp::false_>, mp::false_>()
    .test<mp::list<always, std::integral_constant<char, 0>>, std::integral_constant<char, 0>>()
    .test<mp::list<always, std::integral_constant<char, 1>>, std::integral_constant<char, 1>>()
    .test<mp::list<always, boolean>, boolean>()
    .test<mp::list<maybe, number>, number>()
    .test<mp::list<never, mp::list<>>, mp::list<>>()
    .test<mp::list<maybe, mp::true_>, P<mp::true_>>()
    .test<mp::list<maybe, mp::false_>, P<mp::false_>>()
    .test<mp::list<maybe, number>, P<number>>()
    .test<mp::list<never, P<int>>, P<int>>()
    .test<mp::list<maybe, mp::true_, mp::false_, number>, U<int, mp::true_, mp::false_, number>>()
    .test<mp::list<maybe, mp::always<void>>, mp::always<void>>()
    ;

  test_context<dispatch_list, void>()
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, int>, int>()
    .test<mp::list<maybe, any_list>, any>()
    .test<mp::list<always, mp::list<>>, mp::list<>>()
    .test<mp::list<always, mp::list<int>>, mp::list<int>>()
    .test<mp::list<always, L<int, n>>, L<int, n>>()
    .test<mp::list<never, P<n>>, P<n>>()
    .test<mp::list<maybe, mp::list<int>, L<number>>, U<int, mp::list<int>, L<number>>>()
    ;

  test_context<dispatch_lists, void>()
    // single element
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, int>, int>()
    .test<mp::list<always>, S<>>()
    .test<mp::list<maybe, any_list>, any>()
    .test<mp::list<always, mp::list<>>, mp::list<>>()
    .test<mp::list<always, mp::list<int>>, mp::list<int>>()
    .test<mp::list<always, L<int, n>>, L<int, n>>()
    .test<mp::list<never, P<n>>, P<n>>()
    .test<mp::list<always, P<mp::list<>>>, P<mp::list<>>>()
    .test<mp::list<maybe, U<mp::list<int>, L<number>>>, U<int, mp::list<int>, L<number>>>()
    // multiple element
    .test<mp::list<never, S<int, int, int>>, S<int, int, int>>()
    .test<mp::list<maybe, L<P<any>>, L<P<any>>>, S<any, any>>()
    .test<mp::list<maybe, L<P<any>>, P<L<P<any>>>>, S<any, P<any>>>()
    .test<mp::list<always, mp::list<>, mp::list<int>>, S<mp::list<>, mp::list<int>>>()
    .test<mp::list<always, mp::list<>, mp::list<>>, S<mp::list<>, mp::list<>>>()
    .test<mp::list<always, L<int>, L<n>, mp::list<int>>, S<L<int>, L<n>, mp::list<int>>>()
    .test<mp::list<always, P<mp::list<>>, P<L<int>>>, S<P<mp::list<>>, P<L<int>>>>()
    .test<mp::list<maybe, P<L<void>>, U<mp::list<int>, L<number>>>,
      S<P<L<void>>, U<int, mp::list<int>, L<number>>>>()
    ;

  test_context<dispatch_join_list, void>()
    // single element
    .test<mp::list<never, uncallable>, uncallable>()
    .test<mp::list<never, int>, int>()
    .test<mp::list<always>, S<>>()
    .test<mp::list<maybe, P<any>>, any>()
    .test<mp::list<maybe, P<any>>, P<any>>()
    .test<mp::list<always>, mp::list<>>()
    .test<mp::list<always, int>, mp::list<int>>()
    .test<mp::list<always, int, n>, L<int, n>>()
    .test<mp::list<never, P<n>>, P<n>>()
    .test<mp::list<always, P<n>>, P<L<n>>>()
    .test<mp::list<always, P<S<n, int>>>, P<L<n, int>>>()
    .test<mp::list<always>, P<mp::list<>>>()
    .test<mp::list<maybe, U<int, number>>, U<int, mp::list<int>, L<number>>>()
    .test<mp::list<maybe, U<int, S<>>>, U<int, mp::list<int>, S<>>>()
    // multiple element
    .test<mp::list<never, S<int, int, int>>, S<int, int, int>>()
    .test<mp::list<maybe, P<any>>, S<any, any>>()
    .test<mp::list<maybe, P<any>>, S<any, P<any>>>()
    .test<mp::list<always, int>, S<mp::list<>, mp::list<int>>>()
    .test<mp::list<always>, S<mp::list<>, mp::list<>>>()
    .test<mp::list<always, int, n, int>, S<L<int>, L<n>, mp::list<int>>>()
    .test<mp::list<always, P<int>>, S<P<mp::list<>>, P<L<int>>>>()
    .test<mp::list<always, P<int>>, S<P<mp::list<int>>, P<L<int>>>>()
    .test<mp::list<maybe, P<void>, U<int, number>>,
      S<P<L<void>>, U<int, mp::list<int>, L<number>>>>()
    ;

  test_context<mp::lift<mp::optimizer::extract_all_types_t>, void>()
    .test<int, int>()
    .test<S<>, S<>>()
    .test<int, S<int>>()
    .test<int, S<int, int>>()
    .test<U<int, long>, S<int, long>>()
    .test<U<int, long>, U<int, long>>()
    .test<int, U<int, S<int, int>>>()
    .test<U<int, long>, U<int, S<int, long>>>()
    .test<U<int, S<>>, P<int>>()
    .test<L<int, long>, L<int, long>>()
    ;

  test_context<mp::lift<mp::optimizer::remove_empty_seq_from_union_t>, void>()
    .test<int, int>()
    .test<S<>, S<>>()
    .test<S<int>, S<int>>()
    .test<U<int, long>, U<int, long>>()
    .test<U<int, long>, U<int, long, S<>>>()
    ;
}

TEST_SUITE_END()
