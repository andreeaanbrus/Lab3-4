//
// Created by Andreea on 3/8/2018.
//

#include "offer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Offer* makeOffer(char *type, char *address, int surface, int price) {
    Offer* result = (Offer*) malloc (sizeof(Offer));

    result->type= (char*)malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(result->type,type);

    result->address = (char*)malloc(sizeof(char) * (strlen(address) + 1));
    strcpy(result->address, address);

    result->surface = surface;
    result->price = price;

    return result;
}

void destroyOffer(Offer * o){
    free(o->address);
    free(o->type);
    free(o);
}

Offer* copyOffer(Offer* o) {
    Offer *newOffer =  (Offer*) malloc(sizeof(Offer));
    memset(newOffer, 0, sizeof(newOffer));
    newOffer->address = malloc(100 * sizeof(char));
    memset(newOffer->address, 0, 100 * sizeof(char));
    newOffer->type= malloc(100 * sizeof(char));
    memset(newOffer->type, 0, 100 * sizeof(char));

    memcpy(newOffer -> address, o -> address, strlen(o->address));
    memcpy(newOffer -> type, o -> type, strlen(o->type));
    newOffer -> surface = o -> surface;
    newOffer -> price = o -> price;
    return newOffer;
}

int getSurface(Offer *o) {
    return o->surface;
}

int getPrice(Offer *o) {
    return o->price;
}

char *getType(Offer *o) {
    return o->type;
}

char *getAddress(Offer *o){
    return o->address;
}

void offerToString(Offer *o, char*s) {
    sprintf(s, "Type: %s | Address: %s | Surface:%d | Price: %d\n", o->type, o->address, o->surface, o->price);
}

int checkEqual(Offer *o, Offer *other) {
    if(strcmp(o->type, other->type) == 0 && strcmp(o->address, other->address) == 0 && o->surface == other->surface && o->price == other->price)
        return 1;
    return 0;
}
//
void dbg_offer(Offer* this){
    printf("\t\taddress: %20s mem: %p\n", this->address, this->address);
    printf("\t\ttype   : %20s mem: %p\n", this->type, this->type);
    printf("\t\tsurface: %20d mem: %p\n", this->surface);
    printf("\t\tprice  : %20d mem: %p\n", this->price);
}