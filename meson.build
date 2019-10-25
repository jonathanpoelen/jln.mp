project('jln.mp', 'cpp', default_options : ['cpp_std=c++17'])

subdir('meson_jln_flags')
add_global_arguments(jln_cpp_flags, language:'cpp')
add_global_link_arguments(jln_link_flags, language:'cpp')

test_dep = declare_dependency(include_directories: include_directories('test/include', 'include'))

# start tests
t_0 = executable('size', 'test/src/algorithm/size.cpp', dependencies: test_dep, build_by_default: false)
t_1 = executable('make_int_sequence', 'test/src/algorithm/make_int_sequence.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.algorithm', t_0, t_1)
t_2 = executable('is_invocable', 'test/src/functional/is_invocable.cpp', dependencies: test_dep, build_by_default: false)
t_3 = executable('bind', 'test/src/functional/bind.cpp', dependencies: test_dep, build_by_default: false)
t_4 = executable('invoke', 'test/src/functional/invoke.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.functional', t_2, t_3, t_4)
t_5 = executable('operators', 'test/src/number/operators.cpp', dependencies: test_dep, build_by_default: false)
t_6 = executable('as_number', 'test/src/number/as_number.cpp', dependencies: test_dep, build_by_default: false)
t_7 = executable('numbers', 'test/src/number/numbers.cpp', dependencies: test_dep, build_by_default: false)
t_8 = executable('is_number', 'test/src/number/is_number.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.number', t_5, t_6, t_7, t_8)
t_9 = executable('join', 'test/src/list/join.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.list', t_9)
alias_target('mp', t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9)
# stop tests

executable('mp_test', 'test/mp.cpp', dependencies: test_dep)
