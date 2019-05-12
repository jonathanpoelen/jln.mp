#pragma once

#define TEST_SMP(...) ::jln::mp::smp::__VA_ARGS__{} = ::jln::mp::sfinae< ::jln::mp::__VA_ARGS__>{}
#define TEST_SMP_V(as, a) as = ::jln::mp::sfinae<decltype(a)>{}
