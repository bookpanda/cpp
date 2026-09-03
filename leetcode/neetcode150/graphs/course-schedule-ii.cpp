#include <vector>

class Solution {
  public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> &prerequisites) {
        std::vector<int> inDegree(numCourses, 0);
        std::vector<std::vector<int>> adjList(numCourses);

        for (auto &pr : prerequisites) {
            // a requires b
            adjList[pr[1]].push_back(pr[0]);
            inDegree[pr[0]]++;
        }

        std::vector<int> order;
        order.reserve(numCourses);
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0)
                order.push_back(i);
        }

        int head = 0;
        while (head < order.size()) {
            int course = order[head++];
            for (int next : adjList[course]) {
                inDegree[next]--;
                if (inDegree[next] == 0) {
                    order.push_back(next);
                }
            }
        }

        return (order.size() == numCourses) ? order : std::vector<int>{};
    }
};