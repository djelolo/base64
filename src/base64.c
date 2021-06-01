#include "base64.h"


int convertChar(char in, char* out);


//! Dictionary for base64 encoding/decoding
const char dic[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
              '+', '/', '='};



/*!
   \brief Encode input char into base64
   \param src Source string to convert
   \param dst Encoded string
*/
void encode(char* src, int len, char* dst)
{
  int counter = 0;
  unsigned char buffer;

  for (int i=0 ; i<len ; i++)
  {
    switch (counter)
    {
      case 0:
        *dst++ = dic[(*src >> 2) & 0x3F];
        buffer = (*src++ << 4) & 0x30;
        counter++;
        break;
      case 1:
        *dst++ = dic[((*src >> 4) & 0x0F) | buffer];
        buffer = (*src++ << 2) & 0x3C;
        counter++;
        break;
      case 2:
        *dst++ = dic[((*src >> 6) & 0x03) | buffer];
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


/*!
   \brief Decode input char from base64
   \param src Source string to decode
   \param dst Decoded string
*/
int decode(char* src, char* dst)
{
    unsigned char buffer;
    int counter = 0, length = 0;
    char value;

    while (*src != '\0')
    {
        // Ignore newlines
        if (*src == '\n') {
            src++;
            continue;
        }

        if (convertChar(*src++, &value) != 0)
            return -1;

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
                length++;
                break;
            case 2:
                *dst++ = buffer | (value >> 2);
                buffer = value << 6;
                counter++;
                length++;
                break;
            case 3:
                *dst++ = buffer | value;
                counter = 0;
                length++;
                break;
        }
  }

  if (counter != 0) {
      return -1;
  }
  else
    return length;
}


/*!
   \brief Convert hex value into its base64 equivalent accordint to dictionary
   \param in char to convert (from 0 to 64)
   \param out converted value
   \return -1 if input out of range. 0 otherwise.
*/
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
    else if (in =='/')
        *out = 63;
    else if (in == '=')
        *out = 0;
    else
        retCode = -1;

    return retCode;
}
