#!/bin/sh
if [ -d "$1" ] ;then
  f=$1/build.ninja
elif [ -d "$MESON_BUILD_ROOT" ]; then
  f=$MESON_BUILD_ROOT/build.ninja
fi

sed -i -E '
s/^( command = .*) -o \$out -c \$in/\1 -fsyntax-only $in \&\& :>$out/;t
s/^(build [^:]+): cpp_LINKER/\1: phony/;Ta;n;d;:a
' "${f:-build.ninja}"
