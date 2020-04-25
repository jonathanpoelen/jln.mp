#!/bin/sh
if [ -d "$1" ] ;then
  f=$1/build.ninja
fi

sed -i -E '
s/^( command = .*) -o \$out -c \$in/\1 -fsyntax-only $in \&\& :>$out/
s/^ command = .*\$LINK_ARGS/ command = :>$out/
' "${f:-build.ninja}"
