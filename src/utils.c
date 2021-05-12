#include "utils.h"




int readFile(char* buffer, int size, FILE *stream)
{
    int i = 0;
    int c;

    memset(buffer, '\0', size);

    while ((--size > 0) && ((c=fgetc(stream)) != EOF)) {
        buffer[i++] = c;
    }

    buffer[i+1] = '\0';
    return i;
}
