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

#if IMPL == 0
  using l = emp::make_int_sequence_c<NELEM, repeat_c<NREPEAT, ALGO>>;
#elif IMPL == 1
  using l = emp::make_int_sequence_c<NELEM, transform<
    make_int_sequence<repeat_c<NREPEAT, ALGO>>
  >>;
#else
  struct test
  {
    template<class n>
    using f = emp::iota_c<n::value, NELEM, 1, repeat_c<NREPEAT, ALGO>>;
  };

  using l = emp::make_int_sequence_c<NELEM, transform<test>>;
#endif

#if CHECK
  l value = 0;
#endif

}
