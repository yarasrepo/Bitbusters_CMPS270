#ifndef SPELLMASTER_H
#define SPELLMASTER_H
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "charmap.h"
char* Mode(char lastChar, CharMap* charMap,char* mode);
char* ModeHelper (CharMap* charMap);
char *medium(char lastletter, CharMap *charmap);
int compare(const void *a, const void *b);
