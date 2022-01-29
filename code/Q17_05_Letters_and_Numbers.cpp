#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>
using namespace std;

string findLongestSubarray(string array) {
    vector<int> a(array.length(),0);
    vector<int> b(array.length(),0);
    for (int i=0;i<array.length();i++) {
        a[i] = i>0 ? a[i-1] : 0;
        b[i] = i>0 ? b[i-1] : 0;
        if (array[i] == 'a') {
            a[i]++;
        } else {
            b[i]++;
        }
    }
    vector<int> diff(array.length(),0);
    unordered_map<int,int> lut;
    for (int i=0;i<diff.size();i++) {
        diff[i] = a[i] - b[i];
        lut.insert({diff[i],i});
    }
    // for (auto i:a) cout << i << " ";
    // cout << endl;
    // for (auto i:b) cout << i << " ";
    // cout << endl;
    // for (auto i:diff) cout << i << " ";
    // cout << endl;
    tuple<int,int,int> max{0,-1,-1};
    for (int i=1;i<diff.size();i++) {
        auto it = lut.find(diff[i]);
        if (it != lut.end()) {
            if (i-it->second > get<0>(max)) {
                max = {i-it->second,it->second,i};
            }
        }
    }
    auto [length,start,end] = max;
    return array.substr(start + 1,end-start);
}

bool check(string array) {
    int a = 0;
    int b = 0;
    for (int i=0;i<array.length();i++) {
        if (array[i]=='a')
            a++;
        else
            b++;
    }
    return a==b;
}

//abababbbbbaaaaabababbaaaaaaa
//11223
//01122
//1010
//aaaaabbaa
//123455567
//000001222
//123454345
//if sum equals the  its the next index on left
int main() {
    vector<string> tests = {"aaaabba","abababbbbbaaaaabababbaaaaaaa"};
    for (auto test:tests) {
        cout << test << " " 
            << findLongestSubarray(test) << " " << check(findLongestSubarray(test)) << endl;
    }
}