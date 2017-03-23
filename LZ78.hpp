/**
 * Copyright (C) 2017 UTFSM
 * Author: Diego Arroyuelo
 * Modified by: Juan Pablo Escalona @ 2017-03-23
 *
 * LZ78 Compression tree implementation for big alphabets
 */
#include <unordered_map>
#include <vector>

namespace LZ78
{

template <class A = uint32_t> // default alphabet
class trie_node {
  private:
    uint64_t id;
    std::unordered_map<A, trie_node<A> *> children;
    typename std::unordered_map<A, trie_node<A> *>::iterator cur_child;

  public:
    trie_node(uint64_t _id) { id = _id; }

    trie_node *child(A letter) { return children[letter]; }

    bool has_child(A letter) { return children.find(letter) != end(children); }

    void add_child(A letter, uint64_t _id) {
        children[letter] = new trie_node(_id);
    }

    void getLetters(std::vector<A> &V) {
        for(auto &i: children)
            V.push_back(i.first);
    }

    A nChildren() {return children.size(); }

    void first_child() { cur_child = begin(children); }

    void next_child() { ++cur_child; }

    trie_node *get_cur_child() { return cur_child->second; }

    ~trie_node() { for(auto &i: children) delete i.second; }
};

template <class A = uint32_t>
class trie {
    trie_node<A> *root;
    uint64_t nNodes;

  public:
    trie() { nNodes = 0; root = NULL; }
    uint64_t nodes() { return nNodes; }

    void parse(A *text, uint64_t n) {
        trie_node<A> *curNode = root;
        if (curNode == NULL) {
            root = new trie_node<A>(nNodes++);
            curNode = root;
        }

        for (uint64_t i = 0; i < n; ++i) {
            if (curNode->has_child(text[i]))
                curNode = curNode->child(text[i]);
            else {
                curNode->add_child(text[i], nNodes++);
                curNode = root;
            }
        }
    }

    void generateDFUDS(std::vector<char> &DFUDS, std::vector<A> &letters) {
        return generateDFUDS(root, DFUDS, letters);
    }

    void generateDFUDS(trie_node<A> *T, std::vector<char> &DFUDS, std::vector<A> &letters) {
        DFUDS.insert(end(DFUDS), T->nChildren(), '(');
        DFUDS.push_back(')');

        T->getLetters(letters);
        T->first_child();
        for (A i = 0; i < T->nChildren(); ++i) {
            generateDFUDS(T->get_cur_child(), DFUDS, letters);
            T->next_child();
        }
    }

    ~trie() { if (root != NULL) delete root; }
};

} // end LZ78 Namespace
