#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Twitter {
  public:
    std::unordered_map<int, std::unordered_set<int>> followees;
    std::unordered_map<int, std::unordered_set<int>> followers;
    std::unordered_map<int, std::vector<std::pair<std::pair<int, int>, int>>> tweets;
    std::unordered_map<int, std::set<std::pair<std::pair<int, int>, int>>> feed;
    int t;
    Twitter() { t = 0; }

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({{-t, tweetId}, userId});
        // push to feed of each follower
        for (int followerId : followers[userId]) {
            feed[followerId].insert({{-t, tweetId}, userId});
        }
        feed[userId].insert({{-t, tweetId}, userId});
        t++;
    }

    std::vector<int> getNewsFeed(int userId) {
        // 10 most recent tweets of followees[userId] + userId
        std::vector<int> finalFeed;
        // for (int i=feed[userId].size()-1; i>=0; i--) {
        for (auto [ti, posterId] : feed[userId]) {
            // auto [ti, posterId] = feed[userId][i];
            auto [ts, tweetId] = ti;
            if (followees[userId].find(posterId) == followees[userId].end() && posterId != userId)
                continue;
            finalFeed.push_back(tweetId);
            if (finalFeed.size() == 10)
                break;
        }

        return finalFeed;
    }

    void follow(int followerId, int followeeId) {
        if (followees[followerId].find(followeeId) != followees[followerId].end())
            return;

        followees[followerId].insert(followeeId);
        followers[followeeId].insert(followerId);
        for (auto &tweet : tweets[followeeId]) {
            feed[followerId].insert(tweet);
        }
        // std::sort(feed[followerId].begin(), feed[followerId].end());
    }

    void unfollow(int followerId, int followeeId) {
        followees[followerId].erase(followeeId);
        followers[followeeId].erase(followerId);
        for (auto &tweet : tweets[followeeId]) {
            feed[followerId].erase(tweet);
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */