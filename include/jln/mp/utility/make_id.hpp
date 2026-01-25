// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/detail/first.hpp>

#if JLN_MP_ENABLE_FRIEND_INJECTION

namespace jln::mp
{
  /// \ingroup utility

  /// \cond
  namespace meta
  {
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wunused-function")
    JLN_MP_DIAGNOSTIC_CUDA_IGNORE(1301)
    template<int const* id>
    struct id_info
    {
      friend constexpr auto meta_from_info(id_info const*);
    };
    JLN_MP_DIAGNOSTIC_POP()

    template<class T, class Tag>
    struct meta_t
    {
      using type = T;

      static inline const int id = 0;

      friend constexpr auto meta_from_info(id_info<&id> const*)
      {
        return meta_t{};
      }
    };
  }

  namespace detail
  {
    template<class T>
    struct id_of_info {};

    template<int const* id>
    struct id_of_info<meta::id_info<id>>
    {
      static constexpr int const* value = id;
    };


    template<class T>
    struct type_of_meta {};

    template<class T, class Tag>
    struct type_of_meta<meta::meta_t<T, Tag>*>
    {
      using type = T;
    };

    #if JLN_MP_HAS_MEMOIZED_ALIAS
    # define JLN_MP_MK_ID_INFO(...) static_cast<meta::id_info<__VA_ARGS__> const*>(nullptr)
    #else
    # define JLN_MP_MK_ID_INFO(...) detail::id_info_ptr_v<__VA_ARGS__>
    template<int const* id>
    inline constexpr meta::id_info<id> const* id_info_ptr_v = nullptr;
    #endif
  }
  /// \endcond

#ifdef JLN_MP_DOXYGENATING
  template<int const* id>
  struct id_info
  {};
#else
  using meta::id_info;
#endif

  class default_make_id_tag {};

  using id_t = int const*;

  namespace emp
  {
    /// Generates a unique id per type for a specified tag.
    template<class T, class Tag = default_make_id_tag>
    inline constexpr int const* id_of_v = &meta::meta_t<T, Tag>::id;

    /// Get id of meta::info.
    template<class id_info>
    inline constexpr int const* id_of_info_v = detail::first<id_info, 0>::value;

    template<int const* id>
    inline constexpr int const* id_of_info_v<id_info<id>> = id;

    /// Generates a unique id per type for a specified tag.
    template<class T, class Tag = default_make_id_tag>
    using id_of = id_info<id_of_v<T, Tag>>;

    /// Get the type associated to an id.
    template<int const* id>
    using type_of
    #ifndef JLN_MP_DOXYGENATING
      = typename decltype(
          meta_from_info(JLN_MP_MK_ID_INFO(id))
        )::type
    #endif
    ;

    /// Get the type associated to an id.
    template<class id_info>
    using type_of_info
    #ifndef JLN_MP_DOXYGENATING
      = typename decltype(
          meta_from_info(static_cast<id_info*>(nullptr))
        )::type
    #endif
    ;
  }

  /// Generates a unique type id per type for a specified tag.
  /// \treturn id_info
  template<class Tag = default_make_id_tag, class C = identity>
  struct make_id_for
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, id_info<emp::id_of_v<T, Tag>>);
  };

  /// Generates a unique type id per type.
  /// \treturn id_info
  template<class C = identity>
  using make_id = make_id_for<default_make_id_tag, C>;

  /// \cond
  template<class Tag>
  struct make_id_for<Tag, identity>
  {
    template<class T>
    using f = id_info<emp::id_of_v<T, Tag>>;
  };
  /// \endcond
}

#undef JLN_MP_MK_ID_INFO

#endif
