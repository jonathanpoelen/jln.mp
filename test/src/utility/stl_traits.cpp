#include "test.hpp"

#include "jln/mp/smp/utility/stl_traits.hpp"

// TODO remove
JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-macros")
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")


TEST_SUITE_BEGIN()

class no_type { using type = no_type;  };

template<class>
struct result { using type = result; };

template<class, class = void>
struct maybe_uncallable_impl
{
  using type = no_type;
};

template<class T>
struct maybe_uncallable_impl<T, std::void_t<typename T::type>>
{
  using type = result<typename T::type>;
};

template<template<class...> class Jln>
struct maybe_uncallable
{
  template<class... xs>
  using f = maybe_uncallable_impl<Jln<xs...>>;
};

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunneeded-member-function")
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-member-function")
JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wnon-virtual-dtor")
struct Class
{
  int i;

  void f1();
  void f2()&;
  void f3()&&;
  void f4()&&;
  void f5() const;
  void f6() const&;
  void f7() const&&;
  void f8() const&&;
  void f9() volatile;
  void f10() volatile&;
  void f11() volatile&&;
  void f12() volatile&&;
  void f13() const volatile;
  void f14() const volatile&;
  void f15() const volatile&&;
  void f16() const volatile&&;
  void f17() noexcept;
  void f18()& noexcept;
  void f19()&& noexcept;
  void f20()&& noexcept;
  void f21() const noexcept;
  void f22() const& noexcept;
  void f23() const&& noexcept;
  void f24() const&& noexcept;
  void f25() volatile noexcept;
  void f26() volatile& noexcept;
  void f27() volatile&& noexcept;
  void f28() volatile&& noexcept;
  void f29() const volatile noexcept;
  void f30() const volatile& noexcept;
  void f31() const volatile&& noexcept;
  void f32() const volatile&& noexcept;
  void f33(...);
  void f34(...)&;
  void f35(...)&&;
  void f36(...)&&;
  void f37(...) const;
  void f38(...) const&;
  void f39(...) const&&;
  void f40(...) const&&;
  void f41(...) volatile;
  void f42(...) volatile&;
  void f43(...) volatile&&;
  void f44(...) volatile&&;
  void f45(...) const volatile;
  void f46(...) const volatile&;
  void f47(...) const volatile&&;
  void f48(...) const volatile&&;
  void f49(...) noexcept;
  void f50(...)& noexcept;
  void f51(...)&& noexcept;
  void f52(...)&& noexcept;
  void f53(...) const noexcept;
  void f54(...) const& noexcept;
  void f55(...) const&& noexcept;
  void f56(...) const&& noexcept;
  void f57(...) volatile noexcept;
  void f58(...) volatile& noexcept;
  void f59(...) volatile&& noexcept;
  void f60(...) volatile&& noexcept;
  void f61(...) const volatile noexcept;
  void f62(...) const volatile& noexcept;
  void f63(...) const volatile&& noexcept;
  void f64(...) const volatile&& noexcept;
  void f65(int, int, ...);
  void f66(int, int, ...)&;
  void f67(int, int, ...)&&;
  void f68(int, int, ...)&&;
  void f69(int, int, ...) const;
  void f70(int, int, ...) const&;
  void f71(int, int, ...) const&&;
  void f72(int, int, ...) const&&;
  void f73(int, int, ...) volatile;
  void f74(int, int, ...) volatile&;
  void f75(int, int, ...) volatile&&;
  void f76(int, int, ...) volatile&&;
  void f77(int, int, ...) const volatile;
  void f78(int, int, ...) const volatile&;
  void f79(int, int, ...) const volatile&&;
  void f80(int, int, ...) const volatile&&;
  void f81(int, int, ...) noexcept;
  void f82(int, int, ...)& noexcept;
  void f83(int, int, ...)&& noexcept;
  void f84(int, int, ...)&& noexcept;
  void f85(int, int, ...) const noexcept;
  void f86(int, int, ...) const& noexcept;
  void f87(int, int, ...) const&& noexcept;
  void f88(int, int, ...) const&& noexcept;
  void f89(int, int, ...) volatile noexcept;
  void f90(int, int, ...) volatile& noexcept;
  void f91(int, int, ...) volatile&& noexcept;
  void f92(int, int, ...) volatile&& noexcept;
  void f93(int, int, ...) const volatile noexcept;
  void f94(int, int, ...) const volatile& noexcept;
  void f95(int, int, ...) const volatile&& noexcept;
  void f96(int, int, ...) const volatile&& noexcept;
};

enum class ScopedSEnum : int {};
enum class ScopedUEnum : unsigned long {};

enum SEnum : int {};
enum UEnum : unsigned {};

enum SLEnum : long {};
enum ULEnum : unsigned long {};

enum SLLEnum : long long {};
enum ULLEnum : unsigned long long {};

union Union { int i; float d; };

struct Empty
{};

struct Parent : Class
{
  int j;
};

struct Virtual
{
  virtual void foo() = 0;
};

struct Final final
{
  int i;
};

struct ConvertibleToScopedEnum
{
  operator ScopedUEnum() const noexcept;

  explicit operator ScopedSEnum() const noexcept;
};

struct AutoConvert
{
JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")
  template<class T>
  operator T() const noexcept;
JLN_MP_DIAGNOSTIC_POP()
};

struct NoCopyable
{
  NoCopyable() noexcept = default;
  NoCopyable(NoCopyable const&) = delete;
  NoCopyable& operator=(NoCopyable const&) = delete;
};

struct NoMovable
{
  NoMovable() noexcept = default;
  NoMovable(NoMovable&&) = delete;
  NoMovable(NoMovable const&) noexcept = default;
  NoMovable& operator=(NoMovable&&) = delete;
  NoMovable& operator=(NoMovable const&) noexcept = default;
};

struct NoDestructible
{
  NoDestructible() noexcept = default;
  ~NoDestructible() = delete;
};

struct NoDefault
{
  NoDefault() {}
  ~NoDefault() {}
  NoDefault(NoDefault&&) {}
  NoDefault(NoDefault const&) {}
  NoDefault& operator=(NoDefault&&) { return *this; }
  NoDefault& operator=(NoDefault const&) { return *this; }
};

struct ThrowableDtor
{
  ThrowableDtor() noexcept = default;
  ThrowableDtor(ThrowableDtor&&) = default;
  ThrowableDtor(ThrowableDtor const&) = default;
  ThrowableDtor& operator=(ThrowableDtor&&) = default;
  ThrowableDtor& operator=(ThrowableDtor const&) = default;
  ~ThrowableDtor() noexcept(false) {}
};

struct NoDefaultConstructible
{
  NoDefaultConstructible(int) {}
};

struct ExplicitCtor
{
  explicit ExplicitCtor() = default;
  explicit ExplicitCtor(int) {}
  explicit ExplicitCtor(int, int) {}

  explicit operator bool ();
};

struct ImplicitBool
{
  operator bool ();
};

struct InitializerListCtor
{
  InitializerListCtor(std::initializer_list<int>);
};

struct Swappable1 : NoCopyable {};
struct Swappable2 : NoCopyable {};
struct Swappable3 : NoCopyable {};

void swap(Swappable1&, Swappable1&);
void swap(Swappable1&, Swappable2&) noexcept;
void swap(Swappable2&, Swappable2&) noexcept;
void swap(Swappable1, Swappable3);
void swap(Swappable2, Swappable3);
void swap(Swappable3&, Swappable2);

struct Constructible1
{
  Constructible1() noexcept = default;
  Constructible1(int, int) noexcept {}
  Constructible1(Constructible1&&) noexcept = default;
  Constructible1(Constructible1 const&) noexcept = default;
  Constructible1& operator=(Constructible1&&) noexcept = default;
  Constructible1& operator=(Constructible1 const&) noexcept = default;
};

struct Constructible2
{
  Constructible2() noexcept(false) = default;
  Constructible2(int, int) noexcept {}
  Constructible2(Constructible2&&) noexcept = default;
  Constructible2(Constructible2 const&) noexcept = default;
  Constructible2& operator=(Constructible2&&) noexcept = default;
  Constructible2& operator=(Constructible2 const&) noexcept = default;
};

struct Constructible3
{
  Constructible3() noexcept = default;
  Constructible3(int, int) noexcept(false) {}
  Constructible3(Constructible3&&) noexcept = default;
  Constructible3(Constructible3 const&) noexcept = default;
  Constructible3& operator=(Constructible3&&) noexcept = default;
  Constructible3& operator=(Constructible3 const&) noexcept = default;
};

struct Constructible4
{
  Constructible4() noexcept = default;
  Constructible4(int, int) noexcept {}
  Constructible4(Constructible4&&) noexcept(false) = default;
  Constructible4(Constructible4 const&) noexcept = default;
  Constructible4& operator=(Constructible4&&) noexcept = default;
  Constructible4& operator=(Constructible4 const&) noexcept = default;
};

struct Constructible5
{
  Constructible5() noexcept = default;
  Constructible5(int, int) noexcept {}
  Constructible5(Constructible5&&) noexcept = default;
  Constructible5(Constructible5 const&) noexcept(false) = default;
  Constructible5& operator=(Constructible5&&) noexcept = default;
  Constructible5& operator=(Constructible5 const&) noexcept = default;
};

struct Constructible6
{
  Constructible6() noexcept = default;
  Constructible6(int, int) noexcept {}
  Constructible6(Constructible6&&) noexcept = default;
  Constructible6(Constructible6 const&) noexcept = default;
  Constructible6& operator=(Constructible6&&) noexcept(false) = default;
  Constructible6& operator=(Constructible6 const&) noexcept = default;
};

struct Constructible7
{
  Constructible7() noexcept = default;
  Constructible7(int, int) noexcept {}
  Constructible7(Constructible7&&) noexcept = default;
  Constructible7(Constructible7 const&) noexcept = default;
  Constructible7& operator=(Constructible7&&) noexcept = default;
  Constructible7& operator=(Constructible7 const&) noexcept(false) = default;
};

struct Constructible8
{
  Constructible8() noexcept = default;
  Constructible8(int, int) noexcept {}
  explicit Constructible8(Constructible8&&) noexcept = default;
  Constructible8(Constructible8 const&) noexcept = default;
  Constructible8& operator=(Constructible8&&) noexcept = default;
  Constructible8& operator=(Constructible8 const&) noexcept = default;
};

struct Constructible9
{
  Constructible9() noexcept = default;
  Constructible9(int, int) noexcept {}
  Constructible9(Constructible9&&) noexcept = default;
  explicit Constructible9(Constructible9 const&) noexcept = default;
  Constructible9& operator=(Constructible9&&) noexcept = default;
  Constructible9& operator=(Constructible9 const&) noexcept(false) = default;
};

struct Assignable1
{
  Assignable1& operator=(Assignable1&&) noexcept = default;
  Assignable1& operator=(Assignable1 const&) noexcept = default;
};

