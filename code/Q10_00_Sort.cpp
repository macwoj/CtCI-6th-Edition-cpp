#include <vector>
#include <iostream>
using namespace std;
using intT = long long;
using vecT = vector<intT>;

void bubbleSort(vecT& array) {
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true; 
        for (int i=1;i<array.size();i++) {
            if (array[i] < array[i-1]) {
                swap(array[i],array[i-1]);
                isSorted = false;
            }
        }
    }
}

void merge(vecT& array,int start,int mid,int end,vecT& tmp) {
    //copy the current slices into a tmp array
    for (int i=start;i<=end;i++) {
        tmp[i] = array[i];
    }
    int l = start;
    int r = mid+1;
    int i = start;
    //each one should be sorted so now we must walk
    //through each one and create a sorted merged version
    while (l <= mid && r <= end) {
        if (tmp[l] < tmp[r]) {
            array[i] = tmp[l];
            l++;
        } else {
            array[i] = tmp[r];
            r++;
        }
        i++;
    }
    //only copy the left side thats left over
    //the right is already there in the starting array
    while (l <= mid) {
        array[i] = tmp[l];
        l++;
        i++;
    }
}

void mergeSort(vecT& array,int start,int end,vecT& tmp) {
    if (start >= end) 
        return;
    auto mid = (start+end)/2;
    mergeSort(array,start,mid,tmp);
    mergeSort(array,mid+1,end,tmp);
    merge(array,start,mid,end,tmp);
}

void mergeSort(vecT& array) {
    vecT tmp(array.size());
    mergeSort(array,0,array.size()-1,tmp);
}

int partition(vecT& array,int left,int right) {
    auto pind = (left+right)/2;
    // for_each(array.begin(),array.end(),[](auto i) { cout << i << " ";});
    // cout << endl;
    auto pivot = array[pind];
    // cout << "pivot=" << pivot << endl;
    while (left<=right) {
        //find first element that should be on the right
        while (array[left]<pivot) left++;
        while (array[right]>pivot) right--;
        if (left<=right) {
            swap(array[left],array[right]);
            // for_each(array.begin(),array.end(),[](auto i) { cout << i << " ";});
            // cout << endl;
            left++;
            right--;
        }
    }
    // cout << "left=" << left << endl;
    return left;
}

void quickSort(vecT& array,int left,int right) {
    auto ind = partition(array,left,right);
    if (left<ind-1)
        quickSort(array,left,ind-1);
    if (ind<right)
        quickSort(array,ind,right);
}

void quickSort(vecT& array) {
    quickSort(array,0,array.size()-1);
}

int main() {
    {
        vecT v = {5,2,6,8,9,5,10,100,2,-1,-45,3,23};
        bubbleSort(v);
        for_each(v.begin(),v.end(),[](auto i) { cout << i << " ";});
        cout << endl;
    }
    {
        vecT v = {5,2,6,8,9,5,10,100,2,-1,-45,3,23};
        mergeSort(v);
        for_each(v.begin(),v.end(),[](auto i) { cout << i << " ";});
        cout << endl;
    }
    {
        vecT v = {5,2,6,8,9,5,10,100,2,-1,-45,3,23};
        quickSort(v);
        for_each(v.begin(),v.end(),[](auto i) { cout << i << " ";});
        cout << endl;
    }
}