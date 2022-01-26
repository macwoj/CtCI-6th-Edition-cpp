#include <iostream>
using namespace std;
//001 + 001 = 010
//001 + 010 = 011
//010 + 011 = 111
//0-1 = 1
//1-0 = 1
//0-0 = 0
//1-1 = 0 need to carry
//if both are 1 need to carry next bit over

int add(int a,int b) {
    int res = a^b;
    int rem = (a&b)<<1;
    if (rem) {
        return add(res,rem);
    }
    return res;
}

int main() {
    cout << add(759,629) << "=" << 759+629 << endl;
}