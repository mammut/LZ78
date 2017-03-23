/**
 * Copyright (C) 2017 UTFSM
 * Author: Diego Arroyuelo
 * Modified by: Juan Pablo Escalona
 *
 * LZ78 Compression tree implementation for big alphabets
 */
#include<map>

using namespace std;


typedef uint32_t alphabet;

class trieNode {
	uint64_t id;
	map<alphabet, trieNode*> children;
	std::map<alphabet,trieNode*>::iterator curChild;
public:
	trieNode();
	bool hasChild(alphabet letter) { return children.find(letter) != children.end());}
	trieNode child(alphabet letter) {return children[letter];}
	void addChild(alphabet letter, uint64_t _id) {
	   children[letter] = new trieNode();
	   children[letter]->id = _id;
	}
	alphabet nChildren() {return children.size();}
    void getLetters(vector<alphabet> *V) {
	   for(std::map<alphabet,trieNode*>::iterator it = children.begin(); it != children.end(); ++it)
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
	trie() {root = new trieNode(); nNodes = 0;}
	unsigned long long nodes() {return nNodes;}
	trieNode getRoot() { return root;}
	void addNode(trieNode t, alphabet letter) {
		t->addChild(letter, nNodes++);
	}
};



trie * lz78Parsing(alphabet *Text, uint64_t n) {
   trie *LZT = new trie();
   trieNode curNode = LZT->getRoot();
   uint64_t i;

   for (i=0; i < n; i++) {
      if (curNode->hasChild(T[i]))
         curNode = curNode->child(T[i]);
      else {
	     LZT->addNode(curNode, T[i]]);
		 curNode = LZT->getRoot();
	  }
   }
   return LZT;
}


void generateDFUDS(trienode *T, vector <char> *DFUDS, vector<alphabet> letters {

   for (alphabet i = 0; i < T->nchildren(); i++) DFUDS->push_back('(');
   DFUDS->push-back(')');

   T->getLetters(letters);

   for (alphabet i = 0, T->firstChild(); i < T->nChildren(); i++) {
   	   generateDFDUS(T->getCurChild(), DFUDS, letters);
   	   T->nextChild();
   }
}







// uint64_t para la cantidad de nodos
// uint32_t para las letras



