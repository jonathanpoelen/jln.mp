#!/usr/bin/env python

from os import listdir
from os.path import isfile, join

all_targets = set()
i = 0
output_lines = []

def new_target(name):
  while name in all_targets:
    name += '_'
  all_targets.add(name)
  return name

def new_executable(name, path):
  global i
  target = f't_{i}'
  output_lines.append(f"{target} = executable('{name}', '{path}', dependencies: test_dep, build_by_default: false)")
  i = i+1
  return target

def new_alias(name, targets):
  deps = ", ".join(targets)
  output_lines.append(f"alias_target('{name}', {deps})")

def make_targets(path, prefix):
  l = []
  for f in listdir(path):
    newpath = join(path, f)
    if isfile(newpath):
      if f.endswith('.cpp'):
        name = new_target(f[:-4])
        l.append(new_executable(name, newpath))
    else:
      dirtarget = f'{prefix}.{f}'
      targets = make_targets(newpath, dirtarget)
      name = new_target(dirtarget)
      new_alias(name, targets)
      l += targets
  return l

new_alias('mp', make_targets('test/src', 'mp'))

with open('meson.build') as f:
  content = f.read()
start_str = '# start tests\n'
stop_str = '# stop tests\n'
start = content.index(start_str)
stop = content.index(stop_str, start)

with open('meson.build', 'w') as f:
  f.write(content[:start])
  f.write(start_str)
  f.write('\n'.join(output_lines))
  f.write('\n')
  f.write(stop_str)
  f.write(content[stop + len(stop_str):])
