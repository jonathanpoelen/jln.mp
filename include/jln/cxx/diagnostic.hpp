/* The MIT License (MIT)

Copyright (c) 2019 jonathan poelen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
* \author    Jonathan Poelen <jonathan.poelen+jln@gmail.com>
* \version   0.1
* \brief     C++17 utility macros
*/

#pragma once

#define JLN_PRAGMA(x) JLN_PRAGMA_I(x)

#ifdef _MSC_VER
#  define JLN_PRAGMA_I(x) __pragma(x)
#else
#  define JLN_PRAGMA_I(x) _Pragma(#x)
#endif


// Diagnostic
//@{
#if defined(__GNUC__) || defined(__clang__)

#  define JLN_DIAGNOSTIC_PUSH JLN_PRAGMA(GCC diagnostic push)
#  define JLN_DIAGNOSTIC_POP JLN_PRAGMA(GCC diagnostic pop)

#  define JLN_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_IGNORE(X) JLN_PRAGMA(GCC diagnostic ignored X)
#  define JLN_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_WARNING(X) JLN_PRAGMA(GCC diagnostic warning X)
#  define JLN_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ERROR(X) JLN_PRAGMA(GCC diagnostic error X)
#  ifdef __clang__
#    define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#    define JLN_DIAGNOSTIC_CLANG_IGNORE JLN_DIAGNOSTIC_GCC_IGNORE
#    define JLN_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#    define JLN_DIAGNOSTIC_CLANG_WARNING JLN_DIAGNOSTIC_GCC_WARNING
#    define JLN_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#    define JLN_DIAGNOSTIC_CLANG_ERROR JLN_DIAGNOSTIC_GCC_ERROR
#  else
#    define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE JLN_DIAGNOSTIC_GCC_IGNORE
#    define JLN_DIAGNOSTIC_CLANG_IGNORE(X)
#    define JLN_DIAGNOSTIC_GCC_ONLY_WARNING JLN_DIAGNOSTIC_GCC_WARNING
#    define JLN_DIAGNOSTIC_CLANG_WARNING(X)
#    define JLN_DIAGNOSTIC_GCC_ONLY_ERROR JLN_DIAGNOSTIC_GCC_ERROR
#    define JLN_DIAGNOSTIC_CLANG_ERROR(X)
#  endif

#elif defined(_MSC_VER)

#  define JLN_DIAGNOSTIC_PUSH __pragma(warning(push))
#  define JLN_DIAGNOSTIC_POP __pragma(warning(pop))

#  define JLN_DIAGNOSTIC_MSVC_IGNORE(X) __pragma(warning(disable:X))
#  define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_IGNORE(X)
#  define JLN_DIAGNOSTIC_CLANG_IGNORE(X)

#  define JLN_DIAGNOSTIC_MSVC_WARNING(X) __pragma(warning(4:X))
#  define JLN_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_WARNING(X)
#  define JLN_DIAGNOSTIC_CLANG_WARNING(X)

#  define JLN_DIAGNOSTIC_MSVC_ERROR(X) __pragma(error(X))
#  define JLN_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ERROR(X)
#  define JLN_DIAGNOSTIC_CLANG_ERROR(X)

#else

#  define JLN_DIAGNOSTIC_PUSH
#  define JLN_DIAGNOSTIC_POP

#  define JLN_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_DIAGNOSTIC_CLANG_IGNORE(X)

#  define JLN_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_DIAGNOSTIC_CLANG_WARNING(X)

#  define JLN_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_DIAGNOSTIC_CLANG_ERROR(X)

#endif

//@}
