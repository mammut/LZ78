/**
 * Copyright (C) 2017 UTFSM
 * Author: Diego Arroyuelo
 * Modified by: Juan Pablo Escalona @ 2017-03-23
 *
 * LZ78 Compression tree implementation for big alphabets
 */
#include <map>
#include <vector>
#include <queue>
 #include <stdint.h>

namespace LZ78
{

template <class A = uint32_t> // default alphabet
class trie_node {
  private:
    uint64_t id;
    std::map<A, trie_node<A> *> children;
    typename std::map<A, trie_node<A> *>::iterator cur_child;

  public:
    trie_node(uint64_t _id) { id = _id; }
    ~trie_node() { for(auto &i: children) delete i.second; }

    trie_node *child(A letter) { return children[letter]; }

    bool has_child(A letter) { return children.find(letter) != end(children); }

    void add_child(A letter, uint64_t id) {
        children[letter] = new trie_node(id);
    }

    void getLetters(std::vector<A> &V) {
        for(auto &i: children)
            V.push_back(i.first);
    }

    A n_children() { return children.size(); }

    void first_child() { cur_child = begin(children); }

    void next_child() { ++cur_child; }

    trie_node *get_cur_child() { return cur_child->second; }
};

template <class A = uint32_t>
class trie {
  private:
    trie_node<A> *root;
    uint64_t n_nodes;

  public:
    trie() { n_nodes = 0; root = NULL; }
    ~trie() { if (root != NULL) delete root; }

    /**
     * Number of nodes;
     * @return n_nodes nomber of nodes in the tree
     */
    uint64_t nodes() { return n_nodes; }

    /**
     * Parse the given text of a given alphabet
     * @param text const array of type alphabet
     * @param n    length of the array
     */
    void parse(const A *text, const uint64_t n) {
        if (root == NULL)
            root = new trie_node<A>(n_nodes++);

        trie_node<A> *cur_node = root;
        for (uint64_t i = 0; i < n; ++i)
            if (cur_node->has_child(text[i]))
                cur_node = cur_node->child(text[i]);
            else {
                cur_node->add_child(text[i], n_nodes++);
                cur_node = root;
            }
    }

    /**
     * Public DFUDS helper, starts the recursive calls
     * @param DFUDS   vector of chars ( or )
     * @param letters vector of alphabet with the labels accessed
     */
    void generateDFUDS(std::vector<char> &DFUDS, std::vector<A> &letters) {
        DFUDS.push_back('(');
        letters.push_back('0');
        return generateDFUDS(root, DFUDS, letters);
    }

    /**
     * Generate de LOUDS representation
     * @param LOUDS   vector of bools
     * @param letters vector of alphabet
     */
    void generateLOUDS(std::vector<bool> &LOUDS, std::vector<A> &letters) {
        std::queue<trie_node<A> *> q;
        if (root == NULL) return;

        q.push(root);
        while ( ! q.empty()) {
            trie_node<A> *T = q.front(); q.pop();

            T->first_child();
            T->getLetters(letters);
            for (A i = 0; i < T->n_children(); ++i) {
                q.push(T->get_cur_child());
                T->next_child();
                LOUDS.push_back(1);
            }
            LOUDS.push_back(0);
        }
    }

  private:
    /**
     * Recursive version of DFUDS generator
     * @param T       current node
     * @param DFUDS   vector of '(' and ')'
     * @param letters vector of alphabet
     */
    void generateDFUDS(trie_node<A> *T, std::vector<char> &DFUDS, std::vector<A> &letters) {
        DFUDS.insert(end(DFUDS), T->n_children(), '(');
        DFUDS.push_back(')');

        T->getLetters(letters);
        T->first_child();
        for (A i = 0; i < T->n_children(); ++i) {
            generateDFUDS(T->get_cur_child(), DFUDS, letters);
            T->next_child();
        }
    }
};

} // end LZ78 Namespace
