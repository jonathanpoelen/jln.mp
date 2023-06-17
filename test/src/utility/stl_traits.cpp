#include "test.hpp"

#include "jln/mp/utility/stl_traits.hpp"

#include <functional> // reference_wrapper
#include <initializer_list>


// TODO remove
JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-macros")
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")

class JlnResult;

TEST_SUITE_BEGIN()

class notype { using type = notype;  };

template<class T>
struct result { using type = T; };

template<class, class = void>
struct maybe_uncallable_impl
{
  using type = notype;
};

template<class T>
struct maybe_uncallable_impl<T, std::void_t<typename T::type>>
  : result<typename T::type>
{};

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
  void(*fn)();

  jln::mp::number<1> f1();
  jln::mp::number<2> f2()&;
  jln::mp::number<3> f3()&&;
  jln::mp::number<4> f4() const;
  jln::mp::number<5> f5() const&;
  jln::mp::number<6> f6() const&&;
  jln::mp::number<7> f7() volatile;
  jln::mp::number<8> f8() volatile&;
  jln::mp::number<9> f9() volatile&&;
  jln::mp::number<10> f10() const volatile;
  jln::mp::number<11> f11() const volatile&;
  jln::mp::number<12> f12() const volatile&&;
  jln::mp::number<13> f13() noexcept;
  jln::mp::number<14> f14()& noexcept;
  jln::mp::number<15> f15()&& noexcept;
  jln::mp::number<16> f16() const noexcept;
  jln::mp::number<17> f17() const& noexcept;
  jln::mp::number<18> f18() const&& noexcept;
  jln::mp::number<19> f19() volatile noexcept;
  jln::mp::number<20> f20() volatile& noexcept;
  jln::mp::number<21> f21() volatile&& noexcept;
  jln::mp::number<22> f22() const volatile noexcept;
  jln::mp::number<23> f23() const volatile& noexcept;
  jln::mp::number<24> f24() const volatile&& noexcept;
  jln::mp::number<25> f25(...);
  jln::mp::number<26> f26(...)&;
  jln::mp::number<27> f27(...)&&;
  jln::mp::number<28> f28(...) const;
  jln::mp::number<29> f29(...) const&;
  jln::mp::number<30> f30(...) const&&;
  jln::mp::number<31> f31(...) volatile;
  jln::mp::number<32> f32(...) volatile&;
  jln::mp::number<33> f33(...) volatile&&;
  jln::mp::number<34> f34(...) const volatile;
  jln::mp::number<35> f35(...) const volatile&;
  jln::mp::number<36> f36(...) const volatile&&;
  jln::mp::number<37> f37(...) noexcept;
  jln::mp::number<38> f38(...)& noexcept;
  jln::mp::number<39> f39(...)&& noexcept;
  jln::mp::number<40> f40(...) const noexcept;
  jln::mp::number<41> f41(...) const& noexcept;
  jln::mp::number<42> f42(...) const&& noexcept;
  jln::mp::number<43> f43(...) volatile noexcept;
  jln::mp::number<44> f44(...) volatile& noexcept;
  jln::mp::number<45> f45(...) volatile&& noexcept;
  jln::mp::number<46> f46(...) const volatile noexcept;
  jln::mp::number<47> f47(...) const volatile& noexcept;
  jln::mp::number<48> f48(...) const volatile&& noexcept;
  jln::mp::number<49> f49(int, int, ...);
  jln::mp::number<50> f50(int, int, ...)&;
  jln::mp::number<51> f51(int, int, ...)&&;
  jln::mp::number<52> f52(int, int, ...) const;
  jln::mp::number<53> f53(int, int, ...) const&;
  jln::mp::number<54> f54(int, int, ...) const&&;
  jln::mp::number<55> f55(int, int, ...) volatile;
  jln::mp::number<56> f56(int, int, ...) volatile&;
  jln::mp::number<57> f57(int, int, ...) volatile&&;
  jln::mp::number<58> f58(int, int, ...) const volatile;
  jln::mp::number<59> f59(int, int, ...) const volatile&;
  jln::mp::number<60> f60(int, int, ...) const volatile&&;
  jln::mp::number<61> f61(int, int, ...) noexcept;
  jln::mp::number<62> f62(int, int, ...)& noexcept;
  jln::mp::number<63> f63(int, int, ...)&& noexcept;
  jln::mp::number<64> f64(int, int, ...) const noexcept;
  jln::mp::number<65> f65(int, int, ...) const& noexcept;
  jln::mp::number<66> f66(int, int, ...) const&& noexcept;
  jln::mp::number<67> f67(int, int, ...) volatile noexcept;
  jln::mp::number<68> f68(int, int, ...) volatile& noexcept;
  jln::mp::number<69> f69(int, int, ...) volatile&& noexcept;
  jln::mp::number<70> f70(int, int, ...) const volatile noexcept;
  jln::mp::number<71> f71(int, int, ...) const volatile& noexcept;
  jln::mp::number<72> f72(int, int, ...) const volatile&& noexcept;

  jln::mp::number<1> g1(int);
  jln::mp::number<2> g2(int) const;
  jln::mp::number<1> g3(int) noexcept;
  jln::mp::number<2> g4(int) const noexcept;
};

struct Callable
{
  jln::mp::number<1> operator()();
  jln::mp::number<2> operator()() const;
  jln::mp::number<3> operator()(int);
  jln::mp::number<4> operator()(int) volatile;
};

struct NoexceptCallable
{
  jln::mp::number<1> operator()() noexcept;
  jln::mp::number<2> operator()() const noexcept;
  jln::mp::number<3> operator()(int) noexcept;
  jln::mp::number<4> operator()(int) volatile noexcept;
};

struct Ref : std::reference_wrapper<int> {};

struct DereferableToClass
{
  Class& operator*() const;
};

struct NoexceptDereferableToClass
{
  Class& operator*() const noexcept;
};

class incomplete;

enum class ScopedSEnum : int {};
enum class ScopedUEnum : unsigned long {};

enum SEnum : int {};
enum UEnum : unsigned {};

enum SLEnum : long {};
enum ULEnum : unsigned long {};

enum SLLEnum : long long {};
enum ULLEnum : unsigned long long {};

union Union { int i; float d; };

struct Any
{
  template<class T>
  Any(T&&) {}
};

struct NoexceptAny
{
  template<class T>
  NoexceptAny(T&&) noexcept {}
};

struct Castable
{
  template<class T>
  operator T () const;
};

struct NoexceptCastable
{
  template<class T>
  operator T () const noexcept;
};

struct Empty
{};

struct Aggregate
{
  int i;
};

struct Aggregate2
{
  int j;
};

struct NotStandardLayout : Aggregate, Aggregate2
{};

struct WithProtected
{
  int i;

protected:
  int j;
};

struct Child : Class
{
  int j;
};

class Empty2 {};

struct PriEmptyPubEmpty2 : Empty, public Empty2
{
  int x;
};

struct NonStdLayout : public PriEmptyPubEmpty2
{
  int y;
};

struct PubMem1 { int x; };
struct PubMem2 { int y; };
struct PubMem1PubMem2 : PubMem1, PubMem2 {};

struct CtorInt
{
  CtorInt(int);
};

struct CtorInt2
{
  CtorInt2(int&&);
};

struct Abstract
{
  virtual void foo() = 0;
};

struct Virtual
{
  virtual void foo() {}
};

struct VirtualInParent : Virtual
{};

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

