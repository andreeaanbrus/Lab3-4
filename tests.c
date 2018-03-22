////
//// Created by Andreea on 3/15/2018.
////
//
#include <memory.h>
#include <assert.h>
#include "offer.h"
#include "repo.h"
#include "dinamic_array.h"
#include "controller.h"
#include <stdlib.h>


void TestMakeOffer(){
    Offer *o;
    o = makeOffer("house", "", 100, 1200);
    assert(getSurface(o) == 100);
    assert(strcmp(getType(o), "house") == 0);
    assert(strcmp(getAddress(o), "") == 0);
    assert(getPrice(o) == 1200);
    destroyOffer(o);
}

void TestAddOffer(){
    Repo *repo = createRepo();
    //assert(getLen(repo) == 0);
    Offer *o = makeOffer("house", "m", 100, 1200);
    addOffer(repo, o);
    assert(getLen(repo) == 1);
    Offer *o1 = makeOffer("b", "j", 12, 12);
    addOffer(repo, o1);
    assert(getLen(repo) == 2);
    destroyRepo(repo);
}
void TestRemoveOffer(){
    Repo *repo = createRepo();
    Offer *o = makeOffer("house", "", 100, 1200);
    addOffer(repo, o);
    removeOffer(repo, 0);
    assert(getLen(repo) == 0);
    destroyRepo(repo);
}

void TestUpdateOffer(){
    Repo *repo = createRepo();
    Offer *o = makeOffer("house", "", 100, 1200);
    addOffer(repo, o);
    Offer* o1 = makeOffer("sdas", "dsad", 123, 123);
    updateOffer(repo, 0, o1);
    assert(getElem(getElems(repo), 0) == o1);
}

void TestDynArray() {
    DinArray *v = createDynamicArray(2);
    if (v == NULL)
        assert(0);
    assert(v -> cap == 2);
    assert(v -> len == 0);
    Offer *o1 = makeOffer("house", "", 100, 1200);
    add(v, o1);
    assert(v -> cap == 2);
    assert(v -> len == 1);
    assert(v -> elems[0] == o1);
    Offer *o2 = makeOffer("house1", "", 100, 1200);
    Offer *o3 = makeOffer("house2", "", 100, 1200);
    add(v, o2);
    add(v, o3);
    assert(v -> cap == 4);
    delete(v, 2);
    assert(v->len == 2);
    destroyDynamicArray(v);
}

void TestSortByPrice(){
    Repo *r = createRepo();
    Controller *c = createController(r);
    Offer *o1 = makeOffer("house", "a", 100, 100);
    Offer *o2 = makeOffer("house", "b", 100, 101);
    Offer *o3 = makeOffer("house", "c", 100, 103);
    Offer *o4 = makeOffer("house", "d", 100, 102);
    addOffer(r, o1);
    addOffer(r, o2);
    addOffer(r, o3);
    addOffer(r, o4);
    sortByNumber(c->repo, getPrice, 1);
    assert(getElem(r -> offers, 0) == o1);
    assert(getElem(r -> offers, 1) == o2);
    assert(getElem(r -> offers, 2) == o4);
    assert(getElem(r -> offers, 3) == o3);
    destroyController(c);
}

void TestSortByString(){
    Repo *r = createRepo();
    Controller *c = createController(r);
    Offer *o1 = makeOffer("house", "a", 100, 100);
    Offer *o2 = makeOffer("house", "c", 100, 101);
    Offer *o3 = makeOffer("house", "b", 100, 103);
    Offer *o4 = makeOffer("house", "e", 100, 102);
    addOffer(r, o1);
    addOffer(r, o2);
    addOffer(r, o3);
    addOffer(r, o4);
    sortByString(c->repo, getAddress, -1);
    assert(getElem(r -> offers, 0) == o4);
    assert(getElem(r -> offers, 1) == o2);
    assert(getElem(r -> offers, 2) == o3);
    assert(getElem(r -> offers, 3) == o1);
    destroyController(c);
}

void TestUndoRedo() {
    Repo * r = createRepo();
    Controller *c = createController(r);
    addOfferController(c, "house", "adr1", 120, 200);
    assert(c->repoStackTop == 1);
    assert(c->repoStackIndex == 1);
    undo(c);
    assert(c->repoStackTop == 1);
    assert(c->repoStackIndex == 0);
    redo(c);
    assert(c->repoStackIndex == 1);
    destroyController(c);
}

void tests(){
    TestMakeOffer();
    TestAddOffer();
    TestRemoveOffer();
    TestUpdateOffer();
    TestDynArray();
    TestSortByPrice();
    TestSortByString();
    TestUndoRedo();
}


