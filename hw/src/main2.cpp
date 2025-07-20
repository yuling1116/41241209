// main.cpp
#include <iostream>
#include "header.h"
using namespace std;

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
