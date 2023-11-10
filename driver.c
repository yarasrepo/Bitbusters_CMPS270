#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "charmap.h"
#include "spellmaster.c"

void playGame(char p1Name[], char p2Name[], CharMap* charMap);
void fileReading(CharMap* charMap);

int main()
{
    CharMap* charMap= initializeCharMap();

    fileReading(charMap);

    char p1Name[30];
    char p2Name[30];

    printf("Player 1: ");
    scanf("%s", &p1Name);

    printf("Player 2: ");
    scanf("%s", &p2Name);

    printf("Welcome, %s and %s!!\n", p1Name, p2Name);

    playGame(p1Name, p2Name, charMap);

    destroyCharMap(charMap);
    system("pause");
    return 0;
}

void playGame(char p1Name[], char p2Name[], CharMap* charMap){
    srand(time(NULL));
    printf("tossing coin...\n");
    int coinToss = rand() % 2;
    char word[100];
    printf("Player %d starts!\n", coinToss+1);

    Set* usedWords= createSet();

    int i=coinToss;
    char lastword[1000];
    
    while (i< 1000){
        
        printf("Player %d choose a word from the list: ", i%2 +1);
        scanf("%s", word);

        char firstChar= word[0];

        if (isInCharMap(charMap, firstChar, word)==0  && i!=coinToss){
            printf("Word is not in the list! Player %d wins!\n",(i+1)%2 +1);
            return;
        }

        else if (isInSet(usedWords, word) == 1 && i!=coinToss){
            printf("Word already used! Player %d wins!\n", (i+1)%2 +1);
            return;
        }

        else if (lastword[strlen(lastword) - 1] != word[0] && i!=coinToss){
            printf("The word does not start with the last letter of the previous word! Player %d wins\n", (i+1)%2 +1);
            return;
        }
        addToSet(usedWords, word);

        char lastChar = word[strlen(word) - 1];

        if (charMap->map[idxOfKey(lastChar)] == NULL ){
            printf("No more words to choose from! Player %d wins\n", i%2+1);
            return;
        }

        printf("%s\n", word);
        printf("%d\n", getSize(charMap->map[idxOfKey(lastChar)]));
        removeFromSet(charMap->map[idxOfKey(lastChar)], word);
        printSet(charMap->map[idxOfKey(lastChar)]);
        printf("%d\n", getSize(charMap->map[idxOfKey(lastChar)]));

        printf("Good Spell!!");
        strcpy(lastword, word);
        i++;
    }
}

void fileReading(CharMap* charMap){
    char fileName[100]; 

    printf("Enter the file name: ");
    scanf("%s", &fileName);

    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Failed to open the file '%s'.\n", fileName);
        return;
    }

    printf("File '%s' opened successfully.\n", fileName);

    char word[100];
    Set* wordSet=createSet();
    int sizeFirstLine= fscanf(file, "%d", &sizeFirstLine);
    while (fscanf(file, " %99s", word) == 1) {
        addToSet(wordSet, word);
        addToCharMap(charMap , word[0] , word);
    }

    fclose(file);

    printf("Words in the set:\n");
    printSet(wordSet);
    destroySet(wordSet);
}
