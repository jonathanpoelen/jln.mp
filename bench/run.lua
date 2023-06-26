#!/usr/bin/env lua

bench_file = 'bench/stl_traits.cpp'

f = io.open(bench_file)
bench_file_contents = f:read'a'
f:close()

-- {[algoname] = {'ST'|'SV'|'SVT', {subbench...}}, [N]=algoname}
algos = {
  ['NONE']={'0', {}}, 'NONE',
  ['ALL']={'SVT', {}}, 'ALL',
}

-- extract first, second and last parameter
-- format: BENCH(ST, invoke_result, (int(*)(T), T), FN)
for bench_line in bench_file_contents:gmatch'\nBENCH%(([^\n]+)' do
  parts = {}
  for part in bench_line:gmatch' *([^\n,]+)' do
    table.insert(parts, part)
  end
  algoname = parts[2]
  algodef = algos[algoname]
  -- remove end parenthesis
  subbench = parts[#parts]:sub(1,-2)
  -- algo with multiple subbench
  if algodef then
    table.insert(algodef[2], subbench)
  else
    table.insert(algos, algoname)
    algos[algoname] = {parts[1], subbench ~= '0' and {subbench} or {}}
  end
end

std_versions_table = {
  ['17'] = true, ['c++17'] = true, ['cpp17'] = true,
  ['20'] = true, ['c++20'] = true, ['cpp20'] = true,
  -- ['23'] = true, ['c++23'] = true, ['cpp23'] = true,
  ['2b'] = true, ['c++2b'] = true, ['cpp2b'] = true,
  -- ['26'] = true, ['c++26'] = true, ['cpp26'] = true,
  -- ['2c'] = true, ['c++2c'] = true, ['cpp2c'] = true,
}

default_colors = {'\x1b[m', '\x1b[37m', '\x1b[34m', '\x1b[35m', }
default_nocolors = {'',     '',         '',          '', }

compile_options = ' -fsyntax-only -I include bench/stl_traits.cpp'
show_source = false
show_all_times = true
full = false
noexe = false
timeonly = false
namedonly = false
multibench = false
novariant = false
colors = default_colors

bench_types = {}
compilers = {}
namespaces = {}
stdlibs = {}
builtins = {}
cppversions = {}
bench_algonames = {}

for opti=1,#arg do
  opt = arg[opti]
  algodef = algos[opt]

  if algos[opt] then
    table.insert(bench_algonames, opt)

  elseif opt == 'all' then
    for _, algoname in ipairs(algos) do
      table.insert(bench_algonames, algoname)
    end

  elseif opt == 'tt' or opt == 'time' or opt == 'nomem' then
    timeonly = true

  elseif opt == 'm' or opt == 'multi' or opt == 'multibench' then
    multibench = true

  elseif opt == 'novar' or opt == 'novariant' then
    novariant = true

  elseif opt:sub(1,1) == '-' then
    compile_options = compile_options .. ' ' .. opt

  elseif opt == 'l' or opt == 'list' then
    for _, algoname in ipairs(algos) do
      algodef = algos[algoname]
      print(colors[3] .. algoname .. colors[1] ..
            '\n  ' .. colors[4] .. 'mode: ' .. algodef[1] .. colors[1])
      if #algodef[2] ~= 0 then
        print('  subbench: ' .. table.concat(algodef[2], '\n  subbench: '))
      end
    end
    os.exit(0)

  elseif opt == 'nm' or opt == 'name' or opt == 'names' then
    namedonly = true

  elseif opt == 'n' or opt == 'noexe' then
    noexe = true

  elseif opt == 'nocol' or opt == 'nocolor' then
    colors = default_nocolors
  elseif opt == 'col' or opt == 'color' then
    colors = default_colors

  elseif opt == 'times' then
    show_all_times = true
  elseif opt == 'nt' or opt == 'notimes' then
    show_all_times = false

  elseif opt == 'full' then
    full = true

  elseif opt == 'source' then
    show_source = true

  elseif opt == 'builtin' or opt == 'intrinsic' then
    table.insert(builtins, 1)
  elseif opt == 'nobuiltin' or opt == 'no_builtin'
      or opt == 'nointrinsic' or opt == 'no_intrinsic' then
    table.insert(builtins, 0)

  elseif opt == 'gcc' or opt == 'g++' then
    table.insert(compilers, 'g++')
  elseif opt == 'clang' or opt == 'clang++' then
    table.insert(compilers, 'clang++')

  elseif std_versions_table[opt] then
    table.insert(cppversions, opt:sub(-2))

  elseif opt == 'std' or opt == 'jln' then
    table.insert(namespaces, opt)

  elseif opt == 'libcpp' or opt == 'libc++'
      or opt == 'lcpp' or opt == 'lc++' then
    table.insert(stdlibs, 'libc++')
  elseif opt == 'libstdcpp' or opt == 'libstdc++'
      or opt == 'lstdcpp' or opt == 'lstdc++' then
    table.insert(stdlibs, 'libstdc++')

  elseif opt == 'b' or opt == 'baseline'
      or opt == 's' or opt == 'struct'
      or opt == 'v' or opt == 'value'
      or opt == 't' or opt == 'type' then
    table.insert(bench_types, opt:sub(1,1):upper())
  elseif opt == 'st' or opt == 'sv' or opt == 'svt' then
    table.insert(bench_types, opt:upper())

  else
    io.stderr:write('Unknown "' .. opt .. '" options\n')
    os.exit(1)
  end
end

runsep = not namedonly and (not noexe or show_source) and '-----\n'

bench_type_compiler_option_table = {
  ['0']= ' -DBENCH_TYPE=0  ',
  SVT=   ' -DBENCH_TYPE=SVT',
  SV=    ' -DBENCH_TYPE=SV ',
  ST=    ' -DBENCH_TYPE=ST ',
  S=     ' -DBENCH_TYPE=S  ',
  V=     ' -DBENCH_TYPE=V  ',
  T=     ' -DBENCH_TYPE=T  ',
  B=     ' -DBENCH_TYPE=B  ',
}

if not full and #bench_algonames == 0 then
  bench_algonames = {'ALL'}
  if #bench_types == 0 then bench_types = {'SVT'} end
  if #builtins == 0 then builtins = {'1'} end
end

if #compilers == 0 then compilers = {'g++', 'clang++'} end
if #namespaces == 0 then namespaces = {'std', 'jln'} end
if #stdlibs == 0 then stdlibs = {'libstdc++', 'libc++'} end
if #builtins == 0 then builtins = {'0', '1'} end
if #cppversions == 0 then cppversions = {'17', '20'} end

function make_bench_options(algoname, subbenchs)
  if novariant then
    return {''}
  end

  local subbenchs_opts = {}
  for _, subbench in ipairs(subbenchs) do
    table.insert(subbenchs_opts, ' -DBENCH_' .. algoname .. '_DISABLE_' .. subbench .. '=1')
  end

  if #subbenchs_opts == 0 then
    return {''}
  elseif #subbenchs_opts == 2 then
    return {
      '',
      subbenchs_opts[1],
      subbenchs_opts[2],
    }
  elseif #subbenchs_opts == 3 then
    return {
      '',
      subbenchs_opts[1],
      subbenchs_opts[2],
      subbenchs_opts[3],
      subbenchs_opts[1] .. subbenchs_opts[2],
      subbenchs_opts[1] .. subbenchs_opts[3],
      subbenchs_opts[2] .. subbenchs_opts[3],
    }
  else
    io.stderr:write('oops, script to correct (value is ' .. #subbenchs_opts .. ')')
    os.exit(2)
  end
end

function execute_or_exit(cmd)
  local f = io.popen(cmd)
  local contents = f:read('a')
  local status, exit_or_signal, code = f:close()
  if not status then
    io.stderr:write('Failed: ' .. cmd .. '\nWith ' .. exit_or_signal .. ' code ' .. tostring(code) .. '\n')
    os.exit(3)
  end
  return contents
end

if show_all_times and not namedonly then
  function print_for_time(s)
    io.stdout:write(s)
  end
else
  function print_for_time(s)
  end
end

source_cache = {}

timecmd = timeonly and "" or (namedonly and "/usr/bin/time --format='%M' "
                                         or "/usr/bin/time --format='%MK' " )
timesuffix = timeonly and '' or (namedonly and ',' or 's - ')

if not noexe then
  posix = require'posix'
  clock_gettime = posix.clock_gettime
  CLOCK_MONOTONIC = posix.CLOCK_MONOTONIC
end

function compile(id_elems, cmd)
  if not namedonly then print(colors[2] .. '# ' .. cmd .. colors[1]) end

  if show_source then
    local cacheid = cmd:gsub(' %-DJLN_MP_USE_OPTIONAL_BUILTIN=.', '', 1)
    if cacheid:find('-DBENCH_STD=0', 50, true) then
      cacheid = cacheid:gsub(' %-std=c%+%+..', '', 1)
    end

    local contents = source_cache[cacheid]
    if not contents then
      contents = execute_or_exit(cmd .. ' -Wno-unused-command-line-argument -DBENCH_SHOW_SOURCE=1 -E')
      source_cache[cacheid] = contents
    end

    local lines = {}
    for expr in contents:gmatch('PRINT ([^;]+)') do
      table.insert(lines, expr)
    end
    print(colors[3] .. table.concat(lines, '\n') .. colors[1])
  end

  if noexe then
    if namedonly then
      print(table.concat(id_elems, ','))
    end
    return
  end

  local lines = {}
  cmd = timecmd .. cmd .. " -DJLN_MP_NO_STL_TRAIT=1 -fdiagnostics-color=always 2>&1"

  print_for_time(colors[2] .. '( ')
  for i=0,5 do
    local sec1, ns1 = clock_gettime(CLOCK_MONOTONIC)
    local line = execute_or_exit(cmd)
    local sec2, ns2 = clock_gettime(CLOCK_MONOTONIC)

    -- output too long. Assume this is a compilation error
    if #line > 100 then
      io.stderr:write(line)
      os.exit(3)
    end

    local ms = ((sec2 - sec1) * 1000000000 + (ns2 - ns1)) // 1000000
    line = string.format('%02d.%03d%s%s', ms // 1000, ms % 1000, timesuffix, line:sub(1,-2))
    print_for_time(line .. '  |  ')
    table.insert(lines, line)
  end
  print_for_time(')\n' .. colors[1])

  -- get the median time
  table.sort(lines)
  if namedonly then
    print(table.concat(id_elems, ',') .. ',' .. lines[3])
  else
    print(lines[3])
  end
end

function matrix_compile(algoname, subbenchs_opts, bench_opt)
  local id_elems = {}
  for _, compiler in ipairs(compilers) do
    id_elems[2] = compiler
    local compilercmd = compiler == 'g++' and 'g++    ' or compiler
    for _, stdlib in ipairs(stdlibs) do
      if compiler == 'g++' then
        -- -stdlib may not be supported by gcc, skip compiling with libc++
        if stdlib ~= 'libstdc++' then
          break
        end
        id_elems[3] = stdlib
        stdlib = #compilers > 1 and '                  ' or ''
      else -- clang
        id_elems[3] = stdlib
        stdlib=' -stdlib=' .. stdlib .. (stdlib == 'libc++' and '   ' or '')
      end

      for _, bench_type in ipairs(bench_types) do
        id_elems[4] = bench_type
        for _, subbenchs_opt in ipairs(subbenchs_opts) do
          id_elems[1] = algoname .. subbenchs_opt
          for _, namespace in ipairs(namespaces) do
            id_elems[5] = namespace
            local dnamespace = namespace == 'std'
              and ' -DBENCH_STD=1'
              or ' -DBENCH_STD=0'
            for _, cppversion in ipairs(cppversions) do
              id_elems[6] = cppversion
              for _, builtin in ipairs(builtins) do
                id_elems[7] = 'builtin=' .. builtin
                local dbuiltin = namespace == 'jln'
                  and ' -DJLN_MP_USE_OPTIONAL_BUILTIN=' .. builtin
                  or ''

                compile(id_elems, compilercmd .. bench_opt .. stdlib ..
                        bench_type_compiler_option_table[bench_type] ..
                        ' -std=c++' .. cppversion .. dnamespace .. dbuiltin .. subbenchs_opt)

                if runsep then
                  print(runsep)
                end

                -- builtin is irrelevant with std namespace
                if namespace == 'std' then
                  break
                end
              end
            end
          end
        end
      end
    end
  end
end

if full then
  if #bench_types == 0 then bench_types = {'B', 'SVT', 'SV', 'ST', 'S', 'V', 'T'} end
  local saved_bench_types = bench_types
  local keepable_table = {
    SVT={B=true, SVT=true,  SV=true,  ST=true,  S=true, V=true,  T=true,},
    SV= {B=true, SVT=false, SV=true,  ST=false, S=true, V=true,  T=false,},
    ST= {B=true, SVT=false, SV=false, ST=true,  S=true, V=false, T=true,},
  }
  for _, algoname in ipairs(#bench_algonames ~= 0 and bench_algonames or algos) do
    if algoname ~= 'NONE' then
      algodef = algos[algoname]
      algo_bench_type = algodef[1]
      bench_types = {}
      for _, bench_type in ipairs(saved_bench_types) do
        if keepable_table[algo_bench_type][bench_type] then
          table.insert(bench_types, bench_type)
        end
      end
      subbenchs_opts = make_bench_options(algoname, algodef[2])
      bench_opt = compile_options .. ' -DBENCH_' .. algoname .. '=1'
    else
      bench_types = {'0'}
      subbenchs_opts = {''}
      bench_opt = compile_options
    end
    matrix_compile(algoname, subbenchs_opts, bench_opt)
  end
else
  if #bench_types == 0 then
    local all_types = {}
    for _, algoname in ipairs(bench_algonames) do
      all_types[algos[algoname][1]] = true
    end

    if all_types['SV'] and all_types['ST'] or all_types['SVT'] then
      bench_types = {'S', 'V', 'T'}
    else
      bench_types = {'S', all_types['SV'] and 'V' or 'T'}
    end
  end

  if #bench_algonames == 1 then
    algoname = bench_algonames[1]
    subbenchs_opts = make_bench_options(algoname, algos[bench_algonames[1]][2])
  else
    algoname = table.concat(bench_algonames, ',')
    subbenchs_opts = {''}
  end
  bench_opt = compile_options .. ' -DBENCH_' .. table.concat(bench_algonames, '=1 -DBENCH_') .. '=1'
  matrix_compile(algoname, subbenchs_opts, bench_opt)
end
