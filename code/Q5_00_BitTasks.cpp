#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <bitset>
using namespace std;

bool getBit(unsigned long num,int i) {
    return (num) & (1 << i);
}

unsigned long setBit(unsigned long num,int i) {
    return num | (1 << i);
}

void print(unsigned long i) {
    bitset<8> n(i);
    cout << n << endl;
}

unsigned long clearBit(unsigned long num,int i) {
    return num & ~(1ul << i);
}

unsigned long clearBitsMSBthroughI(unsigned long num,int i) {
    return num & ((1ul << i) - 1);
}

unsigned long clearBitsIthrough0(unsigned long num,int i) {
    return num & ~((1ul << i) - 1);
}

unsigned long updateBit(unsigned long num,int i,bool val) {
    if (val) {
        return num | (1<<i);
    } else {
        return num & ~(1<<i);
    }
}

int main() {
    bitset<8> num{"00010001"};
    cout << getBit(num.to_ulong(),0) << endl;
    cout << getBit(num.to_ulong(),1) << endl;
    cout << getBit(num.to_ulong(),4) << endl;
    cout << "set" << endl;
    print(setBit(num.to_ulong(),1));
    print(setBit(num.to_ulong(),0));
    print(setBit(num.to_ulong(),5));
    cout << "clear" << endl;
    print(clearBit(num.to_ulong(),4));
    print(clearBit(num.to_ulong(),0));
    print(clearBit(num.to_ulong(),5));
    bitset<8> num2{"01110101"};
    cout << "clearBitsMSBthroughI" << endl;
    print(clearBitsMSBthroughI(num2.to_ulong(),4));
    cout << "clearBitsIthrough0" << endl;
    print(clearBitsIthrough0(num2.to_ulong(),4));
    cout << "updateBit" << endl;
    print(updateBit(num2.to_ulong(),4,true));
    print(updateBit(num2.to_ulong(),4,false));
    print(updateBit(num2.to_ulong(),3,true));
    print(updateBit(num2.to_ulong(),3,false));
}