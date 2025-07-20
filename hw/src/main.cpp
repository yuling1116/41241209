// main.cpp
#include <iostream>
#include "header.h"
using namespace std;

int main() {
    int m, n;
    cout << "請輸入 Ackermann 函數參數 m 與 n：";
    cin >> m >> n;

    try {
        cout << "\n[遞迴版本] Ackermann(" << m << ", " << n << ") = "
             << ackermann_recursive(m, n) << endl;

        cout << "[非遞迴版本] Ackermann(" << m << ", " << n << ") = "
             << ackermann_nonrecursive(m, n) << endl;

    } catch (...) {
        cout << "發生例外錯誤（如堆疊溢位或無窮迴圈）" << endl;
    }

    return 0;
}
