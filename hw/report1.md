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


作業一
Problem 2：Powerset 子集列舉

## 解題說明

本題要求使用遞迴方式實作 powerset（冪集合）生成演算法。Powerset 是一個集合的所有子集所構成的集合。

### 解題策略

1. 將問題拆解為：對於每個元素，我們有「取」或「不取」兩種選擇。

2. 使用遞迴函式 generatePowerset()：

   當走到底時（index == set.size()），把 current 子集合加入結果。

   否則：

   不選當前元素 → 遞迴

   選擇當前元素 → 加入 current，再遞迴

   回溯（pop 回前一步）

## 程式實作

以下為主要程式碼：

```cpp
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
```

## 效能分析

1. 時間複雜度：每個元素有兩種選擇（取或不取），總共2n個子集合。
   時間複雜度為 O(2n)。

2. 空間複雜度：每層遞迴需要保存 current 狀態，最大為O(n)
   結果總共會存O(2n)組

## 測試與驗證

### 測試案例

| 測試案例 | 輸入集合    | 預期輸出子集數量 | 實際輸出子集數量 |
| ---- | ------- | -------- | -------- |
| 測試一  | {a}     | 2        | 2        |
| 測試二  | {a,b}   | 4        | 4        |
| 測試三  | {a,b,c} | 8        | 8        |
| 測試四  | 空集合 {}  | 1        | 1        |


### 編譯與執行指令

```shell
g++ -std=c++17 main.cpp -o powerset
./powerset
```

### 結論

1. 遞迴能成功列舉所有子集，並對每個元素進行「取/不取」兩分支遞迴。
2. 程式邏輯貼近組合數學的建構方式，適合學習遞迴與回溯。
3. 隨元素數量增長，powerset 的規模成指數成長，應避免處理太大集合。

## 申論及開發報告
在本題實作過程中，我學習到如何利用「回溯法」來產生所有可能的子集合（powerset）。這種方式對每個元素進行「選擇」與「不選擇」的遞迴拆解，讓我能清楚掌握 powerset 結構的產生邏輯。
實作上，我透過三個參數控制遞迴流程：目前的索引、目前子集合 current、整體結果集 result。當索引達到底時就代表走完一條分支，將當前子集加入結果中。這樣的邏輯對應到 powerset 的2n個組合，效果相當直觀。
在過程中我也曾遇到 bug，例如在回溯前忘了 pop_back()，導致子集合堆疊錯誤，或者是參數順序寫錯，造成遞迴邏輯混亂甚至 segmentation fault。這些經驗讓我深刻體會：即使是簡單的遞迴，也必須精準控制呼叫邏輯與狀態回復。
這題不但讓我練習了遞迴與回溯，也更熟悉如何在程式中維護多層次的遞迴狀態，並將結果有條理地儲存起來。
