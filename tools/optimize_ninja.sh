#!/usr/bin/env sh
if [ -d "$1" ] ;then
  f=$1/build.ninja
elif [ -d "$MESON_BUILD_ROOT" ]; then
  f=$MESON_BUILD_ROOT/build.ninja
fi

sed -i -E '
s/^( command = .*) -o \$out -c \$in/\1 -fsyntax-only $in \&\& :>$out/;t
s/-g[0-9]? |-O[1-3] //g;t
s/^(build [^:]+): cpp_LINKER/\1: phony/;Ta;n;d;:a
' "${f:-build.ninja}"
