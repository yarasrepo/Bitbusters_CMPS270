#ifndef CHARMAP_H
#define CHARMAP_H

#include "set.h"

typedef struct {
    Set* map[26]; 
} CharMap;

// Initialize a map
CharMap* initializeCharMap();

int idxOfKey(char key);

void addToCharMap(CharMap* charMap, char key, const char* value);

int isInCharMap(const CharMap* charMap, char key, const char* value);

void printCharMap(CharMap* charMap);

void printKeyValue(CharMap* charMap);

void destroyCharMap(CharMap* charMap);

#endif
