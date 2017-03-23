/**
 * Copyright (C) 2017 UTFSM
 * Author: Diego Arroyuelo
 * Modified by: Juan Pablo Escalona
 *
 * LZ78 Compression tree implementation for big alphabets
 * uint64_t para la cantidad de nodos
 * uint32_t para las letras
 */
#include <unordered_map>
#include <vector>

namespace LZ78
{

typedef uint32_t alphabet;

class trieNode {
  private:
	uint64_t id;
	std::unordered_map<alphabet, trieNode*> children;
	std::unordered_map<alphabet, trieNode*>::iterator curChild;

  public:
	bool hasChild(alphabet letter) { return children.find(letter) != children.end(); }
	trieNode *child(alphabet letter) {return children[letter];}
	void addChild(alphabet letter, uint64_t _id) {
	   children[letter] = new trieNode();
	   children[letter]->id = _id;
	}
	alphabet nChildren() {return children.size();}
    void getLetters(std::vector<alphabet> *V) {
	   for(std::unordered_map<alphabet,trieNode*>::iterator it = children.begin(); it != children.end(); ++it)
          V->push_back(it->first);
	}
	void firstChild() {curChild = children.begin();}
	void nextChild() {++curChild;}
    trieNode *getCurChild() { return curChild->second;}
};

class trie {
	trieNode *root;
	uint64_t nNodes;
  public:
	trie() { root = new trieNode(); nNodes = 0; }
	uint64_t nodes() { return nNodes; }
	trieNode *getRoot() { return root; }
	void addNode(trieNode *t, alphabet letter) {
		t->addChild(letter, nNodes++);
	}
};



trie *lz78Parsing(alphabet *Text, uint64_t n) {
   trie *LZT = new trie();
   trieNode *curNode = LZT->getRoot();
   uint64_t i;

   for (i=0; i < n; i++) {
      if (curNode->hasChild(Text[i]))
         curNode = curNode->child(Text[i]);
      else {
	     LZT->addNode(curNode, Text[i]);
		 curNode = LZT->getRoot();
	  }
   }
   return LZT;
}


void generateDFUDS(trieNode *T, std::vector<char> &DFUDS, std::vector<alphabet> letters) {
   for (alphabet i = 0; i < T->nChildren(); i++) DFUDS.push_back('(');
   DFUDS.push_back(')');

   T->getLetters(&letters);

   T->firstChild();
   for ( alphabet i = 0; i < T->nChildren(); i++) {
   	   generateDFUDS(T->getCurChild(), DFUDS, letters);
   	   T->nextChild();
   }
}

} // end LZ78 Namespace
