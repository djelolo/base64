#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

const char * argp_program_version = "0.0.1";
static char doc[] = "base64 encoding and decoding utility program";
static struct argp_option options[] = {
  {"encode", 'e', 0, 0, "Encode input in base64", 0},
  {"decode", 'd', 0, 0, "Decode input from base64", 0},
};

struct arguments
{
  int encode;
  int decode;
};

/* Parse a single option. */
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'e':
      arguments->encode = 1;
      break;
    case 'd':
      arguments->decode = 1;
      break;
    case ARGP_KEY_SUCCESS:
      if ((arguments->encode == 1) && (arguments->decode == 1))
        argp_error(state, "Encode and decode options shall not be used simultaneously");
      else if ((arguments->encode == 0) && (arguments->decode == 0))
        argp_error(state, "Please specify one of the options encode or decode");
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}


static struct argp argp = {options, parse_opt, 0, doc, 0, 0, 0 };


const char dic[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
              '+', '/', '='};


void encode(char* src, char* dst);
void decode(char* src, char* dst);
int convertChar(char in, char* out);

// MAIN
int main(int argc, char *argv[]) {
  struct arguments arguments;
  arguments.encode = 0;
  arguments.decode = 0;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

char inBuf[100], outBuf[200] = {0};


  if (arguments.encode)
  {
    sprintf(inBuf, "tester");
    encode(inBuf, outBuf);
    printf("%s\n%s\n", inBuf, outBuf);
  }

  if (arguments.decode)
  {
    sprintf(inBuf, "Q2xlbWVudA==");
    decode(inBuf, outBuf);
    printf("%s\n%s\n", inBuf, outBuf);
  }


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



void decode(char* src, char* dst)
{
  unsigned char buffer;
  int counter = 0;
  char value;

  while (*src != '\0')
  {
    if (convertChar(*src++, &value) != 0)
    {
      printf("Error\n");
      return;
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
    printf("Error\n");
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
