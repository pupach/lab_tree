cmake_minimum_required(VERSION 3.27)
project(lab_hash)

set(CMAKE_C_STANDARD 17)

SET(CMAKE_EXE_LINKER_FLAGS  "-fsanitize=address -lm")


execute_process(COMMAND mkdir -p data)

add_executable(gen_graph b/b_tree.c)

add_custom_target(python
        gen_graph
        COMMAND mkdir -p graphs && ../venv/bin/python3 ../graph.py
        COMMENT "Executing linter"
)
add_executable(Gen_data main.c
        node.c
        node.h
        avl/Avl_tree.c
        decart/decart_tree.c
        rb/rb_tree.c
        avl/Avl_tree.h
        decart/decart_tree.h
        splay/Splay_tree.h
        rb/rb_tree.h
        splay/Splay_tree.c
        skip/Skip_List.c
        bin/bin_tree.c
        bin/bin_tree.h
        b/b_tree.c
        b/b_tree.h)
