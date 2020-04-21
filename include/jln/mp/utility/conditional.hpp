#pragma once

namespace jln::mp
{
  /// \ingroup utility

  template<bool>
  struct conditional_c
  {
    template<class x, class y>
    using f = x;
  };

  /// \cond
  template<>
  struct conditional_c<false>
  {
    template<class x, class y>
    using f = y;
  };
  /// \endcond

  template<class v>
  using conditional = conditional_c<bool(v::value)>;

  namespace emp
  {
    template<class v, class x, class y>
    using conditional = typename mp::conditional_c<bool(v::value)>
      ::template f<x, y>;

    template<bool cond, class x, class y>
    using conditional_c = typename mp::conditional_c<cond>
      ::template f<x, y>;
  }
} // namespace jln::mp
