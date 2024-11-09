#!/usr/bin/env bash
# SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
# SPDX-License-Identifier: MIT
set -ex

if [[ -d "$1" ]]; then
  f="$1"/build.ninja
elif [[ -f "$1" ]]; then
  f="$1"
elif [[ -f "$MESON_BUILD_ROOT/build.ninja" ]]; then
  f="$MESON_BUILD_ROOT"/build.ninja
else
  f=build.ninja
fi

sed -i '
  s/^\( command = .*\) -o \$out -c \$in/\1 -fsyntax-only $in \&\& :>$out/;t
  s/-g[0-9]\? \|-O[1-3] //g;t
  s/^\(build [^:]\+\): cpp_LINKER\(_RSP\)\?/\1: phony/;Ta;n;d;:a
' "$f"
