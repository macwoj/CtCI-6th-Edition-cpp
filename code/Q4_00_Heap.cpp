#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

using heapT = vector<int>;

void print(const heapT& heap,int i=0,string prefix="",bool isLeft=false) {
    if (i < heap.size()) {
        std::cout << prefix << (isLeft ? "├──" : "└──" );
        // print the value of the node
        std::cout << heap[i];
        // if (prefix == "")
        //     cout << " " << isBinarySearchTree(node);
        cout << std::endl;
        // enter the next tree level - left and right branch
        print(heap,2*i+1,prefix + (isLeft ? "│  " : "   "), true);
        print(heap,2*i+2, prefix + (isLeft ? "│  " : "   "),false);
    }
}

void heapify(heapT& h,int i) {
    int large = i;
    int l = 2*i+1;
    int r = 2*i+2;
    if (l < h.size() && h[l] > h[large])
        large = l;
    if (r < h.size() && h[r] > h[large])
        large = r;
    if (large != i) {
        swap(h[i],h[large]);
        print(h);
        heapify(h,large);
    }
}

heapT buildHeap(heapT h) {
    //index to the first non leaf node
    int start = h.size()/2 - 1;
    print(h);
    for (int i=start;i>=0;i--) {
        heapify(h,i);
    } 
    return h;
}

void insertHeap(heapT& h, int val) {
    print(h);
    h.push_back(val);
    print(h);
    buildHeap(h);
}

void deleteHeap(heapT& h,int val) {
    print(h);
    int i=0;
    for (i=0;i<h.size();i++) {
        if (h[i] == val)
            break;
    }
    swap(h[i],h.back());
    h.pop_back();
    buildHeap(h);
}

int main() {
    {
        auto h = buildHeap({ 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17,18 });
        cout << "- - - - - -" << endl;
        insertHeap(h,20);
        cout << "- - - - - -" << endl;
        deleteHeap(h,17);
    }
    {
        cout << "- - - - - -" << endl;
        heapT h = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17,18 };
        make_heap(h.begin(),h.end());
        print(h);
        h.push_back(20);
        push_heap(h.begin(),h.end());
        print(h);
        pop_heap(h.begin(),h.end());
        h.pop_back();
        print(h);
    }
    
}