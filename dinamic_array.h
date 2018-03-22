//
// Created by Andreea on 3/15/2018.
//

#ifndef LAB3_DINAMIC_ARRAY_H
#define LAB3_DINAMIC_ARRAY_H

#include "offer.h"

typedef Offer * TElement;

typedef struct {
    int cap;
    int len;
    TElement * elems;
}DinArray;

DinArray *createDynamicArray(int capacity);
void destroyDynamicArray(DinArray *v);
DinArray *copyDynamicArray(DinArray *v);
void add(DinArray *v, TElement t);
void delete(DinArray *v, int pos);
int resize(DinArray *v);
int getLenDynArr(DinArray *v);
TElement getElem(DinArray *v, int pos);
void interchange(DinArray *v, int i, int j);

#endif //LAB3_DINAMIC_ARRAY_H
