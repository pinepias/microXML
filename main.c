#include "microXML.h"

int main()
{
    MicroXML *xml = MicroParseDocument("test.xml");
    printf("%s\n", xml->element);

    return 0;
}