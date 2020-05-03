#!/usr/bin/env lua

local reset_parser
local preproc
local pattern
local htmlify
local fileinfos
local linkifier
local split_short_and_long_desc
local inlinecode_begin = '<span class="inlinecode highlight"><code class="language-cpp" data-lang="cpp">'
local inlinecode_end = '</code></span>'
local internalref = {}
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

local ctx_tparams
local ctx_namespace
local ctx_ref_namespace

function reset_parser()
  ctx_tparams = nil
  ctx_namespace = ''
  ctx_ref_namespace = ''
  fileinfos = {filename = filename, refs = {}}
end

local f_defgroup = function(name, desc) defgroups[#defgroups+1] = {name, table.concat(desc)} end
local f_ingroup = function(name) fileinfos.ingroup = name end
local f_template = function(params) ctx_tparams = params end

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
      r = r .. ' = ' .. v[5]
    end
    t[#t+1] = r
  end
  return '<' .. table.concat(t, ', ') .. '>'
end

local sanitize_struct_impl

local i_using = kwindexes.using
local f_using = function(name, impl)
  namespaces[ctx_namespace][name] = true
  fileinfos.firstname = fileinfos.firstname or name
  fileinfos[#fileinfos+1] = {
    i = i_using,
    tparams = ctx_tparams,
    human_tparams = ctx_tparams and human_template(ctx_tparams),
    namespace = ctx_namespace,
    name = name,
    refid = torefid(ctx_namespace, name),
    fullname = ctx_ref_namespace .. name,
    impl = sanitize_struct_impl(impl),
  }
  ctx_tparams = nil
end

local i_struct = kwindexes.struct
local f_struct = function(name, spe, tparams, mem, impl)
  namespaces[ctx_namespace][name] = true
  fileinfos.firstname = fileinfos.firstname or name
  fileinfos[#fileinfos+1] = {
    i = i_struct,
    tparams = ctx_tparams,
    human_tparams = ctx_tparams and human_template(ctx_tparams),
    namespace = ctx_namespace,
    name = name,
    refid = torefid(ctx_namespace, name),
    fullname = ctx_ref_namespace .. name,
    impl = sanitize_struct_impl(impl),
    spe = spe and human_template(spe),
    mem = mem,
    humain_tparams_mem = tparams and human_template(tparams),
  }
  ctx_tparams = nil
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
local innerlines = List(C(unl) * sp0, '/// ' * -P'\\')
local lines = Ct(innerlines)
local charid = R('az','09','AZ') + S':_'
local id = charid^1
local cid = C(id)
local balancedtag = P{
  '<' * (1 - S'<>()' + V(1) + V(2))^0 * '>',
  '(' * (1 - S'()' + V(2))^0 * ')',
}
local tparam = Ct(
  (C('template' * balancedtag) + Cc('')) * ws0
  * cid * ws0 * C(P'...'^-1) * ws0 * (cid + Cc(nil)) * ws0
  * ('=' * ws0 * C(id * ws0 * balancedtag^-1))^-1)
local tparams = Ct('<' * List(ws0 * tparam, ',') * '>')
local template = 'template' * ws0 * tparams
-- local template = C('template' * ws0 * balancedtag)

local splitShortAndLongDesc = C(Until('.\n' + -P(1)) * P'.'^-1) * sp0 * C(P(1)^0)
split_short_and_long_desc = function(desc)
  return splitShortAndLongDesc:match(htmlify:match(desc))
end

local sanitize_struct_impl_patt = Cs((
  (P'typename ' + 'template ') / ''
+ 'detail::' * (id * ws0)^1 * (balancedtag * (ws0 * id)^0)^0 * ws0
    / '/* implementation defined */'
+ 1
)^0)

sanitize_struct_impl = function(s)
  if s then
    s = sanitize_struct_impl_patt:match(s)
    if s == '/* implementation defined */' then
      return nil
    end
  end
  return s
end

-- TODO JLN_MP_MAKE_REGULAR_SMP2_P(is_size_of, (N), (C, smp::identity), ...)

local f_ident = function(s) return s end
preproc = P{
  "S";
  S=Cs((V'p' + '#' * unl / '' + 1)^0)

, p='#' * sp0 / '' *
    ( 'ifdef JLN_MP_DOXYGENATING' * C(Until(P'#else' + P'#endif')) * Until'#endif' * 7 / f_ident
    + 'if 0' * Until'#endif' * 7 / ''
    + 'if' * unl * Cs(( V'p'
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

pattern = P{
  "S";
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
    + (template / f_template)^-1 * ws0 *
      ( (P'struct' + 'class') * ws * cid * Until(S':;{<')
        * (':' * ws0 * id * ws0
          * (balancedtag * ws0 * (('::template ' * id * balancedtag + id) * ws0)^0)^-1
          )^-1 *
        ( P';'
        + (tparams + Cc(nil)) * ws0 * '{' * ws0 * (template^-1) * ws0
          * (P'using' + 'class' + 'struct') * ws * cid * ws0 * ('=' * ws0 * C(Until';'))^-1
        + P'{' * ws0 *
          ( '};'
          + 'static const' * P'expr'^-1 * ws0
            * id * ('(' * Until')' * 1)^-1 * ws0 * Cc(nil) * Cc(nil) * C(Until(P' =' + '='))
          )
        ) / f_struct
      + 'using ' * cid * ws0 * '=' * ws0 * C(Until';') / f_using
      )
    + 'namespace ' *
      ( C('emp') * '\n' / f_emp_namespace * ws0 * '{' * (V('e') + (1 - S'{}'))^0
        * (P'}' / f_restore_namespace)
      + ws0 * ('jln::mp' * P'::'^-1)^-1 * (cid + Cc('')) / f_namespace
      )
    + '//' * Until'\n' * 1
    -- + '/*' * Until'*/' * 2
  ,
  S=(V('e') + 1)^1
}

local htmlspecialchars_c = P'<' / '&lt;' + P'&' / '&amp;'
local htmlspecialchars = Cs((htmlspecialchars_c + 1)^0)

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

local tokid = R('az','AZ','09') + S'_'
local highlighting_kw = (
  (P'template' + 'class' + 'struct' + 'using' + 'typename' + 'decltype' + 'sizeof' + 'auto')
    / mk_tag'k'
+ (P'void' + 'int' + 'unsigned' + 'long' + 'char' + 'short') / mk_tag'kt'
+ (P'true' + 'false') / mk_tag'nb'
) * -#tokid
local highlighting_symbol
= S'{}()[]:;,.'^1 / mk_tag'p'
+ S'<>:+-/%*=&|'^1 / mk_tag_specialchar'o'
+ R'09'^1 / mk_tag'mi'

local highlighting = Cs((highlighting_kw + highlighting_symbol + tokid^1 + 1)^0)

local inlinecode = function(s)
  return inlinecode_begin .. linkifier('', s) .. inlinecode_end
end

local blockcode = function(s)
  return '<div class="highlight"><pre class="chroma"><code class="language-cpp" data-lang="cpp">'
      .. linkifier('', s) .. '</code></pre></div>'
end

htmlify = Cs((
  P'\\c ' / '' * (Until(S' \n' + '.\n') / inlinecode)
+ P'`' * C(Until'`') * '`' / inlinecode
+ P'\\code' * C(Until'\\endcode') * '\\endcode' / blockcode
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

  local hi = Cs((P'::' / mk_tag'p' + 1)^1)

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

  local current_table

  local linkify = function(s)
    return current_table[s] or global_table[s] or s
  end

  local patt = Cs(
    ( highlighting_kw
    + R'az' * (R('az','09','AZ') + S':_')^1 / linkify
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
groups = {}

function readfile(filename)
  reset_parser()
  local f = io.open(filename)
  local contents = f:read('*a')
  local t
  f:close()
  if pattern:match(preproc:match(contents)) then
    if not fileinfos.firstname then
      print('parser failure for ' .. filename)
      os.exit(1)
    end
    fileinfos.filename = filename
    local g = groups[fileinfos.ingroup]
    if not g then
      g = {}
      groups[fileinfos.ingroup] = g
    end
    g[#g+1] = fileinfos
    files[#files+1] = {fileinfos}
  end
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
  -- recprint(groups, '')
  -- recprint(namespaces, '')
  -- recprint(defgroups, '')
  -- recprint(internalref, '')
end

function comp_by_firstname(f1, f2)
  return f1.firstname < f2.firstname
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

for name,g in pairs(groups) do
  table.sort(g, comp_by_firstname)

  for _,f in ipairs(g) do
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
        short_desc, long_desc = split_short_and_long_desc(d[1])
      elseif d.i == i_using or d.i == i_struct then
        types[#types+1] = d

        d.human_tparams_html = tohtml(d.namespace, d.human_tparams) or ''
        d.struct_decl_mem_html = ''
        d.long_desc_html = long_desc
        d.short_desc_html = short_desc
        d.tparams = tparams

        if #see ~= 0 then
          for k,x in pairs(see) do
            see[k] = linkifier(d.namespace, x)
          end
          d.see = table.concat(see, ', ')
        end

        for i,extra in pairs(extra_doc) do
          d[kw[i]] = extra
        end

        if d.i == i_using then
          d.impl_html = short_desc
                    or (d.impl and (inlinecode_begin .. tohtml(d.namespace, d.impl)
                                    .. inlinecode_end))
        elseif d.mem then
          d.short_desc_html = short_desc
          d.struct_decl_mem_html = (tohtml(d.namespace, d.spe) or '') .. '::'
                             .. d.mem .. (tohtml(d.namespace, d.humain_tparams_mem) or '')
          if d.impl then
            d.struct_mem_impl_html = inlinecode_begin .. tohtml(d.namespace, d.impl) .. inlinecode_end
          end
        end

        reset_values()
      end
    end
  end
end


htmlfagments = {
  '<!DOCTYPE html><html><head><meta charset="utf-8"/><link rel="stylesheet" type="text/css" media="all" href="default.css"></head><body>\n',
}
function push(s)
  htmlfagments[#htmlfagments + 1] = s
end

push('<nav>\n')
push('<ul>\n')
for name in pairs(groups) do
  push('<li>' .. name .. '</li>\n')
end
push('</ul>\n')
push('</nav>\n')

-- short description

push('<section>\n')
for name,g in pairs(groups) do
  push('<article class="post">\n')
  push('<h1>Group: ' .. name .. '</h1>\n')
  push('<table>\n')
  for _,f in ipairs(g) do
    for _,d in ipairs(f.types) do
      if d.namespace ~= 'emp' then
        push('<tr><td>' .. inlinecode_begin .. '<a href="#' .. d.refid .. '">' .. d.fullname
             .. '</a>' .. d.human_tparams_html .. d.struct_decl_mem_html .. inlinecode_end
             .. '</td><td>' .. ( (d.impl_html and '= ' .. d.impl_html)
                               or d.short_desc_html
                               or (d.struct_mem_impl_html and '= ' .. d.struct_mem_impl_html)
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
  push('<div class="InfoBox"><p><strong class="InfoBox-title">' .. name .. ':</strong> ')
  push(s)
  push('</p></div>')
end

function push_blocks(name, t)
  if #t ~= 0 then
    push_block(name, table.concat(t,'<br/>'))
  end
end

push('<section>\n')
for name,g in pairs(groups) do
  push('<article class="post">\n')
  push('<h1 class="post__title">group: ' .. name .. '</h1>\n')
  push('<div class="post__content">\n')
  for _,f in ipairs(g) do
    local dgroup = {{}}
    local empgroup = {}
    for k,d in ipairs(f.types) do
      if d.namespace == 'emp' then
        empgroup[#empgroup+1] = d
      elseif k ~= 1 and (d.short_desc_html or d.long_desc_html) then
        dgroup[#dgroup+1] = {d}
      else
        table.insert(dgroup[#dgroup], d)
      end
    end

    push('<h2 class="file">&lt;' .. f.filename:sub(9) .. '></h2>')

    local refcache = {}

    for _,dg in ipairs(dgroup) do
      for _,d in ipairs(dg) do
        push('<h3 id="' .. (refcache[d.refid] and '' or d.refid) .. '"><a href="#'
             .. d.refid .. '" class="ref">¶</a>'
             .. inlinecode_begin .. d.fullname .. d.human_tparams_html
             .. d.struct_decl_mem_html .. inlinecode_end .. '</h3>\n')
        refcache[d.refid] = true
      end

      local d = dg[1]
      if not d then
        break
      end

      if d.short_desc_html or d.long_desc_html then
        if d.short_desc_html then push('<p>' .. d.short_desc_html .. '</p>') end
        if d.long_desc_html then push('<p>' .. d.long_desc_html .. '</p>') end
        lastcomment = d
      elseif d.impl_html then
        push('<p>Alias for ' .. d.impl_html .. '</p>')
      end

      if d.tparams then
        push('<dl>')
        for _, tparam in ipairs(d.tparams) do
          push('<dt><code>' .. tparam[1] .. '</code></dt><dd>' .. tparam[2] .. '</dd>')
        end
        push('</dl>')
      end
      if d.impl_html or d.struct_mem_impl_html then
        push_block('Implementation', d.impl_html or d.struct_mem_impl_html)
      end
      push_blocks('Pre-condition', d.pre)
      push_blocks('Post-condition', d.post)
      push_blocks('Semantics', d.semantics)
      push_blocks('Note', d.note)
      if d.see then push('<aside>See: ' .. d.see .. '</aside>') end
    end

    for _,d in ipairs(empgroup) do
      push('<p id="' .. d.refid .. '"><a href="#' .. d.refid .. '" class="ref">¶</a>'
           .. inlinecode_begin .. d.fullname .. d.human_tparams_html
           .. d.struct_decl_mem_html .. inlinecode_end .. ' = '
           .. inlinecode_begin .. (d.impl_html or '/* implementation defined */')
           .. inlinecode_end .. '</p>\n')
    end

  end
  push('</div>\n')
  push('</article>\n')
end
push('</section>\n')

push('</body></html>')

-- for _,x in ipairs(htmlfagments) do print(x) end
print(table.concat(htmlfagments))