struct Assignable2
{
  Assignable2& operator=(Assignable2&&) noexcept(false) = default;
  Assignable2& operator=(Assignable2 const&) noexcept = default;
};

struct Assignable3
{
  Assignable3& operator=(Assignable3&&) noexcept = default;
  Assignable3& operator=(Assignable3 const&) noexcept(false) = default;
};

struct Assignable4
{
  Assignable4& operator=(Assignable4&&) & { return *this; }
  Assignable4& operator=(Assignable4&&) && = delete;
  Assignable4 const& operator=(Assignable4&&) const& = delete;

  Assignable4& operator=(Assignable4 const&) & = delete;
  Assignable4& operator=(Assignable4 const&) && { return *this; }
  Assignable4 const& operator=(Assignable4 const&) const& = delete;
};

struct Assignable5
{
  Assignable5& operator=(Assignable5&&) & = delete;
  Assignable5& operator=(Assignable5&&) && { return *this; }
  Assignable5 const& operator=(Assignable5&&) const& = delete;

  Assignable5& operator=(Assignable5 const&) & = delete;
  Assignable5& operator=(Assignable5 const&) && = delete;
  Assignable5 const& operator=(Assignable5 const&) const& { return *this; }
};

struct Assignable6
{
  Assignable6& operator=(Assignable6&&) & = delete;
  Assignable6& operator=(Assignable6&&) && = delete;
  Assignable6 const& operator=(Assignable6&&) const& { return *this; }

  Assignable6& operator=(Assignable6 const&) & { return *this; }
  Assignable6& operator=(Assignable6 const&) && = delete;
  Assignable6 const& operator=(Assignable6 const&) const& = delete;
};

// TODO test on XXX(YYY&) with incomplete type for YYY

// TODO lvalue -> rvalue is OK for func
// float f() { return 0.f; }
// float (&&r)(void) = f;

JLN_MP_DIAGNOSTIC_POP()

template<class... xs> struct Params;

template<class x, class y>
struct test_xs_impl
{
  template<class... xs>
  using f = ut::Same<ut::Expected<x>, ut::Result<y>, Params<xs...>, ut::ResultValue>;
};

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-member-function")
struct Ok
{
  static void test()
  {}

  template<class... xs>
  using f = Ok;
};
JLN_MP_DIAGNOSTIC_POP()

template<class x>
struct test_xs_impl<x, x> : Ok
{};

template<class T>
struct to_std_integral_constant
{
  using type = T;
};

template<class T, T value>
struct to_std_integral_constant<jln::mp::traits::emp::integral_constant<T, value>>
{
  using type = std::integral_constant<T, value>;
};

template<class T>
using to_std_integral_constant_t = typename to_std_integral_constant<T>::type;

#define CHECK_IMPL(Std, Jln, ...) test_xs_impl<               \
  typename Std<__VA_ARGS__>::type,                            \
  to_std_integral_constant_t<typename Jln<__VA_ARGS__>::type> \
>::template f<__VA_ARGS__>::test()

#define CHECK_T_V_IMPL(Std, Jln, t, v) test_xs_impl<   \
  typename Std<t, v>::type,                            \
  to_std_integral_constant_t<typename Jln<t, v>::type> \
>::template f<t, number<v>>::test()

template<template<class...> class Std, template<class...> class Jln, class x>
void test_x1_cv()
{
  CHECK_IMPL(Std, Jln, x);
  CHECK_IMPL(Std, Jln, const x);
  CHECK_IMPL(Std, Jln, volatile x);
  CHECK_IMPL(Std, Jln, volatile const x);
}

template<template<class...> class Std, template<class...> class Jln, class x>
void test_x1_cv_ref()
{
  CHECK_IMPL(Std, Jln, x);
  CHECK_IMPL(Std, Jln, x&);
  CHECK_IMPL(Std, Jln, x&&);
  CHECK_IMPL(Std, Jln, const x);
  CHECK_IMPL(Std, Jln, const x&);
  CHECK_IMPL(Std, Jln, const x&&);
  CHECK_IMPL(Std, Jln, volatile x);
  CHECK_IMPL(Std, Jln, volatile x&);
  CHECK_IMPL(Std, Jln, volatile x&&);
  CHECK_IMPL(Std, Jln, volatile const x);
  CHECK_IMPL(Std, Jln, volatile const x&);
  CHECK_IMPL(Std, Jln, volatile const x&&);
}

