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
    weak_ptr<Node> parent_;
    T data_;
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
            if (!front->left_) {
                front->left_ = node;
                node->parent_ = front;
            }
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

nodePtr nextLeftNode(nodePtr node) {
    if (!node->left_)
        return node;
    return nextLeftNode(node->left_);
}

nodePtr findLeftChildParent(nodePtr node) {
    auto parent = node->parent_.lock();
    if (!parent)
        return {};
    //if left child return parent
    if (parent->left_ && node.get() == parent->left_.get()) {
        return parent;
    }
    return findLeftChildParent(parent);
}

//left , curr, right
nodePtr nextNode(nodePtr node) {
    if (!node)
        return {};
    if (node->right_) {
        return nextLeftNode(node->right_);
    }
    return findLeftChildParent(node);
}

int main () {
    {
        cout << (nextNode({})==nullptr) << endl;
    }
    {
        auto head = createTree({1,2,3});
        cout << nextNode(head)->data_ << endl;
    }
    {
        auto head = createTree({1,2,3});
        cout << nextNode(head->left_)->data_ << endl;
    }
    {
        auto head = createTree({1,2,3,4,5,6,7,8,9,10,11,12});
        auto start = head->right_->left_;
        cout << start->data_ << " " << nextNode(start)->data_ << endl;
    }
}