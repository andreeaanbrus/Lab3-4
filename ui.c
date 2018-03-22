//
// Created by Andreea on 3/8/2018.
//

#include <endian.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include "ui.h"


UI *createUI(Controller *controller) {
    UI * ui = (UI*)malloc(sizeof(UI));
    ui->controller = controller;
}

void destroyUi(UI *ui) {
    //destroy controller fisrt
    destroyController(ui->controller);
    free(ui);
}

int readInteger(char* message){
    /*
     * read an integer from keyboard
     * message - a message to be displayed before reading
     * return: the read int
     * */
    char s[10];
    long r = 0;
    char *end;
    fprintf(stdout, "%s", message);
//    fflush(stdout);
    errno = 0;
    fgets(s, 10, stdin);
    r = strtol(s, &end, 10);
    return (int)r;
}

void getString(char *s, const char *message) {
    /*
     * reads a string prin keyboard
     * s the string
     * message, a message to be displayed before reading
     * */
    printf("%s",message);
//    fflush(stdin);
    fgets(s, 100, stdin);
    s[strlen(s)-1] = '\0';
}

void addOfferUI(UI *ui){
    char *address = malloc(100);
    char *type = malloc(100);
    int surface = 0;
    int price = 0;
    getString(type, "Give the type: ");
    getString(address, "Give the address: ");
    surface = readInteger("Give the surface(>0): ");
    if(surface == -10000){
        printf("%s\n","Invalid surface number");
        return;
    }
    price = readInteger("Give the price(>0): ");
    if(price == -10000){
        printf("%s\n","Invalid price number!");
        return;
    }
    if (addOfferController(ui->controller, address, type, surface, price) == 0)
        printf("%s\n","Invalid input");
    else
        printf("%s\n","The offer was added");
    free(address);
    free(type);

}

void printOffers(UI * ui){
    Repo* repo = getRepo(ui->controller);
    int len = getLen(repo);
    if(len == 0)
        printf("%s\n", "There are no offers");
    else
        for(int i = 0; i < len; i++)
        {
            Offer *o = getOfferOnPositon(repo, i);
            char str[200];
            offerToString(o, str);
            printf("%s", str);
        }

}

void printMenu(){
    printf("%s", "1 -> Add offer\n");
    printf("%s", "2 -> Print offers\n");
    printf("%s", "3 -> Remove an offer\n");
    printf("%s", "4 -> Update an offer\n");
    printf("%s", "5 -> Display offers which contain a certain sting, sorted ascending by price\n");
    printf("%s", "6 -> Display offers by a given type, having the surface greater than a given one\n");
    printf("%s", "7 -> Display offers by a given surface, sorted ascending by address\n");
    printf("%s", "8 -> Display offers which have a certain price, sorted ascending by address\n");
    printf("%s", "9 -> Undo\n");
    printf("%s","10 -> Redo\n");
    printf("%s", "11 -> Display offers by a given type, having the price smaller than a given value, sorted ascending by price\n");
    printf("%s\n", "0 -> Exit");
}

void removeOfferUI(UI *ui) {
    char *s = malloc(sizeof(char) * 100);
    getString(s, "Give the address:");
    int res = removeOfferController(ui->controller, s);
    if (res == 1)
        printf("%s\n","The offer was removed");
    else
        printf("%s\n","Invalid input");
    free(s);
}

void updateOfferUI(UI* ui){
    int price = 0, surface= 0;
    char address[100], type[100], oldAdr[100];
    getString(oldAdr, "Give the address of the offer you want to change: ");
    getString(address, "Give the new address");
    getString(type, "Give the new type");
    surface = readInteger("Give the new surface(>0): ");
    if(surface == -10000){
        printf("%s\n","Invalid surface number!");
        return;
    }
    price = readInteger("Give the new price(>0): ");
    if(price == -10000){
        printf("%s\n","Invalid price number!");
        return;
    }
    int res = updateOfferController(ui->controller, oldAdr, address, type, surface, price);
    if (res == 1)
        printf("%s\n", "The change was made!");
    else
        printf("%s\n", "The change was not made!");
}

