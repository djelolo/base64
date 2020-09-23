#include <stdio.h>
#include <stdlib.h>


char dic[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
              '+', '/', '='};


void encode(char* src, char* dst);


int main(int argc, char const *argv[]) {
  char inBuf[100], outBuf[200] = {0};
  sprintf(inBuf, "tester");

  encode(inBuf, outBuf);

  printf("%s\n%s\n", inBuf, outBuf);

  return 0;
}






void encode(char* src, char* dst)
{
  int counter = 0;
  unsigned char buffer;

  while (*src != '\0')
  {
    switch (counter)
    {
      case 0:
        *dst++ = dic[*src >> 2];
        buffer = (*src++ << 4) & 0x30;
        counter++;
        break;
      case 1:
        *dst++ = dic[(*src >> 4) | buffer];
        buffer = (*src++ << 2) & 0x3C;
        counter++;
        break;
      case 2:
        *dst++ = dic[(*src >> 6) | buffer];
        *dst++ = dic[*src++ & 0x3F];
        counter = 0;
        break;
    }
  }

  switch (counter)
  {
    case 0:
      break;
    case 1:
      *dst++ = dic[buffer];
      *dst++ = '=';
      *dst++ = '=';
      break;
    case 2:
      *dst++ = dic[buffer];
      *dst++ = '=';
      break;
  }
}