struct ExplicitCopyCtor
{
  ExplicitCopyCtor() = default;
  explicit ExplicitCopyCtor(ExplicitCopyCtor const&) {}
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
  using f = ut::Same<ut::Expected<x>, ut::Result<y>, Params<xs...>, JlnResult>;
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
struct to_emp_integral_constant
{
  using type = T;
};

template<class T, T value>
struct to_emp_integral_constant<std::integral_constant<T, value>>
{
  using type = jln::mp::traits::emp::integral_constant<T, value>;
};

template<class T>
using to_emp_integral_constant_t = typename to_emp_integral_constant<T>::type;

#define CHECK_IMPL(Std, Jln, ...) test_xs_impl<                \
  to_emp_integral_constant_t<typename Std<__VA_ARGS__>::type>, \
  typename Jln<__VA_ARGS__>::type                              \
>::template f<__VA_ARGS__>::test()

#define CHECK_T_V_IMPL(Std, Jln, t, v) test_xs_impl<    \
  to_emp_integral_constant_t<typename Std<t, v>::type>, \
  typename Jln<t, v>::type                              \
>::template f<t, number<v>>::test()

template<template<class...> class Std, template<class...> class Jln, class x>
static void test_x1_cv()
{
  CHECK_IMPL(Std, Jln, x);
  CHECK_IMPL(Std, Jln, const x);
  CHECK_IMPL(Std, Jln, volatile x);
  CHECK_IMPL(Std, Jln, volatile const x);
}

template<template<class...> class Std, template<class...> class Jln, class T, class... Ts>
static void test_x1_cv_ref()
{
  CHECK_IMPL(Std, Jln, T, Ts...);
  CHECK_IMPL(Std, Jln, T&, Ts...);
  CHECK_IMPL(Std, Jln, T&&, Ts...);
  CHECK_IMPL(Std, Jln, const T, Ts...);
  CHECK_IMPL(Std, Jln, const T&, Ts...);
  CHECK_IMPL(Std, Jln, const T&&, Ts...);
  CHECK_IMPL(Std, Jln, volatile T, Ts...);
  CHECK_IMPL(Std, Jln, volatile T&, Ts...);
  CHECK_IMPL(Std, Jln, volatile T&&, Ts...);
  CHECK_IMPL(Std, Jln, volatile const T, Ts...);
  CHECK_IMPL(Std, Jln, volatile const T&, Ts...);
  CHECK_IMPL(Std, Jln, volatile const T&&, Ts...);
}

template<template<class...> class Std, template<class...> class Jln>
static auto test_x1()
{
  test_x1_cv<Std, Jln, void>();
  test_x1_cv_ref<Std, Jln, decltype(nullptr)>();
  test_x1_cv_ref<Std, Jln, Empty>();
  test_x1_cv_ref<Std, Jln, Aggregate>();
  test_x1_cv_ref<Std, Jln, WithProtected>();
  test_x1_cv_ref<Std, Jln, SEnum>();
  test_x1_cv_ref<Std, Jln, UEnum>();
  test_x1_cv_ref<Std, Jln, ScopedSEnum>();
  test_x1_cv_ref<Std, Jln, ScopedUEnum>();
  test_x1_cv_ref<Std, Jln, ConvertibleToScopedEnum>();
  test_x1_cv_ref<Std, Jln, Union>();
  test_x1_cv_ref<Std, Jln, Class>();
  test_x1_cv_ref<Std, Jln, Child>();
  test_x1_cv_ref<Std, Jln, Abstract>();
  test_x1_cv_ref<Std, Jln, Virtual>();
  test_x1_cv_ref<Std, Jln, VirtualInParent>();
  test_x1_cv_ref<Std, Jln, Final>();
  test_x1_cv_ref<Std, Jln, NoCopyable>();
  test_x1_cv_ref<Std, Jln, NoMovable>();
  test_x1_cv_ref<Std, Jln, NoDestructible>();
  test_x1_cv_ref<Std, Jln, NoDefault>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor>();
  test_x1_cv_ref<Std, Jln, NoDefaultConstructible>();
  test_x1_cv_ref<Std, Jln, ExplicitCtor>();
  test_x1_cv_ref<Std, Jln, ExplicitCopyCtor>();
  test_x1_cv_ref<Std, Jln, ImplicitBool>();
  test_x1_cv_ref<Std, Jln, InitializerListCtor>();
  test_x1_cv_ref<Std, Jln, bool>();
  test_x1_cv_ref<Std, Jln, float>();
  test_x1_cv_ref<Std, Jln, int>();
  test_x1_cv_ref<Std, Jln, int*>();
  test_x1_cv_ref<Std, Jln, int const*>();
  test_x1_cv_ref<Std, Jln, int volatile*>();
  test_x1_cv_ref<Std, Jln, int volatile const*>();
  test_x1_cv_ref<Std, Jln, int[]>();
  // TODO only when no pedantic
  // JLN_MP_DIAGNOSTIC_PUSH()
  // JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wzero-length-array")
  // test_x1_cv_ref<Std, Jln, int[0]>();
  // JLN_MP_DIAGNOSTIC_POP()
  test_x1_cv_ref<Std, Jln, int[5]>();
  test_x1_cv_ref<Std, Jln, int[][5]>();
  test_x1_cv_ref<Std, Jln, int[5][5]>();
  test_x1_cv_ref<Std, Jln, NoMovable[]>();
  test_x1_cv_ref<Std, Jln, NoMovable[5]>();
  test_x1_cv_ref<Std, Jln, NoMovable[][5]>();
  test_x1_cv_ref<Std, Jln, NoMovable[5][5]>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor[]>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor[5]>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor[][5]>();
  test_x1_cv_ref<Std, Jln, ThrowableDtor[5][5]>();

  test_x1_cv_ref<Std, Jln, void(int)>();
  test_x1_cv_ref<Std, Jln, void(*)(int)>();
  test_x1_cv_ref<Std, Jln, void(&)(int)>();
  test_x1_cv<Std, Jln, void(int) const>();
  test_x1_cv<Std, Jln, void(int) volatile>();
  test_x1_cv<Std, Jln, void(int) const&>();
  test_x1_cv_ref<Std, Jln, void(int) noexcept>();

  test_x1_cv_ref<Std, Jln, decltype(&Class::i)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f1)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f5)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f9)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f12)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f13)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f28)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f49)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f61)>();
  test_x1_cv_ref<Std, Jln, decltype(&Class::f64)>();
}

template<template<class...> class Std, template<class...> class Jln, class T, class U>
static void test_x2_cv_ref()
{
  test_x1_cv_ref<Std, Jln, T, U>();
  test_x1_cv_ref<Std, Jln, T, U&>();
  test_x1_cv_ref<Std, Jln, T, U&&>();
  test_x1_cv_ref<Std, Jln, T, const U>();
  test_x1_cv_ref<Std, Jln, T, const U&>();
  test_x1_cv_ref<Std, Jln, T, const U&&>();
  test_x1_cv_ref<Std, Jln, T, volatile U>();
  test_x1_cv_ref<Std, Jln, T, volatile U&>();
  test_x1_cv_ref<Std, Jln, T, volatile U&&>();
  test_x1_cv_ref<Std, Jln, T, volatile const U>();
  test_x1_cv_ref<Std, Jln, T, volatile const U&>();
  test_x1_cv_ref<Std, Jln, T, volatile const U&&>();
}

template<template<class...> class Std, template<class...> class Jln>
static void test_arithmetic()
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
static void test_constructible()
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
static void test_assignable()
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
static void test_swappable()
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
static void test_func_and_mem()
{
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
}

template<template<class...> class Std, template<class...> class Jln>
static void test_x1_make_unsigned_signed()
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

template<template<class...> class Std, template<class...> class Jln, class C, class... Ts>
static void test_invoke_mem()
{
  CHECK_IMPL(maybe_uncallable<Std>::template f, maybe_uncallable<Jln>::template f, C, Ts...);
  CHECK_IMPL(maybe_uncallable<Std>::template f, maybe_uncallable<Jln>::template f, C&, Ts...);
  CHECK_IMPL(maybe_uncallable<Std>::template f, maybe_uncallable<Jln>::template f, C&&, Ts...);
  CHECK_IMPL(maybe_uncallable<Std>::template f, maybe_uncallable<Jln>::template f, C const&, Ts...);
  CHECK_IMPL(maybe_uncallable<Std>::template f, maybe_uncallable<Jln>::template f, C const&&, Ts...);
  CHECK_IMPL(maybe_uncallable<Std>::template f, maybe_uncallable<Jln>::template f, C*, Ts...);
  CHECK_IMPL(maybe_uncallable<Std>::template f, maybe_uncallable<Jln>::template f, C const*, Ts...);
}

#ifdef IN_IDE_PARSER
template<template<class...> class Std, template<class...> class Jln, class... xs>
static void test_fake()
{
  // ut::same<typename Std<int>::type, Jln<int>>();
}
#  define test_x1 test_fake
#  define test_x2 test_fake
#  define test_x1_cv_ref test_fake
#  define test_x2_cv_ref test_fake
#  define test_arithmetic test_fake
#  define test_constructible test_fake
#  define test_assignable test_fake
#  define test_x1_make_unsigned_signed test_fake
#  define test_swappable test_fake
#  define test_func_and_mem test_fake
#  define test_invoke_mem test_fake
#endif

TEST()
{
  using namespace jln::mp::traits::emp;
  using jln::mp::number;

#if JLN_MP_CXX_VERSION >= 20
# define CPP_20_OR(cpp20, other) cpp20
#else
# define CPP_20_OR(cpp20, other) other
#endif

  // TODO
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-macros")

#ifdef IN_IDE_PARSER
  #define SINGLE_CALL_CHECK(name, R, ...) jln::mp::list<maybe_uncallable<name>, R, __VA_ARGS__>()
  #define SINGLE_CALL_CHECK_M SINGLE_CALL_CHECK
  #define SINGLE_CALL_CHECK_M2 SINGLE_CALL_CHECK_M
#else
  // test on std::...
  #if 0
    #define TRAIT_NAME(name) std::name
    #define CONVERT_INTEGRAL_CONSTANT(...) to_emp_integral_constant_t<__VA_ARGS__>
  #else
    #define TRAIT_NAME(name) name
    #define CONVERT_INTEGRAL_CONSTANT(...) __VA_ARGS__
  #endif
  #define CHECK_IMPL_R(R, name, ...)                                             \
    test_xs_impl<R, CONVERT_INTEGRAL_CONSTANT(typename name<__VA_ARGS__>::type)> \
      ::template f<__VA_ARGS__>::test()
  #define SINGLE_CALL_CHECK(name, R, ...) CHECK_IMPL_R(R, TRAIT_NAME(name), __VA_ARGS__)
  #define SINGLE_CALL_CHECK_M(name, R, ...) CHECK_IMPL_R(R, maybe_uncallable<TRAIT_NAME(name)>::f, __VA_ARGS__)
  #define SINGLE_CALL_CHECK_M2(name, R, a, b) \
    SINGLE_CALL_CHECK_M(name, R, a, b);       \
    SINGLE_CALL_CHECK_M(name, R, b, a)
#endif
  #define CHECK_X1(name) test_x1<std::name, name>()
  #define CHECK_X1_CV(name, ...) test_x1_cv<std::name, name, __VA_ARGS__>()
  #define CHECK_X1_CV_REF(name, ...) test_x1_cv_ref<std::name, name, __VA_ARGS__>()
  #define CHECK_X1_M(name) test_x1<maybe_uncallable<std::name>::f, maybe_uncallable<name>::f>()
  #define CHECK_X1_ARITHMETIC(name) test_arithmetic<std::name, name>()
  #define CHECK_F(name, fn) fn<std::name, name>()
  #define CHECK_XS_F(name, fn, ...) fn<std::name, name, __VA_ARGS__>()

  // TODO CHECK_XS

  // TODO
  JLN_MP_DIAGNOSTIC_POP()

//   SINGLE_CALL_CHECK(is_complete_type, true_type, void(int));
//   SINGLE_CALL_CHECK(is_complete_type, true_type, void(int) const);
//   SINGLE_CALL_CHECK(is_complete_type, true_type, void(int) const&);
//   SINGLE_CALL_CHECK(is_complete_type, true_type, int&);
//   SINGLE_CALL_CHECK(is_complete_type, true_type, int);
//   SINGLE_CALL_CHECK(is_complete_type, true_type, int const);
//   SINGLE_CALL_CHECK(is_complete_type, true_type, int[2]);
//   SINGLE_CALL_CHECK(is_complete_type, true_type, const int[2]);
//   SINGLE_CALL_CHECK(is_complete_type, false_type, int[]);
//   SINGLE_CALL_CHECK(is_complete_type, false_type, const int[]);
//   SINGLE_CALL_CHECK(is_complete_type, false_type, void);
//   SINGLE_CALL_CHECK(is_complete_type, false_type, void const);
//   SINGLE_CALL_CHECK(is_complete_type, false_type, incomplete);
//   SINGLE_CALL_CHECK(is_complete_type, false_type, incomplete const);
//
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, void(int));
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, void(int) const);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, void(int) const&);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, int&);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, int);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, int const);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, int[2]);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, const int[2]);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, int[]);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, const int[]);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, void);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, true_type, void const);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, false_type, incomplete);
//   SINGLE_CALL_CHECK(is_complete_or_unbounded_type, false_type, incomplete const);
//
//   CHECK_X1_CV_REF(is_const, int);
//
//   CHECK_X1_CV_REF(is_volatile, int);
//
//   CHECK_X1(is_trivial);
//
//   CHECK_X1(is_trivially_copyable);
//
//   CHECK_X1(is_standard_layout);
//   CHECK_X1_CV(is_standard_layout, NotStandardLayout);
//
// #if __cplusplus <= 201703L
//   CHECK_X1(is_pod);
// #endif
//
//   CHECK_X1_CV(is_abstract, void);
//   CHECK_X1_CV_REF(is_abstract, int);
//   CHECK_X1_CV_REF(is_abstract, Virtual);
//   CHECK_X1_CV_REF(is_abstract, VirtualInParent);
//   CHECK_X1_CV_REF(is_abstract, Abstract);
//
//   CHECK_X1(is_aggregate);

  // SINGLE_CALL_CHECK(is_base_of, false_type, void, void);
  // SINGLE_CALL_CHECK(is_base_of, false_type, void, int);
  // SINGLE_CALL_CHECK(is_base_of, false_type, int, void);
  // SINGLE_CALL_CHECK(is_base_of, false_type, SEnum, void);
  // SINGLE_CALL_CHECK(is_base_of, false_type, SEnum, Aggregate);
  // SINGLE_CALL_CHECK(is_base_of, false_type, SEnum, Class);
  // SINGLE_CALL_CHECK(is_base_of, false_type, Child, Aggregate);
  // SINGLE_CALL_CHECK(is_base_of, false_type, Aggregate, Child);
  // SINGLE_CALL_CHECK(is_base_of, false_type, Child, Class);
  // SINGLE_CALL_CHECK(is_base_of, true_type, Class, Child);
  // SINGLE_CALL_CHECK(is_base_of, true_type, Class, Child const);

