#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
void swapNumbers(int& a,int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

int main() {
    vector<tuple<int,int>> data = {
        {5,6},
        {3,1}
    };
    for (auto [a,b]:data)
    {
        swapNumbers(a,b);
        cout << a << " " << b << endl;
    }
}