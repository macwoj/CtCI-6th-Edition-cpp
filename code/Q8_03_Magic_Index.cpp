#include <iostream>
#include <vector>
using namespace std;
using vecT = vector<int>;

int magicIndex(const vecT array,int start,int end) {
    int mid = (start+end)/2;
    if (array[mid] == mid)
        return mid;
    if (start >= end)
        return -1;
    if (mid > array[mid]) {
        return magicIndex(array,mid+1,end);
    } else {
        return magicIndex(array,start,mid-1);
    }

}

int magicIndex(const vecT array) {
    return magicIndex(array,0,array.size()-1);
}

int main() {
    cout << magicIndex({3,4,5,6,7,8}) << endl;
    cout << magicIndex({0,3,4,5,6,7,8}) << endl;
    cout << magicIndex({-10,-5,-4,-3,4,7,8}) << endl;
}