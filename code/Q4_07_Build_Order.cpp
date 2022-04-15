#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <stack>
using namespace std;

inline static int verbse = 0;

using nodeT = char;
using vecT = vector<nodeT>;
using mapT = unordered_map<nodeT,vecT>;
using setT = unordered_set<nodeT>;
using staT = stack<nodeT>;

bool topologicalSort(nodeT v,const mapT& graph,setT& visited,setT cycle,staT& sta) {
    visited.insert(v);
    cycle.insert(v);
    for (auto edge:graph.at(v)) {
        if (cycle.find(edge)!=cycle.end()) {//found cycle
            return false;
        }
        if (visited.find(edge)==visited.end()) {
            if (!topologicalSort(edge,graph,visited,cycle,sta))
                return false;
        }
    }
    sta.push(v);
    return true;
}

vecT buildOrder(const mapT& graph) {
    staT sta;
    setT visited;
    for (auto [v,edges]:graph) {
        if (visited.find(v)==visited.end()) {
            setT cycle;
            if (!topologicalSort(v,graph,visited,cycle,sta))
                return {};
        }
    }
    vecT res;
    while(!sta.empty()) {
        res.push_back(sta.top());
        sta.pop();
    }
    return res;
}

void print(vecT v) {
    for (auto i:v) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    {
        mapT graph = {
            {'a',{'e'}},
            {'b',{'a','h'}},
            {'c',{'a'}},
            {'d',{'g'}},
            {'e',{}},
            {'f',{'c','b'}},
            {'g',{}},
            {'h',{}}
        };
        print(buildOrder(graph));
    }
    {
        mapT graph = {
            {'a',{'e'}},
            {'b',{'a','h'}},
            {'c',{'a'}},
            {'d',{'g'}},
            {'e',{'a'}},
            {'f',{'c','b'}},
            {'g',{}},
            {'h',{}}
        };
        //cycle
        print(buildOrder(graph));
    }
}