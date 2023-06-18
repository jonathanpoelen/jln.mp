#!/usr/bin/env bash

set -e

init_compile_options() {
  disabled=()
  types=()
  compilers=()
  namespaces=()
  stdlibs=()
  builtins=()
  cppversions=()
}

init_compile_options

opts=''
show_source=
full=
all=
single_test=
noexe=
nocolor=

parse_cli() {
  while (($#)) ; do
    opt="${1@U}"
    case "$opt" in
      -*) opts+=" $1";;

      FULL) full=1;;
      NOEXE|N) noexe=1;;

      COLOR) nocolor=;;
      NOCOLOR) nocolor=1;;

      ALL) all=1;;
      SOURCE) show_source=1;;
      INTRINSIC|BUILTIN) builtins+=(1);;
      NOINTRINSIC|NO_INTRINSIC|NOBUILTIN|NO_BUILTIN) builtins+=(0);;

      GCC|G++) compilers+=(g++);;
      CLANG|CLANG++) compilers+=(clang++);;

      cpp17|c++17|17) cppversions+=(17);;
      cpp20|c++20|20) cppversions+=(20);;

      STD) namespaces+=(std);;
      JLN) namespaces+=(jln);;

      LIBCPP|LIBC++) stdlibs+=(libc++);;
      LIBSTDCPP|LIBSTDC++) stdlibs+=(libstdc++);;

      S|STRUCT) types+=('-DBENCH_TYPE=S');;
      V|VALUE) types+=('-DBENCH_TYPE=V');;
      T|TYPE) types+=('-DBENCH_TYPE=T');;
      SV) types+=('-DBENCH_TYPE=SV');;
      ST) types+=('-DBENCH_TYPE=ST');;
      SVT) types+=('-DBENCH_TYPE=SVT');;
      B|BASELINE) types+=('-DBENCH_TYPE=B');;

      IS_MEMBER_OBJECT_POINTER|\
      IS_MEMBER_FUNCTION_POINTER|\
      IS_MEMBER_POINTER)
        opts+=" -DBENCH_$opt=1"
        disabled=(
          "-DBENCH_${opt}_DISABLE_T=1"
          "-DBENCH_${opt}_DISABLE_MEM_T=1"
        )
        ;;

      IS_CONVERTIBLE|\
      IS_NOTHROW_CONVERTIBLE)
        opts+=" -DBENCH_$opt=1"
        disabled=(
          "-DBENCH_${opt}_DISABLE_T=1"
          "-DBENCH_${opt}_DISABLE_REF=1"
          "-DBENCH_${opt}_DISABLE_REF_FALSE=1"
        )
        ;;

      IS_SCOPED_ENUM)
        opts+=" -DBENCH_$opt=1"
        disabled=(
          "-DBENCH_${opt}_DISABLE_T=1"
          "-DBENCH_${opt}_DISABLE_E=1"
        )
        ;;

      IS_SWAPPABLE|\
      IS_NOTHROW_SWAPPABLE)
        opts+=" -DBENCH_$opt=1"
        disabled=(
          "-DBENCH_${opt}_DISABLE_REF=1"
          "-DBENCH_${opt}_DISABLE_REF2=1"
        )
        ;;

      RANK|\
      EXTENT)
        opts+=" -DBENCH_$opt=1"
        disabled=(
          "-DBENCH_${opt}_DISABLE_T=1"
          "-DBENCH_${opt}_DISABLE_ARRAY=1"
        )
        ;;

      DECAY)
        opts+=" -DBENCH_$opt=1"
        disabled=(
          "-DBENCH_${opt}_DISABLE_T=1"
          "-DBENCH_${opt}_DISABLE_REF=1"
        )
        ;;

      INVOKE_RESULT|\
      IS_INVOCABLE|\
      IS_INVOCABLE_R|\
      IS_NOTHROW_INVOCABLE|\
      IS_NOTHROW_INVOCABLE_R)
        opts+=" -DBENCH_$opt=1"
        disabled=(
          "-DBENCH_${opt}_DISABLE_FN=1"
          "-DBENCH_${opt}_DISABLE_MEM_VAR=1"
          "-DBENCH_${opt}_DISABLE_MEM_FN=1"
        )
        ;;

      IS_CONST|\
      IS_VOLATILE|\
      IS_TRIVIAL|\
      IS_TRIVIALLY_COPYABLE|\
      IS_ABSTRACT|\
      IS_AGGREGATE|\
      IS_BASE_OF|\
      IS_CLASS|\
      IS_EMPTY|\
      IS_ENUM|\
      IS_FINAL|\
      IS_POLYMORPHIC|\
      IS_UNION|\
      IS_SIGNED|\
      IS_UNSIGNED|\
      IS_BOUNDED_ARRAY|\
      ADD_LVALUE_REFERENCE|\
      ADD_RVALUE_REFERENCE|\
      HAS_UNIQUE_OBJECT_REPRESENTATIONS|\
      IS_VOID|\
      IS_NULL_POINTER|\
      IS_INTEGRAL|\
      IS_FLOATING_POINT|\
      IS_ARRAY|\
      IS_POINTER|\
      IS_LVALUE_REFERENCE|\
      IS_RVALUE_REFERENCE|\
      IS_REFERENCE|\
      IS_FUNCTION|\
      IS_ARITHMETIC|\
      IS_FUNDAMENTAL|\
      IS_OBJECT|\
      IS_SCALAR|\
      IS_STANDARD_LAYOUT|\
      IS_COMPOUND|\
      IS_CONSTRUCTIBLE|\
      IS_DEFAULT_CONSTRUCTIBLE|\
      IS_COPY_CONSTRUCTIBLE|\
      IS_MOVE_CONSTRUCTIBLE|\
      IS_TRIVIALLY_CONSTRUCTIBLE|\
      IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE|\
      IS_TRIVIALLY_COPY_CONSTRUCTIBLE|\
      IS_TRIVIALLY_MOVE_CONSTRUCTIBLE|\
      IS_NOTHROW_CONSTRUCTIBLE|\
      IS_NOTHROW_DEFAULT_CONSTRUCTIBLE|\
      IS_NOTHROW_COPY_CONSTRUCTIBLE|\
      IS_NOTHROW_MOVE_CONSTRUCTIBLE|\
      IS_ASSIGNABLE|\
      IS_COPY_ASSIGNABLE|\
      IS_MOVE_ASSIGNABLE|\
      IS_NOTHROW_ASSIGNABLE|\
      IS_NOTHROW_COPY_ASSIGNABLE|\
      IS_NOTHROW_MOVE_ASSIGNABLE|\
      IS_TRIVIALLY_ASSIGNABLE|\
      IS_TRIVIALLY_COPY_ASSIGNABLE|\
      IS_TRIVIALLY_MOVE_ASSIGNABLE|\
      IS_DESTRUCTIBLE|\
      IS_TRIVIALLY_DESTRUCTIBLE|\
      IS_NOTHROW_DESTRUCTIBLE|\
      IS_IMPLICIT_LIFETIME|\
      IS_SWAPPABLE_WITH|\
      IS_NOTHROW_SWAPPABLE_WITH|\
      HAS_VIRTUAL_DESTRUCTOR|\
      IS_SAME|\
      ALIGNMENT_OF|\
      REMOVE_CONST|\
      REMOVE_VOLATILE|\
      REMOVE_CV|\
      REMOVE_EXTENTS|\
      REMOVE_ALL_EXTENTS|\
      REMOVE_POINTER|\
      REMOVE_REFERENCE|\
      REMOVE_CVREF|\
      REFERENCE_CONSTRUCTS_FROM_TEMPORARY|\
      REFERENCE_CONVERTS_FROM_TEMPORARY|\
      ADD_POINTER|\
      ADD_CV|\
      ADD_CONST|\
      ADD_VOLATILE|\
      MAKE_SIGNED|\
      MAKE_UNSIGNED|\
      UNWRAP_REFERENCE|\
      UNWRAP_REF_DECAY|\
      UNDERLYING_TYPE|\
      COMMON_TYPE|\
      COMMON_REFERENCE)
        opts+=" -DBENCH_$opt=1"
        single_test=1
        ;;
      # IS_LAYOUT_COMPATIBLE|
      # IS_POINTER_INTERCONVERTIBLE_BASE_OF|

      *) echo "Unknown $1" >&2; exit 1;;
    esac
    shift
  done
}

