#include <unordered_map>
#include <vector>

class Solution {
  public:
    int leastInterval(std::vector<char> &tasks, int n) {
        std::unordered_map<char, int> count;
        for (char task : tasks) {
            count[task]++;
        }

        int maxFreq = 0;
        int tasksWithMaxFreq = 0;
        for (auto &[t, freq] : count) {
            if (freq > maxFreq) {
                maxFreq = freq;
                tasksWithMaxFreq = 1;
            } else if (freq == maxFreq)
                tasksWithMaxFreq++;
        }

        // maxFreq-1 idle ranges, each range has n-(maxCount-1) idles
        int idleRanges = maxFreq - 1;
        int idlesPerRange = n - (tasksWithMaxFreq - 1);
        int totalIdle = idleRanges * idlesPerRange;
        int offset = tasks.size() - (maxFreq * tasksWithMaxFreq);
        int idlesNeeded = std::max(0, totalIdle - offset);
        return tasks.size() + idlesNeeded;
    }
};
// idea: count amount of unique tasks w/ max count
// e.g. A20, B10, C5 -> only care A 20 (bottleneck)
// n=2 -> A_A_A_A_A... = 20 ranges w/ A = 19 idles ranges
// emptySlot = 2*19 = 38
// reduce emptySlot w/ B,C -> 38 - (10+5) = 23
