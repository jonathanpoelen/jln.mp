// for comp in g++ clang++ ; do echo $comp; for ((i=0;i<5;++i)) do /usr/bin/time --format='%Es - %MK' $comp test.cpp -fsyntax-only -std=c++20 -I ~/projects/jln.mpl/include -DINCLUDE='"jln/mp/utility/stl_traits.hpp"' -DJLN_MP_NO_STL_TRAIT=1 -DJLN_MP_USE_OPTIONAL_BUILTIN=0 -DIMPL=0 -DNELEM=500 -DCHECK=0 -DNREPEAT=1 -DALGO='transform<t>' -DEXTRA='template<class T> struct S { enum E : int; void f(T) noexcept; }; template<class T> struct P { S<T>& operator*() noexcept; }; struct t { template<class T> using f = traits::emp::is_nothrow_invocable_t<decltype(&S<T>::f), P<T>, T>; };' || break ; done ; done

#include <jln/mp/algorithm/iota.hpp>
#include <jln/mp/algorithm/repeat.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>
#ifdef INCLUDE
# include INCLUDE
#endif

#ifndef NELEM
# define NELEM 2
#endif
#ifndef NREPEAT
# define NREPEAT 2
#endif
#ifndef CHECK
# define CHECK 0
#endif

#ifndef ALGO
# error "missing ALGO"
# define ALGO listify
#endif

#if NREPEAT == 1
# define REPETABLE_ALGO ALGO
#else
# define REPETABLE_ALGO repeat_c<NREPEAT, ALGO>
#endif

namespace n
{
  using namespace jln::mp;

#ifdef EXTRA
  EXTRA
#endif

#if IMPL == 0
  using l = emp::make_int_sequence_c<NELEM, REPETABLE_ALGO>;
#elif IMPL == 1
  using l = emp::make_int_sequence_c<NELEM, transform<
    make_int_sequence<REPETABLE_ALGO>
  >>;
#else
  struct test
  {
    template<class n>
    using f = emp::iota_c<n::value, NELEM, 1, REPETABLE_ALGO>;
  };

  using l = emp::make_int_sequence_c<NELEM, transform<test>>;
#endif

#if CHECK
  l value = 0;
#endif

}