//   CHECK_X1_CV(is_class, void);
//   CHECK_X1_CV_REF(is_class, int);
//   CHECK_X1_CV_REF(is_class, int[5]);
//   CHECK_X1_CV_REF(is_class, Union);
//   CHECK_X1_CV_REF(is_class, Empty);
//   CHECK_X1_CV_REF(is_class, Aggregate);
//   CHECK_X1_CV_REF(is_class, Virtual);
//   CHECK_X1_CV_REF(is_class, VirtualInParent);
//
//   CHECK_X1_CV(is_empty, void);
//   CHECK_X1_CV_REF(is_empty, int);
//   CHECK_X1_CV_REF(is_empty, Empty);
//   CHECK_X1_CV_REF(is_empty, Aggregate);
//   CHECK_X1_CV(is_enum, void);
//   CHECK_X1_CV_REF(is_enum, int);
//   CHECK_X1_CV_REF(is_enum, Aggregate);
//   CHECK_X1_CV_REF(is_enum, UEnum);
//   CHECK_X1_CV_REF(is_enum, ScopedUEnum);
//
//   CHECK_X1_CV(is_final, void);
//   CHECK_X1_CV_REF(is_final, int);
//   CHECK_X1_CV_REF(is_final, Aggregate);
//   CHECK_X1_CV_REF(is_final, Final);
//
//   CHECK_X1_CV(is_polymorphic, void);
//   CHECK_X1_CV_REF(is_polymorphic, int);
//   CHECK_X1_CV_REF(is_polymorphic, Aggregate);
//   CHECK_X1_CV_REF(is_polymorphic, Abstract);
//   CHECK_X1_CV_REF(is_polymorphic, Virtual);
//   CHECK_X1_CV_REF(is_polymorphic, VirtualInParent);
//
//   CHECK_X1_CV(is_union, void);
//   CHECK_X1_CV_REF(is_union, int);
//   CHECK_X1_CV_REF(is_union, Aggregate);
//   CHECK_X1_CV_REF(is_union, Union);
//
//   CHECK_X1_ARITHMETIC(is_signed);
//   CHECK_X1_ARITHMETIC(is_unsigned);
//
// #if defined(__cpp_lib_bounded_array_traits) && __cpp_lib_bounded_array_traits >= 201902L
//   CHECK_X1_CV(is_bounded_array, void);
//   CHECK_X1_CV_REF(is_bounded_array, int);
//   CHECK_X1_CV_REF(is_bounded_array, int[]);
//   CHECK_X1_CV_REF(is_bounded_array, int[4]);
//   CHECK_X1_CV_REF(is_bounded_array, int[][4]);
//
//   CHECK_X1_CV(is_unbounded_array, void);
//   CHECK_X1_CV_REF(is_unbounded_array, int);
//   CHECK_X1_CV_REF(is_unbounded_array, int[]);
//   CHECK_X1_CV_REF(is_unbounded_array, int[4]);
//   CHECK_X1_CV_REF(is_unbounded_array, int[][4]);
// #endif
//
  // SINGLE_CALL_CHECK(is_convertible, false_type, int, void);
  // SINGLE_CALL_CHECK(is_convertible, false_type, void, int);
  // SINGLE_CALL_CHECK(is_convertible, true_type, void, void);
  // SINGLE_CALL_CHECK(is_convertible, false_type, void, void());
  // SINGLE_CALL_CHECK(is_convertible, false_type, void, void(*)());
  // SINGLE_CALL_CHECK(is_convertible, false_type, void*, void());
  // SINGLE_CALL_CHECK(is_convertible, false_type, void*, void(*)());
  // SINGLE_CALL_CHECK(is_convertible, false_type, void(), void);
  // SINGLE_CALL_CHECK(is_convertible, false_type, void(), void*);
  // SINGLE_CALL_CHECK(is_convertible, false_type, void(*)(), void);
  // SINGLE_CALL_CHECK(is_convertible, false_type, void(*)(), void*);
  // SINGLE_CALL_CHECK(is_convertible, true_type, void(), void(&)());
  // SINGLE_CALL_CHECK(is_convertible, true_type, void(), void(&&)());
  // SINGLE_CALL_CHECK(is_convertible, true_type, void(), void(*)());
  // SINGLE_CALL_CHECK(is_convertible, false_type, Castable, void());
  // SINGLE_CALL_CHECK(is_convertible, true_type, Castable, void(*)());
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Aggregate, Aggregate);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Child, Child);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Child, Aggregate);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Aggregate, Child);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Child, Class);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Class, Child);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Class, Any);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Any, Class);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int, float);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, void*, std::size_t);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, std::size_t, void*);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int, InitializerListCtor);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, NoDefault, NoDefault);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, NoCopyable, NoCopyable);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, NoMovable, NoMovable);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, NoDestructible, NoDestructible);
  // SINGLE_CALL_CHECK(is_convertible, false_type, Castable, NoDestructible);
  // SINGLE_CALL_CHECK(is_convertible, false_type, NoDestructible, Castable);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible1, Constructible1);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible2, Constructible2);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible3, Constructible3);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible4, Constructible4);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible5, Constructible5);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible6, Constructible6);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible7, Constructible7);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible8, Constructible8);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, Constructible9, Constructible9);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int[2], int[2]);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int[], int[]);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int[], int*);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int*, int[]);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int[], int);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int[2], int);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int, int[]);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int, int[2]);
//   CHECK_XS_F(is_convertible, test_x2_cv_ref, int, int);
//
// #if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible >= 201806L
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, int, void);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void, int);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, true_type, void, void);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void, void());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void*, void());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void*, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void(), void);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void(), void*);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void(*)(), void);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, void(*)(), void*);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, true_type, void(), void(&)());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, true_type, void(), void(&&)());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, true_type, void(), void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, Castable, void());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, Castable, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, NoexceptCastable, void());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, true_type, NoexceptCastable, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, Castable, int);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, true_type, NoexceptCastable, int);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Aggregate, Aggregate);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Child, Child);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Child, Aggregate);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Aggregate, Child);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Child, Class);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Class, Child);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Class, Any);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Any, Class);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int, float);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, void*, std::size_t);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, std::size_t, void*);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int, InitializerListCtor);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, NoDefault, NoDefault);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, NoCopyable, NoCopyable);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, NoMovable, NoMovable);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, NoDestructible, NoDestructible);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, Castable, NoDestructible);
  // SINGLE_CALL_CHECK(is_nothrow_convertible, false_type, NoDestructible, Castable);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible1, Constructible1);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible2, Constructible2);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible3, Constructible3);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible4, Constructible4);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible5, Constructible5);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible6, Constructible6);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible7, Constructible7);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible8, Constructible8);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, Constructible9, Constructible9);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int[2], int[2]);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int[], int[]);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int[], int*);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int*, int[]);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int[], int);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int[2], int);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int, int[]);
