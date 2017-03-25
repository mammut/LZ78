#include <iostream>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include "LZ78.hpp"

typedef uint32_t alphabet;

int main(int argc, char const *argv[])
{
    /** Parse arguments */
    if (argc != 3) {
        std::cout << "Uso:\n";
        std::cout << "./LZ78-parser input output\n";
        return 1;
    }
    std::string input = argv[1];
    std::string output = argv[2];

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

    /** Generate the DFUDS tree */
    std::vector<char> DFUDS;
    std::vector<alphabet> letters;
    tree.generateDFUDS(DFUDS, letters);

    /** Write ascii file */
    FILE *ascii = fopen( (output + ".ascii").c_str(), "wb");
    for(auto const &i: DFUDS) fwrite(&i, sizeof(uint8_t), 1, ascii);
    fclose(ascii);

    /** Write letters file */
    FILE *letts = fopen( (output + ".letts").c_str(), "wb");
    uint64_t total_nodes = tree.nodes();
    fwrite(&total_nodes, sizeof(uint64_t), 1, letts);
    for(auto const &i: letters) fwrite(&i, sizeof(uint32_t), 1, letts);
    fclose(letts);

    return 0;
}
