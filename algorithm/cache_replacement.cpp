#include <list>
#include <unordered_map>

using namespace std;

//https://leetcode-cn.com/problems/lru-cache-lcci/
class LRUCache {
    using iter = list<pair<int, int>>::iterator;
    list<pair<int, int>> doubly_list;
    unordered_map<int, iter> hash_map;
    int cap;
public:
    explicit LRUCache(int capacity) : cap(capacity) {
    }

    optional<int> get(int key) {
        if (hash_map.find(key) == hash_map.end()) return std::nullopt;
        doubly_list.push_front(std::move(*hash_map[key]));
        doubly_list.erase(hash_map[key]);
        hash_map[key] = doubly_list.begin();
        return hash_map[key]->second;
    }

    void put(int key, int value) {
        if (hash_map.find(key) == hash_map.end()) {
            doubly_list.emplace_front(key, value);
            hash_map[key] = doubly_list.begin();
            if (hash_map.size() > cap) {
                hash_map.erase(doubly_list.back().first);
                doubly_list.pop_back();
            }
        } else {
            doubly_list.push_front(std::move(*hash_map[key]));
            doubly_list.erase(hash_map[key]);
            hash_map[key] = doubly_list.begin();
            hash_map[key]->second = value;
        }
    }
};

