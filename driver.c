#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "spellmaster.h"

void playGame(char p1Name[], char p2Name[], CharMap *charMap);
void fileReading(CharMap *charMap);
void playWithBot(char p1Name[], CharMap *charMap, char mode[]);
int main()
{
    CharMap *charMap = initializeCharMap();

    fileReading(charMap);

    char p1Name[30];
    char p2Name[30];
    char choice[30];
    char mode[30];

    printf("Welcome to spellmaster! would you like to play against a bot or a player?\n ");
    scanf("%s", &choice);

    printf("Player 1: ");
    scanf("%s", &p1Name);

    if (strcasecmp(choice, "player") == 0)
    {
        printf("Player 2: ");
        scanf("%s", &p2Name);
        printf("Welcome, %s and %s!!\n", p1Name, p2Name);
        playGame(p1Name, p2Name, charMap);
    }
    else
    {
        printf("What difficulty mode would you like to play on? (easy, medium, hard)\n\n");
        scanf("%s", &mode);
        playWithBot(p1Name, charMap, mode);
    }

    destroyCharMap(charMap);
    system("pause");
    return 0;
}

void playGame(char p1Name[], char p2Name[], CharMap *charMap)
{
    srand(time(NULL));
    printf("tossing coin...\n");
    int coinToss = rand() % 2;
    char word[100];
    printf("Player %d starts!\n", coinToss + 1);

    Set *usedWords = createSet();

    int i = coinToss;
    char lastword[1000];

    while (i < 1000)
    {

        printf("Player %d choose a word from the list: ", i % 2 + 1);
        scanf("%s", word);

        char firstChar = word[0];

        // checking if the word is in the list
        if (isInCharMap(charMap, firstChar, word) == 0)
        {
            printf("Word is not in the list! Player %d wins!\n", (i + 1) % 2 + 1);
            return;
        }

        // checking if the word is already used
        else if (isInSet(usedWords, word) == 1 && i != coinToss)
        {
            printf("Word already used! Player %d wins!\n", (i + 1) % 2 + 1);
            return;
        }

        // checking if the word starts with the same character that the last word ends in
        else if (lastword[strlen(lastword) - 1] != word[0] && i != coinToss)
        {
            printf("The word does not start with the last letter of the previous word! Player %d wins\n", (i + 1) % 2 + 1);
            return;
        }
        addToSet(usedWords, word);

        char lastChar = word[strlen(word) - 1];
        Set *options = charMap->map[idxOfKey(lastChar)];

        if (getSize(options) == 0)
        {
            printf("No more words to choose from! Player %d wins\n", i % 2 + 1);
            return;
        }
        removeFromSet(charMap->map[idxOfKey(word[0])], word);
        // printf("%s\n", word);
        //  printf("%d\n", getSize(charMap->map[idxOfKey(word[0])]));
        //     printSet(charMap->map[idxOfKey(word[0])]);
        // printf("%d\n", getSize(charMap->map[idxOfKey(word[0])]));

        printf("Good Spell!!");
        strcpy(lastword, word);
        i++;
    }
}


void playWithBot(char p1Name[], CharMap *charMap, char mode[])
{
    srand(time(NULL));
    printf("tossing coin...\n");
    int coinToss = rand() % 2;
    char word[100];
    
    if (coinToss== 0){
        printf("%s starts!\n", p1Name);
    }
    else{
        printf("Spellmaster starts!\n");
    }

    Set *usedWords = createSet();

    int i = coinToss;
    char lastword[1000];
    
    while (i < 1000  )
    {
        if ((i%2)+1==  1){

            printf("%s choose a word from the list: ", p1Name);
            scanf("%s", word);

            char firstChar = word[0];

            // checking if the word is in the list
            if (isInCharMap(charMap, firstChar, word) == 0)
            {
                printf("Word is not in the list! spellMaster wins!\n");
                return;
            }

            // checking if the word is already used
            else if (isInSet(usedWords, word) == 1 && i != coinToss)
            {
                printf("Word already used! spellMaster wins!\n");
                return;
            }

            // checking if the word starts with the same character that the last word ends in
            else if (lastword[strlen(lastword) - 1] != word[0] && i != coinToss)
            {
                printf("The word does not start with the last letter of the previous word! SpellMaster wins\n");
                return;
            }
        }
        else {
            if (i==1){
                strcpy(word,Mode('!',charMap,mode));
            }
            else {
                char lastChar = lastword[strlen(lastword)-1];
                strcpy(word,Mode(lastChar,charMap,mode));
            }

            printf("Spellmaster chose %s\n", word);
        }

        char lastChar = word[strlen(word) - 1];
        Set *options = charMap->map[idxOfKey(lastChar)];

        if (getSize(options) == 0)
        {
            printf("No more words to choose from! %s wins\n", ((i % 2) + 1 != 1) ? "Spellmaster" : p1Name);
            return;
        }

        removeFromSet(charMap->map[idxOfKey(word[0])], word);

        addToSet(usedWords, word);

        if (strcasecmp(mode, "easy") == 0){
            printf("The used words so far are: ");
            printSet(usedWords);
        }

        if ((i%2)+1==  1){
            printf("Good Spell!!\n");
        }
        
        strcpy(lastword, word);
        i++;
    }
}


void fileReading(CharMap *charMap)
{
    char fileName[100];

    printf("Enter the file name: ");
    scanf("%s", &fileName);

    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Failed to open the file '%s'.\n", fileName);
        return;
    }

    printf("File '%s' opened successfully.\n", fileName);

    char word[100];
    Set *wordSet = createSet();
    int sizeFirstLine = fscanf(file, "%d", &sizeFirstLine);
    while (fscanf(file, " %99s", word) == 1)
    {
        addToSet(wordSet, word);
        addToCharMap(charMap, word[0], word);
    }

    fclose(file);

    printf("Words in the set:\n");
    printSet(wordSet);
    destroySet(wordSet);
}