//   CHECK_XS_F(is_nothrow_convertible, test_x2_cv_ref, int, int[2]);
// #endif
//
// #if defined(__cpp_lib_is_scoped_enum) && __cpp_lib_is_scoped_enum >= 202011L
//   CHECK_X1_ARITHMETIC(is_scoped_enum);
// #endif
//
// #if defined(__cpp_lib_has_unique_object_representations) && __cpp_lib_has_unique_object_representations >= 201606L
//   CHECK_X1(has_unique_object_representations);
// #endif
//
//   CHECK_X1_CV(is_void, void);
//   CHECK_X1_CV_REF(is_void, int);
//
//   CHECK_X1_CV(is_null_pointer, void);
//   CHECK_X1_CV_REF(is_null_pointer, int);
//   CHECK_X1_CV_REF(is_null_pointer, decltype(nullptr));
//
//   CHECK_X1_ARITHMETIC(is_integral);
//
//   CHECK_X1_ARITHMETIC(is_floating_point);
//
//   CHECK_X1_CV(is_array, void);
//   CHECK_X1_CV_REF(is_array, int);
//   CHECK_X1_CV_REF(is_array, int[]);
//   CHECK_X1_CV_REF(is_array, int[5]);
//
//   CHECK_X1_CV(is_pointer, void);
//   CHECK_X1_CV_REF(is_pointer, void*);
//   CHECK_X1_CV_REF(is_pointer, decltype(nullptr));
//
//   CHECK_X1_CV(is_lvalue_reference, void);
//   CHECK_X1_CV_REF(is_lvalue_reference, int);
//
//   CHECK_X1_CV(is_rvalue_reference, void);
//   CHECK_X1_CV_REF(is_rvalue_reference, int);
//
//   CHECK_X1_CV(is_reference, void);
//   CHECK_X1_CV_REF(is_reference, int);
//
//   CHECK_X1_CV(is_function, void);
//   CHECK_X1_CV(is_function, int*);
//   CHECK_X1_CV(is_function, int);
//   CHECK_F(is_function, test_func_and_mem);
//
//   CHECK_X1_CV(is_member_object_pointer, void);
//   CHECK_X1_CV(is_member_object_pointer, int*);
//   CHECK_X1_CV(is_member_object_pointer, int);
//   CHECK_F(is_member_object_pointer, test_func_and_mem);
//
//   CHECK_X1_CV(is_member_function_pointer, void);
//   CHECK_X1_CV(is_member_function_pointer, int*);
//   CHECK_X1_CV(is_member_function_pointer, int);
//   CHECK_F(is_member_function_pointer, test_func_and_mem);
//
//   CHECK_X1_ARITHMETIC(is_arithmetic);
//
//   CHECK_X1(is_fundamental);
//
//   CHECK_X1(is_object);
//
//   CHECK_X1_CV(is_member_pointer, void);
//   CHECK_X1_CV(is_member_pointer, int*);
//   CHECK_X1_CV(is_member_pointer, int);
//   CHECK_F(is_member_pointer, test_func_and_mem);
//
//   CHECK_X1_ARITHMETIC(is_scalar);
//
//   CHECK_X1(is_compound);
//   CHECK_F(is_compound, test_func_and_mem);
//
//   CHECK_X1(add_lvalue_reference);
//
//   CHECK_X1(add_rvalue_reference);
//
//   // CHECK_XS(is_constructible);
//   CHECK_F(is_constructible, test_constructible);
//
//   CHECK_F(is_default_constructible, test_constructible);
//
//   CHECK_F(is_copy_constructible, test_constructible);
//
//   CHECK_F(is_move_constructible, test_constructible);
//
//   // CHECK_XS(is_trivially_constructible);
//   CHECK_F(is_trivially_constructible, test_constructible);
//
//   CHECK_F(is_trivially_default_constructible, test_constructible);
//
//   CHECK_F(is_trivially_copy_constructible, test_constructible);
//
//   CHECK_F(is_trivially_move_constructible, test_constructible);
//
//   // CHECK_XS(is_nothrow_constructible);
//   CHECK_F(is_nothrow_constructible, test_constructible);
//
//   CHECK_F(is_nothrow_default_constructible, test_constructible);
//
//   CHECK_F(is_nothrow_copy_constructible, test_constructible);
//
//   CHECK_F(is_nothrow_move_constructible, test_constructible);
//
  // SINGLE_CALL_CHECK(is_assignable, false_type, int, void);
  // SINGLE_CALL_CHECK(is_assignable, false_type, void, int);
  // SINGLE_CALL_CHECK(is_assignable, false_type, void, void);
  // SINGLE_CALL_CHECK(is_assignable, false_type, void, void());
  // SINGLE_CALL_CHECK(is_assignable, false_type, void, void(*)());
  // SINGLE_CALL_CHECK(is_assignable, false_type, void*, void());
  // SINGLE_CALL_CHECK(is_assignable, false_type, void*, void(*)());
  // SINGLE_CALL_CHECK(is_assignable, false_type, void(), void);
  // SINGLE_CALL_CHECK(is_assignable, false_type, void(), void*);
  // SINGLE_CALL_CHECK(is_assignable, false_type, void(*)(), void);
  // SINGLE_CALL_CHECK(is_assignable, false_type, void(*)(), void*);
  // SINGLE_CALL_CHECK(is_assignable, false_type, void(&)(), void());
  // SINGLE_CALL_CHECK(is_assignable, false_type, void(&&)(), void());
  // SINGLE_CALL_CHECK(is_assignable, false_type, void(*)(), void());
  // SINGLE_CALL_CHECK(is_assignable, false_type, Castable, void());
  // SINGLE_CALL_CHECK(is_assignable, false_type, Castable, void(*)());
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Aggregate, Aggregate);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Child, Child);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Child, Aggregate);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Aggregate, Child);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Child, Class);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Class, Child);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Class, Any);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Any, Class);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int, float);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, void*, std::size_t);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, std::size_t, void*);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int, InitializerListCtor);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, NoDefault, NoDefault);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, NoCopyable, NoCopyable);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, NoMovable, NoMovable);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, NoDestructible, NoDestructible);
  // SINGLE_CALL_CHECK(is_assignable, false_type, Castable, NoDestructible);
  // SINGLE_CALL_CHECK(is_assignable, false_type, NoDestructible, Castable);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Assignable1, Assignable1);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Assignable2, Assignable2);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Assignable3, Assignable3);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Assignable4, Assignable4);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Assignable5, Assignable5);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, Assignable6, Assignable6);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int[2], int[2]);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int[], int[]);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int[], int*);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int*, int[]);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int[], int);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int[2], int);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int, int[]);
//   CHECK_XS_F(is_assignable, test_x2_cv_ref, int, int[2]);
//
//   CHECK_F(is_copy_assignable, test_assignable);
//
//   CHECK_F(is_move_assignable, test_assignable);
//
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, int, void);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void, int);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void, void);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void, void());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void, void(*)());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void*, void());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void*, void(*)());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void(), void);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void(), void*);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void(*)(), void);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void(*)(), void*);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void(&)(), void());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void(&&)(), void());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, void(*)(), void());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, Castable, void());
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, Castable, void(*)());
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Aggregate, Aggregate);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Child, Child);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Child, Aggregate);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Aggregate, Child);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Child, Class);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Class, Child);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Class, Any);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Any, Class);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int, float);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, void*, std::size_t);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, std::size_t, void*);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int, InitializerListCtor);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, NoDefault, NoDefault);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, NoCopyable, NoCopyable);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, NoMovable, NoMovable);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, NoDestructible, NoDestructible);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, Castable, NoDestructible);
  // SINGLE_CALL_CHECK(is_trivially_assignable, false_type, NoDestructible, Castable);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Assignable1, Assignable1);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Assignable2, Assignable2);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Assignable3, Assignable3);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Assignable4, Assignable4);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Assignable5, Assignable5);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, Assignable6, Assignable6);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int[2], int[2]);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int[], int[]);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int[], int*);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int*, int[]);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int[], int);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int[2], int);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int, int[]);
//   CHECK_XS_F(is_trivially_assignable, test_x2_cv_ref, int, int[2]);
//
//   CHECK_F(is_trivially_copy_assignable, test_assignable);
//
//   CHECK_F(is_trivially_move_assignable, test_assignable);
//
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, int, void);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void, int);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void, void);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void, void());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void*, void());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void*, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void(), void);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void(), void*);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void(*)(), void);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void(*)(), void*);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void(&)(), void());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void(&&)(), void());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, void(*)(), void());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, Castable, void());
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, Castable, void(*)());
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Aggregate, Aggregate);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Child, Child);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Child, Aggregate);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Aggregate, Child);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Child, Class);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Class, Child);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Class, Any);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Any, Class);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int, float);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, void*, std::size_t);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, std::size_t, void*);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int, InitializerListCtor);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, NoDefault, NoDefault);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, NoCopyable, NoCopyable);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, NoMovable, NoMovable);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, NoDestructible, NoDestructible);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, Castable, NoDestructible);
  // SINGLE_CALL_CHECK(is_nothrow_assignable, false_type, NoDestructible, Castable);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Assignable1, Assignable1);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Assignable2, Assignable2);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Assignable3, Assignable3);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Assignable4, Assignable4);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Assignable5, Assignable5);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, Assignable6, Assignable6);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int[2], int[2]);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int[], int[]);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int[], int*);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int*, int[]);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int[], int);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int[2], int);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int, int[]);
//   CHECK_XS_F(is_nothrow_assignable, test_x2_cv_ref, int, int[2]);
//
//   CHECK_F(is_nothrow_copy_assignable, test_assignable);
//
//   CHECK_F(is_nothrow_move_assignable, test_assignable);
//
//   CHECK_X1(is_destructible);
//
//   CHECK_X1(is_trivially_destructible);
//
//   CHECK_X1(is_nothrow_destructible);
//
// #if defined(__cpp_lib_is_implicit_lifetime) && __cpp_lib_is_implicit_lifetime >= 202302L
//   // TODO
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
//
// #if defined(__cpp_lib_is_swappable) && __cpp_lib_is_swappable >= 201603L
//   CHECK_F(is_swappable, test_swappable);
//   CHECK_F(is_nothrow_swappable, test_swappable);
//
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, int, int);
  // SINGLE_CALL_CHECK(is_swappable_with, true_type, int&, int&);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, int&&, int&&);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, int&&, int&);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, int&, int&&);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, int, void);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void, int);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void, void);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void, void());
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void, void(*)());
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void*, void());
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void*, void(*)());
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void(), void);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void(), void*);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void(*)(), void);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, void(*)(), void*);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, Castable, void());
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, Castable, void(*)());
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Aggregate, Aggregate);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Child, Child);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Child, Aggregate);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Aggregate, Child);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Child, Class);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Class, Child);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Class, Any);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Any, Class);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int, float);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int, InitializerListCtor);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, NoDefault, NoDefault);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, NoCopyable, NoCopyable);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, NoMovable, NoMovable);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, NoDestructible, NoDestructible);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, Castable, NoDestructible);
  // SINGLE_CALL_CHECK(is_swappable_with, false_type, NoDestructible, Castable);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable1, Swappable1);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable1, Swappable2);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable1, Swappable3);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable2, Swappable1);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable2, Swappable2);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable2, Swappable3);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable3, Swappable1);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable3, Swappable2);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, Swappable3, Swappable3);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int[2], int[2]);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int[], int[]);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int[], int*);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int*, int[]);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int[], int);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int[2], int);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int, int[]);
//   CHECK_XS_F(is_swappable_with, test_x2_cv_ref, int, int[2]);
//
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, int, int);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, true_type, int&, int&);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, int&&, int&&);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, int&&, int&);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, int&, int&&);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, int, void);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void, int);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void, void);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void, void());
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void*, void());
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void*, void(*)());
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void(), void);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void(), void*);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void(*)(), void);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, void(*)(), void*);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, Castable, void());
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, Castable, void(*)());
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Aggregate, Aggregate);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Child, Child);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Child, Aggregate);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Aggregate, Child);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Child, Class);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Class, Child);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Class, Any);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Any, Class);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int, float);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int, InitializerListCtor);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, NoDefault, NoDefault);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, NoCopyable, NoCopyable);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, NoMovable, NoMovable);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, NoDestructible, NoDestructible);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, Castable, NoDestructible);
  // SINGLE_CALL_CHECK(is_nothrow_swappable_with, false_type, NoDestructible, Castable);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable1, Swappable1);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable1, Swappable2);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable1, Swappable3);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable2, Swappable1);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable2, Swappable2);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable2, Swappable3);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable3, Swappable1);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable3, Swappable2);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, Swappable3, Swappable3);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int[2], int[2]);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int[], int[]);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int[], int*);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int*, int[]);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int[], int);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int[2], int);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int, int[]);
