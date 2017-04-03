#include <iostream>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include <unordered_map>
#include "LZ78.hpp"

typedef char alphabet;

int main(int argc, char const *argv[])
{
    LZ78::trie<alphabet> t = LZ78::trie<alphabet>();
    char word[] = "ABBCBCABABCAABCAAB";
    t.parse(word, 18);

    std::vector<uint64_t> LOUDS;

    t.generate_cardinalLOUDS(LOUDS);

    std::cout << "Alphabet size: " << t.alphabet_size() << '\n';
    std::cout << "Number of nodes: " << t.nodes() << '\n';
    for(auto const &i: LOUDS) std::cout << i;
    std::cout << '\n';

    for(auto const &alph: t.alphabet)
        std::cout << alph << ' ';
    std::cout << '\n';

    return 0;
}
