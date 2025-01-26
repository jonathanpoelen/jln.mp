// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/compiler.hpp>

#if JLN_MP_ENABLE_FRIEND_INJECTION && JLN_MP_FEATURE_CONCEPTS

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    namespace mkidx
    {
      template<class Tag, int X>
      struct state;

      #if JLN_MP_MEMOIZED_ALIAS
      # define JLN_MP_MK_STATE(...) \
        static_cast<detail::mkidx::state<__VA_ARGS__>*>(nullptr)
      #else
      # define JLN_MP_MK_STATE(...) detail::mkidx::state_ptr_v<__VA_ARGS__>
      template<class Tag, int id>
      inline constexpr state<Tag, id>* state_ptr_v = nullptr;
      #endif

      template<class T, class Tag>
      struct next_index;
    }

    template<class Tag> class next_index_tag;

    template<class T> struct type_of_index_id;
    template<class T> struct type_of_index_id<list<T>*> { using type = T; };
    template<class T> struct type_of_index_id<T*> { using type = T; };
  }
  /// \endcond

  /// \ingroup utility

  class default_make_index_tag {};

  namespace emp
  {
    /// Generates a unique index per call for a specified tag.
    template<class Tag = default_make_index_tag, auto v = []{}>
    inline constexpr int next_index_v =
      detail::mkidx::next_index<decltype(v)*, detail::next_index_tag<Tag>>::value;

    /// Generates a unique index per type for a specified tag.
    template<class T, class Tag = default_make_index_tag>
    inline constexpr int index_of_v = detail::mkidx::next_index<list<T>*, Tag>::value;

    /// Generates a unique index per type for a specified tag.
    template<class T, class Tag = default_make_index_tag>
    using index_of = number<index_of_v<T, Tag>>;

    /// Get the type associated to an index for a specified tag.
    template<int idx, class Tag = default_make_index_tag>
    using type_of_index = typename detail::type_of_index_id<
      decltype(get_bound_value(JLN_MP_MK_STATE(Tag, idx)))
    >::type;
  }

  /// Generates a unique index per type for a specified tag.
  /// \treturn \number
  template<class Tag = default_make_index_tag, class C = identity>
  struct make_index_for
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, number<emp::index_of_v<T, Tag>>);
  };

  /// Generates a unique index per type.
  /// \treturn \number
  template<class C = identity>
  using make_index = make_index_for<default_make_index_tag, C>;

  /// \cond
  template<class Tag>
  struct make_index_for<Tag, identity>
  {
    template<class T>
    using f = number<emp::index_of_v<T, Tag>>;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail::mkidx
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

  template<int idx, class T, class Tag>
  struct injecter
  {
    friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto get_bound_value(state<Tag, idx>*)
    {
      return T();
    }
  };

  template<class T, class Tag, int idx = 0>
  JLN_MP_CONSTEVAL_OR_CONSTEXPR int get_next_index()
  {
    if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+10)); }) {
      if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+100)); }) {
        if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+1000)); }) {
          if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+10000)); }) {
            return get_next_index<T, Tag, idx+10001>();
          }
          else if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+3000)); }) {
            return get_next_index<T, Tag, idx+3001>();
          }
          else {
            return get_next_index<T, Tag, idx+1001>();
          }
        }
        else if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+300)); }) {
          return get_next_index<T, Tag, idx+301>();
        }
        else {
          return get_next_index<T, Tag, idx+101>();
        }
      }
      else if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+30)); }) {
        return get_next_index<T, Tag, idx+31>();
      }
      else {
        return get_next_index<T, Tag, idx+11>();
      }
    }
    else if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx)); }) {
      if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+2)); }) {
        if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+4)); }) {
          return get_next_index<T, Tag, idx+5>();
        }
        else if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+3)); }) {
          return get_next_index<T, Tag, idx+4>();
        }
        else {
          return get_next_index<T, Tag, idx+3>();
        }
      }
      else if constexpr (requires { get_bound_value(JLN_MP_MK_STATE(Tag, idx+1)); }) {
          return get_next_index<T, Tag, idx+2>();
      }
      else {
          return get_next_index<T, Tag, idx+1>();
      }
    }
    else {
      return idx;
    }
  }

  template<class T, class Tag>
  struct next_index
  {
    static constexpr int value = get_next_index<T, Tag>();

    friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto get_bound_value(state<Tag, value>*)
    {
      return T();
    }
  };
}

#undef JLN_MP_MK_STATE
/// \endcond

#endif
