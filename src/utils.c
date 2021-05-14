#include "utils.h"



/*!
   \brief Read from input stream into buffer with buffer size control
   \param buffer Destination buffer
   \param size Buffer size
   \param stream Input stream
   \return Size of read string
*/
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
