#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "charmap.h"

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
