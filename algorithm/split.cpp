#include <string_view>
#include <vector>
#include <iostream>
using namespace std;

/**
 * 见 https://www.zhihu.com/question/36642771/answer/865135551
 * @param str 待分隔的字符串
 * @param delimiters 分隔符
 * @param tokens 分隔后存放位置
 */
void split(string_view str, vector<string_view>& tokens, string_view delimiters = " ") {
    string_view::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string_view::size_type pos = str.find_first_of(delimiters, lastPos);
    while (pos != string_view::npos || lastPos != string_view::npos) {
        tokens.emplace_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters,pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

int main() {
    vector<string_view> tokens;
    split(" i love you! ", tokens);
    for (auto x : tokens) cout << "**"<< x << "**" << endl;
}
