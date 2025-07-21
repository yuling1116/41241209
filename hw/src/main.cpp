#include <iostream>
#include "header.h"
using namespace std;

int ackermann(int m, int n) {
    if (m < 0 || n < 0)
        throw "m or n < 0";
    else if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    try {
        int result = ackermann(2, 3);
        cout << result << '\n';
    } catch (const char* msg) {
        cerr << "Error: " << msg << '\n';
    }
}
