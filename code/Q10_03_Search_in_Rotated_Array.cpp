#include <iostream>
#include <vector>
using namespace std;

using vecT = vector<int>;

int binSearch(int n, const vecT& array, int start, int end) {
    if (end < start)
        return -1;
    int mid = (start+end)/2;
    if (array[mid] == n)
        return mid;
    if (n < array[mid]) {
        return binSearch(n,array,start,mid-1);
    } else {
        return binSearch(n,array,mid+1,end);
    }
}

int linearSearch(int n, const vecT& array, int start, int end) {
    for (int i=start;i<=end;i++) {
        if (array[i] == n)
            return i;
    }
    return -1;
}

int searchRotated(int n, const vecT& array, int start, int end) {
    if (end < start)
        return -1;
    if (array[start] == array[end])
        return linearSearch(n,array,start,end);
    int mid = (start+end)/2;
    if (array[mid] == n)
        return mid;
    if (array[start] == n)
        return start;
    if (array[end] == n)
        return end;
    if (array[start] < array[mid]) {
        if (n < array[mid] && n >= array[start]) {
            return binSearch(n,array,start,mid-1);
        }
        else {
            return searchRotated(n,array,mid+1,end);
        }
    } else {
        if (n > array[mid] && n <= array[end]) {
            return binSearch(n,array,mid+1,end);
        }
        else {
            return searchRotated(n,array,start,mid-1);
        }
    }
    return -1;
}

int searchRotated(int n, const vecT& array) {
    return searchRotated(n,array,0,array.size()-1);
}

int main() {
    cout << searchRotated(5, {10, 15, 20, 0, 5}) << endl;
    cout << searchRotated(5, {50, 5, 20, 30, 40}) << endl;
    cout << searchRotated(5, {10,11,12, 15, 20, 21,0,1, 5}) << endl;
    cout << searchRotated(5, {50, 5,6,7,8, 20, 30, 40}) << endl;
    cout << searchRotated(5, {5,6,7,8, 20, 30, 40}) << endl;
    cout << searchRotated(5, {50,51, 5,6,7,8, 20, 30, 40}) << endl;
    cout << searchRotated(5, {50,51,51, 5,6,6,6,7,8, 20, 30, 40}) << endl;
    cout << searchRotated(5, {2,2,2,2,2,2,2,5,2,2}) << endl;
}