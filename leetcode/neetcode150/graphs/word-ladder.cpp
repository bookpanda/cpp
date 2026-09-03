#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string> &wordList) {
        std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end())
            return 0;

        std::unordered_set<std::string> beginSet{beginWord};
        std::unordered_set<std::string> endSet{endWord};

        int n = beginWord.size();
        int step = 1;
        while (!beginSet.empty() && !endSet.empty()) {
            if (beginSet.size() > endSet.size()) {
                std::swap(beginSet, endSet);
            }

            std::unordered_set<std::string> nextSet;
            for (const std::string &word : beginSet) {
                std::string currWord = word;
                for (int i = 0; i < n; i++) {
                    char tmp = currWord[i];
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        if (ch == tmp)
                            continue;
                        currWord[i] = ch;
                        if (endSet.count(currWord))
                            return step + 1;

                        if (dict.count(currWord)) {
                            nextSet.insert(currWord);
                            dict.erase(currWord); // mark as visited by erasing
                        }
                    }
                    currWord[i] = tmp;
                }
            }
            beginSet = std::move(nextSet);
            step++;
        }

        return 0;
    }
};
// make graph s.t. each node's neighbors only differ by 1 char
// "hit" -> "hot" -> "dot" -> "dog" -> cog"
// traverse graph, finding shortest path from beginWord to endWord
// beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// O(n^2), n=5000 => 25M *10(length of word), need better way to check if 2 words are adjacent
// root->(h, d, c)
// h->(i, o)
// d->(o)
// c->(o)

// bfs
// for (each char in hit), trie search w/ wildcard, check if word in list, push to queue
// maybe use trie to loop instead;
// _it -> trie search w/ wildcard -> ""
// h_t -> hot
// hi_ -> hit , dont take
// _it-> ""
// h_t -> hot
// _ot -> (dot,lot) -> dog ->cog