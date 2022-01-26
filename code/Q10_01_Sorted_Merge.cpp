#include <iostream>
#include <vector>
using namespace std;
using intT = long long;
using vecT = vector<intT>;

void sortedMerge(vecT& a, const vecT& b,int sizeA,int sizeB) {
    int ia = sizeA-1;
    int ib = sizeB-1;
    int i = a.size()-1;
    while (ib>=0) {
        if (a[ia]>b[ib]) {
            a[i] = a[ia];
            i--;
            ia--;
        } else {
            a[i] = b[ib];
            i--;
            ib--;
        }
    }
}

int main() {
    auto print = [](auto v) {
        for (auto e:v)
            cout << e << " ";
        cout << endl;
     };
     {
         vecT a {0,2,4,6,8,10,-1,-1,-1,-1,-1,-1};
         vecT b {1,3,5,7,9,11};
         sortedMerge(a,b,6,6);
         print(a);
     }
}