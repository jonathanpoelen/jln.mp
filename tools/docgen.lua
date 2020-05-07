#!/usr/bin/env lua

local parseFile
local htmlify
local linkifier
local splitShortAndLongDesc
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
  fileinfos[#fileinfos+1] = {i = i_desc, table.concat(lines)}
end

function human_template(tparams)
  if not tparams then
    return nil
  end

  local t = {}
  local r
  -- 1: template<...>
  -- 2: class or type
  -- 3: '...' or ''
  -- 4: name
  -- 5: = value
  for k,v in ipairs(tparams) do
    if v[2] == 'class' then
      r = v[1] .. (v[4] or '_') .. v[3]
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

local f_type = function(ctx_tparams, k, name, spe, tparams, mem, impl)
  namespaces[ctx_namespace][name] = true
  fileinfos.firstname = fileinfos.firstname or name
  fileinfos[#fileinfos+1] = {
    i = k,
    human_tparams = human_template(ctx_tparams),
    namespace = ctx_namespace,
    name = name,
    refid = torefid(ctx_namespace, name),
    fullname = ctx_ref_namespace .. name,
    impl = sanitize_struct_impl(impl),
    spe = spe,
    mem = mem,
    humain_tparams_mem = human_template(tparams),
  }
end

local i_namespace = kwindexes.namespace
local f_namespace = function(name)
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
local AfterS = function(p) return Until(p) * #p end
local List = function(p, sep) p = P(p) return p * (sep * p)^0 end
local sp = P' '^1
local sp0 = P' '^0
local ws = S' \n'^1
local ws0 = S' \n'^0
local unl = Until'\n' * 1
local cunl = C(Until'\n') * 1
local charid = R('az','09','AZ') + S':_'
local id = charid^1
local cid = C(id)
local balancedparent = P{
  '(' * (1 - S'()' + V(1))^0 * ')',
}
local balancedtag = P{
  '<' * (1 - S'<>()' + V(1) + V(2))^0 * '>',
  '(' * (1 - S'()' + V(2))^0 * ')',
}

splitShortAndLongDesc = C(Until('.\n' + -P(1)) * P'.'^-1) * sp0 * C(P(1)^0)

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
+ 'detail::' * (id * ws0)^1 * (balancedtag * (ws0 * id)^0 * ws0)^0 * balancedparent^0 * ws0
    / '/* implementation defined */'
+ 1
)^0)

sanitize_struct_impl = function(s)
  if s then
    s = sanitize_struct_impl_patt:match(s)
    if s == '/* implementation defined */' then
      return nil
    end
    s = sanitize_space:match(s)
  end
  return s
end

local f_ident = function(s) return s end
local preproc = P{
  "S";
  S=Cs(
  ( V'p'
  + '#' * unl / ''
  + V'c'
  + 1
  )^0)

, c=P'JLN_MP_DCALL_XS(' * id * ',' * ws0 * cid * ',' * ws0
      * C((1-S'()' + balancedparent)^1) * ')'
      / function(f, args) return f .. '<' .. args .. '>' end

, p='#' * sp0 / '' *
    ( 'ifdef JLN_MP_DOXYGENATING'
      * Cs((1 - (P'#else' + P'#endif') + V'c')^0) * Until'#endif' * 7 / f_ident
    + 'if 0' * Until'#endif' * 7 / ''
    + 'if' * unl * Cs(( V'p'
                      + V'c'
                      + (1 - P'#')
                      + '#' * sp0 * -#(P'end' + 'el') * unl / ''
                      )^1)
      * '#' * sp0 * ('el' * unl * V'endif' + unl) / f_ident
    + 'define ' * List(Until(S'\n\\'), P'\\' * 1) * 1 / ''
    )
  + '/// \\cond' * Until'\\endcond' * 9 / ''
  + '/*' * Until'*/' * 2 / ''

, ['endif']=Until('#' * sp0 * (P'endif' + 'if'))
    * ('#' * sp0 * ('if' * unl * V'endif' + 'endif'))
}

