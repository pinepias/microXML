#ifndef _MICRO_H_
#define _MICRO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct MicroXML
{
    struct MicroXML *prev;
    struct MicroXML *next;
    struct MicroXML *parent;
    struct MicroXML *child;

    int initPos;
    int finalPos;

    char *type;
    char *element;
    char *source;

} MicroXML;

//Erros

#define ERROR_MEMORY printf("(MicroXML) Error: allocating memory.\n");

MicroXML *__MICRO_NEXT__(MicroXML *__prev__);
MicroXML *__MICRO__INIT__();


const char *MicroSubtr(const char *str, int init, int final);
int MicroSubpos(const char *str, const char *sub);
int MicroCount(const char *str, char chr);

MicroXML *MicroParse(const char *source);
MicroXML *MicroParseDocument(const char *filePath);

#endif