#include <vector>

class Solution {
  public:
    int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost) {
        // 1. Global Feasibility Condition: sum(gas) >= sum(cost)
        // 2. Range Elimination (greedy): if start at A and run out if gas at B, it means can't start at other stations
        // C between A and B either since starting at C w/ 0 instead of non-negative amount of gas from prev stations
        // starting from A
        int tank = 0, totalTank = 0;
        int start = 0;
        int n = gas.size();
        for (int i = 0; i < n; i++) {
            int net = gas[i] - cost[i];
            totalTank += net;
            tank += net;
            if (tank < 0) {
                // start can't be from current start to i, so try start fresh from i+1
                start = i + 1;
                tank = 0;
            }
        }

        return totalTank < 0 ? -1 : start;
    }
};

// gas = [1,2,3,4,5], cost = [3,4,5,1,2] = sum(gas)==sum(cost)
// start at idx0, t=0->1
// idx1, t=1-3=-2 + 2 =0
// idx2, t=0-4=-4 + 3 = -1
// idx3, t=-1-5=-6 + 4 = -2
// idx4, t=-2-1=-3 + 5 = 2
// idx0, t=2-2=0,

// i=3, t=4
// i=4, t=4-1+5=8
// i=0, t=8-2+1=7
// i=1, t=7-3+2=6
// i=2, t=6-4+3=5
// i=3, t=5-5+4=4

// gas = [2,3,4]=9, cost = [3,4,3]=10 return false since 10 > 9