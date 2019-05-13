#pragma once

namespace jln::mp
{
  struct identity
  {
    template<class x>
    using f = x;
  };

  namespace eager
  {
    template<class x>
    using identity = x;
  }
}

// #include "../sfinae/sfinae_barrier.hpp"
//
// namespace jln::mp::detail
// {
//   template<template<class> class sfinae>
//   struct _sfinae<sfinae, identity>
//   {
//     using type = sfinae_barrier<identity>;
//   };
// }
