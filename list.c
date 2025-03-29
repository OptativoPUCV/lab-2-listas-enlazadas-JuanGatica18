#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *list = (List*) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (list->current == NULL || list->current->next == NULL) 
        return NULL;
    list->current = list->current->next;
    return list->current->data; 
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* nuevoNodo = createNode(data);
    nuevoNodo->next = list->head;
    if (list->head) list->head->prev = nuevoNodo;
    if (list->head == NULL){
        list->tail = nuevoNodo;
    }
    list->head = nuevoNodo;

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    
    Node* nuevoNodo = createNode(data);
    if (list->current == NULL)
    {
        return;
    }
    else
    
    nuevoNodo->next = list->current->next;
    nuevoNodo->prev = list->current;
    
    if (list->current->next != NULL)
    {
        list->current->next->prev = nuevoNodo;
    }

    list->current->next = nuevoNodo;
    if(nuevoNodo->next == NULL)
    {
        list->tail = nuevoNodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->current == NULL)
    {
        return NULL;
    }
    void* data = list->current->data;

    if(list->head == list->tail)
    {
        free(list->current);
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
        return data;
    }
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}