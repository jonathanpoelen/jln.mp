#pragma once

namespace jln::mp
{
  template<template<class...> class source, class error>
  class error_occurred
  {
    template<class new_error>
    using next = error_occurred<source, new_error>;
  };

  namespace err
  {
    class all_parameters_must_be_of_type_mp_list;

    class not_a_number;

    class you_need_to_add_a_specialization;
  }
}
