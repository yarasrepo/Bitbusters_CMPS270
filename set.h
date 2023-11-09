#ifndef SET_H
#define SET_H

#include <stdbool.h>

typedef struct SetNode SetNode;
typedef struct Set Set;

Set* createSet();

void addToSet(Set* set, const char* element);

int isInSet(const Set* set, const char* element);

int getSize(const Set* set);

void printSet(const Set* set);

char** SettoArr(const Set* set);
void freeWordArr(char** wordArr, int size);

void removeFromSet(Set* set, const char* element);

void clearSet(Set* set);

void destroySet(Set* set);

#endif
