#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

bool isPalindromePermutation(string str) {
    unordered_map<char,int> counts;
    for (auto c:str) {
        c = tolower(c);
        if (c>='a' && c<='z') {
            auto [it,isnew] = counts.insert({c,0});
            it->second++;
        }
    }
    int odd_count = 0;
    for (auto it:counts) {
        // cout << it.first << " " << it.second << endl;
        if (it.second%2 == 1)
            odd_count++;
    }
    return odd_count <= 1;
}

bool isPalindromePermutation1(string str) {
    bitset<128> chars;
    for (auto c:str) {
        c = tolower(c);
        if (c>='a' && c<='z') {
            chars.flip(c);
        }
    }
    return chars.count() <= 1;
}

bool isPalindromePermutation2(string str) {
    bitset<64> chars;
    for (auto c:str) {
        c = tolower(c);
        if (c>='a' && c<='z') {
            chars.flip(c-'a');
        }
    }
    auto num = chars.to_ullong();
    return (num & (num -1)) == 0;
}

bool isPalindromePermutation3(string str) {
    unsigned long long chars = 0;
    for (auto c:str) {
        c = tolower(c);
        if (c>='a' && c<='z') {
            chars ^= 1 << c;
        }
    }
    return (chars & (chars -1)) == 0;
}

int main() {
    vector<string> input = {
        "Rats live on no evil star",
        "asda",
        "aabb",
        "aabbc",
        "aabbcd",
        "A man, a plan, a canal, panama",
		"Lleve",
		"Tacotac"};
    for (auto test:input) {
        cout << test << " " << isPalindromePermutation(test) << endl;
        cout << test << " " << isPalindromePermutation1(test) << endl;
        cout << test << " " << isPalindromePermutation2(test) << endl;
        cout << test << " " << isPalindromePermutation3(test) << endl;
    }
    
}