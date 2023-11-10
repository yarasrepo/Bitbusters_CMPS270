#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "charmap.h"
const char name[]= "spellmaster";

char* Mode(char lastChar, CharMap* charMap,char* mode){
    int max=0;
    char* word=NULL;
    int wordSetSize= getSize(charMap->map[idxOfKey(lastChar)]);
    char** options= SettoArr(charMap->map[idxOfKey(lastChar)]);
    int minSetSize = size_of(options)/size_of(options[0]);
    
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
char *medium(char lastletter, CharMap *charmap)
{
    char *words = NULL;
    int size = getSize(charmap->map[idxOfKey(lastletter)]);

    char **options = settoarr(charmap->map[idxOfKey(lastletter)]);
    int *wordfrequencies = malloc(size * sizeof(int));


    for (int i = 0; i < size; i++)
    {
        char s = options[i][strlen(options[i]) - 1];
        int setsize = getSize(charmap->map[idxOfKey(s)]);// getting the number of words for each letter 
        wordfrequencies[i] = setsize; // we're filling the array of the number of words of each letter in map
    }
    qsort(wordfrequencies, size, sizeof(int), compare);
    int medium = wordfrequencies[sizeof(wordfrequencies) / 2];// getting the medium frequency then getting the words at it 
    words = malloc(strlen(options[medium] + 1) * sizeof(char));
    strcpy(words, options[medium]);
    freeWordArr(options , wordfrequencies);
    return words;
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
