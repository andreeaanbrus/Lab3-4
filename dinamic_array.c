//
// Created by Andreea on 3/15/2018.
//

#include <endian.h>
#include <stdlib.h>
#include <stdio.h>
#include "dinamic_array.h"

DinArray *createDynamicArray(int capacity) {
    DinArray *da = (DinArray*)(malloc(sizeof(DinArray)));
    if (da == NULL)
        return NULL;
    da -> cap = capacity;
    da -> len = 0;
    da -> elems = (TElement*)(malloc(capacity * sizeof(TElement)));
    if (da -> elems == NULL)
        return NULL;
    return da;
}

void destroyDynamicArray(DinArray *v) {
    if (v == NULL)
        return;
    //dealocate the elements of the array
    for (int i = 0; i < v->len; i++)
        destroyOffer(v->elems[i]);
    free (v->elems);
    v->elems = NULL;
    free(v);
    v = NULL;
}

DinArray *copyDynamicArray(DinArray *v) {
    DinArray *to_return = createDynamicArray(v->cap);
    for (int i = 0; i < v->len; ++i) {
        TElement new_offer = copyOffer(v->elems[i]);
        add(to_return, new_offer);
    }
    return to_return;
}

int resize(DinArray *v) {
    if (v == NULL)
        return -1;
    v -> cap *= 2;
    TElement *aux = (TElement*)malloc(v->cap * sizeof(TElement));
    if(aux == NULL)
        return -1;
    for(int i = 0; i < v -> len; i++)
        aux[i] = v -> elems[i];
    free(v -> elems);
    v -> elems = aux;
    return 0;
}

void add(DinArray *v, TElement t) {
    if (v == NULL) {
        return;
    }
    if ( v -> elems == NULL) {
        return;
    }
    if (v -> len == v -> cap) {
        resize(v);
    }
    v -> elems[v -> len] = t;
    v -> len += 1;
}

void delete(DinArray *v, int pos) {
    if (v == NULL)
        return;
    if (v->elems == NULL)
        return;
    if (pos < 0 || pos >= v->len)
        return;
    destroyOffer(v->elems[pos]);
    for (int i = pos; i < v -> len - 1; i++)
        v -> elems[i] = v -> elems[i + 1];
    v -> len --;
}

int getLenDynArr(DinArray *v) {
    if(v == NULL)
        return -1;
    return v -> len;
}

TElement getElem(DinArray *v, int pos) {
    return v -> elems[pos];
}

void interchange(DinArray *v, int i, int j) {
    TElement aux = v->elems[i];
    v -> elems[i] = v -> elems[j];
    v -> elems[j] = aux;
}