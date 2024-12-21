// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>

// typename __type_pack_element<...>::xxx gives an error with gcc
#if JLN_MP_ENABLE_TYPE_PACK_ELEMENT && !JLN_MP_FAST_TYPE_PACK_ELEMENT
# define JLN_MP_ENABLE_IF_CALLABLE(b, ...) __type_pack_element<b, void, __VA_ARGS__>
#else
# include <type_traits>
# define JLN_MP_ENABLE_IF_CALLABLE(b, ...) std::enable_if_t<b, __VA_ARGS__>
#endif
