#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include "base64.h"

const char * argp_program_version = "0.0.1";
static char doc[] = "base64 encoding and decoding utility program";
static struct argp_option options[] = {
//  {"verbose", 'v', 0, 0, "Produce verbose output\0", 0},
//  {"in", 'i', "FILE", 0, "Produce verbose output\0", 0},
//  {"verbose", 'v', 0, 0, "Produce verbose output\0", 0},
  {"encode", 'e', 0, 0, "Encode input in base64", 0},
  {"decode", 'd', 0, 0, "Decode input from base64", 0},
//   {"input", 'i', 0, 0, "Input file"}
};

struct arguments
{
//  char *args[2];
//  int verbose;
  int encode;
  int decode;
};

/* A description of the arguments we accept. */
static char args_doc[] = "ARG1 ARG2";

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
    // case 'v':
    //   arguments->verbose = 1;
    //   break;
    // case 'o':
    //   arguments->output_file = arg;
    //   break;

    // case ARGP_KEY_ARG:
    //   if (state->arg_num >= 2)
    //     /* Too many arguments. */
    //     argp_usage (state);
    //
    //   arguments->args[state->arg_num] = arg;
    //
    //   break;
    //
    // case ARGP_KEY_END:
    //   if (state->arg_num < 2)
    //     /* Not enough arguments. */
    //     argp_usage (state);
    //   break;
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
