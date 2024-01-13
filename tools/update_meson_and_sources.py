#!/usr/bin/env python
# SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
# SPDX-License-Identifier: MIT

import os
import shutil

all_targets = set()
cpp_test_paths = []
meson_output_lines = []

def ordered_listdir(path):
  l = os.listdir(path)
  l.sort()
  return l

def new_target(name):
  while name in all_targets:
    name += '_'
  all_targets.add(name)
  return name

def new_executable(name, path, prefix, i):
  target = f'{prefix}{i}'
  meson_output_lines.append(f"{target} = executable('{name}', '{path}', dependencies: test_dep)")
  return target

def new_alias(name, targets):
  deps = ", ".join(targets)
  meson_output_lines.append(f"alias_target('{name}', {deps})")

def make_targets(path, prefix, target_prefix='t'):
  l = []
  for f in ordered_listdir(path):
    newpath = os.path.join(path, f)
    if os.path.isfile(newpath):
      if f.endswith('.cpp'):
        basename = f[:-4]
        cpp_test_paths.append(f'{path}/{f}')
        name = new_target(basename)
        l.append(new_executable(name, newpath, target_prefix, f'_{basename}'))
    else:
      dirtarget = f'{prefix}.{f}'
      targets = make_targets(newpath, dirtarget, f'{target_prefix}_{f}')
      name = new_target(dirtarget)
      new_alias(name, targets)
      l += targets
  return l


LICENSE = (
  '// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>\n'
  '// SPDX-License-Identifier: MIT\n'
)


autogen_tests = []

def gentest(test_prefix, dir_path, filename):
  test_name = f'{test_prefix}{filename[:-3]}cpp'.replace('/','@')
  test_name = f'test/autogen/{test_name}'
  autogen_tests.append(test_name)
  with open(test_name, 'w') as ftest:
    ftest.write(LICENSE)
    ftest.write(f'#include "jln/{dir_path}/{filename}"\n')

def genfiles(dir_path):
  path = f'include/jln/{dir_path}'
  seppos = dir_path.find('/')
  test_prefix = '' if seppos == -1 else f'{dir_path[seppos+1:]}/'

  rootfile = dir_path if seppos == -1 else dir_path[seppos+1:]
  rootdir = '' if seppos == -1 else dir_path[:seppos]
  gentest(test_prefix, rootdir, f'{rootfile}.hpp')

  with open(f'{path}.hpp', 'w') as outfile:
    outfile.write(LICENSE)
    outfile.write("#pragma once\n\n")

    for d in ordered_listdir(path):
      if d in ('smp', 'config'):
        continue

      newpath = f'{path}/{d}'
      if os.path.isdir(newpath):
        if d == 'detail':
          for filename in os.listdir(newpath):
            if filename.endswith('.hpp'):
              gentest(test_prefix, dir_path, f'{d}/{filename}')
        else:
          outfile.write(f'#include <jln/{dir_path}/{d}.hpp>\n')
          with open(f'{newpath}.hpp', 'w') as flist:
            flist.write(LICENSE)
            flist.write("#pragma once\n\n")
            for filename in ordered_listdir(newpath):
              if filename.endswith('.hpp'):
                flist.write(f'#include <jln/{dir_path}/{d}/{filename}>\n')
                gentest(test_prefix, dir_path, f'{d}/{filename}')
      elif not os.path.isdir(newpath[:-4]):
        if d != 'detail':
          outfile.write(f'#include <jln/{dir_path}/{d}>\n')
        gentest(test_prefix, dir_path, d)


if os.path.isdir('test/autogen/'):
  shutil.rmtree('test/autogen/')
os.mkdir('test/autogen')

new_alias('mp', make_targets('test/src', 'mp'))
genfiles('mp')
genfiles('mp/smp')
with open(f'test/autogen/main.cpp', 'w') as f:
  f.write(LICENSE)
  f.write('int main() {}')
autogen_tests.append(f'test/autogen/main.cpp')


with open('meson.build') as f:
  content = f.read()

start_example_str = '# start examples\n'
stop_example_str = '# stop examples\n'
start_examples = content.index(start_example_str)
stop_example = content.index(stop_example_str, start_examples)

start_test_str = '# start tests\n'
stop_test_str = '# stop tests\n'
start_test = content.index(start_test_str, stop_example)
stop_test = content.index(stop_test_str, start_test)

examples = ordered_listdir('examples')

with open('meson.build', 'w') as f:
  f.write(content[:start_examples + len(start_example_str)])

  example_exes = '\n'.join(
    f"example_{name[:-4]} = executable('{name[:-4]}.example', 'examples/{name}', dependencies: example_dep)"
    for name in examples)
  example_all = ', '.join(f'example_{name[:-4]}' for name in examples)

  f.write(example_exes)
  f.write('\n')
  f.write(f"alias_target('examples', {example_all})\n")

  f.write(content[stop_example:start_test + len(start_test_str)])

  f.write('\n'.join(meson_output_lines))
  f.write('\n')
  sources = "',\n  '".join(autogen_tests)
  f.write(f"executable('check_inc', [\n  '{sources}'\n], dependencies: test_dep)\n")

  f.write(content[stop_test:])

with open('test/mp.cpp', 'w') as f:
  f.write(LICENSE)
  for path in cpp_test_paths:
    f.write(f'#include "{path[5:]}"\n')
