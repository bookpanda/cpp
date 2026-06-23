#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

class Solution {
  public:
    int evalRPN(std::vector<std::string> &tokens) {
        std::stack<int> stk;

        for (std::string token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int x2 = stk.top();
                stk.pop();
                int x1 = stk.top();
                stk.pop();

                if (token == "+") {
                    stk.push(x1 + x2);
                } else if (token == "-") {
                    stk.push(x1 - x2);
                } else if (token == "*") {
                    stk.push(x1 * x2);
                } else if (token == "/") {
                    stk.push(x1 / x2);
                }

                continue;
            }

            try {
                int x = std::stoi(token);
                stk.push(x);
            } catch (const std::invalid_argument &e) {
                std::cerr << "Invalid argument: No conversion could be performed.\n";
            } catch (const std::out_of_range &e) {
                std::cerr << "Out of range: The value is too large for an int.\n";
            }
        }

        if (!stk.empty())
            return stk.top();
        return -1;
    }
};