local lines = Ct(List(C(unl) * sp0, '///' * P' '^-1 * -P'\\'))
local tparam = Ct(
  (C('template' * balancedtag) + Cc('')) * ws0
  * cid * ws0 * C(P'...'^-1) * ws0 * (cid + Cc(nil)) * ws0
  * ('=' * ws0 * C(id * ws0 * balancedtag^-1))^-1)
local tparams = Ct('<' * List(ws0 * tparam, ',') * '>')
local template = 'template' * ws0 * tparams
-- local template = C('template' * ws0 * balancedtag)

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
      * ( (P'struct' + 'class') * ws * Cc(kwindexes.struct) * cid * Until(S':;{<')
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
                    * ('(' * Until')' * 1)^-1 * ws0 * Cc(nil) * Cc(nil)
                    * C(Until(P' =' + '=')) * P' '^-1 * '=' * ws0 * C(Until';')
                  )
                )
            )
        + 'using ' * Cc(kwindexes.using) * cid * ws0 * '='
          * ws0 * Cc(nil) * Cc(nil) * Cc(nil) * C(Until';')
        ) / f_type
    + 'namespace ' *
      ( C('emp') * '\n' / f_emp_namespace * ws0 * '{' * (V('e') + (1 - S'{}'))^0
        * (P'}' / f_restore_namespace)
      + ws0 * ('jln::mp' * P'::'^-1)^-1 * (cid + Cc('')) / f_namespace
      )
    + '//' * Until'\n' * 1
    -- + '/*' * Until'*/' * 2
}

parseFile = function(contents)
  reset_parser()
  pattern:match(preproc:match(contents))
  return fileinfos
end

local htmlspecialchars_c = P'<' / '&lt;' + P'&' / '&amp;'
local htmlspecialchars = Cs((htmlspecialchars_c + 1)^0)

local inlinecode = function(s)
  return inlinecode_begin .. linkifier('', s) .. inlinecode_end
end

local blockcode = function(s)
  return blockcode_begin .. linkifier('', s) .. blockcode_end
end

htmlify = Cs((
  P'\\c ' / '' * (Until(S' \n' + '.\n') / inlinecode)
+ P'`' * C(Until'`') * '`' / inlinecode
+ P'\\code' * ws0 * C(Until(ws0 * '\\endcode')) * ws0 * '\\endcode' / blockcode
+ P'\\ints' / '<a href="#g_ints">ints</a>'
+ (P'\\int_' + '\\int') / '<a href="#g_int">int_</a>'
+ P'\\list' / '<a href="#g_list">list</a>'
+ P'\\number' / '<a href="#g_number">number</a>'
+ P'\\sequence' / '<a href="#g_sequence">sequence</a>'
+ P'\\value' / '<a href="#g_value">value</a>'
+ P'\\val' / '<a href="#g_val">val</a>'
+ P'\\bool' / '<a href="#g_bool">boolean</a>'
+ P'\\typelist' / '<a href="#g_typelist">typelist</a>'
+ P'\\function' / '<a href="#g_function">function</a>'
+ P'\\metafunction' / '<a href="#g_metafunction">meta-function</a>'
+ P'\\lazymetafunction' / '<a href="#g_lazymetafunction">lazy meta-function</a>'
+ htmlspecialchars_c
+ 1
)^0)

