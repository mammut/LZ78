#include <iostream>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include "LZ78.hpp"

typedef uint32_t alphabet;

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        std::cout << "Uso:\n";
        std::cout << "./LZ78-parser input output\n";
        return 1;
    }
    std::string input = argv[1];
    std::string output = argv[2];

    FILE *file;
    uint64_t length, result;

    file = fopen(input.c_str(), "rb");
    fseek(file, 0, SEEK_END);
    length = ftell(file)/sizeof(alphabet);
    rewind(file);
    alphabet *buffer = new alphabet[length];
    result = fread(buffer, sizeof(alphabet), length, file);
    if (result == 0) return 1;

    LZ78::trie<alphabet> tree = LZ78::trie<alphabet>();
    tree.parse(buffer, length);

    std::vector<char> DFUDS;
    std::vector<alphabet> letters;

    DFUDS.push_back('('); // DFUDS empty start
    letters.push_back(0); // DFUDS empty start

    tree.generateDFUDS(DFUDS, letters);

    FILE *ascii = fopen( (output + ".ascii").c_str(), "wb");
    for(auto const &i: DFUDS) fwrite(&i, sizeof(uint8_t), 1, ascii);
    fclose(ascii);

    FILE *letts = fopen( (output + ".letts").c_str(), "wb");
    /** uint64_t :: Number of nodes */
    uint64_t total_nodes = tree.nodes();
    fwrite(&total_nodes, sizeof(uint64_t), 1, letts);

    for(auto const &i: letters) fwrite(&i, sizeof(uint32_t), 1, letts);
    fclose(letts);

    return 0;
}
