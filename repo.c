//
// Created by Andreea on 3/8/2018.
//

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "repo.h"

Repo* createRepo() {
    Repo *r = (Repo*)malloc(sizeof(Repo));
    r->offers = createDynamicArray(CAPACITY);
    return r;
}

void destroyRepo(Repo* r){
    destroyDynamicArray(r -> offers);
    free(r);
}

int getLen(Repo *r) {
    return getLenDynArr(r->offers);
}

int addOffer(Repo *r, Offer *o) {
    /*
     * Adds an offer to the repository
     * returns 1 if the offer was added
     * 0 otherwise
     * */

    if(find(r, getAddress(o)) != NULL)
        return 0;
    add(r -> offers, o);
    return 1;
}

Offer *find(Repo *r, char *address) {
    /*Searches the offer with the address 'address'
     * Input: r - the repository
     *        address - the given address, char
       returns NULL if the offer is not found int the repository
       returns the Offer with the given address if the offer is found in the repository
     */
    for(int i = 0; i < getLen(r); i++){
        if(strcmp(getAddress(getElem(r->offers, i)), address) == 0)
            return getElem(r->offers, i);
    }
    return NULL;
}

Offer *getOfferOnPositon(Repo *repo, int pos) {
    /*
     * Returns the offer from a certain position in repository
     * */
    getElem(repo -> offers, pos);
}

void removeOffer(Repo *r, int index) {
    /*
     * removes offer from repository
     * r - the repository
     * index - the position of the offer that needs to be removed
     * */
    delete(r->offers, index);
}

int findRepoId(Repo *r, Offer *o) {
    /*
     * finds an offer in the reposiotyr
     * returns the index of the offer
     * -1 if the offer is not found
     * */
    for(int i = 0; i < getLen(r); i++)
        if (checkEqual(getElem(r->offers, i), o))
            return i;
    return -1;
}

void updateOffer(Repo *r, int index, Offer *o) {
    removeOffer(r, index);
    addOffer(r, o);
}

DinArray * getElems(Repo *r) {
    return r->offers;
}

Repo* copyRepo(Repo *r) {
    Repo *new_repo = (Repo *)malloc(sizeof(Repo));
    new_repo->offers = copyDynamicArray(r->offers);
    return new_repo;
}
