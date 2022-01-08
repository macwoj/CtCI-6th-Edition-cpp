#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

using namespace std;
using graphT = unordered_map<string,vector<string>>;
using visitedT = unordered_set<string>;

bool search(const graphT& graph,string a,string b) {
    if (graph.find(a) == graph.end()) return false;
    if (graph.find(b) == graph.end()) return false;
    queue<string> que;
    que.push(a);
    visitedT visited;
    while(!que.empty()) {
        auto curr = que.front();
        que.pop();
        if (b == curr) return true;
        auto [it,isNotVisited] = visited.insert(curr);
        if (isNotVisited) {
            for (auto n:graph.at(curr))
                que.push(n);
        }
    }
    return false;
}

int main() {
    {
        graphT graph{
            {"a",{"b","c"}},
            {"b",{"d"}},
            {"c",{}},
            {"d",{}},
            {"f",{"c"}}
        };
        cout << search(graph,"a","f") << endl;
    }
        {
        graphT graph{
            {"a",{"b","c"}},
            {"b",{"d"}},
            {"c",{"d"}},
            {"d",{"b","f","c"}},
            {"f",{"c"}}
        };
        cout << search(graph,"a","f") << endl;
    }
}