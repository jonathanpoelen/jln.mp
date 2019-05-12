#pragma once

#define TEST_SMP(...) ::jln::mp::smp::__VA_ARGS__{} = ::jln::mp::sfinae< ::jln::mp::__VA_ARGS__>{}
