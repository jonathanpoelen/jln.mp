#pragma once

namespace ut
{
namespace
{
  template<class T>
  struct MustBeSame
  {};

  template<class T>
  struct MustBeDifferent
  {
    constexpr MustBeDifferent() = default;
    MustBeDifferent(MustBeDifferent const&) = delete;

    template<class U>
    constexpr MustBeDifferent(MustBeDifferent<U> const&)
    {}
  };

  template<class T>
  struct Result
  {};

  template<class T>
  struct Expected
  {};

  template<class T>
  struct NotExpected
  {};

  template<class expected, class result>
  struct Same;

  template<class notExpected, class result>
  struct Different;

  template<class expected, class result>
  struct Same<Expected<expected>, Result<result>>
  {
    static constexpr void test()
    {
      MustBeSame<expected> _ = MustBeSame<result>();
      (void)_;
    }
  };

  template<class notExpected, class result>
  struct Different<NotExpected<notExpected>, Result<result>>
  {
    static constexpr void test()
    {
      MustBeDifferent<notExpected> _ = MustBeDifferent<result>();
      (void)_;
    }
  };

  template<class expected, class result>
  constexpr void same()
  {
    Same<Expected<expected>, Result<result>>::test();
  }

  template<class notExpected, class result>
  constexpr void not_same()
  {
    Different<NotExpected<notExpected>, Result<result>>::test();
  }

  template<class R, class C, class... xs>
  constexpr void invoke_r()
  {
    Same<Expected<R>, Result<typename C::template f<xs...>>>::test();
  }
}
}
