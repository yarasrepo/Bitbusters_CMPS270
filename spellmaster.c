#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spellmaster.h"

const char name[] = "spellmaster";

char *Mode(char lastChar, CharMap *charMap, char *mode)
{
    int idx =0;
  

    if (strcasecmp(mode, "medium") == 0)
    {
        return medium(lastChar, charMap);
    }

   
    char *wordT = NULL;
    int wordSetSize = getSize(charMap->map[idxOfKey(lastChar)]);
    char **options = SettoArr(charMap->map[idxOfKey(lastChar)]);
    int minSetSize = 0;
     int max = wordSetSize ;
    for (int i = 0; i < wordSetSize; i++)
    {
        char s = options[i][strlen(options[i]) - 1];
        int setSize = getSize(charMap->map[idxOfKey(s)]);
        if (strcmp(mode, "easy")== 0 || lastChar == '!')
        {
            if (setSize > max)
            {
                max = setSize;
                idx =i;
               
            }
            wordT = malloc((strlen(options[idxOfKey(lastChar)]) + 1) * sizeof(char));
                strcpy(wordT, options[idx]);

        }
        else if (strcmp(mode, "hard") == 0)
        {
            if (setSize < minSetSize)
            {
                minSetSize = setSize;
                idx-i;
                //continue;
               
            }
             wordT = malloc((strlen(options[lastChar]) + 1) * sizeof(char));
                
                strcpy(wordT, options[idx]);
        }
    }
   freeWordArr(options, wordSetSize);
     
    return wordT;
}

char *ModeHelper(CharMap *charMap)
{
    int max = 0;
    int s;
    int idx;
    for (int i = 0; i < 26; i++)
    {
        s = getSize(charMap->map[i]);

        if (s > max)
        {
            max = s;
            idx = i;
        }
    }

    // if (idx >= 0 && idx < 26)
    char lastchar = (char)(idx + 'a');

    for (int i = 0; i < 26; i++)
    {
        char **wordsInSet = SettoArr(charMap->map[i]);
        for (int j = 0; j < getSize(charMap->map[i]); j++)
        {
            if (wordsInSet[j][strlen(wordsInSet[j]) - 1] == lastchar)
                return wordsInSet[j];
        }
    }

    return NULL;
}

char *medium(char lastletter, CharMap *charmap)
{
    char *words = NULL;
    int size = getSize(charmap->map[idxOfKey(lastletter)]);

    char **options = SettoArr(charmap->map[idxOfKey(lastletter)]);
    int wordfrequencies[size];

    for (int i = 0; i < size; i++)
    {
        char s = options[i][strlen(options[i]) - 1];
        int setsize = getSize(charmap->map[idxOfKey(s)]); // getting the number of words for each letter
        wordfrequencies[i] = setsize;                     // we're filling the array of the number of words of each letter in map
    }
    qsort(wordfrequencies, size, sizeof(int), compare);
    int medium = wordfrequencies[sizeof(wordfrequencies) / 2]; // getting the medium frequency then getting the words at it
    words = malloc(strlen(options[medium] + 1) * sizeof(char));
    strcpy(words, options[medium]);
    return words;
    free(options);
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
