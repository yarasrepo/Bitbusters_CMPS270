#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spellmaster.h"


const char name[]= "spellmaster";

char* Mode(char lastChar, CharMap* charMap,char* mode){
     if(lastChar == '!'){
        return ModeHelper(charMap);
    }
    int max=0;
    char* word=NULL;
    int wordSetSize= getSize(charMap->map[idxOfKey(lastChar)]);
    char** options= SettoArr(charMap->map[idxOfKey(lastChar)]);
    int minSetSize = sizeof(options)/sizeof(options[0]);
    
    for (int i=0; i<wordSetSize; i++){
        char s= options[i][strlen(options[i]) - 1];
        int setSize= getSize(charMap->map[idxOfKey(s)]);
        if(strcmp(mode,"easy")==0){
        if (setSize > max){
            max= setSize;
            word = malloc((strlen(options[i]) + 1) * sizeof(char));
            strcpy(word, options[i]);
        }
    }
       else if(strcmp(mode,"hard")==0){
        if(setSize<minSetSize){
             minSetSize=setSize;
            word = malloc((strlen(options[i])+1)*sizeof(char));
            strcpy(word, options[i]);
        }}
       
    freeWordArr(options, wordSetSize);

    return word;
}}

char* ModeHelper (CharMap* charMap){
    int max=0;
    int s;
    int idx;
    for(int i=0; i< 26; i++){
        s= getSize(charMap->map[i]);

        if (s > max){
            max= s;
            idx=i;
        }
    }
    
    // if (idx >= 0 && idx < 26) 
    char lastchar= (char)(idx + 'a');

    for (int i=0; i< 26; i++){
        char** wordsInSet= SettoArr(charMap->map[i]);
        for (int j=0; j< getSize(charMap->map[i]); j++){
            if (wordsInSet[j][strlen(wordsInSet[j])-1] == lastchar)
                return wordsInSet[j];
        }
    }

    return NULL;
}

char *medium(char lastletter, CharMap *charmap)
{
    char *words = NULL;
    int size = getSize(charmap->map[idxofkey(lastletter)]);

    char **options = settoarr(charmap->map[idxofkey(lastletter)]);
    int wordfrequencies[] = size;

    for (int i = 0; i < size; i++)
    {
        char s = options[i][strlen(options[i]) - 1];
        int setsize = getSize(charmap->map[idxofkey(s)]);// getting the number of words for each letter 
        wordfrequencies[i] = setsize; // we're filling the array of the number of words of each letter in map
    }
    qsort(wordfrequencies, size, sizeof(int), compare);
    int medium = wordfrequencies[sizeof(wordfrequencies) / 2];// getting the medium frequency then getting the words at it 
    words = malloc(strlen(options[medium] + 1) * sizeof(char));
    strcopy(words, options[medium]);
    return words;
    free(options);
}
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
