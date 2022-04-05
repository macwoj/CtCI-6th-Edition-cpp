#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <queue>
using namespace std;

inline static int verbose = 0;

template<typename T>
struct Node {
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
    T data_;
    Node(T d):data_(d) {}
};

using nodeT = Node<int>;
using nodePtr = shared_ptr<nodeT>;
using resT = tuple<bool,int,int>; // valid,min,max

void clean(nodePtr node) {
    if (node!=nullptr) {
        if (node->left_) {
            if (node->left_->data_ < 0)
                node->left_ = nullptr;
            else
                clean(node->left_);
        }
        if (node->right_) {
            if (node->right_->data_ < 0)
                node->right_ = nullptr;
            else
                clean(node->right_);
        }
    }
}

void print(nodePtr node,string prefix="",bool isLeft=false) {
    if (node) {
        std::cout << prefix << (isLeft ? "├──" : "└──" );
        // print the value of the node
        std::cout << node->data_;
        cout << std::endl;
        // enter the next tree level - left and right branch
        print(node->left_,prefix + (isLeft ? "│  " : "   "), true);
        print(node->right_, prefix + (isLeft ? "│  " : "   "),false);
    }
}

nodePtr createTree(const vector<int> values) {
    auto it = values.begin();
    it++;
    nodePtr head = make_shared<nodeT>(values.front());
    queue<nodePtr> currLevel,nextLevel;
    currLevel.push(head);
    for (;it!=values.end();++it) {
        if (verbose > 0)
            cout << *it << endl;
        if (currLevel.empty())
            currLevel = move(nextLevel);
        if (!currLevel.empty()) {
            auto node = make_shared<nodeT>(*it);
            nextLevel.push(node);
            auto front = currLevel.front();
            if (!front->left_)
                front->left_ = node;
            else if(!front->right_) {
                front->right_ = node;
                currLevel.pop();
            }
        }
    }
    clean(head);
    print(head);
    return head;
}

resT isValidBSTImpl(nodePtr node) {
    if (!node) {
        return {true,numeric_limits<int>::max(),-numeric_limits<int>::max()};
    }
    auto [lvalid,lmin,lmax] = isValidBSTImpl(node->left_);
    if (node->left_)
        lvalid &= (node->left_->data_ <= node->data_) && (lmax <= node->data_);
    auto [rvalid,rmin,rmax] = isValidBSTImpl(node->right_);
    if (node->right_)
        rvalid &= (node->data_ < node->right_->data_) && (node->data_ < rmin);
    return {lvalid && rvalid,min(node->data_,min(lmin,rmin)),max(node->data_,max(lmax,rmax))};
}
//left <= curr < right
bool isValidBST(nodePtr node) {
    auto [isValid,_,__] = isValidBSTImpl(node);
    return isValid;
}

int main() {
    cout << isValidBST(createTree({20,10,30,-1,25})) << endl;
    cout << isValidBST(createTree({20,10,30,-1,-1,25})) << endl;
}