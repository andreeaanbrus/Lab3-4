//
// Created by Andreea on 3/8/2018.
//

#include <endian.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "controller.h"

Controller *createController(Repo *repo) {
    Controller *c = (Controller*)malloc(sizeof(Controller));
    c->repo = repo;
    for (int i = 0; i < 200; ++i)
        c->repoStack[i] = NULL;
    c->repoStack[0] = repo;
    c->repoStackTop = 0;
    c->repoStackIndex = 0;
}

void destroyController(Controller *c) {
    for(int i = 0 ; i < 200; i++) {
        if (c->repoStack[i] != NULL)
            destroyRepo(c->repoStack[i]);
    }
    free(c);
}

Repo *getRepo(Controller *c) {
    return c->repo;
}

int addOfferController(Controller *c, char* address, char* type, int surface, int price) {
    /*
     * Adds an offer
     * If succesful, return 1
     * Otherwise return 0
     * */

    updateRepoStack(c);
    if(find(c->repo, address) != NULL)
        return 0;
    Offer *o = makeOffer(type, address, surface, price);
    int res = addOffer(c->repo, o);
    if (res == 0)
        //if the offer was not added, it must be removed
        destroyOffer(o);
    return res;
}

int removeOfferController(Controller *c, char *address) {
    /*
     * Removes an offer by a given address
     * returns 1 if the offer was removed
     * 0 otherwise
    */
    updateRepoStack(c);
    Offer *o = find(c->repo, address);
    if(o != NULL)
    {
        int index = 0;
        index  = findRepoId(c->repo, o);
        removeOffer(c->repo, index);
        return 1;
    }
    else
        return 0;
}

int updateOfferController(Controller *c, char* oldAdr, char *address, char *type, int surface, int price) {
    /*
     * Update an offer
     * return 1 if the update was made
     * return 0 otherwise
     * */
    updateRepoStack(c);
    Offer *o = makeOffer(type, address, surface, price);
    Offer *oldOffer = find(c->repo, oldAdr);
    if(oldOffer == NULL){
        destroyOffer(o);
        return 0;
    }
    else {
        int index = 0;
        index = findRepoId(c->repo, oldOffer);
        updateOffer(c->repo, index, o);
        return 1;
    }
}

void updateRepoStack(Controller *c) {
    if (c->repoStackIndex < c->repoStackTop) {
        for (int i = c->repoStackIndex + 1; i <= c->repoStackTop; ++i) {
            destroyRepo(c->repoStack[i]);
        }
        c->repoStackTop = c->repoStackIndex;
    }
    c->repoStackTop++;
    c->repoStack[c->repoStackTop] = copyRepo(c->repo);
    c->repo = c->repoStack[c->repoStackTop];
    c->repoStackIndex = c->repoStackTop;
}

int undo(Controller *c) {
    if (c->repoStackIndex == 0) {
        return 0;
    }
    c->repoStackIndex--;
    c->repo = c->repoStack[c->repoStackIndex];
    return 1;
}

int redo(Controller *c) {
    if (c->repoStackIndex == c->repoStackTop) {
        return 0;
    }
    c->repoStackIndex++;
    c->repo = c->repoStack[c->repoStackIndex];
    return 1;
}

Repo* filterByAddress(Controller*c, char* s) {
    /*
     * filters repo
     * returns new list of filtered offers
     */
    Repo *repo = createRepo();
    for(int i = 0; i < getLen(c->repo); i++)
        if (strstr(getAddress(getElem(getElems(getRepo(c)), i)), s) != NULL) {
            Offer *off = makeOffer(getType(getElem(getElems(c->repo),i)), getAddress(getElem(getElems(c->repo),i)),
                                   getSurface(getElem(getElems(c->repo),i)), getPrice(getElem(getElems(c->repo),i)));
            addOffer(repo, off);
        }
    return repo;
}

void filterBySurface(Repo *r, int surface) {
    /*
     * filters repo by surface
     * returns new list
     * */

    int i = 0;
    while(i < getLen(r)) {
        if (getSurface(getElem(getElems(r), i)) < surface)
            removeOffer(r, i);
        else
            ++i;
    }
}

Repo *filterByNumber(Controller *c, int (*p)(Offer *o), int nr) {
    /*
     * *p pointer to function
     * order -  1 -> ascending
     *       - -1 -> decending
     */
    Repo *r = createRepo();
    for(int i = 0; i < getLen(c->repo); i++)
        if(p(getElem(getElems(c->repo), i)) == nr) {
            Offer *off = makeOffer(getType(getElem(getElems(c->repo), i)), getAddress(getElem(getElems(c->repo), i)),
                                   getSurface(getElem(getElems(c->repo), i)), getPrice(getElem(getElems(c->repo), i)));
            addOffer(r, off);
        }
    return r;
}

Repo *filterByChar(Controller *c, char* (*p)(Offer*o), char *s) {
    /*
        filters by char
        char * (*p)(Offer *o) function getType or getAddress
        s - the given string
     */
    Repo *r = createRepo();
    for(int i = 0; i < getLen(c->repo); i++)
        if(strcmp(p(getElem(getElems(c->repo), i)), s) == 0) {
                Offer *off = makeOffer(getType(getElem(getElems(c->repo), i)), getAddress(getElem(getElems(c->repo), i)),
                                       getSurface(getElem(getElems(c->repo), i)), getPrice(getElem(getElems(c->repo), i)));
                addOffer(r, off);
            }
    return r;
}

void sortByNumber(Repo *r, int (*p)(Offer *), int order) {
    for(int i = 0; i < getLen(r) - 1; i++)
        for(int j = i + 1; j < getLen(r); j++)
            if(order * p(getElem(getElems(r), i)) > order * p(getElem(getElems(r), j)))
                interchange(r -> offers, i, j);
}

void sortByString(Repo *r, char *(*p)(Offer *), int order) {
    for(int i = 0; i < getLen(r) - 1; i++)
        for(int j = i + 1; j < getLen(r); j++)
            if(order * strcmp(p(getElem(getElems(r), i)), p(getElem(getElems(r), j))) > 0)
                interchange(r -> offers, i, j);
}


void getOffersPriceSmallerThan(Repo *r, int price) {
    int i = 0;
    while(i < getLen(r)) {
        if (getPrice(getElem(getElems(r), i)) > price)
            removeOffer(r, i);
        else
            ++i;
    }
}
