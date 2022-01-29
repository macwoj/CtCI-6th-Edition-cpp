#include <sstream>
#include <string>
#include <iostream>
using namespace std;

string compressString(string str) {
    if (str.empty()) return "";
    stringstream ss;
    char prev = str[0];
    int  count = 0;
    for (auto c:str) {
        if (prev!=c) {
            ss << prev << count;
            prev = c;
            count = 1;
        } else {
            count++;
        }
    }
    ss << prev << count;

    return  ss.str();
}

int main() {
    cout << compressString("aabcccccaaa") << endl;
}