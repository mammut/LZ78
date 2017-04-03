#include <iostream>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include <argp.h>
#include "LZ78.hpp"

struct arguments {
    char *args[1];
    std::string output;
    bool dfuds;
    bool louds;
    bool clouds;
};

/**
 * Parseo de argumentos desde la linea de comandos usando la libreria
 * ARGP. No es estandar de C, por lo que puede que en Mac no compile
 * correctamente
 */
const char *argp_program_version     = "LZ78-parser 1.0.1";
const char *argp_program_bug_address = "<juan.escalona@alumnos.inf.utfsm.cl>";
static char doc[] = "LZ78 parser to DFUDS, LOUDS & Cardinal LOUDS";
static char args_doc[] = "INPUT_FILE";
static struct argp_option options[] = {
  {"output", 'o', "salida.",  0,  "Output files name: name.ascii and name.letts" },
  {"dfuds",  'd', 0, OPTION_ARG_OPTIONAL,  "DFUDS" },
  {"louds",  'l', 0, OPTION_ARG_OPTIONAL,  "LOUDS" },
  {"clouds", 'c', 0, OPTION_ARG_OPTIONAL,  "Cardinal LOUDS" },
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = (struct arguments *)state->input;

  switch (key) {
    case 'o': arguments->output = (std::string) arg; break;
    case 'd': arguments->dfuds = true; break;
    case 'l': arguments->louds = true; break;
    case 'c': arguments->clouds = true; break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;

    case ARGP_KEY_END:
      if (state->arg_num < 1)
        argp_usage(state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

typedef uint32_t alphabet;

int main(int argc, char *argv[])
{
    struct arguments arguments;

    /* Valores de argumentos por defecto y parseo de parametros. */
    arguments.output = "salida";
    arguments.dfuds = false;
    arguments.louds = false;
    arguments.clouds = false;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    std::string input = arguments.args[0];
    std::string output = arguments.output;

    /** Get length of file */
    FILE *input_file = fopen(input.c_str(), "rb");
    fseek(input_file, 0, SEEK_END);
    uint64_t length = ftell(input_file)/sizeof(alphabet);
    rewind(input_file);

    /** Read file into buffer */
    alphabet *buffer = new alphabet[length];
    uint64_t result = fread(buffer, sizeof(alphabet), length, input_file);
    if (result == 0) return 1;

    /** Build the LZ78 trie */
    LZ78::trie<alphabet> tree = LZ78::trie<alphabet>();
    tree.parse(buffer, length);
    delete buffer;

    if (arguments.dfuds) {
        /** Generate the DFUDS tree */
        std::vector<char> DFUDS;
        std::vector<alphabet> letters;
        tree.generateDFUDS(DFUDS, letters);

        /** Write ascii file */
        FILE *ascii = fopen( (output + "-DFUDS.ascii").c_str(), "wb");
        for(auto const &i: DFUDS) fwrite(&i, sizeof(uint8_t), 1, ascii);
        fclose(ascii);

        /** Write letters file */
        FILE *letts = fopen( (output + "-DFUDS.letts").c_str(), "wb");
        uint64_t total_nodes = tree.nodes();
        fwrite(&total_nodes, sizeof(uint64_t), 1, letts);
        for(auto const &i: letters) fwrite(&i, sizeof(uint32_t), 1, letts);
        fclose(letts);
    }

    if (arguments.louds) {
        /** Generate the LOUDS tree */
        std::vector<char> LOUDS;
        std::vector<alphabet> letters;
        tree.generateLOUDS(LOUDS, letters);

        /** Write ascii file */
        FILE *ascii = fopen( (output + "-LOUDS.ascii").c_str(), "wb");
        for(auto const &i: LOUDS)
            fwrite(&i, sizeof(uint8_t), 1, ascii);
        fclose(ascii);

        /** Write letters file */
        FILE *letts = fopen( (output + "-LOUDS.letts").c_str(), "wb");
        uint64_t total_nodes = tree.nodes();
        fwrite(&total_nodes, sizeof(uint64_t), 1, letts);
        for(auto const &i: letters)
            fwrite(&i, sizeof(uint32_t), 1, letts);
        fclose(letts);
    }

    if (arguments.clouds) {
        std::vector<uint64_t> CLOUDS;
        tree.generate_cardinalLOUDS(CLOUDS);

        /** Write ascii file */
        FILE *ascii = fopen( (output + "-CLOUDS.ascii").c_str(), "wb");
        for(auto const &alph: tree.alphabet)
            fwrite(&alph, sizeof(alphabet), 1, ascii);
        fclose(ascii);

        /** Write letters file */
        FILE *letts = fopen( (output + "-CLOUDS.letts").c_str(), "wb");

        uint64_t total_nodes = tree.nodes();
        fwrite(&total_nodes, sizeof(uint64_t), 1, letts);

        uint64_t alphabet_size = tree.alphabet_size();
        fwrite(&alphabet_size, sizeof(uint64_t), 1, letts);

        for(auto const &i: CLOUDS)
            fwrite(&i, sizeof(uint32_t), 1, letts);

        fclose(letts);
    }

    return 0;
}
