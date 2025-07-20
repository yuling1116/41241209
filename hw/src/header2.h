// header.h
#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
using namespace std;

void generatePowerset(const vector<char>& set, int index,
                      vector<char>& current, vector<vector<char>>& result) {
    if (index == set.size()) {
        result.push_back(current);  // 加入目前子集
        return;
    }

    // 不選 set[index]
    generatePowerset(set, index + 1, current, result);

    // 選 set[index]
    current.push_back(set[index]);
    generatePowerset(set, index + 1, current, result);
    current.pop_back();  // 回溯
}

#endif
