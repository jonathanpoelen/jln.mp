#!/usr/bin/env python

import os

all_targets = set()
cpp_test_paths = []
output_lines = []

def new_target(name):
  while name in all_targets:
    name += '_'
  all_targets.add(name)
  return name

def new_executable(name, path, prefix, i):
  target = f'{prefix}{i}'
  output_lines.append(f"{target} = executable('{name}', '{path}', dependencies: test_dep)")
  return target

def new_alias(name, targets):
  deps = ", ".join(targets)
  output_lines.append(f"alias_target('{name}', {deps})")

def make_targets(path, prefix, target_prefix='t_'):
  l = []
  i = 0
  idir = 0
  for f in os.listdir(path):
    newpath = os.path.join(path, f)
    if os.path.isfile(newpath):
      if f.endswith('.cpp'):
        cpp_test_paths.append(f'{path}/{f}')
        name = new_target(f[:-4])
        l.append(new_executable(name, newpath, target_prefix, i))
        i += 1
    else:
      dirtarget = f'{prefix}.{f}'
      targets = make_targets(newpath, dirtarget, f'{target_prefix}{idir}_')
      name = new_target(dirtarget)
      new_alias(name, targets)
      l += targets
      idir += 1
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
  sources = "',\n  '".join(os.path.join('test/autogen', filename)
                        for filename in os.listdir('test/autogen'))
  f.write(f"executable('check_inc', [\n  '{sources}'\n], dependencies: test_dep)\n")
  f.write(stop_str)
  f.write(content[stop + len(stop_str):])

cpp_test_paths.sort()
with open('test/mp.cpp', 'w') as f:
  for path in cpp_test_paths:
    f.write(f'#include "{path[5:]}"\n')
