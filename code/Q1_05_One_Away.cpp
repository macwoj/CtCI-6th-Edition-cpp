#include <string>
#include <tuple>
#include <vector>
#include <iostream>
using namespace std;

bool oneEditReplace(string first, string second) {
    bool found = false;
    for (int i=0;i<first.length();i++) {
        if (first[i]!=second[i]) {
            if (found)
                return false;
            found = true;
        }
    }
    return true;
}

bool oneEditInsert(string first, string second) {
    int i = 0;
    int j = 0;
    for (;i<first.length() && j<second.length();i++,j++) {
        if (first[i]!=second[j]) {
            if (i!=j)
                return false;
            j++;
        }
    }
    return true;
}

bool oneEditAway(string first, string second) {
    if (first.length() == second.length()) {
        return oneEditReplace(first,second);
    } else if (first.length() == second.length()-1) {
        return oneEditInsert(first,second);
    } else if (first.length()-1 == second.length()) {
        return oneEditInsert(second,first);
    }
    return false;
}

int main() {
    vector<tuple<string,string>> tests = {
        {"pale","bale"},
        {"pale","bales"},
        {"bale","bales"},
        {"ale","bale"},
        {"bale","ale"},
        {"bale","ble"},
    };
    for (auto [first,second]:tests) {
        cout << first << " " << second << " " << oneEditAway(first,second) << endl;
    }
}