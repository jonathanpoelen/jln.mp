#pragma once

#include "../functional/always.hpp"

namespace jln::mp
{
  struct unsatisfactory_concept_error;
  using unsatisfactory_concept = always<unsatisfactory_concept_error>;

  namespace detail
  {
    template<class predicate, template<class...> class function, class... args>
    struct _when;
  }

  template<class predicate, template<class...> class function, class... args>
  struct when
  {
    template<class... xs>
    using f = typename detail::_when<predicate, function, args...>
      ::template f<xs...>
      ::template f<>;
  };
}


#include "../functional/is_invovable.hpp"
#include "../functional/if.hpp"
#include "sfinae.hpp"

namespace jln::mp::detail
{
  template<class predicate, template<class...> class function, class... args>
  struct _sfinae<when<predicate, function, args...>>
  {
    using type = when<predicate, function, args...>;
  };

  template<class function>
  struct _when_impl
  {
    template<class... xs>
    using f = always<typename function::template f<xs...>>;
  };

  template<class function, class when>
  using _when_sfinae = typename conditional<std::is_same<unsafe_sfinae<function>, when>>::template f<
    if_<is_invocable<function>, _when_impl<function>, unsatisfactory_concept>,
    unsafe_sfinae<function>
  >;

  template<class predicate, template<class...> class function, class... args>
  struct _when
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<
        _when_sfinae<function<args...>, when<predicate, function, args...>>,
        unsatisfactory_concept>
      ::template f<xs...>;
  };

  template<
    class predicate, template<class...> class function,
    class subpredicate, template<class...> class subfunction, class... args>
  struct _when<predicate, function, when<subpredicate, subfunction, args...>>
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<function<_when<subpredicate, subfunction, args...>>, unsatisfactory_concept>
      ::template f<xs...>;
  };
}
