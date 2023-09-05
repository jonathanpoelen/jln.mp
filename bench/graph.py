#!/usr/bin/env python3
from collections import defaultdict, OrderedDict
from pygal.style import DarkStyle
import pygal
import sys

all_datas = defaultdict(lambda: defaultdict(OrderedDict))

name = sys.argv[1]

with open(name) as f:
  for line in f:
    if 'ALL' in line: continue
    if 'NONE' in line: continue
    if 'DISABLE' in line: continue

    # 0=name  1=comp  2=stdlib  3=type  4=lib  5=cppversion  6=builtin  7=time  8=memory
    infos = line.split(',')
    if infos[4] == 'jln' and infos[6][-1] == '0':
      continue

    # all_datas[f'{infos[1]}-cpp{infos[5]}-{infos[2]}-builtin={infos[6]}-{infos[3]}'][infos[4]][infos[0]] = float(infos[7])

    # radar
    if 'B' == infos[3]: continue
    all_datas[f'{infos[1]}-{infos[2]}-{infos[3]}'][f'{infos[4]}-cpp{infos[5]}'][infos[0]] = float(infos[7])

    # bar
    # all_datas[f'{infos[0]}-{infos[1]}-{infos[2]}'][f'{infos[4]}-cpp{infos[5]}'][infos[3]] = float(infos[7])

def normalize(lib_data: dict[str, dict[str, float]]) -> dict[str, dict[str, float]] | None:
  for lib, data in lib_data.items():
    base = data['B']
    data.pop('B')
    for k in data.keys():
      data[k] = max(data[k] - base, 0.0)

  all0 = [max(l:=[data[k] for data in lib_data.values()]) - min(l) < 0.003 for k in data.keys()]
  if all(all0):
    return None
  return {lib: {k: v * 1000 for is0, (k, v) in zip(all0, data.items()) if not is0}
          for lib, data in lib_data.items()}

def bar(id, lib_data):
  chart = pygal.Bar(style=DarkStyle)
  chart.title = f'Jln benchmark results: {id} [{name}]'
  for lib, data in lib_data.items():
    chart.add(lib, data.values())
  chart.x_labels = data.keys()
  chart.render_to_file(f'{id}.svg')

nmax = 12
std17 = 'std-cpp17'
jln17 = 'jln-cpp17'
std20 = 'std-cpp20'
jln20 = 'jln-cpp20'
def radar(id, lib_data):
  for p in (
    (std17, jln17),
    (std20, jln20),
    #(jln17, jln20),
  ):
    lib_values = [(lib, list(lib_data[lib].values())) for lib in p]
    keys = list(lib_data[p[0]].keys())

    length = len(lib_data[p[0]])
    n = (length + nmax - 1) // nmax
    for num in range(n):
      i = num * nmax
      j = min(i + nmax, length)
      chart = pygal.Radar(fill=True)
      chart.title = f'Jln benchmark results: {id} ({num}) [{name}]'
      chart.y_title = 'In second (lower is better)'
      for lib, values in lib_values:
        chart.add(lib, values[i:j])
      chart.x_labels = keys[i:j]
      chart.render_to_file(f'{id}-{p}-{num}.svg')

for id, lib_data in all_datas.items():
  #lib_data = normalize(lib_data)
  #if not lib_data:
  #  continue

  #bar(id, lib_data)
  radar(id, lib_data)
