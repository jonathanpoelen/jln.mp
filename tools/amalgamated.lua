#!/usr/bin/env lua

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
      local content = patt:match(info[1])
      info[1] = ''
      return content
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

l=require'lpeg'
P=l.P
S=l.S
C=l.C
Cs=l.Cs
Ct=l.Ct

nl = S'\n '^0
ws = P' '^0
patt = Cs(
  ('/*' * (1 - P'*/')^0 * 2 * nl / process_comment)^-1 * (
    '#' * ws * 'include' * ws * '<' * C(P'jln/'^-1) * C((1 - P'>')^0) * 1 * nl / process_include
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

embed = {
  first_comment or '',
  '// amalgamated version of https://github.com/jonathanpoelen/jln.mp\n\n'
  '#pragma once\n\n',
  '#ifndef JLN_MP_HPP\n',
  '#define JLN_MP_HPP\n\n',
  '#include <',
  tconcat(includes, '>\n#include <'),
  '>\n\n',
}

for path,info in pairs(files) do
  if #info[1] ~= 0 then
    tinsert(embed, info[1])
    tinsert(embed, '\n')
  end
end

print(tconcat(embed, ''))
print('#endif')
