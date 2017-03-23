#include <iostream>
#include "LZ78.hpp"

int main(int argc, char const *argv[])
{
    LZ78::trie tree = LZ78::trie();
    std::cout << tree.nodes() << std::endl;
    return 0;
}