template<template<class...> class Std, template<class...> class Jln>
void test_x1()
{
  test_x1_cv<Std, Jln, void>();
  test_x1_cv_ref<Std, Jln, decltype(nullptr)>();
  test_x1_cv_ref<Std, Jln, Empty>();
  test_x1_cv_ref<Std, Jln, SEnum>();
  test_x1_cv_ref<Std, Jln, UEnum>();
  test_x1_cv_ref<Std, Jln, ScopedSEnum>();
  test_x1_cv_ref<Std, Jln, ScopedUEnum>();
  test_x1_cv_ref<Std, Jln, ConvertibleToScopedEnum>();
  test_x1_cv_ref<Std, Jln, Union>();
  test_x1_cv_ref<Std, Jln, Class>();
  test_x1_cv_ref<Std, Jln, Parent>();
  test_x1_cv_ref<Std, Jln, Virtual>();
  test_x1_cv_ref<Std, Jln, Final>();
  test_x1_cv_ref<Std, Jln, NoCopyable>();
  test_x1_cv_ref<Std, Jln, NoMovable>();
  test_x1_cv_ref<Std, Jln, NoDestructible>();
  test_x1_cv_ref<Std, Jln, NoDefault>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor>();
  test_x1_cv_ref<Std, Jln, NoDefaultConstructible>();
  test_x1_cv_ref<Std, Jln, ExplicitCtor>();
  test_x1_cv_ref<Std, Jln, ImplicitBool>();
  test_x1_cv_ref<Std, Jln, InitializerListCtor>();
  test_x1_cv_ref<Std, Jln, bool>();
  test_x1_cv_ref<Std, Jln, float>();
  test_x1_cv_ref<Std, Jln, int>();
  test_x1_cv_ref<Std, Jln, int*>();
  test_x1_cv_ref<Std, Jln, int[]>();
  test_x1_cv_ref<Std, Jln, const int[]>();
  test_x1_cv_ref<Std, Jln, volatile int[]>();
  test_x1_cv_ref<Std, Jln, volatile const int[]>();
  // TODO only when no pedantic
  // JLN_MP_DIAGNOSTIC_PUSH()
  // JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wzero-length-array")
  // test_x1_cv_ref<Std, Jln, int[0]>();
  // test_x1_cv_ref<Std, Jln, const int[0]>();
  // test_x1_cv_ref<Std, Jln, volatile int[0]>();
  // test_x1_cv_ref<Std, Jln, volatile const int[0]>();
  // JLN_MP_DIAGNOSTIC_POP()
  test_x1_cv_ref<Std, Jln, int[5]>();
  test_x1_cv_ref<Std, Jln, const int[5]>();
  test_x1_cv_ref<Std, Jln, volatile int[5]>();
  test_x1_cv_ref<Std, Jln, volatile const int[5]>();
  test_x1_cv_ref<Std, Jln, int[][5]>();
  test_x1_cv_ref<Std, Jln, int[5][5]>();
  test_x1_cv_ref<Std, Jln, const int[5][5]>();
  test_x1_cv_ref<Std, Jln, volatile int[5][5]>();
  test_x1_cv_ref<Std, Jln, volatile const int[5][5]>();
  test_x1_cv_ref<Std, Jln, NoMovable[]>();
  test_x1_cv_ref<Std, Jln, const NoMovable[]>();
  test_x1_cv_ref<Std, Jln, volatile NoMovable[]>();
  test_x1_cv_ref<Std, Jln, volatile const NoMovable[]>();
  test_x1_cv_ref<Std, Jln, NoMovable[5]>();
  test_x1_cv_ref<Std, Jln, const NoMovable[5]>();
  test_x1_cv_ref<Std, Jln, volatile NoMovable[5]>();
  test_x1_cv_ref<Std, Jln, volatile const NoMovable[5]>();
  test_x1_cv_ref<Std, Jln, NoMovable[][5]>();
  test_x1_cv_ref<Std, Jln, NoMovable[5][5]>();
  test_x1_cv_ref<Std, Jln, const NoMovable[5][5]>();
  test_x1_cv_ref<Std, Jln, volatile NoMovable[5][5]>();
  test_x1_cv_ref<Std, Jln, volatile const NoMovable[5][5]>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor[]>();
  test_x1_cv_ref<Std, Jln, volatile const ThrowableDtor[5]>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor[][5]>();
  test_x1_cv_ref<Std, Jln, const ThrowableDtor[5][5]>();

  test_x1_cv_ref<Std, Jln, void(int)>();
  test_x1_cv_ref<Std, Jln, void(*)(int)>();
  test_x1_cv_ref<Std, Jln, void(&)(int)>();
  test_x1_cv<Std, Jln, void(int) const>();
  test_x1_cv<Std, Jln, void(int) volatile>();
  test_x1_cv<Std, Jln, void(int) const&>();
  test_x1_cv_ref<Std, Jln, void(int) noexcept>();

  test_x1_cv_ref<Std, Jln, decltype(&Class::i)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f1)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f6)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f11)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f16)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f17)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f37)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f65)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f81)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f96)>();
}

template<template<class...> class Std, template<class...> class Jln>
void test_arithmetic()
{
  test_x1<Std, Jln>();

  test_x1_cv_ref<Std, Jln, char>();
  test_x1_cv_ref<Std, Jln, signed char>();
  test_x1_cv_ref<Std, Jln, unsigned char>();
  test_x1_cv_ref<Std, Jln, wchar_t>();
#ifdef __cpp_char8_t
  test_x1_cv_ref<Std, Jln, char8_t>();
#endif
  test_x1_cv_ref<Std, Jln, char16_t>();
  test_x1_cv_ref<Std, Jln, char32_t>();

  test_x1_cv_ref<Std, Jln, short>();
  test_x1_cv_ref<Std, Jln, unsigned short>();
  test_x1_cv_ref<Std, Jln, int>();
  test_x1_cv_ref<Std, Jln, unsigned int>();
  test_x1_cv_ref<Std, Jln, long>();
  test_x1_cv_ref<Std, Jln, unsigned long>();
  test_x1_cv_ref<Std, Jln, long long>();
  test_x1_cv_ref<Std, Jln, unsigned long long>();

  test_x1_cv_ref<Std, Jln, float>();
  test_x1_cv_ref<Std, Jln, double>();
  test_x1_cv_ref<Std, Jln, long double>();
}