linkifier_init = function()
  local links_by_namespace = {['']={}}
  local global_table = {}

  local mk_tag = function(tag)
    local span = '<span class="'..tag..'">'
    return function(s)
      return span .. s .. '</span>'
    end
  end

  local mk_tag_specialchar = function(tag)
    local span = '<span class="'..tag..'">'
    return function(s)
      return span .. htmlspecialchars:match(s) .. '</span>'
    end
  end

  local toHiSymbol = mk_tag'p'

  local hi = Cs((P'::' / toHiSymbol + 1)^1)

  for namespace, t in pairs(namespaces) do
    if #namespace == 0 then
      for name in pairs(t) do
        global_table[name] = '<a href="#mp::' .. name .. '">' .. name .. '</a>'
      end
    else
      local link_table = {}
      links_by_namespace[namespace] = link_table

      local prefix = namespace .. '::'
      local hiprefix = hi:match(prefix)

      for name in pairs(t) do
        local codename = prefix .. name
        global_table[codename] = '<a href="#' .. codename .. '">' .. hiprefix .. name .. '</a>'
        link_table[name] = '<a href="#' .. codename .. '">' .. name .. '</a>'
      end
    end
  end

  local tokid = R('az','AZ','09') + S'_'

  local highlighting_symbol
  = S'{}()[]:;,.'^1 / toHiSymbol
  + S'<>:+-/%*=&|'^1 / mk_tag_specialchar'o'
  + R'09'^1 / mk_tag'mi'

  local current_table
  local patt = Cs(
    ( ( ( P'template' + 'class' + 'struct' + 'using'
        + 'typename' + 'decltype' + 'sizeof' + 'auto'
        ) / mk_tag'k'
      + (P'void' + 'int' + 'unsigned' + 'long' + 'char' + 'short') / mk_tag'kt'
      + (P'true' + 'false') / mk_tag'nb'
      ) * -#tokid
    + R'az' * charid^1 / function(s)
        return current_table[s] or global_table[s] or s
      end
    + highlighting_symbol
    + tokid^1
    + 1
    )^0
  )

  linkifier = function(namespace, s)
    current_table = links_by_namespace[namespace]
    return patt:match(s)
  end
end
end

files = {}
files_by_group = {}
groups = {}

function readfile(filename)
  local f = io.open(filename)
  local contents = f:read('*a')
  f:close()

  local fileinfos = parseFile(contents)
  if not fileinfos.firstname then
    print('parser failure for ' .. filename)
    os.exit(1)
  end

  fileinfos.filename = filename:sub(9)
  fileinfos.filerefid = filename:sub(16)
  local g = groups[fileinfos.ingroup]
  if not g then
    g = {}
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
i_desc = kwindexes.desc
i_see = kwindexes.see
i_tparam = kwindexes.tparam
i_pre = kwindexes.pre
i_post = kwindexes.post
i_note = kwindexes.note
i_semantics = kwindexes.semantics

linkifier_init()

function tohtml(namespace, s)
  if s then
    s = s:gsub('[\n ]+', ' ')
    return linkifier(namespace, s)
  end
  return nil
end

local types = {}

