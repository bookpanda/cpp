#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    std::string alienOrder(std::vector<std::string> &words) {
        int n = words.size();
        std::unordered_map<char, std::vector<char>> adjList;
        std::set<char> nodes;
        std::unordered_map<char, int> prereq;

        for (const auto &word : words) {
            for (char c : word)
                nodes.insert(c);
        }
        for (char c : nodes)
            prereq[c] = 0;

        // scan every pair: skip the common prefix, take order on first differing char
        for (int i = 0; i < n - 1; i++) {
            std::string w1 = words[i];
            std::string w2 = words[i + 1];
            int i1 = 0, i2 = 0;
            while (i1 < w1.size() && i2 < w2.size() && w1[i1] == w2[i2]) {
                i1++;
                i2++;
            }
            // w1=abc, w2=ab (wrong order, c is before empty space)
            if (i2 == w2.size() && i1 < w1.size())
                return "";
            if (i1 == w1.size() || i2 == w2.size())
                continue;
            char c1 = w1[i1], c2 = w2[i2];

            // first differing char after common prefix
            adjList[c1].push_back(c2);
            // cout << c1 << "->" << c2 << "\n";
            prereq[c2]++;
            // cout << "prereq["<<c2<<"] = " << prereq[c2] << "\n";
        }

        std::queue<char> q;
        std::unordered_map<char, bool> visited;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (prereq.count(ch) && prereq[ch] == 0) {
                q.push(ch);
                visited[ch] = true;
            }
        }

        std::string order = "";
        while (!q.empty()) {
            char ch = q.front();
            q.pop();
            // cout << "ch: " << ch << "\n";
            order += ch;

            for (char next : adjList[ch]) {
                prereq[next]--;
                if (visited[next])
                    return ""; // wrong lex order
                if (prereq[next] == 0) {
                    q.push(next);
                    visited[next] = true;
                }
            }
        }

        return nodes.size() == order.size() ? order : "";
    }
};

// words = ["wre","wrt","wrf","er","ett","rftt"]
// 1. look for order ONLY between words:
// wrt/wrf: t->f
// wrt/er: w->e
// er/rftt: e->r
// er/ett: r->t
// wre/wrt: e->t
// w->e->r->t->f & e->t
// when at e, r has 1 indeg, while t has 2 indeg
// view as requirement: to visit r, must visit e first
//                      to visit t, must visit e,r first
// 2. traverse graph, traverse from node w/ 0 in-deg
// try to go to next w/ prereq[next]=0
// w->e: prereq[r]=1->0, prereq[t]=2->1
// e->r: prereq[t]=1->0
// 3. find cycle = return ""
// find visited[next]=true may suffice?

// words = ["z","x","z"]
// z->x->z (cycle = language order is invalid, return "" when cycle is found)