template<template<class...> class Std, template<class...> class Jln, class... xs>
void test_constructible()
{
  test_x1<Std, Jln>();

  CHECK_IMPL(Std, Jln, Constructible1, xs...);
  CHECK_IMPL(Std, Jln, Constructible2, xs...);
  CHECK_IMPL(Std, Jln, Constructible3, xs...);
  CHECK_IMPL(Std, Jln, Constructible4, xs...);
  CHECK_IMPL(Std, Jln, Constructible5, xs...);
  CHECK_IMPL(Std, Jln, Constructible6, xs...);
  CHECK_IMPL(Std, Jln, Constructible7, xs...);
  CHECK_IMPL(Std, Jln, Constructible8, xs...);
  CHECK_IMPL(Std, Jln, Constructible9, xs...);

  CHECK_IMPL(Std, Jln, const Constructible1, xs...);
  CHECK_IMPL(Std, Jln, const Constructible2, xs...);
  CHECK_IMPL(Std, Jln, const Constructible3, xs...);
  CHECK_IMPL(Std, Jln, const Constructible4, xs...);
  CHECK_IMPL(Std, Jln, const Constructible5, xs...);
  CHECK_IMPL(Std, Jln, const Constructible6, xs...);
  CHECK_IMPL(Std, Jln, const Constructible7, xs...);
  CHECK_IMPL(Std, Jln, const Constructible8, xs...);
  CHECK_IMPL(Std, Jln, const Constructible9, xs...);

  CHECK_IMPL(Std, Jln, volatile Constructible1, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible2, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible3, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible4, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible5, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible6, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible7, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible8, xs...);
  CHECK_IMPL(Std, Jln, volatile Constructible9, xs...);

  CHECK_IMPL(Std, Jln, volatile const Constructible1, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible2, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible3, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible4, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible5, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible6, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible7, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible8, xs...);
  CHECK_IMPL(Std, Jln, volatile const Constructible9, xs...);
}

template<template<class...> class Std, template<class...> class Jln, class... xs>
void test_assignable()
{
  test_constructible<Std, Jln, xs...>();

  CHECK_IMPL(Std, Jln, Assignable1, xs...);
  CHECK_IMPL(Std, Jln, Assignable2, xs...);
  CHECK_IMPL(Std, Jln, Assignable3, xs...);
  CHECK_IMPL(Std, Jln, Assignable4, xs...);
  CHECK_IMPL(Std, Jln, Assignable5, xs...);
  CHECK_IMPL(Std, Jln, Assignable6, xs...);
}

template<template<class...> class Std, template<class...> class Jln>
void test_swappable()
{
  test_x1<Std, Jln>();

  CHECK_IMPL(Std, Jln, Assignable1);
  CHECK_IMPL(Std, Jln, Assignable2);
  CHECK_IMPL(Std, Jln, Assignable3);
  CHECK_IMPL(Std, Jln, Assignable4);
  CHECK_IMPL(Std, Jln, Assignable5);
  CHECK_IMPL(Std, Jln, Assignable6);

  CHECK_IMPL(Std, Jln, Assignable1[2]);
  CHECK_IMPL(Std, Jln, Assignable2[2]);
  CHECK_IMPL(Std, Jln, Assignable3[2]);
  CHECK_IMPL(Std, Jln, Assignable4[2]);
  CHECK_IMPL(Std, Jln, Assignable5[2]);
  CHECK_IMPL(Std, Jln, Assignable6[2]);
}

