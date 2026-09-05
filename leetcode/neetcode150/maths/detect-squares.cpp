#include <cmath>
#include <unordered_map>
#include <vector>

class DetectSquares {
  private:
    std::unordered_map<int, std::vector<int>> py;
    int counts[1001][1001] = {};

  public:
    DetectSquares() {}

    void add(std::vector<int> point) {
        int x = point[0], y = point[1];
        if (counts[x][y] == 0) {
            py[y].push_back(x);
            counts[x][y]++;
            return;
        }
        counts[x][y]++;
    }

    int count(std::vector<int> point) {
        int ans = 0;
        int x = point[0], y = point[1];

        for (int x2 : py[y]) {
            // (x,y), (x2, y)
            int side = std::abs(x - x2);
            if (side == 0)
                continue;

            // (x, y2), (x2, y2)
            int candidates[] = {y - side, y + side};
            for (int y2 : candidates) {
                if (y2 < 0 || y2 > 1000)
                    continue;
                ans += counts[x2][y] * counts[x][y2] * counts[x2][y2];
            }
        }
        return ans;
    }
    // {x1, y1}, find 3 pts
    // need 1 pt w/ x=x1 (suppose y=y2) ptsInX[x=5] = {list of y values}: n pts
    // need 1 pt w/ y=y1 (suppose x=x2) ptsInY[y] = {list of x values}: m pts
    // need 1 pt w/ x=x2 && y=y2
    //      naive: check n*m coords,  n=750, m=750, searching around >500k coords
    //      better: check pts in ptsInX[x2] and pick only ones w/ y=y2, suppose find 700 points
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */