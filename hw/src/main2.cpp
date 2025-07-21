#include <iostream>
#include "header.h"
using namespace std;

void generatePowerset(const vector<char>& set, int index,
                      vector<char>& current, vector<vector<char>>& result) {
    if (index == set.size()) {
        result.push_back(current);
        return;
    }

    // 不選 set[index]
    generatePowerset(set, index + 1, current, result);

    // 選 set[index]
    current.push_back(set[index]);
    generatePowerset(set, index + 1, current, result);
    current.pop_back();
}

int main() {
    vector<char> set = {'a', 'b', 'c'};
    vector<char> current;
    vector<vector<char>> result;

    generatePowerset(set, 0, current, result);

    cout << "Powerset of { a, b, c }:\n";
    for (const auto& subset : result) {
        cout << "{ ";
        for (char ch : subset) cout << ch << " ";
        cout << "}\n";
    }

    return 0;
}
