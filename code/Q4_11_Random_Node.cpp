#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <queue>
#include <unordered_set>
#include <sstream>
using namespace std;

inline static int verbose = 0;

template<typename T>
struct Node {
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
    T data_;
    int size_;
    Node(T d):data_(d) {}
};

using nodeT = Node<int>;
using nodePtr = shared_ptr<nodeT>;

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
        std::cout << node->data_ << "(" << node->size_ << ")";
        cout << std::endl;
        // enter the next tree level - left and right branch
        print(node->left_,prefix + (isLeft ? "│  " : "   "), true);
        print(node->right_, prefix + (isLeft ? "│  " : "   "),false);
    }
}

void calcSize(nodePtr node) {
    if (!node)
        return;
    calcSize(node->left_);
    calcSize(node->right_);
    int left = (node->left_) ? node->left_->size_ : 0;
    int right = (node->right_) ? node->right_->size_ : 0;
    node->size_ = left + right + 1;
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
            if (!front->left_) {
                front->left_ = node;
            }
            else if(!front->right_) {
                front->right_ = node;
                currLevel.pop();
            }
        }
    }
    clean(head);
    calcSize(head);
    return head;
}

nodePtr randomNode(nodePtr node, int randNumber) {
    int n = randNumber;
    if (node->left_)
        n -= node->left_->size_;
    if (n<0)
        return randomNode(node->left_,randNumber);
    else if (n==0)
        return node;
    else
        return randomNode(node->right_,n-1);
}

nodePtr randomNode(nodePtr node) {
    int r = rand()%(node->size_);
    cout << "rand=" << r << endl;
    return randomNode(node,r);
}

int main() {
    srand (time(NULL));
    {
        auto tree = createTree({1,2,3});
        cout << randomNode(tree)->data_ << endl;
        cout << randomNode(tree)->data_ << endl;
        cout << randomNode(tree)->data_ << endl;
        cout << randomNode(tree)->data_ << endl;
        cout << randomNode(tree)->data_ << endl;
    }
    // {
    //     vector<int> t;
    //     for (int i=0;i<100;i++) {
    //         t.push_back(i);
    //     }
    //     auto tree = createTree(t);
    //     print(tree);
    // }
}