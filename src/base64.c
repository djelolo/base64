#include "base64.h"


int convertChar(char in, char* out);

const char dic[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
              '+', '/', '='};



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



int decode(char* src, char* dst)
{
  unsigned char buffer;
  int counter = 0;
  char value;

  while (*src != '\0')
  {
    if (convertChar(*src++, &value) != 0)
    {
      return -1;
    }

    switch (counter)
    {
      case 0:
        buffer = value << 2;
        counter++;
        break;
      case 1:
        *dst++ = buffer | (value >> 4);
        buffer = value << 4;
        counter++;
        break;
      case 2:
        *dst++ = buffer | (value >> 2);
        buffer = value << 6;
        counter++;
        break;
      case 3:
        *dst++ = buffer | value;
        counter = 0;
    }
  }
  *dst = '\0';

  if (counter != 0)
    return -1;
}



int convertChar(char in, char* out)
{
  int retCode = 0;

  if ((in >= 'A') && (in <= 'Z'))
    *out = in -'A';
  else if ((in >= 'a') && (in <= 'z'))
    *out = in -'a' + 26;
  else if ((in >= '0') && (in <= '9'))
    *out = in - '0' + 52;
  else if (in == '+')
    *out = 62;
  else if (in =='\\')
    *out = 63;
  else if (in == '=')
    *out = 0;
  else {
    retCode = -1;
  }

    return retCode;
}
