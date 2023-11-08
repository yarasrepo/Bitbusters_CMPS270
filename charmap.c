#include "charmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CharMap* initializeCharMap() {
    CharMap* charMap = (CharMap*)malloc(sizeof(CharMap));
    if (charMap == NULL) {
        return NULL; 
    }

    for (int i = 0; i < 26; i++) {
        charMap->map[i] = createSet();
    }

    return charMap;
}

int idxOfKey(char key){
    if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
        if (key >= 'A' && key <= 'Z') {
            key = key - 'A' + 'a';
        }
        return key - 'a';
    }

    return -1;
}

void addToCharMap(CharMap* charMap, char key, const char* value) {
    if (charMap == NULL) {
        charMap = initializeCharMap();
        if (charMap == NULL) {
            printf("Failed to allocate memory for CharMap.\n");
            return;
        }
    }
    
    addToSet(charMap->map[idxOfKey(key)], value);
}



int isInCharMap(const CharMap* charMap, char key, const char* value) {
    
        return isInSet(charMap->map[idxOfKey(key)], value); 
    
    return 0; 
}

void printCharMap(CharMap* charMap){
    if (charMap == NULL){
        printf("No elements found!");
        return;
    }
    
    for (int i=0; i< 26; i++){
        printSet(charMap->map[i]);
    }
}

void printKeyValue(CharMap* charMap) {
    if (charMap == NULL) {
        printf("No elements found!\n");
        return;
    }

    for (int i=0; i<26; i++) {
        printf("%c: ", i+'a');

        if (charMap->map[i] != NULL ) {
            printSet(charMap->map[i]); 
        }

    }
}

void destroyCharMap(CharMap* charMap){
    for (int i = 0; i < 26; i++) {
        destroySet(charMap->map[i]); 
    }
}