void displayByAddress(UI *ui) {
    char *s = malloc(sizeof(char) * 100);
    getString(s, "Give the string: ");
    if(s == "")
        printOffers(ui);
    else {
        Repo *newList;
        newList = filterByAddress(ui->controller, s);
        sortByNumber(newList, getPrice, 1);
        //print
        int len = getLen(newList);
        if(len == 0)
            printf("%s\n", "There are no offers");
        else
            for(int i = 0; i < len; i++) {
                Offer *o = getOfferOnPositon(newList, i);
                char str[200];
                offerToString(o, str);
                printf("%s", str);
            }
        //
        destroyRepo(newList);
    }
    free(s);
}

void displayByType(UI *ui) {
    char *s = malloc(sizeof(char) * 100);
    int surface = 0;
    getString(s, "Give the type: ");
    surface = readInteger("Give the minumum surface(>0): ");
    int order = readInteger("For ascending order press 1, for descending order press 2 ");
    if (order == 2)
        order  = -1;
    if(order != -1 && order != 1)
        printf("%s\n","Invalid input!");
    else {
        Repo *newList = filterByChar(ui->controller, getType, s);
        filterBySurface(newList, surface);
        sortByNumber(newList, getSurface, order);
        //print
        int len = getLen(newList);
        if (len == 0)
            printf("%s\n", "There are no offers");
        else
            for (int i = 0; i < len; i++) {
                Offer *o = getOfferOnPositon(newList, i);
                char str[200];
                offerToString(o, str);
                printf("%s", str);
            }
        //
        destroyRepo(newList);
    }
    free(s);
}

void displayByPrice(UI *ui) {
    int price = 0;
    price = readInteger("Give the price: ");
    Repo *newList;
    newList = filterByNumber(ui->controller, getPrice, price);
    sortByString(newList, getAddress, 1);
    //print()
    int len = getLen(newList);
    if(len == 0)
        printf("%s\n", "There are no offers");
    else
        for(int i = 0; i < len; i++) {
            Offer *o = getOfferOnPositon(newList, i);
            char str[200];
            offerToString(o, str);
            printf("%s", str);
        }
    destroyRepo(newList);
}

void displayBySurface(UI *ui) {
    int surface = 0;
    surface = readInteger("Give the surface: ");
    Repo *newList;
    newList = filterByNumber(ui->controller, getSurface, surface);
    sortByString(newList, getAddress, 1);
    //print()
    int len = getLen(newList);
    if(len == 0)
        printf("%s\n", "There are no offers");
    else
        for(int i = 0; i < len; i++) {
            Offer *o = getOfferOnPositon(newList, i);
            char str[200];
            offerToString(o, str);
            printf("%s", str);
        }
    destroyRepo(newList);
}

void undoUI(UI * ui) {
    if( undo(ui->controller) == 1)
        printf("%s\n","Undo done!");
    else
        printf("%s\n","Undo impossible");
}

void redoUI(UI * ui) {
    if( redo(ui->controller) )
        printf("%s\n", "Redo done!");
    else
        printf("%s\n", "Redo impossible");
}

void displayByTypePrice(UI * ui) {
    char * type = malloc(sizeof(char) * 100);
    getString(type, "Give the type: ");
    int price = readInteger("Give the price: ");
    Repo * newList = filterByChar(ui->controller, getType, type);
    //pret mai mare decat pret dat
    //TODO
    getOffersPriceSmallerThan(newList, price);
    sortByNumber(newList, getPrice, 1);
    //print
    int len = getLen(newList);
    if (len == 0)
        printf("%s\n", "There are no offers");
    else
        for (int i = 0; i < len; i++) {
            Offer *o = getOfferOnPositon(newList, i);
            char str[200];
            offerToString(o, str);
            printf("%s", str);
        }
    destroyRepo(newList);
    free(type);
}

void startUI(UI *ui){
    int command;
    setbuf(stdout, NULL); //ca sa nu mai fac fflush
    while(1){
        printMenu();
        command = readInteger("Give the command: ");
        if(command >= 0 && command <= 11) {
            if (command == 0)
                return;
            if (command == 1)
                addOfferUI(ui);
            if (command == 2)
                printOffers(ui);
            if (command == 3)
                removeOfferUI(ui);
            if (command == 4)
                updateOfferUI(ui);
            if (command == 5)
                displayByAddress(ui);
            if (command == 6)
                displayByType(ui);
            if (command == 7)
                displayBySurface(ui);
            if (command == 8)
                displayByPrice(ui);
            if (command == 9)
                undoUI(ui);
            if (command == 10)
                redoUI(ui);
            if(command == 11)
                displayByTypePrice(ui);
        }
        else
            printf("%s\n", "Invalid command!");
    }

}


