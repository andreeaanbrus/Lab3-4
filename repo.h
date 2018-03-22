//
// Created by Andreea on 3/8/2018.
//

#ifndef LAB3_4_REPO_H
#define LAB3_4_REPO_H

#include "offer.h"
#include "dinamic_array.h"

#define CAPACITY 10

typedef struct {
    //int len;
    //Offer* offers[100];
    DinArray * offers;
}Repo;

Repo* createRepo();
void destroyRepo(Repo*);
int addOffer(Repo*, Offer*);
Offer* find(Repo* ,char *);
int getLen(Repo*);
Offer* getOfferOnPositon(Repo*, int id);
void removeOffer(Repo*, int);
int findRepoId(Repo*, Offer*);
void updateOffer(Repo *r, int index, Offer*o);
DinArray * getElems(Repo *r);
Repo* copyRepo(Repo*);

#endif //LAB3_4_REPO_H
