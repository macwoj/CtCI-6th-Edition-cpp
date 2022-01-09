#include <bitset>
#include <iostream>
using namespace std;

using uint = unsigned int;

uint insertMintoN(uint n,uint m,int i,int j) {
    if (i < 0 || j < 0 || i > 31 || j > 31)
        return 0;
    int length = j - i + 1;
    uint mask = (1 << length) - 1;
    n = n & ~(mask << i);
    n = n | (m << i);
    return n;
}

int main () {
    cout << bitset<12>(insertMintoN(
        bitset<12>("10000000000").to_ulong(),
        bitset<12>("10011").to_ulong(),
        2,6)) << endl;
    cout << bitset<12>(insertMintoN(
        bitset<12>("10000000000").to_ulong(),
        bitset<12>("10011").to_ulong(),
        7,11)) << endl;
}