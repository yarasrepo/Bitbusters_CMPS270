#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct SetNode {
    char* element;
    SetNode* next;
};

struct Set {
    SetNode* head;
};

Set* createSet() {
    Set* set = (Set*)malloc(sizeof(Set));
    if (set == NULL) {
        return NULL; 
    }
    set->head = NULL;
    return set;
}

void addToSet(Set* set, const char* element) {
    if (set == NULL || element == NULL) {
        return; 
    }

    if (isInSet(set, element)) {
        printf("element already in set");
        return;
    }

    SetNode* newNode = (SetNode*)malloc(sizeof(SetNode));
    if (newNode == NULL) {
        return; 
    }
    newNode->element = strdup(element);
    newNode->next = set->head;
    set->head = newNode;
}

int isInSet(const Set* set, const char* element) {
    if (set == NULL || element == NULL) {
        return 0; 
    }

    SetNode* current = set->head;
    while (current != NULL) {
        if (strcmp(current->element, element) == 0) {
            return 1; 
        }
        current = current->next;
    }

    return 0; 
}


int getSize(const Set* set) {
    if (set == NULL) {
        return 0;
    }

    int size = 0;
    SetNode* current = set->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}

void printSet(const Set* set){
    if (set == NULL) {
        printf("set is empty");
        return;
    }

    SetNode* current = set->head;
    int count  = 0 ; 
    while (current != NULL) {
        printf("%s\t", current->element);
        count++ ; 

        if (count == 5 ){
            printf("\n") ;
            count = 0 ;
        }
        current = current->next;
    }
    printf("\n");
}

void removeFromSet(Set* set, const char* element) {
    if (set == NULL || element == NULL) {
        return; 
    }

    SetNode* current = set->head;
    SetNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->element, element) == 0) {
            if (prev == NULL) {
                set->head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->element);
            free(current);
            return; 
        }

        prev = current;
        current = current->next;
    }
}


void clearSet(Set* set) {
    if (set == NULL) {
        return;
    }

    SetNode* current = set->head;
    while (current != NULL) {
        SetNode* next = current->next;
        free(current->element);
        free(current);
        current = next;
    }

    set->head = NULL;
}

void destroySet(Set* set) {
    if (set == NULL) {
        return;
    }

    clearSet(set);
    free(set);
}