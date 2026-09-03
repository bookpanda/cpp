#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class TimeMap {
  public:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> m;
    TimeMap() {}

    void set(std::string key, std::string value, int timestamp) { m[key].push_back({value, timestamp}); }

    std::string get(std::string key, int timestamp) { // return the value w/ latest timestamp before timestamp
        auto map_it = m.find(key);
        if (map_it == m.end())
            return "";

        const auto &vals = map_it->second;
        if (vals.empty() || vals[0].second > timestamp)
            return "";

        // Is my target value strictly less than the current element in the array
        auto comp = [](int ts, const std::pair<std::string, int> &element) { return ts < element.second; };
        // everything is built on top of the "strict less-than" (<)
        // C++ algorithms require comparators to adhere to Strict Weak Ordering.
        // this means if an element is compared to itself, the comparator must return false (A < A is false), so NEVER
        // use <=, >= in comparators

        auto it = std::upper_bound(vals.begin(), vals.end(), timestamp, comp);
        return std::prev(it)->first;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */