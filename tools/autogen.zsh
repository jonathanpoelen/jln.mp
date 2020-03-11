#!/bin/env zsh

set -e

cd ${0:h}/../include/jln

rm ../../test/autogen/*

setopt extendedglob

for f in mp/(*~smp)/*.hpp; do
  echo "#include \"$f\""
  echo "#include \"jln/$f\"\n" > ../../test/autogen/${f[4,-1]//\//@}.cpp
done > mp.hpp

echo 'int main(){}' > ../../test/autogen/main.cpp

{
  echo '#pragma once

#include "functional/sfinaefwd.hpp"

namespace jln::mp
{
  using detail::sfinae;
  using detail::sfinae_once;
}
'

for f in mp/smp/**/(*~sfinae).hpp; do
  echo "#include \"${f[8,-1]}\""
  echo "#include \"jln/$f\"\n" > ../../test/autogen/${f[4,-1]//\//@}.cpp
done 

} > mp/smp/sfinae.hpp

echo '#pragma once

#include "smp/sfinae.hpp"' > mp/smp.hpp

cd ../../
./tools/update_meson.py

./tools/embed.lua include/jln/mp.hpp > single_include/jln/mp.hpp
./tools/embed.lua include/jln/mp/smp.hpp > single_include/jln/mp/smp.hpp
