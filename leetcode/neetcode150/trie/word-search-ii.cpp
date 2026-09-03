#include <string>
#include <vector>

class TrieNode {
  public:
    std::string word = "";
    TrieNode *children[26] = {};
    TrieNode() {}
    ~TrieNode() {
        for (int i = 0; i < 26; i++)
            delete children[i];
    }
};

class Solution {
  private:
    int m, n;
    TrieNode *root = nullptr;
    std::vector<std::string> foundWords;

    void addWord(const std::string &word) {
        TrieNode *curr = root;
        for (char ch : word) {
            int chIdx = ch - 'a';
            if (!curr->children[chIdx])
                curr->children[chIdx] = new TrieNode();
            curr = curr->children[chIdx];
        }
        curr->word = word;
    }
    void dfs(std::vector<std::vector<char>> &board, int r, int c, TrieNode *parent) {
        int idx = board[r][c] - 'a';
        TrieNode *curr = parent->children[idx];
        if (!curr)
            return;

        if (!curr->word.empty()) {
            foundWords.push_back(curr->word);
            curr->word.clear(); // prevents duplication
        }

        char orig = board[r][c];
        board[r][c] = '#'; // visited

        static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto &d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n || board[nr][nc] == '#')
                continue;

            int chIdx = board[nr][nc] - 'a';
            dfs(board, nr, nc, curr);
        }
        board[r][c] = orig;

        // leaf pruning
        bool isLeaf = true;
        for (int i = 0; i < 26; i++) {
            if (curr->children[i]) {
                isLeaf = false;
                break;
            }
        }
        if (isLeaf) {
            delete curr;
            parent->children[idx] = nullptr;
        }
    }

  public:
    std::vector<std::string> findWords(std::vector<std::vector<char>> &board, std::vector<std::string> &words) {
        root = new TrieNode();
        for (const std::string word : words) {
            addWord(word);
        }

        m = board.size();
        n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int chIdx = board[i][j] - 'a';
                if (!root->children[chIdx])
                    continue;
                dfs(board, i, j, root);
            }
        }

        delete root;
        return foundWords;
    }
};
// 12x12 board, 30k word of length 10
// dfs to save mem?
// tracing word on board = looking at prefixes of words = trie
// 144 starting cells, each each can go 4 dirs, 9 times (4^9 = 2^18 = 250k)
// 144 * 0.25M = 36M
// each cell move, track position on trie -> find O(1)