//   CHECK_XS_F(is_nothrow_swappable_with, test_x2_cv_ref, int, int[2]);
// #endif
//
//   CHECK_X1(has_virtual_destructor);
//
  // SINGLE_CALL_CHECK(is_same, true_type, void, void);
  // SINGLE_CALL_CHECK(is_same, false_type, void, int);
  // SINGLE_CALL_CHECK(is_same, true_type, int, int);
  // SINGLE_CALL_CHECK(is_same, false_type, int, int const);
//
// #if defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible >= 201907L
//   CHECK_XS_F(is_layout_compatible, test_x2_cv_ref, int, int);
//   CHECK_XS_F(is_layout_compatible, test_x2_cv_ref, int, long);
//   CHECK_XS_F(is_layout_compatible, test_x2_cv_ref, long, long long);
//   CHECK_XS_F(is_layout_compatible, test_x2_cv_ref, SEnum, SEnum);
//   CHECK_XS_F(is_layout_compatible, test_x2_cv_ref, SEnum, SLEnum);
//   CHECK_XS_F(is_layout_compatible, test_x2_cv_ref, SLEnum, SLLEnum);
// #endif
//
// #if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible >= 201907L
//   CHECK_XS_F(is_pointer_interconvertible_base_of, test_x2_cv, Empty, PriEmptyPubEmpty2);
//   CHECK_XS_F(is_pointer_interconvertible_base_of, test_x2_cv, Empty2, PriEmptyPubEmpty2);
//   CHECK_XS_F(is_pointer_interconvertible_base_of, test_x2_cv, PriEmptyPubEmpty2, NonStdLayout);
//   CHECK_XS_F(is_pointer_interconvertible_base_of, test_x2_cv, NonStdLayout, NonStdLayout);
//
//   static_assert(
//     std::is_pointer_interconvertible_with_class(&PubMem1PubMem2::x)
//     == is_pointer_interconvertible_with_class(&PubMem1PubMem2::x));
//   static_assert(
//     std::is_pointer_interconvertible_with_class<PubMem1PubMem2, int>(&PubMem1PubMem2::x)
//     == is_pointer_interconvertible_with_class<PubMem1PubMem2, int>(&PubMem1PubMem2::x));
// #endif
//
  // SINGLE_CALL_CHECK(alignment_of, decltype(integral_constant<std::size_t, alignof(int)>()), int);
  //
  // SINGLE_CALL_CHECK(rank, decltype(integral_constant<std::size_t, 0>()), int);
  // SINGLE_CALL_CHECK(rank, decltype(integral_constant<std::size_t, 1>()), int[1]);
  // SINGLE_CALL_CHECK(rank, decltype(integral_constant<std::size_t, 2>()), int[1][2]);
  //
  // SINGLE_CALL_CHECK(extent, decltype(integral_constant<std::size_t, 0>()), int);
  // SINGLE_CALL_CHECK(extent, decltype(integral_constant<std::size_t, 0>()), int[]);
  // SINGLE_CALL_CHECK(extent, decltype(integral_constant<std::size_t, 0>()), int[][3]);
  // SINGLE_CALL_CHECK(extent, decltype(integral_constant<std::size_t, 2>()), int[2][3]);
