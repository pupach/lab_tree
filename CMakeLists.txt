cmake_minimum_required(VERSION 3.27)
project(lab_hash)

set(CMAKE_C_STANDARD 17)

SET(CMAKE_EXE_LINKER_FLAGS  "-fsanitize=address -lm")


execute_process(COMMAND mkdir -p data)

add_executable(gen_graph B_tree.c)

add_custom_target(python
        gen_graph
        COMMAND mkdir -p graphs && ../venv/bin/python3 ../graph.py
        COMMENT "Executing linter"
)
add_executable(Gen_data main.c
        ElemTree.c
        ElemTree.h
        Avl_tree.c
        Decartach.c
        RedBlackTree.c
        Avl_tree.h
        Decartach.h
        Splay_tree.h
        RedBlackTree.h
        Splay_tree.c
        Skip_List.c
        BinTree.c
        BinTree.h
        b_tree.c
        b_tree.h)
