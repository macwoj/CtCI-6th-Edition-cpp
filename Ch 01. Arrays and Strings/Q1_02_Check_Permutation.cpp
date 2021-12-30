#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
using mapT = unordered_map<char,int>;

// time - O(n) space - O(n)
bool checkPermutation(string a,string b) {
    mapT map_a;
    mapT map_b;
    for (auto c:a) {
        auto [it,isnew] = map_a.insert({c,0});
        it->second++;
    }
    for (auto c:b) {
        auto [it,isnew] = map_b.insert({c,0});
        it->second++;
    }
    return map_a == map_b;
}

//time - O(n log n) space - O(1)
bool checkPermutationInplace(string a,string b) {
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    return a==b;
}

int main () {
    cout << checkPermutation("aabc","bcaa") << endl;
    cout << checkPermutation("aabc","ccaa") << endl;
    cout << checkPermutationInplace("aabc","bcaa") << endl;
    cout << checkPermutationInplace("aabc","ccaa") << endl;
}