run() {
  if (( ! ${#types} )); then
    types=('-DBENCH_TYPE=S' '-DBENCH_TYPE=V' '-DBENCH_TYPE=T')
  fi

  if (( ! ${#cppversions} )); then
    cppversions=(17 20)
  fi

  if (( ! ${#namespaces} )); then
    namespaces=(std jln)
  fi

  if (( ! ${#compilers} )); then
    compilers=(g++ clang++)
  fi

  if (( ! ${#builtins} )); then
    builtins=(0 1)
  fi

  if (( ! ${#stdlibs} )); then
    stdlibs=(libstdc++ libc++)
  fi

  disabled_combi=('')
  case ${#disabled[@]} in
    2) disabled_combi=(
      ''
      "${disabled[0]}"
      "${disabled[1]}"
    );;
    3) disabled_combi=(
      ''
      "${disabled[0]}"
      "${disabled[1]}"
      "${disabled[2]}"
      "${disabled[0]} ${disabled[1]}"
      "${disabled[0]} ${disabled[2]}"
      "${disabled[1]} ${disabled[2]}"
    );;
    0) ;;
    *) echo oops, script to correct "(value is ${#disabled[@]})" >&2; exit 2;;
  esac

  for compiler in ${compilers[@]}; do
    for stdlib in ${stdlibs[@]}; do
      if [[ $compiler = 'g++' ]]; then
        # -stdlib may not be supported by gcc, skip compiling with libc++
        if [[ $stdlib = 'libc++' ]]; then
          break
        fi
        stdlib=''
      else  # clang++
        stdlib="-stdlib=$stdlib"
      fi

      for type in ${types[@]}; do
        for ddisabled in "${disabled_combi[@]}"; do
          for namespace in ${namespaces[@]}; do
            [[ $namespace = 'std' ]] \
              && dnamespace='-DBENCH_STD=1' \
              || dnamespace='-DBENCH_STD=0 -DJLN_MP_NO_STL_TRAIT=1'
            for cppversion in ${cppversions[@]}; do
              for builtin in ${builtins[@]}; do
                [[ $namespace = 'jln' ]] \
                  && dbuiltin='-DJLN_MP_USE_OPTIONAL_BUILTIN='$builtin \
                  || dbuiltin=

                  compile $compiler -fsyntax-only -I ../include stl_traits.cpp \
                    $opts $stdlib $type $ddisabled $dnamespace -std=c++$cppversion $dbuiltin
                  echo -n "$runsep"

                # builtin is irrelevant with std namespace
                if [[ $namespace = 'std' ]]; then
                  break;
                fi
              done
            done
          done
        done
      done
    done
  done
}

parse_cli "$@"

if [[ -z $nocolor ]]; then
  color1=$'\x1b[37m'
  color2=$'\x1b[34m'
  colorend=$'\x1b[m'
else
  color1=''
  color2=''
  colorend=''
fi

[[ -z $noexe || -n $show_source ]] && runsep='-----'$'\n' || runsep=''

compile() {
  echo "$color1# $@$colorend"

  if [[ -n $show_source ]]; then
    echo -n "$color2"
    "$@" -Wno-unused-command-line-argument -DBENCH_SHOW_SOURCE=1 -E \
      | sed -E '/^ *PRINT/!d;{s/(PRINT.*)PRINT/\1\n/g;s/ *PRINT ([^;]+);/\1/}'
    echo -n "$colorend"
  fi

  if [[ -n $noexe ]]; then
    return 0
  fi

  declare -i i
  declare result=$(for ((i=0; i < 5; ++i)); do
    /usr/bin/time --format='%Es - %MK' "$@" -fdiagnostics-color=always || exit 3
  done 2>&1)

  # output too long. Assume this is a compilation error
  if (( ${#result} > 100 )); then
    echo "$result" >&2
    exit 3
  fi

  # get the median time
  sort <<<"${result}" | { read; read; read l; echo "$l"; }
}

# echo opts: $opts
# echo disabled: ${disabled[@]}
# echo types: ${types[@]}
# echo builtins: ${builtins[@]}
# echo namespaces: ${namespaces[@]}
# echo stdlibs: ${stdlibs[@]}
# echo compilers: ${compilers[@]}

cd "$(dirname "$0")"

if [[ -z $all && -z $single_test ]] && (( ! ${#disabled[@]} )); then
  all=1
fi

if [[ -n $all ]]; then
  opts+=' -DBENCH_ALL=1';
fi

if [[ -n $full ]]; then
  previous_opts=$opts
  for param in all \
    is_member_object_pointer \
    is_member_function_pointer \
    is_member_pointer \
    is_convertible \
    is_nothrow_convertible \
    is_scoped_enum \
    is_swappable \
    is_nothrow_swappable \
    rank \
    extent \
    decay \
    invoke_result \
    is_invocable \
    is_invocable_r \
    is_nothrow_invocable \
    is_nothrow_invocable_r \
    is_const \
    is_volatile \
    is_trivial \
    is_trivially_copyable \
    is_abstract \
    is_aggregate \
    is_base_of \
    is_class \
    is_empty \
    is_enum \
    is_final \
    is_polymorphic \
    is_union \
    is_signed \
    is_unsigned \
    is_bounded_array \
    add_lvalue_reference \
    add_rvalue_reference \
    has_unique_object_representations \
    is_void \
    is_null_pointer \
    is_integral \
    is_floating_point \
    is_array \
    is_pointer \
    is_lvalue_reference \
    is_rvalue_reference \
    is_reference \
    is_function \
    is_arithmetic \
    is_fundamental \
    is_object \
    is_scalar \
    is_standard_layout \
    is_compound \
    is_constructible \
    is_default_constructible \
    is_copy_constructible \
    is_move_constructible \
    is_trivially_constructible \
    is_trivially_default_constructible \
    is_trivially_copy_constructible \
    is_trivially_move_constructible \
    is_nothrow_constructible \
    is_nothrow_default_constructible \
    is_nothrow_copy_constructible \
    is_nothrow_move_constructible \
    is_assignable \
    is_copy_assignable \
    is_move_assignable \
    is_nothrow_assignable \
    is_nothrow_copy_assignable \
    is_nothrow_move_assignable \
    is_trivially_assignable \
    is_trivially_copy_assignable \
    is_trivially_move_assignable \
    is_destructible \
    is_trivially_destructible \
    is_nothrow_destructible \
    is_implicit_lifetime \
    is_swappable_with \
    is_nothrow_swappable_with \
    has_virtual_destructor \
    is_same \
    alignment_of \
    remove_const \
    remove_volatile \
    remove_cv \
    remove_extents \
    remove_all_extents \
    remove_pointer \
    remove_reference \
    remove_cvref \
    reference_constructs_from_temporary \
    reference_converts_from_temporary \
    add_pointer \
    add_cv \
    add_const \
    add_volatile \
    make_signed \
    make_unsigned \
    unwrap_reference \
    unwrap_ref_decay \
    underlying_type \
    common_type \
    common_reference \
  ; do
    init_compile_options
    opts=$previous_opts
    parse_cli $param
    types=('-DBENCH_TYPE=B' '-DBENCH_TYPE=S' '-DBENCH_TYPE=V' '-DBENCH_TYPE=T' '-DBENCH_TYPE=SVT')
    run
  done
else
  run
fi
