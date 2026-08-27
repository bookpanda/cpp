#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
  private:
    std::unordered_map<std::string, std::multiset<std::string>> adjList;
    std::vector<std::string> route;
    void visit(std::string airport) {
        while (adjList[airport].size()) {
            std::string next = *adjList[airport].begin();
            adjList[airport].erase(adjList[airport].begin());
            visit(next);
        }
        route.push_back(airport);
    }

  public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> &tickets) {
        for (const auto &ticket : tickets) {
            adjList[ticket[0]].insert(ticket[1]);
        }
        visit("JFK");

        return std::vector<std::string>(route.rbegin(), route.rend());
    }
};
// start JFK
// assign airports w/ lower lexi order w/ shorter dist?
// adjList[JFK]: ATL, SFO, airportIdx=2
// adjList[ATL]: JFK, SFO, airportIdx=1
// adjList[SFO]: ATL, airportIdx=1
// JFK, ATL, JFK, SFO, ATL, SFO

// [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
// JFK->ATL->JFK->SFO->ATL->SFO
