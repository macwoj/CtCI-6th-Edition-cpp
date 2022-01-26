#include <vector>
#include <iostream>
using namespace std;

using intT = unsigned long long;
using vecT = vector<intT>;

int binSearch(vecT& array,intT val) {
    int low = 0;
    int high = array.size()-1;
    while(low<=high) {
        auto mid = (low+high)/2;
        if (array[mid]>val)
            high = mid-1;
        else if (array[mid]<val)
            low = mid+1;
        else    
            return mid;
    }
    return -1;
}

int main() {
    {
        vecT arr = {1,2,3,4,5,6,7,8,9};
        cout << binSearch(arr,1) << endl;
        cout << binSearch(arr,9) << endl;
        cout << binSearch(arr,3) << endl;
        cout << binSearch(arr,10) << endl;
    }

}