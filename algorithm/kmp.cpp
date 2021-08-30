/**
 * KMP字符串匹配算法
 * https://www.zhihu.com/question/21923021/answer/1032665486
 */
#include <iostream>
#include <vector>
#include <string_view>

using namespace std;

// 生成KMP pattern的next数组,是一个DP算法
vector<int> make_next(string_view str) {
    int n = str.size();
    // 字符串str[0...i]的最大前后缀为next[i]
    vector<int> next(n, 0);
    for (int i = 1; i < n; ++i) {
        int k = next[i - 1];
        while (true) {
            // if next[i - 1] == k and str[k] = str[i] then next[i] >= k + 1
            // if next[i] = k + x + 1 then next[i - 1] >= k + x
            if (str[k] == str[i]) {
                next[i] = k + 1;
                break;
            } else {
                if (k != 0) k = next[k - 1];
                else break;
            }
        }
    }
    return next;
}


// KMP字符串匹配算法:输出pattern在text第一次出现的位置
int KMP(string_view text, string_view pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0;
    if (n < m) return -1;
    vector<int> next = make_next(pattern);
    // text的下标始终不回退
    for (int i = 0, j = 0; i < n; ++i) {
        // 当遇到不匹配时,按next移动,避免不必要的尝试
        while (j != 0 && text[i] != pattern[j]) j = next[j - 1];
        if (text[i] == pattern[j]) ++j;
        if (j == m) return i - m + 1;
    }
    return -1;
}

int main() {
    cout << KMP("hello", "ll") << endl;
    cout << KMP("test_ts", "tet") << endl;
    return 0;
}