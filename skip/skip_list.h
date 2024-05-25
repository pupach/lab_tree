//
// Created by pupach on 26.04.24.
//

#ifndef LAB_TREE_SKIP_LIST_H
#define LAB_TREE_SKIP_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define POISON_NEGATIVE -1000000000
#define POISON_POSITIVE 1000000000
extern struct Node;

typedef struct {
    int key;
    struct Node *next;
    struct Node *down;
    struct Node *up;
    struct Node *prev;

}Node;

typedef struct {
    Node *arr;
    Node *head;
    Node *tail;

    int size;

}List;

/**
 * @brief Создает список с пропусками по адресу переданного указателя
 * 
 * @param[in] указатель на список с пропусками
 * @param[in] размер первоночального массива
 */

void ListInit(List *list, int MAX_SIZE_ARR);

/**
 * @brief Удаляет узел из списка с пропусками
 * 
 * @param[in] указатель на список с пропусками
 * @param[in] значение, подлежащее удалению
 *  @return NULL
 */
Node *Remove(List *list, int ToRemove);

/**
 * @brief Вставляет узел в список с пропусками
 * 
 * @param[in] указатель на список с пропусками
 * @param[in] Узел для вставки
 *  @return NULL
 */
Node *Insert(List *list, Node *ToInsert);

#endif //LAB_TREE_SKIP_LIST_H
