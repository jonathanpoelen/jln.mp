project('jln.mp', 'cpp', default_options : ['cpp_std=c++17'])

subdir('meson_jln_flags')
add_global_arguments(jln_cpp_flags, language:'cpp')
add_global_link_arguments(jln_link_flags, language:'cpp')

test_dep = declare_dependency(include_directories: include_directories('test/include', 'include'))

# start tests
executable('size', 'test/src/algorithm/size.cpp', dependencies: test_dep, build_by_default: false)
executable('is_invocable', 'test/src/functional/is_invocable.cpp', dependencies: test_dep, build_by_default: false)
executable('bind', 'test/src/functional/bind.cpp', dependencies: test_dep, build_by_default: false)
executable('invoke', 'test/src/functional/invoke.cpp', dependencies: test_dep, build_by_default: false)
executable('is_number', 'test/src/number/is_number.cpp', dependencies: test_dep, build_by_default: false)
executable('join', 'test/src/list/join.cpp', dependencies: test_dep, build_by_default: false)
executable('enumerate', 'test/src/list/enumerate.cpp', dependencies: test_dep, build_by_default: false)

# stop tests

executable('mp_test', 'test/mp.cpp', dependencies: test_dep)
