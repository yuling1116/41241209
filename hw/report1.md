# 41241209

作業一

Problem 1：Ackermann 函數

## 解題說明

本題要求實作一個遞迴與非遞迴函式，計算 Ackermann 函數𝐴(𝑚,𝑛)。
此函數以極快的速度成長，即使對於小的 m 和 n，也會產生極深的遞迴呼叫。

### 解題策略

1. 遞迴版本： 直接依照定義實作，適合理解遞迴的基本架構。
2. 非遞迴版本： 使用 stack 模擬函式呼叫過程，避免堆疊溢位。

## 程式實作

以下為遞迴版本程式碼：

```cpp
#include <iostream>
using namespace std;

int ackermann_recursive(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann_recursive(m - 1, 1);
    else
        return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

int main() {
    int result = ackermann_recursive(2, 3);
    cout << result << '\n';
}
```

以下為非遞迴版本程式碼：

```cpp
#include <iostream>
#include <stack>
using namespace std;

int ackermann_nonrecursive(int m, int n) {
    stack<int> stk;
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

int main() {
    int result = ackermann_nonrecursive(2, 3);
    cout << result << '\n';
}
```

## 效能分析

1. 時間複雜度： Ackermann 函數為超指數級別，遞迴深度極快增長。
   理論上為超出原始遞迴複雜度類別 (hyper-exponential)。
2. 空間複雜度：遞迴版為)O(m+n)：呼叫堆疊深度與 m,n 有關。
   非遞迴版為O(m+n)：模擬遞迴所需的堆疊。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m, n$ | 預期輸出 | 遞迴輸出 | 非遞迴輸出 |
| ---- | ----------- | ---- | ---- | ----- |
| 測試一  | $0, 0$      | 1    | 1    | 1     |
| 測試二  | $1, 2$      | 4    | 4    | 4     |
| 測試三  | $2, 2$      | 7    | 7    | 7     |
| 測試四  | $3, 3$      | 61   | 61   | 61    |
| 測試五  | $4, 1$      | 非常大  | 無法計算 | 無法計算  |


### 編譯與執行指令

```shell
$ g++ -std=c++17 -o ack ackermann.cpp
$ ./ack
9
```

### 結論

1. 遞迴與非遞迴版本皆能正確處理中小規模的 Ackermann 輸入。

2. 當輸入過大（如 𝑚≥4）時，遞迴層數將導致程式記憶體溢位或運行時間過長。

3. 非遞迴版本能避開系統呼叫堆疊限制，但仍會被值成長速度所制約。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **遞迴與數學定義一致**  
   本題公式即為一種典型的遞迴定義，因此使用遞迴是最直覺的方式。
2. **可展示嵌套遞迴技巧**  
   此題是經典的遞迴練習，特別是「遞迴中再呼叫遞迴」的複雜結構，能幫助我深入理解函數呼叫堆疊與遞迴框架的運作。
3. **學會堆疊模擬遞迴邏輯**  
   為避免遞迴層數過深導致 stack overflow，我使用 stack 進行非遞迴模擬，實際掌握遞迴等價的迴圈邏輯轉換。

在非遞迴版本的實作初期，我曾經錯誤地將 stk.push(m) 和 n = n - 1 的順序顛倒，或漏掉 stk.pop() 的時機，導致程式進入無窮迴圈，CPU 占用率爆高，無法正常結束執行。模擬遞迴時，一點順序錯誤就可能造成邏輯崩壞。

尤其 Ackermann 函數的輸出無法預測，讓 debug 更困難。

無窮迴圈是程式邏輯錯誤中最難察覺的類型，必須透過 小規模測試、逐步印出變數狀態 來除錯。

因此，我特別在實作過程中加入了多次輸出檢查與註解，以協助確認 stack 操作流程與變數變化，最終才成功穩定跑出正確結果。
