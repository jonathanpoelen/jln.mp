#pragma once

#include <jln/mp/smp/algorithm/zip.hpp>
#include <jln/mp/smp/algorithm/matrix_longest.hpp>
#include <jln/mp/algorithm/zip_longest.hpp>

namespace jln::mp::smp
{
  template<class FillValue, class C = listify>
  using zip_longest = right_matrix_longest<FillValue, zip<C>>;

  template<class FillValue, class F = listify, class C = listify>
  using zip_longest_with = right_matrix_longest<FillValue, zip_with<F, C>>;
}
