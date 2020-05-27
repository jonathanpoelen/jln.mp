Online documentation: https://jonathanpoelen.github.io/jln.mp/

# Configure

```sh
git worktree add docs/html html_doc
```

# Compile

```zsh
eval `luarocks --lua-version=5.1 path`

luajit ./tools/docgen.lua \
  include/jln/mp/algorithm/* \
  include/jln/mp/functional/* \
  include/jln/mp/list/* \
  include/jln/mp/number/* \
  include/jln/mp/utility/* \
  include/jln/mp/value/* \
  > docs/html/index.html
```
