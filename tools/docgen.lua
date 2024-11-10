#!/usr/bin/env lua
-- SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
-- SPDX-License-Identifier: MIT

local parseFile
local preprocOnlyPattern
local htmlify
local linkifier
local md2html
local splitShortAndLongDesc
local fragmentName
local inlinecode_begin = '<code class="inlinecode highlight" data-lang="cpp">'
local inlinecode_end = '</code>'
local blockcode_begin = '<code class="blockcode highlight" data-lang="cpp">'
local blockcode_end = '</code>'
local defgroups = {}
local namespaces = {
  ['traits::emp'] = {},
  traits = {},
  -- smp = {},
  emp = {},
  mp = {},
}
namespaces[''] = namespaces.mp
local exclude_namespaces = {
  'detail'
}
local _global_filename

local kw = {
  'treturn',
  'semantics',
  'pre',
  'post',
  'note',
  'see',
  'tparam',
  'defgroup',
  'desc',
  'namespace',
  'struct',
  'using',
  'static_constexpr',
  'comment',
}
local kwindexes = {}

function torefid(namespace, name)
  if #namespace == 0 then
    return 'mp::' .. name
  else
    return namespace .. '::' .. name
  end
end

do
local lpeg = require'lpeg'
local C = lpeg.C
local P = lpeg.P
local R = lpeg.R
local S = lpeg.S
local V = lpeg.V
local Cc = lpeg.Cc
local Cs = lpeg.Cs
local Ct = lpeg.Ct

local kwpatts = {}
for k,v in ipairs(kw) do
  local f = function() return k end
  kwindexes[v] = k
  kwpatts[v] = P(v) / f
end

local ctx_namespace
local ctx_ref_namespace
local fileinfos

local reset_parser = function()
  ctx_namespace = ''
  ctx_ref_namespace = ''
  fileinfos = {}
end

local f_defgroup = function(name, desc) defgroups[#defgroups+1] = {name, table.concat(desc)} end
local f_ingroup = function(name) fileinfos.ingroup = name end

local i_tparam = kwindexes.tparam
local f_push_tparam = function(name, desc)
  fileinfos[#fileinfos+1] = {i_tparam, name, table.concat(desc)}
end

local f_push_lines = function(k, lines)
  if lines[1] == '\n' then
    lines[1] = ''
  end
  fileinfos[#fileinfos+1] = {k, table.concat(lines)}
end

local i_desc = kwindexes.desc
local f_desc = function(lines)
  local desc = table.concat(lines)
  -- add description lines to the fragment if one already exists
  for _, t in ipairs(fileinfos) do
    if t.i == i_desc then
      t[1] = t[1] .. desc
      return
    end
  end
  fileinfos[#fileinfos+1] = {i = i_desc, desc}
end

function human_template(tparams)
  if not tparams then
    return nil
  end

  local t = {}
  local r
  -- 1: 'template<...>' or nil
  -- 2: 'class' or type
  -- 3: '...' or ''
  -- 4: name or nil
  -- 5: = value
  for k,v in ipairs(tparams) do
    if v[2] == 'class' then
      r = (v[1] and v[1] .. ' ' or '') .. (v[4] or '_') .. v[3]
    elseif v[4] then
      r = v[2] .. v[3] .. ' ' .. v[4]
    else
      r = v[2] .. v[3]
    end
    if v[5] then
      -- sanitize_struct_impl(v[5])
      r = r .. ' = ' .. v[5]
    end
    t[#t+1] = r
  end
  return '<' .. table.concat(t, ', ') .. '>'
end

local sanitize_struct_impl

local f_type = function(ctx_tparams, k, cpp_type, name, spe, tparams, mem, impl)
  namespaces[ctx_namespace][name] = true
  fileinfos.firstname = fileinfos.firstname or name
  fileinfos[#fileinfos+1] = {
    i = k,
    human_tparams = human_template(ctx_tparams),
    namespace = ctx_namespace,
    cpp_type = cpp_type,
    name = name,
    refid = torefid(ctx_namespace, name),
    fullname = ctx_ref_namespace .. name,
    impl = sanitize_struct_impl(impl),
    spe = spe,
    mem = mem,
    human_tparams_mem = human_template(tparams),
  }
end

local i_namespace = kwindexes.namespace
local f_namespace = function(name)
  if not namespaces[name] then
    error('missing \\cond ... \\endcond with\n  namespace: '
          .. name .. '\n  filename: ' .. _global_filename)
  end
  local ref_name = (name == '') and '' or name .. '::'
  ctx_namespace = name
  ctx_ref_namespace = ref_name
  fileinfos[#fileinfos+1] = {i_namespace, name}
end

local previous_name
local f_emp_namespace = function(name)
  previous_name = ctx_namespace
  f_namespace(ctx_namespace == '' and name or ctx_namespace .. '::' .. name)
end
local f_restore_namespace = function()
  f_namespace(previous_name)
end

local Until = function(p) return (1 - P(p))^0 end
local After = function(p) return Until(p) * p end
local List = function(p, sep) p = P(p) return p * (sep * p)^0 end
local Balanced = function(open, close)
  return P{ open * (1 - S(open..close) + V(1))^0 * close, }
end
local sp = P' '^1
local sp0 = P' '^0
local ws = S' \n'^1
local ws0 = S' \n'^0
local unl = Until'\n' * 1
local cunl = C(Until'\n') * 1
local alnum = R('az','09','AZ')
local charid = alnum + S':_'
local id = charid^1
local cid = C(id)
local balancedparent = Balanced('(', ')')
local tagasoperator = '<' * S'= ' + '>='
local balancedtag = P{
  '<' * (1 - S'<>()' + tagasoperator + V(1) + V(2))^0 * '>',
  '(' * (1 - S'()' + V(2))^0 * ')',
}
local cbalancedparent = C((1-S'()' + balancedparent)^1)
local cbalancedparent_arg = C((1-S'(),' + balancedparent)^1)

splitShortAndLongDesc = C(Until('.\n' + -P(1)) * P'.'^-1) * sp0 * C(P(1)^0)

fragmentName = Cs(
  P'jln/mp/' / function(s) return '<span class="depth1">jln/mp/</span>' end
* (Until(S'/') * '/' / function(s) return '<span class="depth2">' .. s .. '</span>' end)
* (Until(S'.') / function(s) return '<span class="basename">' .. s .. '</span>' end)
* (P'.hpp' / function(s) return '<span class="ext">.hpp</span>' end)
)

local sanitize_space = Cs(ws0 / '' * (
  ' >' * ws / ' > '
+ ' <' * ws / ' < '
+ ',\n' * ws0 / ', '
+ '\n' * ws0 / ''
+ ws / ' '
+ 1
)^0)

local sanitize_struct_impl_patt = Cs((
  (P'typename ' + 'template ') / ''
+ 1
)^0)
local contains_impl = P{ (P'detail::' + '__' + 'impl') + 1 * V(1) }
local detect_chars = P{ alnum + 1 * V(1) }

sanitize_struct_impl = function(s)
  if not s or not detect_chars:match(s) or contains_impl:match(s) then
    return nil
  end
  s = sanitize_struct_impl_patt:match(s)
  return s
end

local blockComment = '/*' * Until'*/' * 2

local f_ident = function(s) return s end
local preproc -- used into JLN_MP_CALL transformation
preproc = P{
  "S";
  S=Cs(
  ( V'p'
  + '#' * unl / ''
  + V'c'
  + 1
  )^0)

, c='JLN_MP_' * P'FORCE_'^0 * 'DCALL' * P'F'^0 * P'_V'^0 * P'_C'^0 * P'_TRACE'^0 * '_XS('
    * ((1-S'()<,' + tagasoperator + balancedparent + balancedtag)^1)
    * ',' * ws0 * cid
    * ',' * ws0 * cbalancedparent
    * ')'
    / function(f, args) return preproc:match(f) .. '::f<' .. preproc:match(args) .. '>' end

  + P'JLN_MP_FORCE_LAZY_P' * P'_T'^0 * '('
    * ((1-S'()<,' + tagasoperator + balancedparent + balancedtag)^1)
    * ',' * ws0 * cbalancedparent
    * ')'
    / function(arg) return preproc:match(arg) end

  + P'JLN_MP_TRACE_F(' * cbalancedparent * ')'
    / function(f) return preproc:match(f) end

  + P'JLN_MP_CALL_TRACE' * P'_T'^0 * '('
    * cbalancedparent_arg
    * ',' * ws0 * cbalancedparent
    * ')'
    / function(f, args) return preproc:match(f) .. '::f<' .. preproc:match(args) .. '>' end

  + P'JLN_MP_MSVC_FIX_CALL' * P'_T'^0 * '(' * ws0
    * '(' * cbalancedparent * '),'
    * ws0 * cbalancedparent
    * ')'
    / function(f, args) return preproc:match(f) .. '::f<' .. preproc:match(args) .. '>' end

  + 'JLN_MP_DCALL_TRACE_XS_0('
    * ((1-S'()<,' + tagasoperator + balancedparent + balancedtag)^1)
    * ')'
    / function(f, args) return preproc:match(f) .. '::f<>' end

  + 'JLN_MP_CALL_TRACE_0_ARGS(' * ws0 * cbalancedparent * ')'
    / function(f) return preproc:match(f) .. '::f<>' end

  + P'JLN_MP_IDENT(' * cbalancedparent * ')'
    / function(f) return preproc:match(f) end

  + P'JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE('
    * ws0 * cid * ',' * ws0 * cbalancedparent * ws0 * ')'
    / function(name, args) return 'number<emp::' .. name .. '_v<' .. preproc:match(args) .. '>>' end

  + P'JLN_MP_NUMBER_FROM_VARIABLE_TEMPLATE_OR_TYPE('
    * ws0 * cid * ',' * ws0 * id * ',' * ws0 * cbalancedparent * ws0 * ')'
    / function(name_v, args) return 'number<' .. name_v .. '<' .. preproc:match(args) .. '>>' end

  + P'JLN_MP_' * P'RAW_'^0 * 'EXPR_TO_BOOL(' * cbalancedparent * ')'
    / function(f) return 'bool(' .. preproc:match(f) .. ')' end

  + P'JLN_MP_RAW_EXPR_TO_BOOL_NOT(' * cbalancedparent * ')'
    / function(f) return '!' .. preproc:match(f) end

  + P'JLN_MP_EXPR_TO_BOOL_NOT(' * cbalancedparent * ')'
    / function(f) return '!(' .. preproc:match(f) .. ')' end

  + P'JLN_MP_IS_SAME(' * ws0 * cbalancedparent_arg * ',' * ws0 * cbalancedparent * ws0 * ')'
    / function(a, b) return 'std::is_same_v<' .. preproc:match(a) .. ', ' .. preproc:match(b) .. '>' end

  + P'JLN_MP_INTEGRAL_AS(' * ws0 * cid * ',' * ws0 * cid * ws0 * ')'
    / function(t, expr) return t .. '{' .. preproc:match(expr) .. '}' end

  + P'JLN_MP_AS_BOOL(' * ws0 * cbalancedparent * ws0 * ')'
    / function(expr) return 'bool{' .. preproc:match(expr) .. '}' end

  + P'JLN_MP_AS_MP_INT(' * ws0 * cbalancedparent * ws0 * ')'
    / function(expr) return 'int_{' .. preproc:match(expr) .. '}' end

  + P'JLN_MP_SET_CONTAINS(' * cbalancedparent * ')'
    / function(expr) return 'emp::set_contains_xs_v<' .. expr .. '>' end

  + P'JLN_MP_LIFT_WRAP(' * cid * ')'
    / function(name) return 'lift_t<' .. name .. '>' end

  + P'JLN_MP_CALL_TRY_IMPL(' * cid * ws0 * ',' * ws0 * cbalancedparent * ws0 * ')'
    / function(f, args) return 'try_<' .. preproc:match(f) .. '>::f<' .. preproc:match(args) .. '>' end

  + P'JLN_MP_SET_CONTAINS_BASE' * balancedparent / '/*...*/'
  + P'JLN_MP_TPL_AUTO_OR_INT' / 'auto /*or int_*/'
  + P'JLN_MP_TRACE_TYPENAME' / ''

, p='#' * sp0 / '' *
    ( P'ifdef JLN_MP_DOXYGENATING' / ''
      * Cs((1 - P'#' + V'#preproc' / '' + V'c')^0)
      * V'rm#endif'
    + 'if 0' * After(V'#endif') / ''
    + 'if' * unl / '' * Cs(( V'c'
                           + V'\\cond'
                           + (1 - P'#')
                           + V'p'
                           + V'#preproc' / ''
                           )^1)
      * V'rm#endif'
    + (V'#def' + V'#undef') / ''
    )
  + V'\\cond'

, ['#preproc']='#' * sp0 * (
    'if' * unl * ( (1 - P'#')
                 + V'#preproc'
                 )^1
    * V'#endif'
  + P'el' * unl * ((1 - P'#') + V'#preproc')^0
  + V'#def'
  + V'#undef'
  )

, ['#def']='define ' * List(Until(S'\n\\'), P'\\' * 1) * 1
, ['#undef']='undef ' * unl
, ['#endif']='#' * sp0 * 'endif'
, ['rm#endif']=V'#endif' / ''

, ['\\cond']=('/// \\cond' * Until'\\endcond' * 9 + blockComment) / ''
}

local lines = Ct(List(C(unl) * sp0, '///' * P' '^-1 * -P'\\'))
local tparam = Ct(
  (C('template' * balancedtag) + Cc(nil)) * ws0
  * C(id * balancedtag^-1 * (ws0 * blockComment)^-1)
  * ws0 * C(P'...'^-1) * ws0 * (cid + Cc(nil)) * ws0
  * ('=' * ws0 * C('[]{}' + id * ws0 * balancedtag^-1))^-1)
local tparams = Ct('<' * List(ws0 * tparam, ',') * '>')
local template = 'template' * ws0 * tparams
-- local template = C('template' * ws0 * balancedtag)

local ignore_namespace
for k,name in ipairs(exclude_namespaces) do
  if ignore_namespace then
    ignore_namespace = ignore_namespace + P(name)
  else
    ignore_namespace = P(name)
  end
  ignore_namespace = ignore_namespace + P('jln::mp::' .. name)
end

local pattern = P{
  (V('e') + 1)^1,
  e=( '/// ' *
      ( '\\' *
        ( 'ingroup ' * cunl / f_ingroup
        + (
            ( kwpatts.treturn
            + kwpatts.semantics
            + kwpatts.pre
            + kwpatts.post
            + kwpatts.note
            + kwpatts.see
            ) * sp0 * lines
          ) / f_push_lines
        + 'tparam ' * sp0 * C(Until(S' ')) * sp * lines / f_push_tparam
        + 'defgroup ' * sp0 * C(Until(S' ')) * sp * lines / f_defgroup
        )
      + lines / f_desc
      ) * sp0)^1
    + (template + Cc(nil)) * ws0
      * ( (P'struct' + 'class') * ws * Cc(kwindexes.struct) * Cc(nil) * cid * Until(S':;{<')
          * (C(balancedtag) * ws0 + Cc(nil))
          * (':' * ws0 * id * ws0
            * (balancedtag * ws0 * (('::template ' * id * balancedtag + id) * ws0)^0)^-1
            )^-1
          * ( P';'
            + P'{' * ws0
              * ( template^-1 * ws0 * (P'using' + 'class' + 'struct')
                  * ws * cid * ws0 * ('=' * ws0 * C(Until';'))^-1
                + ( '};'
                  + 'static const' * P'expr'^-1 * ws0 * id
                    * ('(' * Until')' * 1)^-1 * ws0 * Cc(nil)
                    * C(Until(P' =' + '=')) * P' '^-1 * '=' * ws0 * C(Until';')
                  )
                )
            )
        + 'using ' * Cc(kwindexes.using) * Cc(nil) * cid * ws0 * '='
          * ws0 * Cc(nil) * Cc(nil) * Cc(nil) * C(Until';')
        -- using name;
        + 'using ' * Cc(kwindexes.using) * Cc(nil) * (id / function(name)
            local i = name:find(':[a-zA-Z0-9_]+$')
            return i and name:sub(i+1) or name
          end) * ';'
          * Cc(nil) * Cc(nil) * Cc(nil) * Cc(nil)
        + (P'static ' + 'inline ')^0 * 'constexpr ' * Cc(kwindexes.static_constexpr)
          * cid * ws * cid * ws0 * '=' * ws0 * Cc(nil) * Cc(nil) * Cc(nil) * C(Until';')
        ) / f_type
    + 'namespace '
      * ( ignore_namespace * ws0 * Balanced('{', '}')
        + ( C('emp') * '\n' / f_emp_namespace * ws0 * '{' * (V('e') + (1 - S'{}'))^0
            * (P'}' / f_restore_namespace)
          + ws0 * ('jln::mp' * P'::'^-1)^-1 * (cid + Cc('')) / f_namespace
          )
        )
    + '//' * Until'\n' * 1
    -- + '/*' * Until'*/' * 2
}

preprocOnlyPattern = (ws + (P'#' + '//') * unl)^0 * -P(1)

parseFile = function(contents)
  reset_parser()
  pattern:match(preproc:match(contents))
  return fileinfos
end

htmlifier_init = function()
  local htmlspecialchars_c = P'<' / '&lt;' + P'&' / '&amp;'
  local htmlspecialchars = Cs((htmlspecialchars_c + 1)^0)

  local links_by_namespace = {['']={}}
  local global_table = {}

  local tag_table = {}

  local mk_tag = function(tag)
    local span = '<span class="'..tag..'">'
    return function(s)
      local r = tag_table[s]
      if not r then
        r = span .. s .. '</span>'
        tag_table[s] = r
      end
      return r
    end
  end

  local mk_tag_specialchar = function(tag)
    local span = '<span class="'..tag..'">'
    return function(s)
      local r = tag_table[s]
      if not r then
        r = span .. htmlspecialchars:match(s) .. '</span>'
        tag_table[s] = r
      end
      return r
    end
  end

  for namespace, t in pairs(namespaces) do
    if #namespace == 0 then
      for name in pairs(t) do
        global_table[name] = '<a href="#mp::' .. name .. '">' .. name .. '</a>'
      end
    else
      local link_table = {}
      links_by_namespace[namespace] = link_table

      local prefix = namespace .. '::'
      local hiprefix = prefix:gsub('::', '<span class="p">::</span>')

      for name in pairs(t) do
        local codename = prefix .. name
        global_table[codename] = '<a href="#' .. codename .. '">' .. hiprefix .. name .. '</a>'
        link_table[name] = '<a href="#' .. codename .. '">' .. name .. '</a>'
      end
    end
  end

  local tokid = R('az','AZ','09') + S'_'

  local current_table
  local patt = Cs(
    ( ( ( P'template' + 'class' + 'struct' + 'using' + 'typename'
        + 'decltype' + 'sizeof' + 'auto' + 'static_assert'
        + 'constexpr' + 'return' + 'namespace' + 'static_cast'
        ) / mk_tag'k'
      + ( P'void' + 'int' + 'unsigned' + 'long' + 'bool' + 'char' + 'short'
        + 'double' + 'float'
        ) / mk_tag'kt'
      + (P'true' + 'false') / mk_tag'nb'
      ) * -#tokid
    + R'az' * charid^1 / function(s)
        return current_table[s] or global_table[s] or s:gsub('::', '<span class="p">::</span>')
      end
    + P'//' * Until'\n' / mk_tag_specialchar'c1'
    + P'/*' * Until'*/' * 2 / mk_tag_specialchar'c1'
    + S'#' * Until'\n' / mk_tag_specialchar'cp'
    + S'{}()[]:;,.'^1 / mk_tag'p'
    + S'<>+-/%*=&|' / mk_tag_specialchar'o'
    + R'09'^1 / mk_tag'mi'
    + tokid^1
    + 1
    )^0
  )

  linkifier = function(namespace, s)
    current_table = links_by_namespace[namespace]
    return patt:match(s)
  end

  local inlinecode = function(s)
    return inlinecode_begin .. linkifier('', s) .. inlinecode_end
  end

  local blockcode = function(s)
    local first_space = s:match('^\n +')
    if first_space then
      first = true
      s = s:gsub(first_space, function()
        r = first and '' or '\n'
        first = false
        return r
      end)
    end
    return blockcode_begin .. linkifier('', s) .. blockcode_end
  end

  local inline_func = function(s)
    local e = global_table[s]
    return e and (inlinecode_begin .. e .. inlinecode_end) or ''
  end

  local mdinlinecodepatt = P'`' * C(Until'`') * '`' / inlinecode

  htmlify = Cs((
    mdinlinecodepatt
  + P'\\c ' / '' * (Until(S' \n' + '.\n') / inlinecode)
  + P'\\code' * (sp0 * '\n')^0 * C(Until(ws0 * '\\endcode')) * ws0 * '\\endcode' / blockcode
  + P'\\ints' / ('<a href="#d_sequence">sequence</a> of ' .. inline_func('int_'))
  + (P'\\int_' + '\\int') / inline_func('int_')
  + P'\\list' / inline_func('list')
  + P'\\number' / inline_func('number')
  + P'\\map' / '<a href="#d_map">map</a>'
  + P'\\set' / '<a href="#d_set">set</a>'
  + P'\\sequence' / '<a href="#d_sequence">sequence</a>'
  + P'\\predicate' / '<a href="#d_predicate">predicate</a>'
  + P'\\value' / '<a href="#d_value">value</a>'
  + P'\\val' / inline_func('val')
  + P'\\bool' / (function()
    local a = global_table['true_']
    local b = global_table['false_']
    return a and b
       and (inlinecode_begin .. a .. inlinecode_end .. ' / '
         .. inlinecode_begin .. b .. inlinecode_end)
       or ''
  end)()
  + P'\\typelist' / '<a href="#d_typelist">typelist</a>'
  + P'\\function' / '<a href="#d_function">function</a>'
  + P'\\metafunction' / '<a href="#d_metafunction">meta-function</a>'
  + P'\\lazymetafunction' / '<a href="#d_lazymetafunction">lazy meta-function</a>'
  + P'\\link ' * cid / inlinecode
  + htmlspecialchars_c
  + 1
  )^0)


  local mdfragment2htmlpatt = Cs((mdinlinecodepatt + 1)^0)

  local def_list = function(word, def)
    return '<dt id="d_' .. word:gsub('[ -]', ''):lower() .. '">'
        .. mdfragment2htmlpatt:match(word)
        .. '</dt><dd>' .. mdfragment2htmlpatt:match(def) .. '</dd>\n'
  end

  local normal_list = function(line)
    return '<li>' .. mdfragment2htmlpatt:match(line) .. '</li>'
  end

  local lvl_stack = {}

  local t2idpatt = Cs(((R('az','AZ','09') + S'_-')^1 + P(1) / '')^1)

  local headers

  local headerize = function(h, title)
    local current_lvl = #h
    local id = t2idpatt:match(title):lower()
    local prefix = ''
    if current_lvl ~= 1 then
      id = lvl_stack[current_lvl-1] .. '__' .. id
    else
      prefix = '</section>\n' .. prefix .. '<section>'
      headers[#headers+1] = {id, title}
    end
    lvl_stack[current_lvl] = id
    return prefix .. '<h'..current_lvl..' id="' .. id .. '">' .. title
        .. '<a href="#' .. id .. '" class="titleref">¶</a>' .. '</h'..current_lvl..'>\n'
  end

  local wrap_with = function(open, close)
    return function(s)
      return open .. s .. close
    end
  end


  local e = lpeg.Cp()

  local wordid = (R('az', 'AZ') + S'`_-')^1
  local urlchar = 1 - S' \n.!?'

  local md2htmlpatt = Cs((
    P'```cpp\n' * C(Until('\n```')) * '\n```' / blockcode
  + C(P'#'^1) * ' ' * cunl / headerize
  + #P'-' *
    ( #(P'- ' * wordid * ':')
    * ( Cs((P'- ' * C(wordid * (P' ' * wordid)^0) * ': ' * cunl / def_list)^1)
        / wrap_with('<dl>\n', '</dl>\n')
      )
    + ( Cs((P'- ' * cunl / normal_list)^1)
        / wrap_with('<ul>\n', '</ul>\n')
      )
    )
  + P'\n'^1 / ''
  + Cs((
      mdinlinecodepatt
    + '[![' * C(Until']') * 1 * '(' * C(Until')') * 1 * '](' * C(Until')') * 1
      / function(text, img, link)
          return '<a href="' .. link .. '"><img src="' .. img .. '" alt="' .. text .. '"></a>'
        end
    + '[' * C(Until']') * 1 * '(' * C(Until')') * 1
      / function(text, link) return '<a href="' .. link .. '">' .. text .. '</a>' end
    + 'https://' * urlchar^1 * (S'!?.'^1 * urlchar^1)^0
      / function(link) return '<a href="' .. link .. '">' .. link .. '</a>' end
    + (1 - P'\n')
    )^1)
    / wrap_with('<p>', '</p>\n')
  )^0)

  md2html = function(contents)
    headers = {}
    local html = md2htmlpatt:match(contents)
    if html then
      html = '<section id="main">' .. html .. '</section>\n'
    end
    return headers, html
  end

end
end

local stderr = io.stderr
function log(...)
  io.stderr:write(...)
  io.stderr:write('\n')
end

files = {}
files_by_group = {}
groups = {}

function readfile(filename)
  log('read ', filename)
  _global_filename = filename
  local f = io.open(filename)
  local contents = f:read('*a')
  f:close()

  local fileinfos = parseFile(contents)

  if not fileinfos.ingroup then
    if preprocOnlyPattern:match(contents) then
      return
    end
    error('missing \\ingroup in ' .. _global_filename)
  end

  if not fileinfos.firstname then
    if filename:find('/config.hpp', 0, true) then
      return
    end
    error('parser failure for ' .. filename)
  end

  fileinfos.filename = filename:sub(9)
  fileinfos.filerefid = filename:sub(16)
  fileinfos.dirname = fileinfos.filerefid:match'%w+'
  local g = groups[fileinfos.ingroup]
  if not g then
    g = {name=fileinfos.ingroup}
    groups[fileinfos.ingroup] = g
  end
  g[#g+1] = fileinfos
  files[#files+1] = fileinfos
end

for _,filename in ipairs(arg) do
  readfile(filename)
end

do
  function recprint(x, p)
    local ty = type(x)
    if ty == 'table' then
      print()
      local newp = p .. '  '
      for k,v in pairs(x) do
        io.stdout:write(newp, k, ': ')
        recprint(v, newp)
      end
    elseif ty == 'number' then
      print('cat:', kw[x])
    else
      print(x)
    end
  end
  -- recprint(groups, '') os.exit()
  -- recprint(namespaces, '')
  -- recprint(defgroups, '')
end

i_struct = kwindexes.struct
i_using = kwindexes.using
i_static_constexpr = kwindexes.static_constexpr
i_desc = kwindexes.desc
i_see = kwindexes.see
i_treturn = kwindexes.treturn
i_tparam = kwindexes.tparam
i_pre = kwindexes.pre
i_post = kwindexes.post
i_note = kwindexes.note
i_semantics = kwindexes.semantics

htmlifier_init()

function tohtml(namespace, s)
  if s then
    s = s:gsub('[\n ]+', ' ')
    return linkifier(namespace, s)
  end
  return nil
end

local ttypes = {}
local tgroups = {}

for name,g in pairs(groups) do
  tgroups[#tgroups+1] = g

  local short_desc, long_desc, treturn, see, tparams, extra_doc
  local reset_values = function()
    short_desc = nil
    long_desc = nil
    treturn = nil
    see = {}
    tparams = {}
    extra_doc = {
      [i_post]={},
      [i_pre]={},
      [i_note]={},
      [i_semantics]={}
    }
  end
  reset_values()

  local gtypes = {}
  g.types = gtypes

  for _,f in ipairs(g) do

    local types = {}
    f.types = types
    for _,d in ipairs(f) do
      if d[1] == i_see then
        see[#see+1] = d[2]
      elseif d[1] == i_tparam then
        tparams[#tparams+1] = {d[2], htmlify:match(d[3])}
      elseif d[1] == i_treturn then
        treturn = htmlify:match(d[2])
      elseif extra_doc[d[1]] then
        table.insert(extra_doc[d[1]], htmlify:match(d[2]))
      elseif d.i == i_desc then
        short_desc, long_desc = splitShortAndLongDesc:match(htmlify:match(d[1]))
      elseif d.i == i_using or d.i == i_struct or d.i == i_static_constexpr then
        types[#types+1] = d
        if d.namespace == '' then
          ttypes[#ttypes+1] = d
          gtypes[#gtypes+1] = d
        end

        d.cpp_type_html = d.cpp_type and tohtml(d.namespace, d.cpp_type) .. ' ' or ''
        d.long_desc_html = long_desc and #long_desc > 0 and long_desc
        d.short_desc_html = short_desc and #short_desc > 0 and short_desc
        d.treturn = treturn
        d.tparams = tparams
        -- after replacing macros, set_contains_xs_v references itself,
        -- implementation should be ignored
        if d.i ~= i_static_constexpr or d.name ~= 'set_contains_xs_v' then
          d.impl_html = tohtml(d.namespace, d.impl)
          d.inline_impl_html = d.impl and (inlinecode_begin .. d.impl_html .. inlinecode_end)
        end

        if #see ~= 0 then
          for k,x in pairs(see) do
            see[k] = linkifier(d.namespace, x)
          end
          d.see = table.concat(see, ', ')
        end

        for i,extra in pairs(extra_doc) do
          d[kw[i]] = extra
        end

        d.mem_html = d.spe and tohtml(d.namespace, d.spe)
                  or tohtml(d.namespace, d.human_tparams)
                  or ''

        if d.i == i_using then
          d.is_alias = true
        elseif d.mem then
          d.mem_html = d.mem_html .. '<span class="p">::</span>'
                    .. d.mem .. (tohtml(d.namespace, d.human_tparams_mem) or '')
        end

        reset_values()
      end
    end
  end
end

-- os.exit()

htmlfagments = {
  [[<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <link rel="stylesheet" type="text/css" media="all" href="default.css">
  <title>Jln.Mp: A C++17 metaprogramming library - V2</title>
</head>
<body>
]],
}
function push(s)
  htmlfagments[#htmlfagments + 1] = s
end


-- Concept, Glossary and TOC

local f = io.open'README.md'
local headers, html_intro = md2html(f:read('*a'))
f:close()

push'<section><h1>Table of contents<a href="#toc" class="titleref">¶</a></h1><nav id="toc"><ul>'
for _,title in ipairs(headers) do
  push('<li><a href="#' .. title[1] .. '">' .. title[2] .. '</a></li>')
end
push([[
<li><a href="#files_by_group">Files by group</a></li>
<li><a href="#files_in_alphabetical_order">Files in alphabetical order</a></li>
<li><a href="#functions_by_group">Functions by group</a></li>
<li><a href="#functions_in_alphabetical_order">Functions in alphabetical order</a></li>
<li><a href="#short_descriptions">Short descriptions</a></li>
<li><a href="#detailed_descriptions">Detailed descriptions</a></li>
</ul></nav></section>
]])

push'<div class="from_mdfile">'
push(html_intro)
push'</div>\n'


function push_nav_by_group(t, gn, type, h1, prefix, idxname, getsubtable, getlink)
  local id = h1:lower():gsub(' ', '_')
  push('<section id="' .. id .. '">')
  push('<h1 id="' .. id .. '">' .. h1 .. '<a href="#' .. id .. '" class="titleref">¶</a></h1>')
  push('<nav><p>')
  for _,g in ipairs(t) do
    push('<a class="link_group" href="#g' .. gn .. '__'
         .. g[idxname] .. '">' .. g[idxname] .. '</a>')
  end
  push('</p><ul class="index_list ' .. type .. '_list">\n')

  local refid, text
  for _,g in ipairs(t) do
    push('<li id="g' .. gn .. '__' .. g[idxname]
         .. '" class="index_group"><a class="index_cat" href="#g'
         .. gn .. '__' .. g[idxname] .. '">' .. prefix .. g[idxname]
         .. '</a><ul class="subindex_list ' .. type .. '_sublist">\n')

    for _,d in ipairs(getsubtable(g)) do
      refid, text = getlink(d)
      if text then
        push('<li><a href="#' .. refid .. '" class="index_link">' .. text .. '</a></li>\n')
      end
    end

    push('</ul></li>')
  end
  push('</ul></nav></section>\n')
end


-- filename list by group

function comp_by_filerefid(f1, f2)
  return f1.filerefid < f2.filerefid
end

function comp_by_name(f1, f2)
  return f1.name < f2.name
end

table.sort(tgroups, comp_by_name)

push_nav_by_group(
  tgroups, 1, 'file', 'Files by group', 'Group: ', 'name',
  function(g)
    table.sort(g, comp_by_filerefid)
    return g
  end,
  function(d)
    d.fragment_filename = fragmentName:match(d.filename)
    return d.filerefid, d.fragment_filename
  end
)

-- filename list

table.sort(files, comp_by_filerefid)

local files_by_dir = {}
local current_dir
local previous_name
for _,d in ipairs(files) do
  if previous_name ~= d.dirname then
    previous_name = d.dirname
    current_dir = {d}
    files_by_dir[#files_by_dir+1] = {d.dirname, current_dir}
  else
    current_dir[#current_dir+1] = d
  end
end

push_nav_by_group(
  files_by_dir, 2, 'file', 'Files in alphabetical order', 'Directory: ', 1,
  function(g) return g[2] end,
  function(d) return d.filerefid, d.fragment_filename end
)

-- function list by group

push_nav_by_group(
  tgroups, 3, 'func', 'Functions by group', 'Group: ', 'name',
  function(g)
    previous_name = nil
    table.sort(g.types, comp_by_name)
    return g.types
  end,
  function(d)
    if previous_name ~= d.name then
      previous_name = d.name
      return d.refid, d.fullname
    end
  end
)

-- function list

table.sort(ttypes, comp_by_name)

local types_by_letter = {}
local current_letter, previous_letter, first_letter
previous_name = nil
for _,d in ipairs(ttypes) do
  first_letter = d.name:byte()
  if previous_letter ~= first_letter then
    previous_letter = first_letter
    current_letter = {d}
    previous_name = d.name
    types_by_letter[#types_by_letter+1] = {string.char(first_letter):upper(), current_letter}
  elseif previous_name ~= d.name then
    previous_name = d.name
    current_letter[#current_letter+1] = d
  end
end

push_nav_by_group(
  types_by_letter, 4, 'func', 'Functions in alphabetical order', '', 1,
  function(g) return g[2] end,
  function(d) return d.refid, d.fullname end
)

-- short description

function comp_by_firstname(f1, f2)
  return f1.firstname < f2.firstname
end

push('<section>\n')

push('<h1 id="short_descriptions">Short descriptions</h1>')
push('<nav><p>')
for _,g in ipairs(tgroups) do
  push('<a class="link_group" href="#g_' .. g.name .. '">' .. g.name .. '</a>')
end
push('</p></nav>\n')

for _,g in ipairs(tgroups) do
  table.sort(g, comp_by_firstname)
  push('<article>\n')
  push('<h2 id="g_' .. g.name .. '"><a href="#g_' .. g.name .. '" class="ref">¶</a>Group: ' .. g.name .. '</h2>\n')
  push('<table>\n')
  for _,f in ipairs(g) do
    table.sort(f.types, comp_by_name)
    for _,d in ipairs(f.types) do
      if d.namespace ~= 'emp' then
        push('<tr><td>' .. inlinecode_begin .. '<a href="#' .. d.refid .. '">' .. d.fullname
             .. '</a>' .. d.mem_html .. inlinecode_end
             .. '</td><td>' .. ( d.short_desc_html
                               or (d.inline_impl_html and '= ' .. d.inline_impl_html)
                               or '')
             .. '</td></tr>\n')
      end
    end
  end
  push('</table>\n')
  push('</article>\n')
end
push('</section>\n')

-- long description

function push_block(name, s)
  push('<div class="InfoBox"><h4 class="InfoBox-title">' .. name .. '</h4>\n')
  push(s)
  push('</div>')
end

function push_list(name, t)
  if #t ~= 0 then
    push_block(name, '<ul><li>' .. table.concat(t,'</li><li>') .. '</li></ul>')
  end
end

function push_blocks(name, t)
  if #t ~= 0 then
    push_block(name, '<p>' .. table.concat(t,'<br/>') .. '</p>')
  end
end

push('<section>\n')

push('<h1 id="detailed_descriptions">Detailed descriptions</h1>')
push('<nav><p>')
for _,g in ipairs(tgroups) do
  push('<a class="link_group" href="#g6__' .. g.name .. '">' .. g.name .. '</a>')
end
push('</p></nav>\n')

for _,g in ipairs(tgroups) do
  push('<article>\n')
  push('<h2 id="g6__' .. g.name .. '" class="group__title"><a href="#g6__' .. g.name .. '" class="ref">¶</a>Group: ' .. g.name .. '</h2>\n')
  push('<div class="group__content">\n')
  for _,f in ipairs(g) do
    push('<h2 class="file" id="' .. f.filerefid .. '"><a href="#' .. f.filerefid .. '" class="ref">¶</a>&lt;' .. f.filename .. '></h2>')
    push('<div class="group__file">\n')

    local refcache = {}
    local emp = {}

    for _,d in ipairs(f.types) do
      local refid = (refcache[d.refid] and '' or ' id="' .. d.refid .. '"')
      if d.namespace == 'emp' then
        emp[#emp+1] = '<h3 class="emp"' .. refid
            .. '><a href="#' .. d.refid .. '" class="ref">¶</a>'
            .. inlinecode_begin .. d.cpp_type_html
            .. d.fullname:gsub('::', '<span class="p">::</span>')
            .. d.mem_html .. inlinecode_end .. ' = '
            .. (d.inline_impl_html or '/*...*/')
            .. '</h3>\n'
      else
        push('<h3' .. (refcache[d.refid] and '' or ' id="' .. d.refid .. '"') .. '><a href="#'
             .. d.refid .. '" class="ref">¶</a>'
             .. inlinecode_begin .. d.cpp_type_html .. d.fullname
             .. d.mem_html .. inlinecode_end .. '</h3>\n')
        refcache[d.refid] = true

        if d.treturn then push('<p>Return: ' .. d.treturn .. '</p>') end
        if d.short_desc_html then push('<p>' .. d.short_desc_html .. '</p>') end
        if d.long_desc_html then push('<p>' .. d.long_desc_html .. '</p>') end

        if d.tparams and #d.tparams ~= 0 then
          push('<dl>')
          for _, tparam in ipairs(d.tparams) do
            push('<dt><code>' .. tparam[1] .. '</code></dt><dd>' .. tparam[2] .. '</dd>\n')
          end
          push('</dl>\n')
        end

        if d.impl_html then
          push_block('Implementation', blockcode_begin .. d.impl_html .. blockcode_end)
        end
        push_list('Pre-condition', d.pre)
        push_list('Post-condition', d.post)
        push_blocks('Semantics', d.semantics)
        push_blocks('Note', d.note)
        if d.see then push('<aside>See: ' .. d.see .. '</aside>') end
      end
    end

    push('<div class="group__emp">\n')
    push(table.concat(emp))
    push('</div>\n')
    push('</div>\n')

  end
  push('</div>\n')
  push('</article>\n')
end
push('</section>\n')

push('</body></html>')

-- for _,x in ipairs(htmlfagments) do print(x) end
print(table.concat(htmlfagments))