//   CHECK_T_V_IMPL(std::extent, extent_c, int, 1);
//   CHECK_T_V_IMPL(std::extent, extent_c, int[], 1);
//   CHECK_T_V_IMPL(std::extent, extent_c, int[][3], 1);
//   CHECK_T_V_IMPL(std::extent, extent_c, int[2][3], 1);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, void);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i));
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), Class**);
//   SINGLE_CALL_CHECK_M(invoke_result, int&&, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, int&&, decltype(&Class::i), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, int const&, decltype(&Class::i), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, int const&&, decltype(&Class::i), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, int const&, decltype(&Class::i), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile&, decltype(&Class::i), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile&&, decltype(&Class::i), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile&, decltype(&Class::i), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile const&, decltype(&Class::i), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile const&&, decltype(&Class::i), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile const&, decltype(&Class::i), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i) const, Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i) volatile, Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i) volatile const, Class*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass**);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), DereferableToClass&);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), DereferableToClass&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), DereferableToClass const&);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), DereferableToClass const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), DereferableToClass volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass**);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), NoexceptDereferableToClass&);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), NoexceptDereferableToClass&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass*);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), NoexceptDereferableToClass const&);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), NoexceptDereferableToClass const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), NoexceptDereferableToClass volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, int&&, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), std::reference_wrapper<Class>&);
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Class::i), std::reference_wrapper<Class>&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), std::reference_wrapper<Class>*);
//   SINGLE_CALL_CHECK_M(invoke_result, int const&, decltype(&Class::i), std::reference_wrapper<Class const>&);
//   SINGLE_CALL_CHECK_M(invoke_result, int const&, decltype(&Class::i), std::reference_wrapper<Class const>&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), std::reference_wrapper<Class const>*);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile&, decltype(&Class::i), std::reference_wrapper<Class volatile>&);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile&, decltype(&Class::i), std::reference_wrapper<Class volatile>&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), std::reference_wrapper<Class volatile>*);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile const&, decltype(&Class::i), std::reference_wrapper<Class volatile const>&);
//   SINGLE_CALL_CHECK_M(invoke_result, int volatile const&, decltype(&Class::i), std::reference_wrapper<Class volatile const>&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::i), std::reference_wrapper<Class volatile const>*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Ref::get), Ref&);
//   // Note C++20: The behavior is unspecified (possibly ill-formed) if it explicitly or implicitly attempts to form a pointer-to-member to a standard library function
//   // https://en.cppreference.com/w/cpp/language/extending_std#Addressing_restriction
//   // (does not work with std::invoke_result from libstdc++)
//   SINGLE_CALL_CHECK_M(invoke_result, int&, decltype(&Ref::get), std::reference_wrapper<int>&);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::fn));
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::fn), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::fn), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::fn), Class**);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*&&)(), decltype(&Class::fn), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*&)(), decltype(&Class::fn), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*&&)(), decltype(&Class::fn), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*&)(), decltype(&Class::fn), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*const&)(), decltype(&Class::fn), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*const&&)(), decltype(&Class::fn), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*const&)(), decltype(&Class::fn), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*volatile&)(), decltype(&Class::fn), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*volatile&&)(), decltype(&Class::fn), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*volatile&)(), decltype(&Class::fn), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*volatile const&)(), decltype(&Class::fn), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*volatile const&&)(), decltype(&Class::fn), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, void(*volatile const&)(), decltype(&Class::fn), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(int), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(int), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, number<1>(int), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(int), int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(int) noexcept, Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(int) noexcept, Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, number<1>(int) noexcept, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(int) noexcept, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(*)(int), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(*)(int), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, number<1>(*)(int), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(*)(int), int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(*)(int) noexcept, Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(*)(int) noexcept, Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, number<1>(*)(int) noexcept, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, number<1>(*)(int) noexcept, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1));
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g1), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g1), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g1), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g1), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g1), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2));
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Child, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Child&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Child&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Child*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Child const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Child const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), Child const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Child volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Child volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Child volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Child volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Child volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), Child volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), DereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), DereferableToClass&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), DereferableToClass&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), DereferableToClass const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g2), DereferableToClass const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g2), DereferableToClass volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3));
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g3), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g3), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g3), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::g3), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g3), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4));
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Child, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Child&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Child&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Child*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Child const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Child const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), Child const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Child volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Child volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Child volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Child volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Child volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), Child volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), DereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), DereferableToClass&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), DereferableToClass&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), DereferableToClass const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::g4), DereferableToClass const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::g4), DereferableToClass volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::f1), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::f1), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f1), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::f2), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, decltype(&Class::f2), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f2), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, decltype(&Class::f3), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, decltype(&Class::f3), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f3), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, decltype(&Class::f4), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f4), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<5>, notype), decltype(&Class::f5), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<5>, decltype(&Class::f5), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<5>, notype), decltype(&Class::f5), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<5>, decltype(&Class::f5), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<5>, notype), decltype(&Class::f5), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<5>, decltype(&Class::f5), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<5>, notype), decltype(&Class::f5), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<5>, decltype(&Class::f5), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f5), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<6>, decltype(&Class::f6), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<6>, decltype(&Class::f6), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<6>, decltype(&Class::f6), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<6>, decltype(&Class::f6), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f6), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<7>, decltype(&Class::f7), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f7), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<8>, decltype(&Class::f8), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<8>, decltype(&Class::f8), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<8>, decltype(&Class::f8), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<8>, decltype(&Class::f8), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f8), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<9>, decltype(&Class::f9), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<9>, decltype(&Class::f9), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<9>, decltype(&Class::f9), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<9>, decltype(&Class::f9), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f9), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f10), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<10>, decltype(&Class::f10), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f11), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<11>, decltype(&Class::f11), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<12>, decltype(&Class::f12), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f12), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<13>, decltype(&Class::f13), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<13>, decltype(&Class::f13), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<13>, decltype(&Class::f13), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<13>, decltype(&Class::f13), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f13), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<14>, decltype(&Class::f14), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<14>, decltype(&Class::f14), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f14), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<15>, decltype(&Class::f15), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<15>, decltype(&Class::f15), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f15), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<16>, decltype(&Class::f16), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f16), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<17>, decltype(&Class::f17), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<17>, decltype(&Class::f17), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<17>, decltype(&Class::f17), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<17>, decltype(&Class::f17), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f17), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<18>, decltype(&Class::f18), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<18>, decltype(&Class::f18), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<18>, decltype(&Class::f18), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<18>, decltype(&Class::f18), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f18), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<19>, decltype(&Class::f19), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f19), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<20>, decltype(&Class::f20), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<20>, decltype(&Class::f20), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<20>, decltype(&Class::f20), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<20>, decltype(&Class::f20), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f20), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<21>, decltype(&Class::f21), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<21>, decltype(&Class::f21), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<21>, decltype(&Class::f21), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<21>, decltype(&Class::f21), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f21), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f22), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<22>, decltype(&Class::f22), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f23), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<23>, decltype(&Class::f23), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<24>, decltype(&Class::f24), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f24), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<26>, decltype(&Class::f26), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<26>, decltype(&Class::f26), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<27>, decltype(&Class::f27), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<27>, decltype(&Class::f27), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f34), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<25>, decltype(&Class::f25), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f25), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<26>, decltype(&Class::f26), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<26>, decltype(&Class::f26), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f26), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<27>, decltype(&Class::f27), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<27>, decltype(&Class::f27), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const&, int);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f27), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<28>, decltype(&Class::f28), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f28), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<29>, notype), decltype(&Class::f29), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<29>, decltype(&Class::f29), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f29), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<30>, decltype(&Class::f30), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f30), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<31>, decltype(&Class::f31), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f31), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<32>, decltype(&Class::f32), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f32), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<33>, decltype(&Class::f33), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f33), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f34), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<34>, decltype(&Class::f34), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f35), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<35>, decltype(&Class::f35), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<36>, decltype(&Class::f36), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f36), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<38>, decltype(&Class::f38), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<38>, decltype(&Class::f38), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<39>, decltype(&Class::f39), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<39>, decltype(&Class::f39), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f46), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<37>, decltype(&Class::f37), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f37), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<38>, decltype(&Class::f38), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<38>, decltype(&Class::f38), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f38), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<39>, decltype(&Class::f39), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<39>, decltype(&Class::f39), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const&, int);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f39), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<40>, decltype(&Class::f40), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f40), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<41>, decltype(&Class::f41), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f41), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<42>, decltype(&Class::f42), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f42), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<43>, decltype(&Class::f43), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f43), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<44>, decltype(&Class::f44), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f44), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<45>, decltype(&Class::f45), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f45), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f46), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<46>, decltype(&Class::f46), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f47), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<47>, decltype(&Class::f47), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<48>, decltype(&Class::f48), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f48), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<49>, decltype(&Class::f49), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<49>, decltype(&Class::f49), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<49>, decltype(&Class::f49), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<49>, decltype(&Class::f49), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f49), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<50>, decltype(&Class::f50), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<50>, decltype(&Class::f50), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f50), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<51>, decltype(&Class::f51), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<51>, decltype(&Class::f51), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile const&, int, int, int);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f51), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<52>, decltype(&Class::f52), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f52), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<53>, notype), decltype(&Class::f53), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<53>, decltype(&Class::f53), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<53>, notype), decltype(&Class::f53), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<53>, decltype(&Class::f53), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<53>, notype), decltype(&Class::f53), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<53>, decltype(&Class::f53), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<53>, notype), decltype(&Class::f53), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<53>, decltype(&Class::f53), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f53), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<54>, decltype(&Class::f54), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<54>, decltype(&Class::f54), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<54>, decltype(&Class::f54), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<54>, decltype(&Class::f54), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f54), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<55>, decltype(&Class::f55), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f55), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<56>, decltype(&Class::f56), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<56>, decltype(&Class::f56), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<56>, decltype(&Class::f56), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<56>, decltype(&Class::f56), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f56), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<57>, decltype(&Class::f57), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<57>, decltype(&Class::f57), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<57>, decltype(&Class::f57), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<57>, decltype(&Class::f57), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f57), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f58), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f58), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<58>, decltype(&Class::f58), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f59), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<59>, decltype(&Class::f59), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<60>, decltype(&Class::f60), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f60), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<61>, decltype(&Class::f61), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<61>, decltype(&Class::f61), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<61>, decltype(&Class::f61), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<61>, decltype(&Class::f61), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f61), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<62>, decltype(&Class::f62), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<62>, decltype(&Class::f62), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f62), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<63>, decltype(&Class::f63), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<63>, decltype(&Class::f63), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile const&, int, int, int);  SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f63), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<64>, decltype(&Class::f64), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f64), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<65>, decltype(&Class::f65), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<65>, decltype(&Class::f65), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<65>, decltype(&Class::f65), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<65>, decltype(&Class::f65), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f65), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<66>, decltype(&Class::f66), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<66>, decltype(&Class::f66), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<66>, decltype(&Class::f66), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<66>, decltype(&Class::f66), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f66), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<67>, decltype(&Class::f67), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f67), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<68>, decltype(&Class::f68), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<68>, decltype(&Class::f68), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<68>, decltype(&Class::f68), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<68>, decltype(&Class::f68), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f68), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<69>, decltype(&Class::f69), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<69>, decltype(&Class::f69), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<69>, decltype(&Class::f69), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<69>, decltype(&Class::f69), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f69), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f70), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f70), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<70>, decltype(&Class::f70), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f71), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<71>, decltype(&Class::f71), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<72>, decltype(&Class::f72), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, decltype(&Class::f72), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, Callable);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, Callable&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, Callable&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, Callable const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, Callable const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, Callable, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, Callable&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, Callable&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, Callable volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, Callable volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable const&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, Callable volatile const&&, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, NoexceptCallable);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, NoexceptCallable&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<1>, NoexceptCallable&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, NoexceptCallable const&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<2>, NoexceptCallable const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, NoexceptCallable, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, NoexceptCallable&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<3>, NoexceptCallable&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, NoexceptCallable volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, number<4>, NoexceptCallable volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable const&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result, notype, NoexceptCallable volatile const&&, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, void);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i));
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), Class**);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&&, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&&, decltype(&Class::i), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int const&, decltype(&Class::i), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int const&&, decltype(&Class::i), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int const&, decltype(&Class::i), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile&, decltype(&Class::i), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile&&, decltype(&Class::i), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile&, decltype(&Class::i), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile const&, decltype(&Class::i), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile const&&, decltype(&Class::i), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile const&, decltype(&Class::i), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i) const, Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i) volatile, Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i) volatile const, Class*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass**);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), DereferableToClass volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass**);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), NoexceptDereferableToClass&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), NoexceptDereferableToClass&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), NoexceptDereferableToClass const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), NoexceptDereferableToClass const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), NoexceptDereferableToClass volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&&, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), std::reference_wrapper<Class>&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Class::i), std::reference_wrapper<Class>&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), std::reference_wrapper<Class>*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int const&, decltype(&Class::i), std::reference_wrapper<Class const>&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int const&, decltype(&Class::i), std::reference_wrapper<Class const>&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), std::reference_wrapper<Class const>*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile&, decltype(&Class::i), std::reference_wrapper<Class volatile>&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile&, decltype(&Class::i), std::reference_wrapper<Class volatile>&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), std::reference_wrapper<Class volatile>*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile const&, decltype(&Class::i), std::reference_wrapper<Class volatile const>&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int volatile const&, decltype(&Class::i), std::reference_wrapper<Class volatile const>&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::i), std::reference_wrapper<Class volatile const>*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Ref::get), Ref&);
//   // Note C++20: The behavior is unspecified (possibly ill-formed) if it explicitly or implicitly attempts to form a pointer-to-member to a standard library function
//   // https://en.cppreference.com/w/cpp/language/extending_std#Addressing_restriction
//   // (does not work with std::invoke_result_if_noexcept from libstdc++)
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, int&, decltype(&Ref::get), std::reference_wrapper<int>&);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::fn));
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::fn), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::fn), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::fn), Class**);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*&&)(), decltype(&Class::fn), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*&)(), decltype(&Class::fn), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*&&)(), decltype(&Class::fn), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*&)(), decltype(&Class::fn), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*const&)(), decltype(&Class::fn), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*const&&)(), decltype(&Class::fn), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*const&)(), decltype(&Class::fn), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*volatile&)(), decltype(&Class::fn), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*volatile&&)(), decltype(&Class::fn), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*volatile&)(), decltype(&Class::fn), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*volatile const&)(), decltype(&Class::fn), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*volatile const&&)(), decltype(&Class::fn), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, void(*volatile const&)(), decltype(&Class::fn), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(int), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(int), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(int), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(int), int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(int) noexcept, Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(int) noexcept, Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, number<1>(int) noexcept, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(int) noexcept, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(*)(int), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(*)(int), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(*)(int), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(*)(int), int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(*)(int) noexcept, Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(*)(int) noexcept, Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, number<1>(*)(int) noexcept, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, number<1>(*)(int) noexcept, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1));
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g1), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2));
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), Child volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g2), DereferableToClass volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3));
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, decltype(&Class::g3), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, decltype(&Class::g3), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, decltype(&Class::g3), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, decltype(&Class::g3), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g3), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4));
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Child, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Child&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Child&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Child*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Child const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Child const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), Child const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Child volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Child volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Child volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Child volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Child volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), Child volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), DereferableToClass volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), NoexceptDereferableToClass, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), NoexceptDereferableToClass&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), NoexceptDereferableToClass&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), NoexceptDereferableToClass const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, decltype(&Class::g4), NoexceptDereferableToClass const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::g4), NoexceptDereferableToClass volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f1), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f2), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f3), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f4), Class volatile const*);
//
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class*);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class const);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class const&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class const&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class const*);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile*);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile const);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile const&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile const&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f5), Class volatile const*);

