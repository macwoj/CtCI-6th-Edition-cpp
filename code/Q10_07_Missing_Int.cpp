#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

template <int TSize>
int findMissingInt(vector<int> input) {
    bitset<TSize> bits;
    for (auto i:input) {
        bits.set(i);
    }
    for (int i=0;i<=numeric_limits<int>::max();i++) {
        if (!bits[i])
            return i;
    }
    return -1;
}

int findMissingInt(vector<int> input, int range) {
    int byteSize = range/8;
    if (range%8 > 0)
        byteSize++;
    vector<unsigned int> bits(byteSize,0);
    for (auto i:input) {
        bits[i/8] |= 1<<i%8;
    }
    for (int i=0;i<bits.size()*8;i++) {
        auto res = bits[i/8] & 1<<i%8;
        if (!res)
            return i;
    }
    return -1;
}

int findMissing2(vector<int> input,int range,int maxRange) {
    vector<int> blocks(maxRange/range,0);
    for (auto i:input)
        blocks[i/range]++;
    int block = -1;
    for (int i=0;i<blocks.size();i++) {
        if (blocks[i]!=range) {
            block = i;
            break;
        }
    }
    int low = range * block;
    int high = range * (block + 1);
    vector<bool> bits(range,0);
    for (auto i:input) {
        if (i>=low && i<high) {
            bits[i-low] = 1;
        }
    }
    for (int i=0;i<bits.size();i++) {
        if (!bits[i])
            return i+low;
    }
    return -1;
}

int main() {
    cout << findMissingInt<5>({0,1,2,3}) << endl;
    cout << findMissingInt({0,1,2,3,4,6,7,8},9) << endl;
    cout << findMissingInt({0,1,2,3,4,5,6,7},9) << endl;
    {
        vector<int> in;
        for (int i=0;i<100;i++) {
            if (i!=59) {
                in.push_back(i);
            }
        }
        cout << findMissing2(in,10,100) << endl;
    }
}