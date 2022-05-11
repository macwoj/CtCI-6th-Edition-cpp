#include <string>
#include <iostream>

using namespace std;

bool isSubstring(string s1,string s2) {
    auto res = s1.find(s2);
    return res != string::npos;
}

bool isRotation(string s1,string s2) {
    if (s1.size() == s2.size() && !s1.empty()) {
        auto s = s1+s1;
        return isSubstring(s,s2);
    }
    return false;
}

int main() {
    cout << isRotation("bottler","erbottl") << endl;
    cout << isRotation("bottler","erdottl") << endl;

}