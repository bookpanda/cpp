#include <string>

class Solution {
  public:
    bool isAnagram(std::string s, std::string t) {
        if (s.length() != t.length())
            return false;

        int freq[26] = {0};
        for (int i = 0; i < s.length(); i++) {
            freq[s[i] - 'a']++;
            freq[t[i] - 'a']--;
        }
        // a: 3, n: 1, g: 1, r: 1, m: 1
        // r: 1, a: 1, t:1
        for (int count : freq) {
            if (count != 0)
                return false;
        }
        return true;
    }
};