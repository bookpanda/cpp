#include <queue>
#include <vector>

class Solution {
  public:
    bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
        std::vector<int> prereq(numCourses, 0);
        std::vector<std::vector<int>> adjList(numCourses);

        for (auto pr : prerequisites) {
            // a requires b
            adjList[pr[1]].push_back(pr[0]);
            prereq[pr[0]]++;
        }

        std::queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (prereq[i] == 0)
                q.push(i);
        }

        int takenCourses = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            takenCourses++;

            for (int next : adjList[course]) {
                prereq[next]--;
                if (prereq[next] == 0) {
                    q.push(next);
                }
            }
        }

        return takenCourses == numCourses;
    }
};

// numCourses = 2, prerequisites = [[1,0]]
// adjList={{1}}, prereq={0,1}, q={0}
// 0: takenCourses=1, push 1 , prereq={0,0}
// 1: takenCourses=2,
// return true

// numCourses = 2, prerequisites = [[1,0],[0,1]]
// adjList={{1},{0}}, prereq={1,1}, q={}
// return false

// 0<->1 (cycle)
// false

// prerequisites = [[1,0],[0,1],[1, 2]]
// 2->(1<->0)
// false
// counter for each course: keep track of #prereq courses