//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f6), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f7), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f8), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f9), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f10), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f11), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f12), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<13>, decltype(&Class::f13), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<13>, decltype(&Class::f13), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<13>, decltype(&Class::f13), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<13>, decltype(&Class::f13), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f13), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<14>, decltype(&Class::f14), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<14>, decltype(&Class::f14), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f14), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<15>, decltype(&Class::f15), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<15>, decltype(&Class::f15), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f15), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<16>, decltype(&Class::f16), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f16), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<17>, decltype(&Class::f17), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<17>, decltype(&Class::f17), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<17>, decltype(&Class::f17), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<17>, notype), decltype(&Class::f17), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<17>, decltype(&Class::f17), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f17), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<18>, decltype(&Class::f18), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<18>, decltype(&Class::f18), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<18>, decltype(&Class::f18), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<18>, decltype(&Class::f18), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f18), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<19>, decltype(&Class::f19), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f19), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<20>, decltype(&Class::f20), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<20>, decltype(&Class::f20), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<20>, decltype(&Class::f20), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<20>, decltype(&Class::f20), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f20), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<21>, decltype(&Class::f21), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<21>, decltype(&Class::f21), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<21>, decltype(&Class::f21), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<21>, decltype(&Class::f21), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f21), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f22), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<22>, decltype(&Class::f22), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f23), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<23>, decltype(&Class::f23), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<24>, decltype(&Class::f24), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f24), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const*);
//
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class*);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const*);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile*);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const&&);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f25), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f26), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const&, int);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f27), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f28), Class volatile const*, int);
//
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class&, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class&&, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class*, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const&, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const&&, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class const*, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f29), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f30), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f31), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f32), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f33), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f34), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f35), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f36), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<38>, decltype(&Class::f38), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<38>, decltype(&Class::f38), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<39>, decltype(&Class::f39), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<39>, decltype(&Class::f39), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const&);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f46), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class const*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile*);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile const);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile const*);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<37>, decltype(&Class::f37), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f37), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<38>, decltype(&Class::f38), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<38>, decltype(&Class::f38), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f38), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<39>, decltype(&Class::f39), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<39>, decltype(&Class::f39), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const&, int);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f39), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<40>, decltype(&Class::f40), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f40), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<41>, notype), decltype(&Class::f41), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<41>, decltype(&Class::f41), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f41), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<42>, decltype(&Class::f42), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f42), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<43>, decltype(&Class::f43), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f43), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<44>, decltype(&Class::f44), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f44), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<45>, decltype(&Class::f45), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f45), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f46), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<46>, decltype(&Class::f46), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f47), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<47>, decltype(&Class::f47), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class const*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile*, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile const, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<48>, decltype(&Class::f48), Class volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f48), Class volatile const*, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f49), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f50), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile const&, int, int, int);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f51), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f52), Class volatile const*, int, int, int);
//
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), int, int, int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class, int, int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class&, int, int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class&&, int, int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class*, int, int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class const, int, int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class const&, int, int, int);
  // SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f53), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f54), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f55), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f56), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f57), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f58), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f59), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f60), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<61>, decltype(&Class::f61), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<61>, decltype(&Class::f61), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<61>, decltype(&Class::f61), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<61>, decltype(&Class::f61), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f61), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<62>, decltype(&Class::f62), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<62>, decltype(&Class::f62), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f62), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<63>, decltype(&Class::f63), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<63>, decltype(&Class::f63), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile const&, int, int, int);  SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f63), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<64>, decltype(&Class::f64), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f64), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<65>, decltype(&Class::f65), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<65>, decltype(&Class::f65), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<65>, decltype(&Class::f65), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, CPP_20_OR(number<65>, notype), decltype(&Class::f65), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<65>, decltype(&Class::f65), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f65), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<66>, decltype(&Class::f66), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<66>, decltype(&Class::f66), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<66>, decltype(&Class::f66), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<66>, decltype(&Class::f66), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f66), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<67>, decltype(&Class::f67), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f67), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<68>, decltype(&Class::f68), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<68>, decltype(&Class::f68), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<68>, decltype(&Class::f68), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<68>, decltype(&Class::f68), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f68), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<69>, decltype(&Class::f69), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<69>, decltype(&Class::f69), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<69>, decltype(&Class::f69), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<69>, decltype(&Class::f69), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f69), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f70), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f70), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<70>, decltype(&Class::f70), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f71), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<71>, decltype(&Class::f71), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), int, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class const*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class volatile, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class volatile&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class volatile&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class volatile*, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class volatile const, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class volatile const&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<72>, decltype(&Class::f72), Class volatile const&&, int, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, decltype(&Class::f72), Class volatile const*, int, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable const&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, Callable volatile const&&, int, int);
//
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, NoexceptCallable);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, NoexceptCallable&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<1>, NoexceptCallable&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, NoexceptCallable const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<2>, NoexceptCallable const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile const&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile const&&);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<3>, NoexceptCallable, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<3>, NoexceptCallable&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<3>, NoexceptCallable&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<4>, NoexceptCallable volatile&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, number<4>, NoexceptCallable volatile&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile const&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile const&&, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable const&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile&&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile const&, int, int);
//   SINGLE_CALL_CHECK_M(invoke_result_if_noexcept, notype, NoexceptCallable volatile const&&, int, int);
//
//   SINGLE_CALL_CHECK(is_invocable, false_type, int);
//   SINGLE_CALL_CHECK(is_invocable, false_type, void);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_invocable, true_type, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_invocable, true_type, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_invocable, true_type, void());
//   SINGLE_CALL_CHECK(is_invocable, false_type, void(), int);
//   SINGLE_CALL_CHECK(is_invocable, true_type, void() noexcept);
//   SINGLE_CALL_CHECK(is_invocable, false_type, void() noexcept, int);
//   SINGLE_CALL_CHECK(is_invocable, false_type, void(int));
//   SINGLE_CALL_CHECK(is_invocable, true_type, void(int), int);
//   SINGLE_CALL_CHECK(is_invocable, false_type, void(int) noexcept);
//   SINGLE_CALL_CHECK(is_invocable, true_type, void(int) noexcept, int);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK(is_invocable, true_type, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK(is_invocable, true_type, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK(is_invocable, true_type, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK(is_invocable, true_type, Callable);
//   SINGLE_CALL_CHECK(is_invocable, true_type, NoexceptCallable);
//   SINGLE_CALL_CHECK(is_invocable, true_type, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_invocable, true_type, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable, false_type, decltype(&Class::i), NoexceptDereferableToClass*);
//
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, void);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_nothrow_invocable, true_type, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, true_type, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, void());
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, void(), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, true_type, void() noexcept);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, void() noexcept, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, void(int));
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, void(int), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, void(int) noexcept);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, true_type, void(int) noexcept, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, true_type, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, Callable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, true_type, NoexceptCallable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, true_type, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable, false_type, decltype(&Class::i), NoexceptDereferableToClass*);
//
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, void);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, long, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, long, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, long, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, long, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, long, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, void());
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, void(), int);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, void() noexcept);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, void() noexcept, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, void(int));
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, void(int), int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, void(int) noexcept);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, void(int) noexcept, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void());
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void(), int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void() noexcept);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void() noexcept, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void(int));
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void(int), int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void(int) noexcept);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, int, void(int) noexcept, int);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, Any, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, Any, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, Any, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, Any, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, Any, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, Any, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, Callable);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, NoexceptCallable);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, Any, Callable);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, Any, NoexceptCallable);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, void, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, void, decltype(&Class::i), NoexceptDereferableToClass*);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, long, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, long, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_invocable_r, true_type, long, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, long, decltype(&Class::i), NoexceptDereferableToClass*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_invocable_r, false_type, char*, decltype(&Class::i), NoexceptDereferableToClass*);
//
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, void);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, void, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, void, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, long, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, long, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, long, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, long, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, long, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i));
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), Class, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), Class*, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, void());
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, void(), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, void, void() noexcept);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, void() noexcept, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, void(int));
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, void(int), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, void(int) noexcept);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, void, void(int) noexcept, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void());
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void(), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void() noexcept);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void() noexcept, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void(int));
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void(int), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void(int) noexcept);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, int, void(int) noexcept, int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, void, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, NoexceptAny, decltype(&Class::f1), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, NoexceptAny, decltype(&Class::f1), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, NoexceptAny, decltype(&Class::f1), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, NoexceptAny, decltype(&Class::f24), int);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, NoexceptAny, decltype(&Class::f24), Class);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, NoexceptAny, decltype(&Class::f24), Class*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, Callable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, void, NoexceptCallable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, Callable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, Any, NoexceptCallable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, NoexceptAny, Callable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, NoexceptAny, NoexceptCallable);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, void, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, void, decltype(&Class::i), NoexceptDereferableToClass*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, long, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, long, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, true_type, long, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, long, decltype(&Class::i), NoexceptDereferableToClass*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), DereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), DereferableToClass*);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), NoexceptDereferableToClass);
//   SINGLE_CALL_CHECK(is_nothrow_invocable_r, false_type, char*, decltype(&Class::i), NoexceptDereferableToClass*);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int&&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&&, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const&&, int const&&);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, unsigned);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, unsigned&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, unsigned&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, unsigned const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, unsigned);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, unsigned&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int&, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int&&, unsigned);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int&&, unsigned&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int&&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int&&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int&&, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&, unsigned);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&, unsigned&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&&, unsigned);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&&, unsigned&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const&&, unsigned const&&);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, CtorInt&, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt&&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt&&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt&&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt&&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt&&, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&, int const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&&, int);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&&, int&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&&, int&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&&, int const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  CtorInt const&&, int const&&);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  ExplicitCopyCtor&&, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  ExplicitCopyCtor const&, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  ExplicitCopyCtor const&&, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor const&&);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Class);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Class&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Class&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Class const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Class const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Class);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Class&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Class&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Class const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Class const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  Class&&, Class);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Class&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Class&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Class const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Class const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  Class const&, Class);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Class&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Class&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Class const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Class const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  Class const&&, Class);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Class&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Class&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Class const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Class const&&);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Child);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Child&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Child&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Child const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class, Child const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Child);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Child&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Child&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Child const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&, Child const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  Class&&, Child);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Child&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Child&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Child const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class&&, Child const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  Class const&, Child);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Child&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Child&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Child const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&, Child const&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  Class const&&, Child);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Child&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Child&&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Child const&);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, Class const&&, Child const&&);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int[2], int[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int(&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int(&)[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int(&&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int(&&)[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const(&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const(&)[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type,  int const(&&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int const(&&)[2], int(&)[2]);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, void, void);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, void, void*);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, void*, void);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, void const*, void);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, void, void const*);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, void const*, int*);
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type, void const*&&, int*);
//
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, int, void());
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, false_type, void(), void());
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type, void(&)(), void());
//   SINGLE_CALL_CHECK(reference_constructs_from_temporary, true_type, void(&&)(), void());
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int&&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&&, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const&&, int const&&);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, unsigned);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, unsigned&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, unsigned&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, unsigned const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, unsigned);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, unsigned&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int&, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int&&, unsigned);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int&&, unsigned&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int&&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int&&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int&&, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&, unsigned);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&, unsigned&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&, unsigned const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&&, unsigned);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&&, unsigned&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&&, unsigned&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&&, unsigned const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const&&, unsigned const&&);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor, ExplicitCopyCtor const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&, ExplicitCopyCtor const&&);
//   static_assert(is_convertible_v<ExplicitCopyCtor, ExplicitCopyCtor&&>);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  ExplicitCopyCtor&&, ExplicitCopyCtor); // TODO should be false_type
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor&&, ExplicitCopyCtor const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  ExplicitCopyCtor const&, ExplicitCopyCtor);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&, ExplicitCopyCtor const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  ExplicitCopyCtor const&&, ExplicitCopyCtor); // TODO should be false_type
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, ExplicitCopyCtor const&&, ExplicitCopyCtor const&&);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, CtorInt&, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt&&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt&&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt&&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt&&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt&&, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&, int const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&&, int);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&&, int&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&&, int&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&&, int const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  CtorInt const&&, int const&&);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Class);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Class&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Class&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Class const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Class const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Class);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Class&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Class&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Class const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Class const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  Class&&, Class);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Class&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Class&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Class const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Class const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  Class const&, Class);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Class&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Class&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Class const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Class const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  Class const&&, Class);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Class&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Class&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Class const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Class const&&);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Child);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Child&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Child&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Child const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class, Child const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Child);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Child&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Child&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Child const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&, Child const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  Class&&, Child);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Child&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Child&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Child const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class&&, Child const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  Class const&, Child);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Child&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Child&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Child const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&, Child const&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  Class const&&, Child);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Child&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Child&&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Child const&);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, Class const&&, Child const&&);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int[2], int[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int(&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int(&)[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int(&&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int(&&)[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const(&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const(&)[2], int(&)[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type,  int const(&&)[2], int[2]);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int const(&&)[2], int(&)[2]);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, void, void);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, void, void*);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, void*, void);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, void const*, void);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, void, void const*);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, void const*, int*);
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type, void const*&&, int*);
//
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, int, void());
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, false_type, void(), void());
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type, void(&)(), void());
//   SINGLE_CALL_CHECK(reference_converts_from_temporary, true_type, void(&&)(), void());
//   // CHECK_X2(reference_constructs_from_temporary);
//   // int&&, int -> true
//   // int&&, int&& -> false
//
//   CHECK_X1_CV(remove_const, void);
//   CHECK_X1_CV_REF(remove_const, int);
//
//   CHECK_X1_CV(remove_volatile, void);
//   CHECK_X1_CV_REF(remove_volatile, int);
//
//   CHECK_X1_CV(remove_cv, void);
//   CHECK_X1_CV_REF(remove_cv, int);
//
//   CHECK_X1_CV(remove_extent, void);
//   CHECK_X1_CV_REF(remove_extent, int);
//   CHECK_X1_CV_REF(remove_extent, int[]);
//   CHECK_X1_CV_REF(remove_extent, int[2]);
//   CHECK_X1_CV_REF(remove_extent, int[][2]);
//   CHECK_X1_CV_REF(remove_extent, int[2][3]);
//
//   CHECK_X1_CV(remove_all_extents, void);
//   CHECK_X1_CV_REF(remove_all_extents, int);
//   CHECK_X1_CV_REF(remove_all_extents, int[]);
//   CHECK_X1_CV_REF(remove_all_extents, int[2]);
//   CHECK_X1_CV_REF(remove_all_extents, int[][2]);
//   CHECK_X1_CV_REF(remove_all_extents, int[2][3]);
//
//   CHECK_X1_CV(remove_pointer, void);
//   CHECK_X1_CV_REF(remove_pointer, int);
//   CHECK_X1_CV_REF(remove_pointer, int*);
//
//   CHECK_X1_CV(remove_reference, void);
//   CHECK_X1_CV_REF(remove_reference, int);
//
// #if defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref >= 201711L
//   CHECK_X1_CV(remove_cvref, void);
//   CHECK_X1_CV_REF(remove_cvref, int);
// #endif
//
//   CHECK_X1_CV(add_pointer, void);
//   CHECK_X1_CV_REF(add_pointer, int);
//
//   CHECK_X1_CV(add_cv, void);
//   CHECK_X1_CV_REF(add_cv, int);
//
//   CHECK_X1_CV(add_const, void);
//   CHECK_X1_CV_REF(add_const, int);
//
//   CHECK_X1_CV(add_volatile, void);
//   CHECK_X1_CV_REF(add_volatile, int);
//
//   CHECK_F(make_signed, test_x1_make_unsigned_signed);
//   CHECK_F(make_unsigned, test_x1_make_unsigned_signed);
//
//   CHECK_X1(decay);
//
// #if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref >= 201811L
//   CHECK_X1_CV(unwrap_reference, void);
//   CHECK_X1_CV_REF(unwrap_reference, int);
//   // TODO CHECK_X1_CV_REF(unwrap_reference, std::reference_wrapper<int>);
//
//   CHECK_X1(unwrap_ref_decay);
//   // TODO CHECK_X1_CV_REF(add_pointer, std::reference_wrapper<int>);
// #endif
//
  // SINGLE_CALL_CHECK_M(common_reference, notype, JLN_MP_NIL);
