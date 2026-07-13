#include <string>

class Node {
  public:
    Node *children[26] = {};
    bool isWord = false;
    Node() {}
    ~Node() {
        for (Node *child : children)
            delete child;
    }
};

class WordDictionary {
  private:
    Node *root;

  public:
    WordDictionary() { root = new Node(); }
    ~WordDictionary() { delete root; }

    void addWord(std::string word) {
        Node *curr = root;
        for (char &c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = new Node();
            }
            curr = curr->children[idx];
        }
        curr->isWord = true;
    }

    bool search(std::string word) { return searchWord(word, 0, root); }

  private:
    bool searchWord(const std::string &word, int idx, Node *curr) {
        if (!curr)
            return false;
        if (idx == word.size())
            return curr->isWord;
        if (word[idx] != '.') {
            int chIdx = word[idx] - 'a';
            return searchWord(word, idx + 1, curr->children[chIdx]);
        }

        for (int i = 0; i < 26; i++) {
            if (curr->children[i] && searchWord(word, idx + 1, curr->children[i]))
                return true;
        }
        return false;
    }
};
// "bad"
// "dad"
// "mad"
// search("pad") q({root,0}): false
// search(".ad") q({root,0}): [{b,1},{d,1},{m,1}]
// {b,1}: [{d,1},{m,1},{a,2}]
// {d,1}: [{m,1},{a,2},{a,2}]
// {m,1}: [{a,2},{a,2},{a,2}] (ok, since a's are not same nodes)
// {a,2} : [{a,2},{a,2},{d,3}]
// search("b..")  q({root,0}): [{b,1}]
// {b,1}: [{a,2}]
// {a,2}: [{d,3}]

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */