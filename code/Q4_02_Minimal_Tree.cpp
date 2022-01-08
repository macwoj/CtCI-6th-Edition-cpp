#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

template<typename T>
struct Node {
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
    T data_;
    Node(T d):data_(d) {}
};

using nodeT = Node<int>;
using nodePtr = shared_ptr<nodeT>;

//10 , mid = 10/2 = 5
//  0,4 mid = 2
//      0,1 mid = 0
//          0,-1 1,1
//  6,10 16/2=9 mid = 8
//      6,7 mid =6
//      9,10

nodePtr minimalTree(const vector<int>& array, int start,int end) {
    if (start > end) return {};
    if (start < 0 || start >= array.size()) return {};
    if (end < 0 || end >= array.size()) return {};
    if (start == end) return make_shared<nodeT>(array[start]);
    auto mid = (start+end) / 2;
    auto node = make_shared<nodeT>(array[mid]);
    node->left_ = minimalTree(array,start,mid-1);
    node->right_ = minimalTree(array,mid+1,end);
    return node;
}

nodePtr minimalTree(const vector<int>& array) {
    return minimalTree(array,0,array.size()-1);
}

bool isBinarySearchTree(nodePtr node) {
    if (node) {
        if (node->left_) {
            if (node->data_ < node->left_->data_)
                return false;
            if (!isBinarySearchTree(node->left_))
                return false;
        }
        if (node->right_) {
            if (node->data_ > node->right_->data_)
                return false;
            if (!isBinarySearchTree(node->right_))
                return false;
        }
    }
    return true;
}

void print(nodePtr node,string prefix="",bool isLeft=false) {
    if (node) {
        std::cout << prefix << (isLeft ? "├──" : "└──" );
        // print the value of the node
        std::cout << node->data_;
        if (prefix == "")
            cout << " " << isBinarySearchTree(node);
        cout << std::endl;
        // enter the next tree level - left and right branch
        print(node->left_,prefix + (isLeft ? "│  " : "   "), true);
        print(node->right_, prefix + (isLeft ? "│  " : "   "),false);
    }
}

int main() {
    print(minimalTree({0,1,2,3,4,5}));
    print(minimalTree({0,1}));
    print(minimalTree({0,1,2}));
    print(minimalTree({0,1,2,3,4,5,6,7,8,10}));
    print(minimalTree({3,1,2,3,4,5}));
}