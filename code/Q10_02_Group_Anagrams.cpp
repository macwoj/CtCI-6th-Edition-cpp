#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

using vecT = vector<string>;
using mapT = unordered_map<string,vecT>;

vecT sortAnagrams(const vecT& words) {
    mapT map;
    for (auto w:words) {
        auto key = w;
        sort(key.begin(),key.end());
        auto [it,isNew] = map.insert({key,{}});
        it->second.push_back(w);
    }
    vecT res;
    for (auto it:map) {
        for (auto w:it.second) {
            res.push_back(w);
        }
    }
    return res;
}

int main() {
    auto print = [](auto v) {
        for (auto w:v) {
            cout << w << " ";
        }
        cout << endl;
    };
    {
        vecT words = {"aba","cda","dfe","baa","fde","aab"};
        print(sortAnagrams(words));
    }
}