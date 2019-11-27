#pragma once

#include "../algorithm/transform.hpp"
#include "../utility/unpack.hpp"
#include "../../list/size.hpp"
#include "../../list/is_list.hpp"
#include "../../functional/if.hpp"
#include "../../number/operators.hpp"
#include "../../algorithm/same.hpp"
#include "../../algorithm/zip.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using zip = contract<
    mp::if_<
      mp::transform<mp::is_list<>, mp::and_<>>,
      mp::transform<mp::unpack<mp::size<>>, mp::same<>>
    >,
    mp::zip<subcontract<C>>>;

  template<class F = listify, class C = listify>
  using zip_with = zip<transform<unpack<F>, C>>;

  template<class C = listify>
  using zip_shortest = contract<
    mp::transform<mp::is_list<>, mp::and_<>>,
    mp::zip_shortest<subcontract<C>>>;

  template<class F = listify, class C = listify>
  using zip_shortest_with = zip_shortest<transform<unpack<F>, C>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, zip<C>>
  {
    using type = smp::zip<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, zip_shortest<C>>
  {
    using type = smp::zip_shortest<sfinae<C>>;
  };
}