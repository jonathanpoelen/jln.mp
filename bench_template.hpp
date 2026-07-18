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

namespace n
{
  using namespace jln::mp;


#if NREPEAT == 1
using Algo = ALGO;
#else
using Algo = repeat_c<NREPEAT, ALGO>;
#endif

// Algo<0..NELEM>
#if IMPL == 0
  using l = emp::make_int_sequence_c<NELEM, Algo>;
// Algo<0>, Algo<0,1> .. Algo<0..(NELEM-1)>
#elif IMPL == 1
  using l = emp::make_int_sequence_c<NELEM, transform<
    make_int_sequence<Algo>
  >>;
// Algo<0..(0+NELEM)>, Algo<1..(1+NELEM)> .. Algo<(NELEM-1)..(NELEM-1+NELEM)>
#else
  struct test
  {
    template<class n>
    using f = emp::iota_c<n::value, NELEM, 1, Algo>;
  };

  using l = emp::make_int_sequence_c<NELEM, transform<test>>;
#endif

#if CHECK
  l value = 0;
#endif

}
