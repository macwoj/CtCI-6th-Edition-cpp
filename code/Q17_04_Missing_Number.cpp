#include <iostream>
#include <vector>
using namespace std;

using vecT = vector<int>;

bool getBit(int num,int bit) {
    return num & (1<<bit);
}

int findMissing(const vecT& arr,int bit) {
    if (bit >= sizeof(int)*8) {
        return 0;
    }
    vecT ones;
    vecT zeros;
    for (auto n:arr) {
        if (getBit(n,bit)) {
            ones.push_back(n);
        } else {
            zeros.push_back(n);
        }
    }
    if (zeros.size() <= ones.size()) {
        auto v = findMissing(zeros,bit+1);
        return (v<<1)|0;
    } else {
        auto v = findMissing(ones,bit+1);
        return (v<<1)|1;
    }
}
//000 001 010 011 100 exp 3 0's and 2 1's
//000 001 010 011 exp 2 0's and 2 1's
int findMissing(const vecT& arr) {
    return findMissing(arr,0);
}

int main() {
    cout << findMissing({0,1,2,4}) << endl;
    cout << findMissing({1,2,3,4}) << endl;
}