#include <stack>
#include <utility>

class MinStack {
  public:
    std::stack<std::pair<int, int>> stk;
    MinStack() {}

    void push(int value) {
        if (stk.empty()) {
            stk.push({value, value});
            return;
        }

        int minVal = std::min(stk.top().second, value);
        stk.push({value, minVal});
    }

    void pop() { stk.pop(); }

    int top() { return stk.top().first; }

    int getMin() { return stk.top().second; }
};
// -2, 0, -3
// (-3,-3), (0,-3), (-2,-3), (-4, -4)

// -4 -3 5

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */