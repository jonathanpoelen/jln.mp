#!/bin/bash
cd "$(dirname $0)/.."

files=$(find test/src -name '*.cpp')

sed -ni '/^# start tests/{i# start tests\
'"$(sed -E 's#.*/(.*)\.cpp$#executable('\'\\1\',\ \'\&\'', dependencies: test_dep, build_by_default: false)\\#' <<<"$files")"'

:e;/^# stop tests/{:f;p;n;bf};n;be};p' meson.build

sed -E 's/^.{5}(.*)/#include "\1"/' <<<"$files" > test/mp.cpp
