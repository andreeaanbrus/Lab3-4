//
// Created by Andreea on 3/8/2018.
//

#ifndef LAB3_4_OFFER_H
#define LAB3_4_OFFER_H

typedef struct {
    int surface;
    char* type;
    char* address;
    int price;
} Offer;

Offer* makeOffer(char *type, char * address, int surface, int price);
Offer* copyOffer(Offer*);
int getSurface(Offer *o);
int getPrice(Offer *o);
char *getType(Offer *o);
char *getAddress(Offer *o);
void destroyOffer(Offer *o);
void offerToString(Offer *o, char *s);
int checkEqual(Offer*o, Offer*other);
int compareAddress(Offer *o, char *s);

void dbg_offer(Offer*);
#endif //LAB3_4_OFFER_H