//   SINGLE_CALL_CHECK_M(common_reference, int, int);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, int volatile const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int&,                 int&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile&,        int&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int&&,                int&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&&,          int&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile&&,       int&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&&,          int const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&,           int const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int const&&,          int const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile&,        int volatile&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int volatile&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile&,        int volatile&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int volatile&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile&&,       int volatile&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int volatile&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile&&,       int volatile&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int volatile&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int volatile const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int volatile const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int volatile const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&,  int volatile const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int volatile const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int volatile const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int volatile const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int,                  int volatile const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int volatile const&&, int volatile const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, long, long volatile const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile, CtorInt volatile, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt volatile const, CtorInt volatile const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt const, CtorInt const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt, CtorInt volatile const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile, CtorInt2 volatile, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,          CtorInt2 volatile, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile, CtorInt2 volatile, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile, CtorInt2 volatile, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,          CtorInt2 volatile, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,          CtorInt2 volatile, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile, CtorInt2 volatile, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,          CtorInt2 volatile, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,          CtorInt2 volatile, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile, CtorInt2 volatile, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,          CtorInt2 volatile, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,          CtorInt2 volatile, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile const, CtorInt2 volatile const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,                CtorInt2 volatile const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile const, CtorInt2 volatile const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile const, CtorInt2 volatile const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,                CtorInt2 volatile const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,                CtorInt2 volatile const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile const, CtorInt2 volatile const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,                CtorInt2 volatile const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,                CtorInt2 volatile const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 volatile const, CtorInt2 volatile const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,                CtorInt2 volatile const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,                CtorInt2 volatile const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2 const, CtorInt2 const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2,       CtorInt2 const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, CtorInt2, CtorInt2 volatile const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int volatile&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int volatile&&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, int, AutoConvert volatile const&&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&, int volatile const&&);
//
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int&&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int const);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int const&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int const&&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int volatile);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int volatile &);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int volatile &&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int volatile const);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int volatile const&);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, char*&&, int volatile const&&);
//
//   {
//     using R1 = std::pair<long, long>;
//     using P1 = std::pair<int, long>;
//     using P2 = std::pair<long, int>;
//     SINGLE_CALL_CHECK_M2(common_reference, R1, P1, P2);
//     using R2 = std::tuple<long, long>;
//     using T1 = std::tuple<int, long>;
//     using T2 = std::tuple<long, int>;
//     SINGLE_CALL_CHECK_M2(common_reference, R2, T1, T2);
//     using P3 = std::pair<int, int*>;
//     SINGLE_CALL_CHECK_M2(common_reference, notype, P3, P2);
//     using T3 = std::tuple<int, int*>;
//     SINGLE_CALL_CHECK_M2(common_reference, notype, T3, T2);
//     using T4 = std::tuple<int, int, int>;
//     SINGLE_CALL_CHECK_M2(common_reference, notype, T4, T2);
//   }
//
//   SINGLE_CALL_CHECK_M2(common_reference, int&, int&, std::reference_wrapper<int>);
//   SINGLE_CALL_CHECK_M2(common_reference, notype, int&, std::reference_wrapper<std::reference_wrapper<int>>);
//   SINGLE_CALL_CHECK_M2(common_reference, std::reference_wrapper<int> const&, std::reference_wrapper<int>&, std::reference_wrapper<int> const&);
//
//   SINGLE_CALL_CHECK_M(common_reference, int, int, int, int);
//   SINGLE_CALL_CHECK_M(common_reference, int const&&, int const&&, int const&&, int const&&);
//   SINGLE_CALL_CHECK_M(common_reference, long, int, int, long, int);
//   SINGLE_CALL_CHECK_M(common_reference, void*, void*, char*);
//   SINGLE_CALL_CHECK_M(common_reference, notype, int, int, long, int, char*);
//   SINGLE_CALL_CHECK_M(common_reference, notype, int, void);
//
//   CHECK_X1_M(underlying_type);
//
//   CHECK_X1_M(common_type);
  // SINGLE_CALL_CHECK_M(common_type, float, int, float);
  // SINGLE_CALL_CHECK_M(common_type, float, int, float, long long);
  // SINGLE_CALL_CHECK_M(common_type, void, void, void, void);
  // SINGLE_CALL_CHECK_M(common_type, notype, int, float, void);
  // SINGLE_CALL_CHECK_M(common_type, notype, int, float, long long, void);
  // SINGLE_CALL_CHECK_M(common_type, notype, void, int, float, long long);
  // SINGLE_CALL_CHECK_M(common_type, notype, int, int*);
  // SINGLE_CALL_CHECK_M(common_type, notype, int, int, int, int*);
  // SINGLE_CALL_CHECK_M(common_type, notype, int*, int, int, int);
  // SINGLE_CALL_CHECK_M(common_type, long, int, long const&);
  // SINGLE_CALL_CHECK_M(common_type, notype, ScopedSEnum, ConvertibleToScopedEnum);
  // SINGLE_CALL_CHECK_M(common_type, ScopedUEnum, ScopedUEnum, ConvertibleToScopedEnum);
  // SINGLE_CALL_CHECK_M(common_type, int, AutoConvert, int);
  // SINGLE_CALL_CHECK_M(common_type, long, int, long, AutoConvert, int);
  // SINGLE_CALL_CHECK_M(common_type, Class, Child, Class);
  // SINGLE_CALL_CHECK_M(common_type, Class*, Child*, Class*);
  // SINGLE_CALL_CHECK_M(common_type, int, std::true_type, std::false_type);
  // SINGLE_CALL_CHECK_M(common_type, notype, JLN_MP_NIL);
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
