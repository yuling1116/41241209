// header.h
#ifndef HEADER_H
#define HEADER_H

#include <stack>

// 遞迴版本
int ackermann_recursive(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann_recursive(m - 1, 1);
    else
        return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

// 非遞迴版本
int ackermann_nonrecursive(int m, int n) {
    std::stack<int> stk;
    stk.push(m);

    while (!stk.empty()) {
        m = stk.top();
        stk.pop();

        if (m == 0)
            n += 1;
        else if (n == 0) {
            n = 1;
            stk.push(m - 1);
        } else {
            stk.push(m - 1);
            stk.push(m);
            n -= 1;
        }
    }

    return n;
}

#endif
