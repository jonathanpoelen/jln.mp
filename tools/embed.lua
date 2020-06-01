#!/usr/bin/env lua

function eprint(...)
  io.stderr:write(...)
  io.stderr:write'\n'
end

function readfile(path)
  eprint('readfile: ', path)
  local f=io.open(path)
  local content = f:read('*a')
  f:close()
  return content
end

files={}
for i=1,#arg do
  files[arg[i]] = {readfile(arg[i]), true}
end

tinsert = table.insert
tconcat = table.concat

system_includes = {}

function process_include(type, incpath)
  if type == '<' then
    system_includes[incpath] = true
  else
    eprint('incpath: ', incpath)
    local path, pwd = canonical_path(incpath)
    local info = files[path]
    if not info then
      info = {readfile(path), true}
      files[path] = info
    end

    if info[2] then
      tinsert(pwd_stack, pwd)
      info[2] = false
      local content = patt:match(info[1])
      info[1] = ''
      pwd_stack[#pwd_stack] = nil
      return content
    end
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
    '#' * ws * 'include' * ws * C(S'"<') * C((1 - S'">')^0) * 1 * nl / process_include
  + '#pragma once' * nl / ''
  + 1
  )^0
)

splitpath = C((1 - P'/')^0)
splitpath = Ct(splitpath * ('/' * splitpath)^0)

function canonical_path(path)
  local parts = splitpath:match(path)
  local t = {unpack(pwd_stack[#pwd_stack])}
  for _,v in ipairs(parts) do
    if v ~= '..' then
      tinsert(t, v)
    else
      t[#t] = nil
    end
  end
  local current_path = tconcat(t, '/')
  t[#t] = nil
  return current_path, t
end

for path,info in pairs(files) do
  if info[2] then
    eprint('> ', path)
    local parts = splitpath:match(path)
    parts[#parts] = nil
    pwd_stack = {parts}
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
