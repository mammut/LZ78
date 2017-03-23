#include <iostream>
#include <vector>
#include "LZ78.hpp"

typedef uint32_t alphabet;

int main(int argc, char const *argv[])
{
    LZ78::trie<alphabet> tree = LZ78::trie<alphabet>();
    alphabet text[] = {1,2,3,4,1,1,2,6};
    tree.parse(text, 8);

    std::vector<char> DFUDS;
    std::vector<alphabet> letters;

    DFUDS.push_back('('); // DFUDS empty start
    letters.push_back(0); // DFUDS empty start

    tree.generateDFUDS(DFUDS, letters);

    for(auto const &i: DFUDS) std::cout << i;
    std::cout << '\n';

    for(auto const &i: letters) std::cout << i;
    std::cout << '\n';

    return 0;
}
