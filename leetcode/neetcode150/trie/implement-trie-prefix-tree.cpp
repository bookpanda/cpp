#include <string>

class Node {
  public:
    Node *children[26] = {};
    bool isWord = false;
    Node() {}
};

class Trie {
  private:
    Node *root;

  public:
    Trie() { root = new Node(); }

    void insert(std::string word) {
        Node *curr = root;
        for (char &c : word) {
            int idx = c - 'a';
            if (curr->children[idx] == nullptr) {
                curr->children[idx] = new Node();
            }
            curr = curr->children[idx];
        }
        curr->isWord = true;
    }

    bool search(std::string word, bool isPrefix = false) {
        Node *curr = root;
        for (char &c : word) {
            int idx = c - 'a';
            if (curr->children[idx] == nullptr)
                return false;
            curr = curr->children[idx];
        }
        return isPrefix ? true : curr->isWord;
    }

    bool startsWith(std::string prefix) { return search(prefix, true); }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// apple: root->(a,f)->(p,f)->(p,f)->(l,f)->(e,t)
// app: root->(a,f)->(p,f)->(p,t)->(l,f)->(e,t)
// car:    \->(c,f)->(a,f)->(r,t)