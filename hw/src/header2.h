#ifndef HEADER_H
#define HEADER_H

#include <vector>
using namespace std;

void generatePowerset(const vector<char>& set, int index,
                      vector<char>& current, vector<vector<char>>& result);

#endif
