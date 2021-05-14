#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include "base64.h"
#include "utils.h"


#define BUFFER_SIZE 12  //<! Must be multiple of 3

//! Program version
const char * argp_program_version = "0.1";

//! Program brief description
static char doc[] = "base64 encoding and decoding utility program";

//! Available options
static struct argp_option options[] = {
  {"in", 'i', "FILE", 0, "Use file as input", 0},
  {"out", 'o', "FILE", 0, "Write output to file", 0},
  {"encode", 'e', 0, 0, "Encode input in base64", 0},
  {"decode", 'd', 0, 0, "Decode input from base64", 0},
};

//! Structure for arguments reading
struct arguments
{
  int encode;
  int decode;
  char *output_file;
  char *input_file;
};

/* A description of the arguments we accept. */
// static char args_doc[] = "input string";

/*!
   \brief Parse options
   \param key Given option
   \param arg Value passed to option
   \param argp_state Structure to store options
   \return Error code (0 if OK)
*/
static error_t parse_opt(int key, char *arg, struct argp_state *state)
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
    case 'o':
      arguments->output_file = arg;
      break;
    case 'i':
      arguments->input_file = arg;
      break;
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



/*!
   \brief Main
   \param argc Arguments count
   \param argv Arguments values
   \return Return code (0 = OK)
*/
int main(int argc, char *argv[]) {
    struct arguments arguments;
    arguments.encode = 0;
    arguments.decode = 0;
    arguments.output_file = "";
    arguments.input_file = "";

    // Parse arguments
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // Initialize values
    char inBuffer[BUFFER_SIZE + 1];                 // +1 for nul char at end of string
    char outBuffer[(BUFFER_SIZE * 4 / 3 ) + 1];     // Buffer size increased by 1/3 when encoding

    FILE* outFile = 0;
    FILE* inFile = 0;

    // Writing to file or to stdout depending on options
    if (strcmp(arguments.output_file, "") != 0) {}
        outFile = fopen(arguments.output_file, "w");
    }
    else {
        outFile = stdout;
    }

    // Reading from file or from stdout depending on options
    if (strcmp(arguments.input_file, "") != 0) {
        inFile = fopen(arguments.input_file, "r");
    }
    else {
        inFile = stdin;
    }


    // Iterate over input
    while (0 != readFile(inBuffer, sizeof(inBuffer), inFile)) {
        memset(outBuffer, '\0', sizeof(outBuffer));
        // encoding
        if (arguments.encode)
            encode(inBuffer, outBuffer);

        // decoding
        if (arguments.decode)
            decode(inBuffer, outBuffer);

        fprintf(outFile, "%s", outBuffer);
    }

    // Write new line char at end of file and close file
    fprintf(outFile, "\n");
    fclose(outFile);


    return 0;
}
