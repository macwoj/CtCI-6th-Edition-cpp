#include <string>
#include <unordered_set>
#include <iostream>
#include <bitset>

using namespace std;
using setT = unordered_set<char>;

bool isUnique0(string str) {
    setT chars;
    for (auto c:str) {
        auto [it,is_uniq] = chars.insert(c);
        if (!is_uniq)
            return false;
    }
    return true;
}

bool isUnique1(string str) {
    bitset<128> chars = {};
    for (auto c:str) {
        if (chars[c] == 1) 
            return false;
        chars[c] = 1;
    }
    return true;
}

bool isUnique2(string str) {
    for (int i=0;i<str.size();i++) {
        for (int j=0;j<str.size();j++) {
            if (str[i]==str[j] && i!=j)
                return false;
        }
    }
    return true;
}

int main() {
    cout << isUnique0("abcdef") << endl;
    cout << isUnique0("abcdeff") << endl;
    cout << isUnique1("abcdef") << endl;
    cout << isUnique1("abcdeff") << endl;
    cout << isUnique2("abcdef") << endl;
    cout << isUnique2("abcdeff") << endl;
}