template<template<class...> class Std, template<class...> class Jln>
void test_func_and_mem()
{
  test_x1<Std, Jln>();

  test_x1_cv_ref<Std, Jln, void()>();
  test_x1_cv_ref<Std, Jln, void(...)>();
  test_x1_cv_ref<Std, Jln, void(int)>();
  test_x1_cv_ref<Std, Jln, void(int, ...)>();
  test_x1_cv_ref<Std, Jln, void(*)()>();
  test_x1_cv_ref<Std, Jln, void(*)(...)>();
  test_x1_cv_ref<Std, Jln, void(*)(int)>();
  test_x1_cv_ref<Std, Jln, void(*)(int, ...)>();
  test_x1_cv_ref<Std, Jln, void(&)()>();
  test_x1_cv_ref<Std, Jln, void(&)(...)>();
  test_x1_cv_ref<Std, Jln, void(&)(int)>();
  test_x1_cv_ref<Std, Jln, void(&)(int, ...)>();
  test_x1_cv_ref<Std, Jln, void() noexcept>();
  test_x1_cv_ref<Std, Jln, void(...) noexcept>();
  test_x1_cv_ref<Std, Jln, void(int) noexcept>();
  test_x1_cv_ref<Std, Jln, void(int, ...) noexcept>();
  test_x1_cv_ref<Std, Jln, void(*)() noexcept>();
  test_x1_cv_ref<Std, Jln, void(*)(...) noexcept>();
  test_x1_cv_ref<Std, Jln, void(*)(int) noexcept>();
  test_x1_cv_ref<Std, Jln, void(*)(int, ...) noexcept>();
  test_x1_cv_ref<Std, Jln, void(&)() noexcept>();
  test_x1_cv_ref<Std, Jln, void(&)(...) noexcept>();
  test_x1_cv_ref<Std, Jln, void(&)(int) noexcept>();
  test_x1_cv_ref<Std, Jln, void(&)(int, ...) noexcept>();
  test_x1_cv<Std, Jln, void() const>();
  test_x1_cv<Std, Jln, void() const&>();
  test_x1_cv<Std, Jln, void() const&&>();
  test_x1_cv<Std, Jln, void(...) const>();
  test_x1_cv<Std, Jln, void(...) const&>();
  test_x1_cv<Std, Jln, void(...) const&&>();
  test_x1_cv<Std, Jln, void(int) const>();
  test_x1_cv<Std, Jln, void(int) const&>();
  test_x1_cv<Std, Jln, void(int) const&&>();
  test_x1_cv<Std, Jln, void(int, ...) const>();
  test_x1_cv<Std, Jln, void(int, ...) const&>();
  test_x1_cv<Std, Jln, void(int, ...) const&&>();
  test_x1_cv<Std, Jln, void() volatile>();
  test_x1_cv<Std, Jln, void() volatile&>();
  test_x1_cv<Std, Jln, void() volatile&&>();
  test_x1_cv<Std, Jln, void(...) volatile>();
  test_x1_cv<Std, Jln, void(...) volatile&>();
  test_x1_cv<Std, Jln, void(...) volatile&&>();
  test_x1_cv<Std, Jln, void(int) volatile>();
  test_x1_cv<Std, Jln, void(int) volatile&>();
  test_x1_cv<Std, Jln, void(int) volatile&&>();
  test_x1_cv<Std, Jln, void(int, ...) volatile>();
  test_x1_cv<Std, Jln, void(int, ...) volatile&>();
  test_x1_cv<Std, Jln, void(int, ...) volatile&&>();
  test_x1_cv<Std, Jln, void() volatile const>();
  test_x1_cv<Std, Jln, void() volatile const&>();
  test_x1_cv<Std, Jln, void() volatile const&&>();
  test_x1_cv<Std, Jln, void(...) volatile const>();
  test_x1_cv<Std, Jln, void(...) volatile const&>();
  test_x1_cv<Std, Jln, void(...) volatile const&&>();
  test_x1_cv<Std, Jln, void(int) volatile const>();
  test_x1_cv<Std, Jln, void(int) volatile const&>();
  test_x1_cv<Std, Jln, void(int) volatile const&&>();
  test_x1_cv<Std, Jln, void(int, ...) volatile const>();
  test_x1_cv<Std, Jln, void(int, ...) volatile const&>();
  test_x1_cv<Std, Jln, void(int, ...) volatile const&&>();

  test_x1_cv_ref<Std, Jln, decltype(&Class::i)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f1)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f2)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f3)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f4)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f5)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f6)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f7)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f8)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f9)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f10)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f11)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f12)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f13)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f14)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f15)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f16)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f17)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f18)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f19)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f20)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f21)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f22)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f23)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f24)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f25)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f26)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f27)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f28)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f29)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f30)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f31)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f32)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f33)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f34)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f35)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f36)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f37)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f38)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f39)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f40)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f41)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f42)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f43)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f44)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f45)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f46)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f47)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f48)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f49)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f50)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f51)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f52)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f53)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f54)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f55)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f56)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f57)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f58)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f59)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f60)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f61)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f62)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f63)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f64)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f65)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f66)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f67)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f68)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f69)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f70)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f71)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f72)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f73)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f74)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f75)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f76)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f77)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f78)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f79)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f80)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f81)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f82)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f83)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f84)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f85)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f86)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f87)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f88)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f89)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f90)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f91)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f92)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f93)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f94)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f95)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f96)>();
}

template<template<class...> class Std, template<class...> class Jln>
void test_x1_make_unsigned_signed()
{
  test_x1_cv<Std, Jln, SEnum>();
  test_x1_cv<Std, Jln, ULEnum>();
  test_x1_cv<Std, Jln, SLEnum>();
  test_x1_cv<Std, Jln, ULEnum>();
  test_x1_cv<Std, Jln, SLLEnum>();
  test_x1_cv<Std, Jln, ULLEnum>();
  test_x1_cv<Std, Jln, ScopedSEnum>();
  test_x1_cv<Std, Jln, ScopedUEnum>();

  test_x1_cv<Std, Jln, char>();
  test_x1_cv<Std, Jln, signed char>();
  test_x1_cv<Std, Jln, unsigned char>();
  test_x1_cv<Std, Jln, wchar_t>();
#ifdef __cpp_char8_t
  test_x1_cv<Std, Jln, char8_t>();
#endif
  test_x1_cv<Std, Jln, char16_t>();
  test_x1_cv<Std, Jln, char32_t>();

  test_x1_cv<Std, Jln, short>();
  test_x1_cv<Std, Jln, unsigned short>();
  test_x1_cv<Std, Jln, int>();
  test_x1_cv<Std, Jln, unsigned int>();
  test_x1_cv<Std, Jln, long>();
  test_x1_cv<Std, Jln, unsigned long>();
  test_x1_cv<Std, Jln, long long>();
  test_x1_cv<Std, Jln, unsigned long long>();
}

#ifdef IN_IDE_PARSER
template<template<class...> class Std, template<class...> class Jln, class... xs>
void test_fake()
{
  // ut::same<typename Std<int>::type, Jln<int>>();
}
#  define test_x1 test_fake
#  define test_arithmetic test_fake
#  define test_constructible test_fake
#  define test_assignable test_fake
#  define test_x1_make_unsigned_signed test_fake
#  define test_swappable test_fake
#  define test_func_and_mem test_fake
#endif

