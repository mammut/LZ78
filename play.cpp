#include <iostream>
#include <vector>
#include "LZ78.hpp"

typedef char alphabet;

int main(int argc, char const *argv[])
{
    LZ78::trie<alphabet> t = LZ78::trie<alphabet>();
    char word[] = "ABBCBCABABCAABCAAB";
    t.parse(word, 18);
    std::vector<bool> LOUDS;
    std::vector<alphabet> letters;

    t.generateLOUDS(LOUDS, letters);

    std::cout << t.nodes() << '\n';
    for(auto const &i: LOUDS) std::cout << i;
    std::cout << '\n';
    for(auto const &i: letters) std::cout << i << " ";

    return 0;
}
