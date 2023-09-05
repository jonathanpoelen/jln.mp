// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

namespace ut
{
namespace
{
  template<class Tag, class T>
  struct MustBeSame
  {
    constexpr MustBeSame() = default;

    template<class Tag2>
    constexpr MustBeSame(MustBeSame<Tag2, T> const&)
    {}
  };

  class ExpectedValue;
  class ResulValue;

  template<class Tag, class T>
  struct MustBeDifferent
  {
    constexpr MustBeDifferent() = default;
    MustBeDifferent(MustBeDifferent const&) = delete;

    template<class Tag2>
    constexpr MustBeDifferent(MustBeDifferent<Tag2, T> const&) = delete;

    template<class Tag2, class U>
    constexpr MustBeDifferent(MustBeDifferent<Tag2, U> const&)
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

  template<class expected, class result, class expectedName, class resultName>
  struct Same;

  template<class notExpected, class result, class expectedName, class resultName>
  struct Different;

  template<class expected, class result, class expectedName, class resultName>
  struct Same<Expected<expected>, Result<result>, expectedName, resultName>
  {
    static constexpr void test()
    {
      MustBeSame<expectedName, expected> _ = MustBeSame<resultName, result>();
      (void)_;
    }
  };

  template<class notExpected, class result, class expectedName, class resultName>
  struct Different<NotExpected<notExpected>, Result<result>, expectedName, resultName>
  {
    static constexpr void test()
    {
      MustBeDifferent<expectedName, notExpected> _ = MustBeDifferent<resultName, result>();
      (void)_;
    }
  };

  template<class expected, class result,
    class expectedName = ExpectedValue, class resultName = ResulValue>
  constexpr void same()
  {
    Same<Expected<expected>, Result<result>, expectedName, resultName>::test();
  }

  template<class notExpected, class result,
    class expectedName = ExpectedValue, class resultName = ResulValue>
  constexpr void not_same()
  {
    Different<NotExpected<notExpected>, Result<result>, expectedName, resultName>::test();
  }

  template<class R, class C, class... xs>
  constexpr void invoke_r()
  {
    Same<Expected<R>, Result<typename C::template f<xs...>>, ExpectedValue, ResulValue>::test();
  }
}
}
