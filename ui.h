//
// Created by Andreea on 3/8/2018.
//

#ifndef LAB3_4_UI_H
#define LAB3_4_UI_H

#include "controller.h"

typedef struct {
    Controller * controller;
}UI;

UI *createUI(Controller* controller);
void destroyUi(UI * ui);
void addOfferUI(UI* ui);
void startUI(UI * ui);
void removeOfferUI(UI *ui);
void updateOfferUI(UI *ui);
void printOffers(UI *ui);
void printMenu();
void getString(char *s, const char *message);
int readInteger(char *message);
void displayByType(UI *ui);
void displayBySurface(UI *ui);
void displayByPrice(UI *ui);
void redoUI(UI * ui);
void undoUI(UI * ui);

#endif //LAB3_4_UI_H
