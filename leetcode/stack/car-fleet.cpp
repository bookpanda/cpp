#include <algorithm>
#include <stack>
#include <vector>

class Solution {
  public:
    int carFleet(int target, std::vector<int> &position, std::vector<int> &speed) {
        std::vector<std::pair<int, int>> cars;
        for (size_t i = 0; i < position.size(); i++) {
            cars.push_back({position[i], speed[i]});
        }
        std::sort(cars.begin(), cars.end());
        std::reverse(cars.begin(), cars.end());

        std::stack<std::pair<int, int>> stk;
        for (auto car : cars) {
            if (stk.empty()) {
                stk.push(car);
                continue;
            }

            double posB = stk.top().first;
            double speedB = stk.top().second;
            double timeB = (target - posB) / speedB;

            double timeA = ((double)target - car.first) / car.second;
            // cout << "carB: " << posB << ", speed: " << speedB << ", t=" << timeB << "\n";
            // cout << "carA: " << car.first << ", speed: " << car.second << ", t=" << timeA << "\n";

            if (timeB < timeA) { // A can't catch up to B
                stk.push(car);
                // cout << "A can't catch up to B\n";
                continue;
            } else {
                // stk.pop();
                // stk.push(car); // car is slower so it can be caught up
                // cout << "A caught up to B\n";
            }
        }

        int n = stk.size();
        // while(!stk.empty()) {
        //     cout << stk.top().first << " ";
        //     stk.pop();
        // }

        return n;
    }
};

//  target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
// 0123456789012
// 1  3 1  4 2

// A(s_a)->. C(s_c)->  B(s_b)->.    |
// distance/speed = time
// A is a meters from target, B is b meters from target
// B would reach target in b/s_b = t_b
// A would reach target in a/s_a = t_b
// t_a <= t_b == A catches up to B (same fleet)

// A, C, B
// solve for A,C first -> merge AC into 1 car
// AC(s_c)->  B(s_b)->

// if car is behind but faster, will eventually catch up w/ car in front
// must consider target

// cant simulate whole thing O(nm): too slow!