#!/usr/bin/env zsh

set -e

cd ${0:h}/../include/jln

rm ../../test/autogen/* ||:

setopt extendedglob

gentest()
{
  echo "#include \"jln/$1\"\n" > ../../test/autogen/${1[4,-1]//\//@}.cpp
}

genfiles()
{
  echo '#pragma once'
  echo
  for d in $@; do
    files=($d/*.hpp)
    prefix=${d:t}
    {
      echo '#pragma once'
      echo
      for f in $files ; do
        echo "#include \"$prefix/${f:t}\""
        gentest $f
      done
    } > $d.hpp
    echo "#include \"${d:h:t}/$prefix.hpp\""
  done
}

genfiles mp/(*~(smp|config|detail))(/) > mp.hpp
genfiles mp/smp/*(/) > mp/smp.hpp

for f in mp/{config,detail}/**/*.hpp ; gentest $f
for f in mp/smp/*.hpp ; [ -d $f[1,-5] ] || gentest $f

echo "#include \"jln/$f\"\n" > ../../test/autogen/${f[4,-1]//\//@}.cpp

echo 'int main(){}' > ../../test/autogen/main.cpp

cd ../../
./tools/update_meson.py
