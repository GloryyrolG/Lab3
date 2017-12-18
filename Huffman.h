#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <bits/stdc++.h>

using namespace std;

class HuffTree;

struct rec {
    int freq;
    HuffTree* tr;

    rec() {
        freq = 0;
        tr = NULL;
    }

    rec(int _freq, HuffTree* _tr) {
        freq = _freq;
        tr = _tr;
    }

    friend inline bool operator <(const rec& a, const rec& b) {
        return a.freq > b.freq;
    }
};

class HuffNode {
    public:
        virtual ~HuffNode() {}
        virtual int weight() = 0;
        virtual bool isLeaf() = 0;
        virtual void del() = 0;
};

class IntlNode: public HuffNode {
    private:
        HuffNode* ch[2];
        int wgt;

    public:
        IntlNode(HuffNode* lc, HuffNode* rc);
        ~IntlNode();
        int weight();
        bool isLeaf();
        void setLChild(HuffNode* lc);
        void setRChild(HuffNode* rc);
        HuffNode* lChild() const;
        HuffNode* rChild() const;
        void del();
};

class LeafNode: public HuffNode {
    private:
        char ch;
        int wgt;

    public:
        LeafNode(const char ch, int wgt);
        ~LeafNode();
        int weight();
        bool isLeaf();
        char value();
        void del();
};

class HuffTree {
    private:
        HuffNode* rt;

    public:
        HuffTree();
        HuffTree(const char ch, int wgt);
        HuffTree(HuffTree* lc, HuffTree* rc);
        ~HuffTree();
        int weight();
        HuffNode* root();
};

class MyHuffmanCode {
    private:
        HuffTree* tr;
        string code[52];
        string fcode, fin, fout;

        int buildTree();

    public:
        MyHuffmanCode();
        ~MyHuffmanCode();
        int setFcode(const string& fcode);
        int setFin(const string& fin);
        int setFout(const string& fout);
        void DFS(HuffNode* node, int pos, char s[]);
        void encode();
        char getCode(char* &s);
        void decode();
};

inline int getNo(const char ch);

#endif // __HUFFMAN_H__
