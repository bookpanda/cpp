#include <string>
#include <vector>

class Codec {
  private:
    // std::string escapeSlash(const std::string& s) {
    //     std::string out;
    //     for (char c : s) {
    //         if (c == '/') out += "//";
    //         else out += c;
    //     }
    //     return out;
    // }
    // void unescapeSlash(std::string& s) {
    //     size_t start = 0;
    //     while ((start = s.find("//", start)) != std::string::npos) {
    //         s.replace(start, 2, "/");
    //         start += 1; // advance past replaced segment
    //     }
    // }
  public:
    // Encodes a list of strings to a single string.
    std::string encode(std::vector<std::string> &strs) {
        std::string ans = "";
        for (const auto &s : strs) {
            // ans += escapeSlash(s);
            for (char c : s) {
                if (c == '/')
                    ans += "//";
                else
                    ans += c;
            }
            ans += "/:";
        }
        return ans;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(std::string s) {
        std::vector<std::string> ans;
        int n = s.size();
        std::string currentString = "";

        for (int i = 0; i < n; i++) {
            if (i + 1 < n && s[i] == '/' && s[i + 1] == ':') {
                ans.push_back(currentString);
                currentString.clear();
                i++;
            } else if (i + 1 < n && s[i] == '/' && s[i + 1] == '/') {
                currentString += '/';
                i++;
            } else {
                currentString += s[i];
            }
        }
        return ans;
    }
};
// cant use , to separate str1,str2,str3 as str can have , inside
// str can be "", must have delimiters between strs

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));