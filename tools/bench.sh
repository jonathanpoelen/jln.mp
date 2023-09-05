#!/bin/bash
# SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
# SPDX-License-Identifier: MIT

TIMES=${TIMES:-3}
NELEM=${NELEM:-100}
NREPEAT=${NREPEAT:-50}
STD=${STD:-17}

compile()
{
  echo "$ ${@@Q}"

  l=$(/usr/bin/time --format='%Es - %MK' "$@" 2>&1) || {
    echo "$l" >&2
    exit 1
  }

  {
    echo "$l"
    echo "$l" >&2
    for ((i=1; i < TIMES; ++i)); do
      l=$(/usr/bin/time --format='%Es - %MK' "$@" 2>&1)
      echo "$l"
      echo "$l" >&2
    done
  } | sort -n | {
    for ((i=TIMES / 2; i < TIMES; ++i)); do
      read l
    done
    echo $'\e[31m> '"$l"$'\e[m'
  }
}

if [[ -z $COMPILER ]]; then
  COMPILERS=(g++ clang++)
else
  COMPILERS=($COMPILER)
fi

if [[ -z $IMPL ]]; then
  IMPLS=(0 1 2)
else
  read -a IMPLS <<<"$IMPL"
fi

extra=()

if [[ -n $INCLUDE ]]; then
  extra+=(-DINCLUDE="$INCLUDE")
fi

if [[ -n $ALGO ]]; then
  extra+=(-DALGO="$ALGO")
fi

for impl in ${IMPLS[@]}; do
  for comp in ${COMPILERS[@]}; do
    compile $comp -DIMPL=$impl -DNELEM=$NELEM -DNREPEAT=$NREPEAT ${extra[@]} -std=c++$STD -fsyntax-only -fdiagnostics-color=always "$@"
  done
done
