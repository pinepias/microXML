#include "microXML.h"

MicroXML *__MICRO__INIT__()
{
    MicroXML *__micro__ = (MicroXML *)malloc(sizeof(MicroXML));

    if (!__micro__)
    {
        ERROR_MEMORY
        return NULL;
    }

    __micro__->prev = NULL;
    __micro__->next = NULL;
    __micro__->parent = NULL;
    __micro__->child = NULL;

    __micro__->initPos = 0;
    __micro__->finalPos = 0;
    __micro__->finalElement = 0;

    __micro__->type = NULL;
    __micro__->element = NULL;
    __micro__->source = NULL;

    return __micro__;
}

MicroXML *__MICRO_NEXT__(MicroXML *__micro__)
{
    bool __in__tag__ = false;
    int __tag__start__ = -1;
    int __tag__end__ = -1;

    MicroXML *__next__ = NULL;

    
    for (int i = __micro__->initPos; i < strlen(__micro__->source); ++i)
    {
        if (__micro__->source[i] == '<' && __micro__->source[__min(i + 1, strlen(__micro__->source))] != '/'
        && MicroCount(MicroSubtr(__micro__->source, 0, i), '\'') % 2 == 0
        && MicroCount(MicroSubtr(__micro__->source, 0, i), '\"') % 2 == 0)
        {
            __in__tag__ = true;
            __tag__start__ = i;
        }

        if ((__micro__->source[i] == '>' || __micro__->source[i] == ' ')
        && MicroCount(MicroSubtr(__micro__->source, 0, i), '\'') % 2 == 0
        && MicroCount(MicroSubtr(__micro__->source, 0, i), '\"') % 2 == 0)
        {
            if (__in__tag__)
            {
                __in__tag__ = false;
                __tag__end__ = i;

                char *type = (char *)MicroSubtr(__micro__->source, __tag__start__ + 1, __tag__end__ - __tag__start__ - 1);
                __micro__->type = type;

                __micro__->initPos = __tag__start__;
                __micro__->finalPos = __tag__end__;

                if (__micro__->source[i] == ' ')
                {
                    int j = i + 1;
                    while (__micro__->source[j] != '>' && j < strlen(__micro__->source))
                    {
                        j++;
                    }

                    
                    int __final__attributes__ = j;
                    int __init__ = 0;

                    const char *__atribute__ = MicroRemoveChr(MicroSubtr(__micro__->source, __tag__start__ + strlen(type) + 1, __final__attributes__ - __tag__start__ - strlen(type) - 1), ' ');
                    
                    for (int i = 0; i < strlen(__atribute__); ++i)
                    {
                        if (__atribute__[i] == '=')
                        {
                            printf("%s\n", MicroSubtr(__atribute__, __init__, i));
                            __init__ = i+1;
                        }
                    }

                }


                __tag__start__ = -1;
                __tag__end__ = -1;    

                

            }
        }
    }


    return NULL;    
}

    



MicroXML *MicroParse(const char *source)
{
    MicroXML *root = __MICRO__INIT__();

    root->source = (char *)source;
    return root;
}

const char *MicroSubtr(const char *str, int pos, int len)
{
    char *temp = (char *)malloc(len + 1);

    if (temp == NULL)
    {
        ERROR_MEMORY
        return NULL;
    }

    for (int i = 0; i < len; ++i)
    {
        temp[i] = str[pos + i];
    }

    temp[len] = '\0';
    return temp;
}

const char *MicroRemoveChr(const char *str, char chr) {

    char *otherStr;

    for (int i = 0; str[i] != '\0'; ++i) 
    {
        while (str[i] == ' ') 
        {
            for (int j = i; str[j] != '\0'; ++j) 
            {
                otherStr[j] = str[j + 1];
            }
        }
    }

    return otherStr;
}

int MicroCount(const char *str, char chr)
{
    int counter = 0;

    while (*str != '\0') 
    {
        if (*str == chr) 
        {
            counter++;
        }

        str++;
    }

    return counter;
}

int MicroStrCount(const char *str, const char *sub)
{
    int count = 0;
    size_t substr_len = strlen(sub);

    while (*str) 
    {
        if (strncmp(str, sub, substr_len) == 0) 
        {
            count++;
            str += substr_len;
        }
        else 
        {
            str++;
        }
    }

    return count;
}

int MicroGetSub(const char *str, const char *sub, int index) 
{
    const char *pos = str;
    int count = 0;
    index += 1;

    while ((pos = strstr(pos, sub)) != NULL) {
        if (++count == index) {
            return pos - str;
        }
        pos += strlen(sub);
    }

    return -1; // Retorna -1 se não encontrar a substring na posição especificada
}

int MicroSubpos(const char *str, const char *sub) 
{
    const char *pos = strstr(str, sub);
    return (pos != NULL) ? pos - str : -1;
}

MicroXML *MicroParseDocument(const char *filePath)
{
    FILE *file = fopen(filePath, "r");
    MicroXML *root = __MICRO__INIT__();

    if (!file)
    {
        ERROR_MEMORY
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(fileSize + 1);

    if (!content)
    {
        ERROR_MEMORY
        fclose(file);
        return NULL;
    }

    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';

    fclose(file);
    root->source = content;

    MicroXML *next = __MICRO_NEXT__(root);


    return root;

}