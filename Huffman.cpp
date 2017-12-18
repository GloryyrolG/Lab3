#include "Huffman.h"

using namespace std;

IntlNode::IntlNode(HuffNode* lc, HuffNode* rc) {
    ch[0] = lc;
    ch[1] = rc;
    wgt = lc->weight() + rc->weight();
}

IntlNode::~IntlNode() {
    for (int i = 0; i < 2; i ++) {
        delete ch[i];
        ch[i] = NULL;
    }
}

int IntlNode::weight() {
    return wgt;
}

bool IntlNode::isLeaf() {
    return 0;
}

void IntlNode::setLChild(HuffNode* lc) {
    ch[0] = lc;
}

void IntlNode::setRChild(HuffNode* rc) {
    ch[1] = rc;
}

HuffNode* IntlNode::lChild() const {
    return ch[0];
}

HuffNode* IntlNode::rChild() const {
    return ch[1];
}

void IntlNode::del() {
    for (int i = 0; i < 2; i ++) {
        if (ch[i]) {
            ch[i]->del();
            delete ch[i];
            ch[i] = NULL;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

LeafNode::LeafNode(const char ch, int wgt) {
    this->ch = ch;
    this->wgt = wgt;
}

LeafNode::~LeafNode() {
}

int LeafNode::weight() {
    return wgt;
}

bool LeafNode::isLeaf() {
    return 1;
}

char LeafNode::value() {
    return ch;
}

void LeafNode::del() {
}

//---------------------------------------------------------------------------------------------------------------------

HuffTree::HuffTree() {
    rt = NULL;
}

HuffTree::HuffTree(const char ch, int wgt) {
    rt = new LeafNode(ch, wgt);
}

HuffTree::HuffTree(HuffTree* lc, HuffTree* rc) {
    rt = new IntlNode(lc->root(), rc->root());
}

HuffTree::~HuffTree() {
    if (rt) {
        rt->del();
        delete rt;
        rt = NULL;
    }
}

int HuffTree::weight() {
    return rt->weight();
}

HuffNode* HuffTree::root() {
    return rt;
}

//---------------------------------------------------------------------------------------------------------------------

MyHuffmanCode::MyHuffmanCode() {
    tr = NULL;
}

MyHuffmanCode::~MyHuffmanCode() {
    if (tr) {
        delete tr;
        tr = NULL;
    }
}

int MyHuffmanCode::setFcode(const string& fcode) {
    this->fcode = fcode;
    FILE* fp;
    if (!(fp = fopen(fcode.c_str(), "r"))) {
        printf("The file does not exist!\n");
        return -1;
    }
    fclose(fp);
    return buildTree();
}

int MyHuffmanCode::setFin(const string& fin) {
    this->fin = fin;
    FILE* fp;
    if (!(fp = fopen(fin.c_str(), "r"))) {
        printf("The file does not exist!\n");
        return -1;
    }
    fclose(fp);
    return 0;
}

int MyHuffmanCode::setFout(const string& fout) {
    this->fout = fout;
}

void MyHuffmanCode::DFS(HuffNode* node, int pos, char s[]) {
    if (node->isLeaf()) {
        s[pos] = '\0';
        code[getNo(((LeafNode*)node)->value())] = s;
        return ;
    }
    s[pos] = '0';
    DFS(((IntlNode*)node)->lChild(), pos + 1, s);
    s[pos] = '1';
    DFS(((IntlNode*)node)->rChild(), pos + 1, s);
}

int MyHuffmanCode::buildTree() {
    if (tr) {
        delete tr;
        tr = NULL;
    }
    freopen(fcode.c_str(), "r", stdin);
    char ch[2];
    int freq;
    map<char, int> cnt;
    cnt.clear();
    priority_queue<rec> Q;
    for (; !Q.empty(); Q.pop());
    for (; scanf("%s%d", ch, &freq) != EOF; ) {
        if (getNo(ch[0]) == -1) {
            printf("Error!\n");
            fclose(stdin);
            freopen("CON", "r", stdin);
            return -1;
        }
        if (!freq) {
            continue;
        }
        if (cnt.find(ch[0]) == cnt.end()) {
            cnt[ch[0]] = freq;
        }
        else {
            cnt[ch[0]] += freq;
        }
    }
    for (map<char, int>::iterator it = cnt.begin(); it != cnt.end(); it ++) {
        Q.push(rec((*it).second, new HuffTree((*it).first, (*it).second)));
    }
    HuffTree *t1, *t2, *t3;
    for (; Q.size() > 1; ) {
        t1 = Q.top().tr;
        Q.pop();
        t2 = Q.top().tr;
        Q.pop();
        t3 = new HuffTree(t1, t2);
        Q.push(rec(t3->weight(), t3));
    }
    tr = t3;
    char s[52] = {'\0'};
    DFS(tr->root(), 0, s);
    fclose(stdin);
    freopen("CON", "r", stdin);
    return 0;
}

void MyHuffmanCode::encode() {
    freopen(fin.c_str(), "r", stdin);
    freopen(fout.c_str(), "w", stdout);
    bool flag;
    char ch;
    int i;
    char s[1010];
    string res = "";
    for (; scanf("%s", s) != EOF; ) {
        flag = 0;
        for (i = 0; s[i] != '\0'; i ++) {
            if ((ch = getNo(s[i])) == -1) {
                printf("Error!\n");
                flag = 1;
                break;
            }
            res = res + code[ch];
        }
        if (!flag) {
            cout << res << endl;
        }
        res = "";
    }
    fclose(stdin);
    fclose(stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
}

char MyHuffmanCode::getCode(char* &s) {
    HuffNode* p = tr->root();
    for (; (*s) != '\0'; s ++) {
        if (p->isLeaf()) {
            return ((LeafNode*)p)->value();
        }
        if ((*s) == '0') {
            if (!((IntlNode*)p)->lChild()) {
                return '\0';
            }
            p = ((IntlNode*)p)->lChild();
        }
        else if ((*s) == '1') {
            if (!((IntlNode*)p)->rChild()) {
                return '\0';
            }
            p = ((IntlNode*)p)->rChild();
        }
        else {
            return '\0';
        }
    }
    if (p->isLeaf()) {
        return ((LeafNode*)p)->value();
    }
    return '\0';
}

void MyHuffmanCode::decode() {
    freopen(fin.c_str(), "r", stdin);
    freopen(fout.c_str(), "w", stdout);
    bool flag;
    char ch;
    char* p;
    char s[1010];
    string res = "";
    for (; scanf("%s", s) != EOF; ) {
        flag = 0;
        for (p = s; (*p) != '\0'; ) {
            if ((ch = getCode(p)) == '\0') {
                printf("Error!\n");
                flag = 1;
                break;
            }
            res = res + ch;
        }
        if (!flag) {
            cout << res << endl;
        }
        res = "";
    }
    fclose(stdin);
    fclose(stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
}

//---------------------------------------------------------------------------------------------------------------------

inline int getNo(const char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A';
    }
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 26;
    }
    return -1;
}
