cmake_minimum_required(VERSION 3.27)
project(lab_tree C)

set(CMAKE_C_STANDARD 17)

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
        Skip_List.h)
