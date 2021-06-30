#include "base64.h"

#include <ctype.h>


//! Return code for character conversion
typedef enum {
    ERROR = -1,     //!< Input char is no part of base64 set
    OK,             //!< Conversion ok
    SIGN_EQUAL      //!< Input char is equal sign (filling characte)
} conv_ret_code;




conv_ret_code convertChar(char in, char* out);
char checkBinaryChar(char c);

//! Flag used to know if one non printable character has been found when decoding
static int nonPrintableCharFound = 0;

//! Dictionary for base64 encoding/decoding
const char dic[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
              '+', '/', '='};



/*!
   \brief Encode input char into base64
   \param src Source string to convert
   \param len Input buffer length
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
    conv_ret_code convResult;

    while (*src != '\0')
    {
        // Ignore newlines
        if (*src == '\n') {
            src++;
            continue;
        }

        if ((convResult = convertChar(*src++, &value)) < 0)
            return -1;

        switch (counter)
        {
            case 0:
                buffer = value << 2;
                counter++;
                break;
            case 1:
                *dst++ = checkBinaryChar(buffer | (value >> 4));
                buffer = value << 4;
                counter++;
                length++;
                break;
            case 2:
                if (convResult != SIGN_EQUAL) {
                    *dst++ = checkBinaryChar(buffer | (value >> 2));
                    buffer = value << 6;
                    length++;
                }
                counter++;
                break;
            case 3:
                if (convResult != SIGN_EQUAL) {
                    *dst++ = checkBinaryChar(buffer | value);
                    length++;
                }
                counter = 0;
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
   \brief Return true if decoded file contains non printable characters
   \return 1 if file is type binary
*/
int isBinary()
{
    return nonPrintableCharFound;
}

/*!
   \brief Convert hex value into its base64 equivalent accordint to dictionary
   \param in char to convert (from 0 to 64)
   \param out converted value
   \return -1 if input out of range. 0 otherwise.
*/
conv_ret_code convertChar(char in, char* out)
{
    conv_ret_code retCode = OK;

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
    else if (in == '=') {
        *out = 0;
        retCode = SIGN_EQUAL;
    }
    else
        retCode = ERROR;

    return retCode;
}


/*!
   \brief Check and store if char is printable (internal variable \p nonPrintableCharFound updated)
   \param c character to check
   \return checked character (unchanged)
*/
char checkBinaryChar(char c)
{
    nonPrintableCharFound = nonPrintableCharFound || (!isprint((int) c));
    return c;
}