TEST()
{
  using namespace jln::mp::traits::emp;
  using jln::mp::number;

  // TODO
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-macros")

  #define SINGLE_CHECK(name, ...) CHECK_IMPL(std::name, name, __VA_ARGS__)
  #define SINGLE_CHECK_M(name, ...) CHECK_IMPL( \
    maybe_uncallable<std::name>::f, maybe_uncallable<name>::f, __VA_ARGS__)
  #define SINGLE_CHECK_T_V(name, ...) CHECK_T_V_IMPL(std::name, name, __VA_ARGS__)
  #define CHECK_X1(name) test_x1<std::name, name>()
  #define CHECK_X1_M(name) test_x1<maybe_uncallable<std::name>::f, maybe_uncallable<name>::f>()
  #define CHECK_X1_T(name) test_x1<std::name, name##_t>()
  #define CHECK_X1_ARITHMETIC(name) test_arithmetic<std::name, name>()
  #define CHECK_F(f, name) f<std::name, name>()
  #define CHECK_F_T(f, name) f<std::name, name##_t>()
  #define CHECK_WITH(name, ...) \
    test_xs_impl<std::name<__VA_ARGS__>::type, name<__VA_ARGS__>::type>::f<__VA_ARGS__>()

  // TODO
  JLN_MP_DIAGNOSTIC_POP()

  CHECK_X1(is_const);
  CHECK_X1(is_volatile);
  // CHECK_X1(is_trivial);
  // CHECK_X1(is_trivially_copyable);
  // CHECK_X1(is_standard_layout);
// #if __cplusplus <= 201703L
//   CHECK_X1(is_pod);
// #endif
//   CHECK_X1(is_empty);
//   CHECK_X1(is_polymorphic);
//   CHECK_X1(is_abstract);
//   CHECK_X1(is_final);
//   CHECK_X1(is_aggregate);
// #if defined(__cpp_lib_is_implicit_lifetime) && __cpp_lib_is_implicit_lifetime >= 202302L
// // template<typename T>
// // struct is_implicit_lifetime : std::disjunction<
// //       std::is_scalar<T>,
// //       std::is_array<T>,
// //       std::is_aggregate<T>,
// //       std::conjunction<
// //             std::is_trivially_destructible<T>,
// //             std::disjunction<
// //                    std::is_trivially_default_constructible<T>,
// //                    std::is_trivially_copy_constructible<T>,
// // std::is_trivially_move_constructible<T>>>> {};
//   CHECK_X1(is_implicit_lifetime);
// #endif
//   CHECK_X1_ARITHMETIC(is_signed);
//   CHECK_X1_ARITHMETIC(is_unsigned);
// #if defined(__cpp_lib_bounded_array_traits) && __cpp_lib_bounded_array_traits >= 201902L
//   CHECK_X1(is_bounded_array);
//   CHECK_X1(is_unbounded_array);
// #endif
// #if defined(__cpp_lib_is_scoped_enum) && __cpp_lib_is_scoped_enum >= 202011L
//   CHECK_X1_ARITHMETIC(is_scoped_enum);
// #endif
//   CHECK_X2(is_convertible);
#if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible >= 201806L
  // CHECK_X2(is_nothrow_convertible);
#endif
// #if defined(__cpp_lib_has_unique_object_representations) && __cpp_lib_has_unique_object_representations >= 201606L
//   CHECK_X1(has_unique_object_representations);
// #endif
  // CHECK_X1(is_void);
//   CHECK_X1_ARITHMETIC(is_integral);
//   CHECK_X1_ARITHMETIC(is_floating_point);
//   CHECK_X1(is_array);
//   CHECK_X1(is_pointer);
//   CHECK_X1(is_lvalue_reference);
//   CHECK_X1(is_rvalue_reference);
//   CHECK_X1(is_reference);
  // CHECK_X1(is_function);
//   CHECK_X1(is_member_object_pointer);
//   CHECK_X1(is_member_function_pointer);
//   CHECK_X1(is_enum);
//   CHECK_X1(is_union);
//   CHECK_X1(is_class);
//   CHECK_X1_ARITHMETIC(is_arithmetic);
//   CHECK_X1(is_fundamental);
//   CHECK_X1(is_object);
//   CHECK_X1(is_member_pointer);
//   CHECK_X1(is_null_pointer);
//   CHECK_X1_ARITHMETIC(is_scalar);
//   CHECK_X1(is_compound);
  // // CHECK_XS(is_constructible);
  // CHECK_F(test_constructible, is_constructible);
  // CHECK_F(test_constructible, is_default_constructible);
  // CHECK_F(test_constructible, is_copy_constructible);
  // CHECK_F(test_constructible, is_move_constructible);
  // // CHECK_XS(is_trivially_constructible);
  // CHECK_F(test_constructible, is_trivially_constructible);
  // CHECK_F(test_constructible, is_trivially_default_constructible);
  // CHECK_F(test_constructible, is_trivially_copy_constructible);
  // CHECK_F(test_constructible, is_trivially_move_constructible);
  // // CHECK_XS(is_nothrow_constructible);
  // CHECK_F(test_constructible, is_nothrow_constructible);
  // CHECK_F(test_constructible, is_nothrow_default_constructible);
  // CHECK_F(test_constructible, is_nothrow_copy_constructible);
  // CHECK_F(test_constructible, is_nothrow_move_constructible);
  // // CHECK_X2(is_assignable);
  // CHECK_F(test_assignable, is_copy_assignable);
  // CHECK_F(test_assignable, is_move_assignable);
  // // CHECK_X2(is_trivially_assignable);
  // CHECK_F(test_assignable, is_trivially_copy_assignable);
  // CHECK_F(test_assignable, is_trivially_move_assignable);
  // // CHECK_X2(is_nothrow_assignable);
  // CHECK_F(test_assignable, is_nothrow_copy_assignable);
  // CHECK_F(test_assignable, is_nothrow_move_assignable);
  CHECK_X1(is_destructible);
  // CHECK_X1(is_trivially_destructible);
  CHECK_X1(is_nothrow_destructible);
