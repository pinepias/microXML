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

    return __micro__;
}

MicroXML *__MICRO_NEXT__(MicroXML *__micro__)
{

    if (__micro__->prev == NULL)
    {
        int __init__ = -1;
        int __final__ = -1;
        
        int __name__init__ = -1;
        int __name__final__ = -1;

    
        for (int i = 0; i < strlen(__micro__->source); ++i)
        {
            if (__micro__->source[i] == ' ' && __name__final__ == -1)
            {
                __name__final__ = i-1;
            }

            if (__micro__->source[i] == '<' && __init__ == -1)
            {
                __init__ = i;
                __name__init__ = __min(i + 1, strlen(__micro__->source));
            }

            if (__micro__->source[i] == '>' && __final__ == -1 && 
            (MicroCount(MicroSubtr(__micro__->source, __init__, i), '\"') % 2 == 0))
            {
                __final__ = i;
            }
        }

        const char *type = MicroSubtr(__micro__->source, __name__init__, __name__final__);
        __micro__->type = type;
        __micro__->element = MicroSubtr(__micro__->source, __init__, __final__);
        __micro__->initPos = __init__;
        __micro__->finalPos = __final__;
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
    len = len + 1;
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

int MicroCount(const char *str, char chr)
{
    int counter = 0;

    while (*str != '\0') {

        if (*str == chr) {
            counter++;
        }

        str++;
    }

    return counter;
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