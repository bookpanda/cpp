#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    int m, n;
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};
    bool exist(std::vector<std::vector<char>> &board, std::string word) {
        m = board.size();
        n = board[0].size();
        std::unordered_map<char, int> freq;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                freq[board[i][j]]++;
        }
        if (freq[word[0]] > freq[word[word.length() - 1]])
            std::reverse(word.begin(), word.end());

        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        bool found = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != word[0])
                    continue;

                visited[i][j] = true;
                found = dfs(board, word, i, j, 1, visited);
                visited[i][j] = false;

                if (found)
                    return true;
            }
        }

        return false;
    }
    bool dfs(std::vector<std::vector<char>> &board, std::string word, int row, int col, int idx,
             std::vector<std::vector<bool>> &visited) {
        if (idx == word.size())
            return true;

        // check 4 adjacent tiles
        for (int i = 0; i < 4; i++) {
            int r2 = row + dr[i];
            int c2 = col + dc[i];
            // check if out-of-bound or visited or not value
            if (r2 < 0 || r2 >= m || c2 < 0 || c2 >= n || visited[r2][c2] || board[r2][c2] != word[idx])
                continue;

            visited[r2][c2] = true;
            if (dfs(board, word, r2, c2, idx + 1, visited))
                return true;
            visited[r2][c2] = false;
        }

        return false;
    }
};
// bfs/dfs max depth 15
// dfs if found -> return early
// bfs will find answer almost at the end