for name,g in pairs(groups) do
  local short_desc, long_desc, see, tparams, extra_doc
  local reset_values = function()
    short_desc = nil
    long_desc = nil
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
      elseif extra_doc[d[1]] then
        table.insert(extra_doc[d[1]], htmlify:match(d[2]))
      elseif d.i == i_desc then
        short_desc, long_desc = splitShortAndLongDesc:match(htmlify:match(d[1]))
      elseif d.i == i_using or d.i == i_struct then
        types[#types+1] = d
        if d.namespace == '' then
          gtypes[#gtypes+1] = d
        end

        d.human_tparams_html = tohtml(d.namespace, d.human_tparams) or ''
        d.long_desc_html = long_desc
        d.short_desc_html = short_desc
        d.tparams = tparams
        d.impl_html = tohtml(d.namespace, d.impl)
        d.inline_impl_html = d.impl and (inlinecode_begin .. d.impl_html .. inlinecode_end)

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
                  or tohtml(d.namespace, d.human_tparams) or ''

        if d.i == i_using then
          d.is_alias = true
        elseif d.mem then
          d.mem_html = d.mem_html .. '::'
                    .. d.mem .. (tohtml(d.namespace, d.humain_tparams_mem) or '')
        end

        reset_values()
      end
    end
  end
end

-- os.exit()

htmlfagments = {
  '<!DOCTYPE html><html><head><meta charset="utf-8"/><link rel="stylesheet" type="text/css" media="all" href="default.css"></head><body>\n',
}
function push(s)
  htmlfagments[#htmlfagments + 1] = s
end

-- group list

push('<nav>\n')
push('<ul>\n')
for name in pairs(groups) do
  push('<li>' .. name .. '</li>\n')
end
push('</ul>\n')
push('</nav>\n')

-- filename list by group

function comp_by_filerefid(f1, f2)
  return f1.filerefid < f2.filerefid
end

function show_file_list(files)
  for _,d in ipairs(files) do
    push('<li><a href="#' .. d.filerefid .. '">' .. d.filename .. '</a></li>\n')
  end
end

push('<nav>\n')
push('<ul class="index_list">\n')
for name,g in pairs(groups) do
  table.sort(g, comp_by_filerefid)
  push('<li>Group: ' .. name .. '</li>\n')
  show_file_list(g)
end
push('</ul>\n')
push('</nav>\n')

-- filename list

push('<nav>\n')
push('<ul class="index_list">\n')
table.sort(files, comp_by_filerefid)
show_file_list(files)
push('</ul>\n')
push('</nav>\n')

-- function list by group

function comp_by_name(f1, f2)
  return f1.name < f2.name
end

function show_function_list(files)
  for _,d in ipairs(files) do
    push('<li><a href="#' .. d.refid .. '">' .. d.fullname .. '</a></li>\n')
  end
end

push('<nav>\n')
push('<ul class="index_list">\n')
for name,g in pairs(groups) do
  table.sort(g.types, comp_by_name)
  push('<li>Group: ' .. name .. '</li>\n')
  show_function_list(g.types)
end
push('</ul>\n')
push('</nav>\n')

-- function list

push('<nav>\n')
push('<ul class="index_list">\n')
table.sort(types, comp_by_name)
show_function_list(types)
push('</ul>\n')
push('</nav>\n')

-- group definition

push('<dl>\n')
table.sort(defgroups, function(a, b) return a[1] < b[1] end)
for _,def in ipairs(defgroups) do
  push('<dt>' .. def[1] .. '</dt>\n')
  push('<dd>' .. def[2] .. '</dd>\n')
end
push('</dl>\n')

-- short description

function comp_by_firstname(f1, f2)
  return f1.firstname < f2.firstname
end

push('<section>\n')
for name,g in pairs(groups) do
  table.sort(g, comp_by_firstname)
  push('<article class="group">\n')
  push('<h1>Group: ' .. name .. '</h1>\n')
  push('<table>\n')
  for _,f in ipairs(g) do
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
  push('<div class="InfoBox"><p><h4 class="InfoBox-title">' .. name .. '</h4>\n')
  push(s)
  push('</p></div>')
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
for name,g in pairs(groups) do
  push('<article class="group">\n')
  push('<h1 class="group__title">Group: ' .. name .. '</h1>\n')
  push('<div class="group__content">\n')
  for _,f in ipairs(g) do
    push('<h2 class="file" id="' .. f.filerefid .. '">&lt;' .. f.filename .. '></h2>')
    push('<div class="group__file">\n')

    local refcache = {}
    local emp = {}

    for _,d in ipairs(f.types) do
      local refid = (refcache[d.refid] and '' or ' id="' .. d.refid .. '"')
      if d.namespace == 'emp' then
        emp[#emp+1] = '<h3 class="emp"' .. refid
            .. '><a href="#' .. d.refid .. '" class="ref">¶</a>'
            .. inlinecode_begin .. d.fullname .. d.mem_html .. inlinecode_end .. ' = '
            .. (d.inline_impl_html or '/* implementation defined */')
            .. '</h3>\n'
      else
        push('<h3' .. (refcache[d.refid] and '' or ' id="' .. d.refid .. '"') .. '><a href="#'
             .. d.refid .. '" class="ref">¶</a>'
             .. inlinecode_begin .. d.fullname .. d.mem_html .. inlinecode_end .. '</h3>\n')
        refcache[d.refid] = true

        if d.short_desc_html then push('<p>' .. d.short_desc_html .. '</p>') end
        if d.long_desc_html then push('<p>' .. d.long_desc_html .. '</p>') end

        if d.tparams then
          push('<dl>')
          for _, tparam in ipairs(d.tparams) do
            push('<dt><code>' .. tparam[1] .. '</code></dt><dd>' .. tparam[2] .. '</dd>')
          end
          push('</dl>')
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
