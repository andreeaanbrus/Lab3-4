//
// Created by Andreea on 3/8/2018.
//

#ifndef LAB3_4_CONTROLLER_H
#define LAB3_4_CONTROLLER_H

#include "repo.h"

typedef struct {
    Repo *repo;
    Repo *repoStack[200];
    int repoStackTop;
    int repoStackIndex;
}Controller;


void updateRepoStack(Controller *this);
int undo(Controller *this);
int redo(Controller *this);

Controller* createController(Repo *repo);
void destroyController(Controller *c);
int addOfferController(Controller *c, char* address, char* type, int surface, int price);
Repo* getRepo(Controller *c);
int removeOfferController(Controller *c, char* address);
int updateOfferController(Controller *c, char* oldArd, char* address, char* type, int surface, int price);
Repo *filterByAddress(Controller *c, char*s);
void filterBySurface(Repo *r, int surface);
Repo* filterByNumber(Controller *c, int (*p)(Offer *o), int nr);
Repo* filterByChar(Controller *c, char*(*p)(Offer *o), char *s);
void sortByNumber(Repo *r, int (*p)(Offer *o), int order);
void sortByString(Repo *r, char* (*p)(Offer *o), int order);
void getOffersPriceSmallerThan(Repo *r, int price);


#endif //LAB3_4_CONTROLLER_H
