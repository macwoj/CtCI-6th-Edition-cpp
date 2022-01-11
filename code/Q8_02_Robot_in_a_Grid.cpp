#include <vector>
#include <list>
#include <unordered_map>
#include <tuple>
#include <iostream>
using namespace std;
using pT = tuple<int,int>;
using gridT = vector<vector<bool>>;
using pathT = list<pT>;
struct hasher {
    size_t operator()(const pT& p) const {
        auto [a,b] = p;
        return hash<int>()(a) ^ hash<int>()(b);
    }
};
using memoT = unordered_map<pT,pathT,hasher>;
using memoPtr = shared_ptr<memoT>;

pathT findPath(const gridT& g,int r,int c,memoPtr memo = make_shared<memoT>()) {
    if (r<0 || r >= g.size()) return {};
    if (c<0 || c >= g[0].size()) return {};
    if (!g[r][c]) return {};
    if (r==g.size()-1 && c==g.size()-1) return {{r,c}};
    auto it = memo->find({r,c});
    if (it!=memo->end())
        return it->second;
    auto res = findPath(g,r+1,c,memo);
    if (res.empty())
        res = findPath(g,r,c+1,memo);
    if (!res.empty())
        res.push_front({r,c});
    memo->insert({{r,c},res});
    return res;
}
pathT findPath(const gridT& g) {
    return findPath(g,0,0);
}

void print(gridT g,pathT p) {
    for (auto r:g) {
        for (auto c:r) {
            cout << c << " ";
        }
        cout << endl;
    }
    for (auto x:p) {
        auto [r,c] = x;
        cout << r << "," << c << " ";
    }
    cout << endl;
}

int main() {
    {
        gridT g = {
            {1,1,1,1,1,1},
            {0,0,0,0,0,1},
            {0,0,0,0,0,1},
            {0,0,0,0,0,1},
            {0,0,0,0,0,1},
            {0,0,0,0,0,1}
        };
        print(g,findPath(g));
    }
        {
        gridT g = {
            {1,1,1,1,1,1},
            {0,0,0,0,0,1},
            {0,0,0,0,0,0},
            {0,0,0,0,0,1},
            {0,0,0,0,0,1},
            {0,0,0,0,0,1}
        };
        print(g,findPath(g));
    }
        {
        gridT g = {
            {1,1,1,1,1,0},
            {0,0,0,1,1,1},
            {0,0,0,1,0,1},
            {0,0,0,1,0,1},
            {0,0,0,1,0,1},
            {0,0,0,1,0,1}
        };
        print(g,findPath(g));
    }
}