// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/compiler.hpp>

#if defined(__cpp_generic_lambdas) && __cpp_generic_lambdas >= 201707L
# ifdef __cpp_consteval
#   if __cpp_consteval >= 201811L
#     define JLN_MP_CONSTEVAL_OR_CONSTEXPR consteval
#   endif
# endif
# ifndef JLN_MP_CONSTEVAL_OR_CONSTEXPR
#   define JLN_MP_CONSTEVAL_OR_CONSTEXPR constexpr
# endif

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    namespace mkid
    {
      template<class Tag, int X>
      struct state;

      #if JLN_MP_MEMOIZED_ALIAS
      # define JLN_MP_MKID_STATE(...) \
        static_cast<detail::mkid::state<__VA_ARGS__>*>(nullptr)
      #else
      # define JLN_MP_MKID_STATE(...) detail::mkid::state_ptr_v<__VA_ARGS__>
      template<class Tag, int id>
      inline constexpr state<Tag, id>* state_ptr_v = nullptr;
      #endif

      template<class T, class Tag>
      struct next_id;
    }

    template<class Tag> class next_id_tag;

    template<class T> struct type_of_id;
    template<class T> struct type_of_id<list<T>*> { using type = T; };
    template<class T> struct type_of_id<T*> { using type = T; };
  }
  /// \endcond

  /// \ingroup utility

  class default_make_id_tag {};

  namespace emp
  {
    /// Generates a unique id per call for a specified tag.
    template<class Tag = default_make_id_tag, auto v = []{}>
    inline constexpr int next_id_v =
      detail::mkid::next_id<decltype(v)*, detail::next_id_tag<Tag>>::value;

    /// Generates a unique id per type for a specified tag.
    template<class T, class Tag = default_make_id_tag>
    inline constexpr int id_of_v = detail::mkid::next_id<list<T>*, Tag>::value;

    /// Generates a unique id per type for a specified tag.
    template<class T, class Tag = default_make_id_tag>
    using id_of = number<id_of_v<T, Tag>>;

    /// Get the type associated to an id for a specified tag.
    template<int id, class Tag = default_make_id_tag>
    using type_of = typename detail::type_of_id<
      decltype(get_bound_value(JLN_MP_MKID_STATE(Tag, id)))
    >::type;
  }

  /// Generates a unique id per type for a specified tag.
  /// \treturn \number
  template<class Tag = default_make_id_tag, class C = identity>
  struct make_id_for
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, number<emp::id_of_v<T, Tag>>);
  };

  /// Generates a unique id per type.
  /// \treturn \number
  template<class C = identity>
  using make_id = make_id_for<default_make_id_tag, C>;

  /// \cond
  template<class Tag>
  struct make_id_for<Tag, identity>
  {
    template<class T>
    using f = number<emp::id_of_v<T, Tag>>;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail::mkid
{
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
  JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wunused-function")
  template<class Tag, int X>
  struct state
  {
    friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto get_bound_value(state*);
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<int id, class T, class Tag>
  struct injecter
  {
    friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto get_bound_value(state<Tag, id>*)
    {
      return T();
    }
  };

  template<class T, class Tag, int id = 0>
  JLN_MP_CONSTEVAL_OR_CONSTEXPR int get_next_id()
  {
    if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+10)); }) {
      if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+100)); }) {
        if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+1000)); }) {
          if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+10000)); }) {
            return get_next_id<T, Tag, id+10001>();
          }
          else if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+3000)); }) {
            return get_next_id<T, Tag, id+3001>();
          }
          else {
            return get_next_id<T, Tag, id+1001>();
          }
        }
        else if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+300)); }) {
          return get_next_id<T, Tag, id+301>();
        }
        else {
          return get_next_id<T, Tag, id+101>();
        }
      }
      else if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+30)); }) {
        return get_next_id<T, Tag, id+31>();
      }
      else {
        return get_next_id<T, Tag, id+11>();
      }
    }
    else if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id)); }) {
      if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+2)); }) {
        if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+4)); }) {
          return get_next_id<T, Tag, id+5>();
        }
        else if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+3)); }) {
          return get_next_id<T, Tag, id+4>();
        }
        else {
          return get_next_id<T, Tag, id+3>();
        }
      }
      else if constexpr (requires { get_bound_value(JLN_MP_MKID_STATE(Tag, id+1)); }) {
          return get_next_id<T, Tag, id+2>();
      }
      else {
          return get_next_id<T, Tag, id+1>();
      }
    }
    else {
      return id;
    }
  }

  template<class T, class Tag>
  struct next_id
  {
    static constexpr int value = get_next_id<T, Tag>();

    friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto get_bound_value(state<Tag, value>*)
    {
      return T();
    }
  };
}

#undef JLN_MP_MKID_STATE
/// \endcond

#endif
