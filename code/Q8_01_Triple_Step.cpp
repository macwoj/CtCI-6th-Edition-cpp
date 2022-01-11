#include <unordered_map>
#include <memory>
#include <iostream>
using namespace std;

using intT = long long;
using memoT = unordered_map<intT,intT>;
using memoPtr = shared_ptr<memoT>;

intT countWays(intT n,memoPtr memo = make_shared<memoT>()) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    auto it = memo->find(n);
    if (it!=memo->end())
        return it->second;
    auto res = countWays(n-1,memo) + countWays(n-2,memo) + countWays(n-3,memo);
    memo->insert({n,res});
    return res;
}

int main() {
    for (int i=0;i<30;i++) {
        cout << i << "=" << countWays(i) << " ways" << endl;
    }
}