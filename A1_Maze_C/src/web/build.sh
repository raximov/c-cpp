#!/bin/bash

./3rdparty/emsdk/emsdk  install latest

./3rdparty/emsdk/emsdk  activate latest

source ./3rdparty/emsdk/emsdk_env.sh

EXPORTED_FUNCS=$(cat << _EOF_
create_maze
free_maze
create_path
free_path
get_solution_bfs
areStartEndValid
get_max_size
load_maze_from_content
generate_maze
malloc
free
_EOF_
)

EXPORTED_FUNCS_STRING=$(echo "$EXPORTED_FUNCS" | sed 's/^/"_/' | sed 's/$/",/' | tr '\n' ' ' | sed 's/, $//')

emcc backend.c -o web/backend.js \
-s WASM=1 \
-s EXPORTED_FUNCTIONS="$EXPORTED_FUNCS_STRING" \
-s MODULARIZE=1 -s EXPORT_NAME='backend_module' \
-s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "getValue", "stringToUTF8", "setValue"]'
