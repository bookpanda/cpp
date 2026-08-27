#include <algorithm>
#include <climits>
#include <vector>

class Solution {
  public:
    int minCostConnectPoints(std::vector<std::vector<int>> &points) {
        // prim's algo
        // for step n times
        // for unvisited nodes: find one w/ smallest dist
        // for remaining unvisited nodes: update dist: check if the newly added node makes it shorter

        int n = points.size();
        std::vector<int> minDist(n, INT_MAX);
        std::vector<bool> visited(n, false);
        minDist[0] = 0;

        int totalWeight = 0;
        for (int i = 0; i < n; i++) {
            int closestDist = INT_MAX;
            int chosenNode = -1;
            for (int j = 0; j < n; j++) {
                if (visited[j])
                    continue;
                if (closestDist > minDist[j]) {
                    closestDist = minDist[j];
                    chosenNode = j;
                }
            }

            visited[chosenNode] = true;
            totalWeight += minDist[chosenNode];

            int chosenX = points[chosenNode][0];
            int chosenY = points[chosenNode][1];
            for (int j = 0; j < n; j++) {
                if (visited[j])
                    continue;
                int manhattanDist = std::abs(chosenX - points[j][0]) + std::abs(chosenY - points[j][1]);
                minDist[j] = std::min(minDist[j], manhattanDist);
            }
        }

        return totalWeight;
    }
};
// points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// {1,3,3}, {0,1,4}, {3,4,4}, {0,3,7}, {0,4,7}, {1,4,7}, {1,2,9}, {2,3,10}, {0,2,13}, {2,4,14},
// 0-1-3-4: w=3+4+4=11
// 1-2: w=9
// total w = 9+11=20

// 1000 points, need 999 edges
// naive: 1000*1000 possible edges, pick 999 edges to make MST
// actually it is 500k edges
// cutout threshold
