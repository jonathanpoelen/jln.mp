#!/usr/bin/env lua
-- SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
-- SPDX-License-Identifier: MIT

function eprint(...)
  io.stderr:write(...)
  io.stderr:write'\n'
end

function readfile(path)
  eprint('readfile: ', path)
  local f = io.open(path)
  local content = f:read('*a')
  f:close()
  return content
end

files={}
for i=1,#arg do
  files[arg[i]:gsub('.*jln/', '')] = {readfile(arg[i]), true}
end

tinsert = table.insert
tconcat = table.concat

system_includes = {}
sources = {}
copyrights = {}

function process_include(jln_prefix, incpath)
  if jln_prefix ~= '' then
    eprint('incpath: ', incpath)
    local info = files[incpath]
    if not info then
      info = {readfile('include/jln/' .. incpath), true}
      files[incpath] = info
    end
    if info[2] then
      info[2] = false
      tinsert(sources, patt:match(info[1]))
      info[1] = ''
    end
  else
    eprint('syspath: ', incpath)
    system_includes[incpath] = true
  end
  return ''
end

function process_comment(comment)
  first_comment = first_comment or comment
  return ''
end

function process_copyright(comment)
  copyrights[comment] = comment
  return ''
end

function process_license(comment)
  license = comment
  return ''
end

l=require'lpeg'
P=l.P
S=l.S
C=l.C
Cs=l.Cs
Ct=l.Ct

nl = S'\n '^0
ws = P' '^0
patt = Cs(
  ('/*' * (1 - P'*/')^0 * 2 * nl / process_comment)^-1 *
  ('// SPDX-FileCopyrightText:' * (1 - P'\n')^0 * 1 / process_copyright)^-1 *
  ('// SPDX-License-Identifier:' * (1 - P'\n')^0 * 1 / process_license)^-1 * (
    '#' * ws * 'include' * ws * '<' * C(P'jln/'^-1) * C((1 - P'>')^0) * 1
    * ws * (P'//' * (1 - P'\n')^0)^-1 * '\n' / process_include
  + '#pragma once' * nl / ''
  + 1
  )^0
)

splitpath = C((1 - P'/')^0)
splitpath = Ct(splitpath * ('/' * splitpath)^0)

unpack = unpack or table.unpack

for path,info in pairs(files) do
  if info[2] then
    eprint('> ', path)
    info[2] = false
    info[1] = patt:match(info[1])
  end
end

includes = {}
for k in pairs(system_includes) do
  tinsert(includes, k)
end
table.sort(includes)

for k,_ in pairs(copyrights) do
  tinsert(copyrights, k)
end
table.sort(copyrights)

embed = {
  first_comment or '',
  tconcat(copyrights, ''),
  license or '',
  '// Amalgamated version of https://github.com/jonathanpoelen/jln.mp\n\n',
  '#pragma once\n\n',
  '#ifndef JLN_MP_HPP\n',
  '#define JLN_MP_HPP\n\n',
  '#include <',
  tconcat(includes, '>\n#include <'),
  '>\n\n',
}

print(tconcat(embed, ''))

source = tconcat(sources, '')

-- remove #if ... \n (empty) #else (empty) #endif
source = Cs(
  ( P'#' * ws * 'if' * (1 - P'\n')^0 * '\n'
  * (ws * '#' * ws * 'el' * (1 - P'\n')^0 * '\n')^0
  * ws * '#' * ws * 'endif\n'
  / ''
  + 1
  )^0
)
:match(source)

-- remove } // namespace jln::mp \n namespace jln::mp {
source = Cs(
  ( P'\n} // namespace jln::mp\n' * P'\n'^0 * 'namespace jln::mp\n{\n'
  / '\n'
  + 1
  )^0
)
:match(source)

print(source)

for path,info in pairs(files) do
  if #info[1] ~= 0 then
    print(info[1])
  end
end

print('#endif')