#if defined(__cpp_lib_is_swappable) && __cpp_lib_is_swappable >= 201603L
  // CHECK_F(test_swappable, is_swappable);
  // CHECK_F(test_swappable, is_nothrow_swappable);
  // CHECK_X2(is_swappable_with);
  // CHECK_X2(is_nothrow_swappable_with);
#endif
  // CHECK_X1(has_virtual_destructor);
  // CHECK_X2(is_same);
  // CHECK_X2(is_base_of);
#if defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible >= 201907L
  // CHECK_X2(is_layout_compatible);
#endif
#if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible >= 201907L
  // CHECK_X2(is_pointer_interconvertible_base_of);
  // CHECK_X2(is_pointer_interconvertible_with_class);
#endif
  // SINGLE_CHECK(alignment_of, int);
  // SINGLE_CHECK(rank, int);
  // SINGLE_CHECK(rank, int[1]);
  // SINGLE_CHECK(rank, int[1][2]);
  // SINGLE_CHECK(extent, int);
  // SINGLE_CHECK(extent, int[]);
  // SINGLE_CHECK(extent, int[][3]);
  // SINGLE_CHECK(extent, int[2][3]);
  // SINGLE_CHECK_T_V(extent, int, 1);
  // SINGLE_CHECK_T_V(extent, int[], 1);
  // SINGLE_CHECK_T_V(extent, int[][3], 1);
  // SINGLE_CHECK_T_V(extent, int[2][3], 1);
  // CHECK_XS(is_invocable);
  // CHECK_XS(is_invocable_r);
  // CHECK_XS(is_nothrow_invocable);
  // CHECK_XS(is_nothrow_invocable_r);
  // CHECK_XS(invoke_result);
  // CHECK_X2(reference_constructs_from_temporary);
  // CHECK_X2(reference_converts_from_temporary);
  // CHECK_X1(remove_const);
  // CHECK_X1(remove_volatile);
  // CHECK_X1(remove_cv);
  // CHECK_X1(add_const);
  // CHECK_X1(add_volatile);
  // CHECK_X1(add_cv);
  // CHECK_X1(remove_reference);
  // CHECK_X1(add_lvalue_reference);
  // CHECK_X1(add_rvalue_reference);
  // CHECK_F_T(test_x1_make_unsigned_signed, make_signed);
  // CHECK_F_T(test_x1_make_unsigned_signed, make_unsigned);
  // CHECK_X1_T(remove_extent);
  // CHECK_X1_T(remove_all_extents);
  // CHECK_X1_T(remove_pointer);
  // CHECK_X1_T(add_pointer);
  // CHECK_X1(decay);
//   // CHECK_XS(aligned_storage);
//   // CHECK_XS(aligned_union);
// #if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref >= 201811L
//   CHECK_X1(unwrap_ref_decay);
//   CHECK_X1(unwrap_reference);
// #endif
// #if defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref >= 201711L
//   CHECK_X1(remove_cvref);
// #endif
// #if __cplusplus >= 202002L
//   // CHECK_XS(common_reference);
//   // CHECK_XS(basic_common_reference);
// #endif
  // CHECK_X1(underlying_type);
  // CHECK_X1_M(common_type);
  // SINGLE_CHECK_M(common_type, int, float);
  // SINGLE_CHECK_M(common_type, int, float, long long);
  // SINGLE_CHECK_M(common_type, void, void, void);
  // SINGLE_CHECK_M(common_type, int, float, void);
  // SINGLE_CHECK_M(common_type, int, float, long long, void);
  // SINGLE_CHECK_M(common_type, void, int, float, long long);
  // SINGLE_CHECK_M(common_type, int, int*);
  // SINGLE_CHECK_M(common_type, int, int, int, int*);
  // SINGLE_CHECK_M(common_type, int*, int, int, int);
  // SINGLE_CHECK_M(common_type, int, long const&);
  // SINGLE_CHECK_M(common_type, ScopedSEnum, ConvertibleToScopedEnum);
  // SINGLE_CHECK_M(common_type, ScopedUEnum, ConvertibleToScopedEnum);
  // SINGLE_CHECK_M(common_type, AutoConvert, int);
  // SINGLE_CHECK_M(common_type, int, long, AutoConvert, int);
  // SINGLE_CHECK_M(common_type, Parent, Class);
  // SINGLE_CHECK_M(common_type, Parent*, Class*);
  // SINGLE_CHECK_M(common_type, std::true_type, std::false_type);
  // SINGLE_CHECK(extent, int[][3]);
}

// TODO
// TEST()
// {
//   using namespace jln::mp;
//
//   test_unary_pack<traits::is_same>();
//
//   test_context<traits::is_same<>, smp::traits::is_same<>>()
//     .test<std::true_type, int, int>()
//     .test<std::false_type, int, void>()
//     .not_invocable<>()
//     .not_invocable<int>()
//     .not_invocable<int, int, int>()
//     ;
//
//   ut::not_invocable<smp::traits::is_same<bad_function>>();
//   ut::not_invocable<smp::traits::is_same<bad_function>, int>();
//   ut::not_invocable<smp::traits::is_same<bad_function>, int, int, int>();
// }

TEST_SUITE_END()
