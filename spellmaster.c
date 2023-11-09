#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "charmap.h"
#include "set.h"



const char name[]= "spellmaster";

char* easyMode(char lastChar, CharMap* charMap){
    int max=0;
    char* word=NULL;
    int size= getSize(charMap->map[idxOfKey(lastChar)]);
    char** options= SettoArr(charMap->map[idxOfKey(lastChar)]);

    for (int i=0; i<size; i++){
        char s= options[i][strlen(options[i]) - 1];
        int setSize= getSize(charMap->map[idxOfKey(s)]);

        if (setSize > max){
            max= setSize;
            word = malloc((strlen(options[i]) + 1) * sizeof(char));
            strcpy(word, options[i]);
        }
    }
    freeWordArr(options, size);

    return word;
}