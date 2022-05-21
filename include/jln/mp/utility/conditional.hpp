#pragma once

namespace jln::mp
{
  /// \ingroup utility

  template<bool>
  struct conditional_c;

  template<>
  struct conditional_c<true>
  {
    template<class true_value, class false_value>
    using f = true_value;
  };

  template<>
  struct conditional_c<false>
  {
    template<class true_value, class false_value>
    using f = false_value;
  };

  template<class bool_>
  using conditional = conditional_c<bool(bool_::value)>;

  namespace emp
  {
    template<class bool_, class true_value, class false_value>
    using conditional = typename mp::conditional_c<bool(bool_::value)>
      ::template f<true_value, false_value>;

    template<bool bool_, class true_value, class false_value>
    using conditional_c = typename mp::conditional_c<bool_>
      ::template f<true_value, false_value>;
  }
} // namespace jln::mp
