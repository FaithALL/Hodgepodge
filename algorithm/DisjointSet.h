/**
 * 并查集
 * https://zhuanlan.zhihu.com/p/93647900/
 */
#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
#include <unordered_map>

template<typename Type>
class DisjointSet {
private:
    std::unordered_map<Type, Type> father;
public:
    DisjointSet() = default;

    void reset(const std::vector<Type> &vec) {
        father.clear();
        for (auto item: vec) {
            father[item] = item;
        }
    }

    Type find(Type item) {
        if (father[item] == item) return item;
        else return father[item] = find(father[item]);
    }

    void merge(Type x, Type y) {
        father[find(x)] = find(y);
    }
};

#endif //DISJOINTSET_H