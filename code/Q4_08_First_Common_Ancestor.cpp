#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <queue>
#include <unordered_set>
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
                node->parent_ = front;
                currLevel.pop();
            }
        }
    }
    clean(head);
    print(head);
    return head;
}

nodePtr findAncestorImpl(nodePtr node,nodePtr n1,nodePtr n2) {
    if (!node) {
        return {};
    }
    if (node == n1)
        return n1;
    if (node == n2)
        return n2;
    auto left = findAncestorImpl(node->left_,n1,n2);
    auto right = findAncestorImpl(node->right_,n1,n2);
    bool found1 = left==n1 || right==n1;
    bool found2 = left==n2 || right==n2;
    if (found1 && found2)
        return node;
    if (left)
        return left;
    if (right)
        return right;
    return {};
}

nodePtr findAncestor(nodePtr head,nodePtr n1,nodePtr n2) {
    cout << "Looking for " << n1->data_ << " " << n2->data_ << endl;
    auto node = findAncestorImpl(head,n1,n2);
    if (node && node != n1 && node != n2) {
        cout << "Found " << node->data_ << endl;
        return node;
    }
    return {};
}

nodePtr findAncestorParent(nodePtr n1,nodePtr n2) {
    cout << "Looking for " << n1->data_ << " " << n2->data_ << endl;
    unordered_set<nodePtr> path1;
    while (n1) {
        path1.insert(n1);
        n1 = n1->parent_.lock();
    }
    while (n2) {
        if (path1.find(n2)!=path1.end()) {
            cout << "Found " << n2->data_ << endl;
            break;
        }
        n2 = n2->parent_.lock();
    }
    return n2;
}

int main() {
    {
        auto head = createTree({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17});
        findAncestor(head,head->left_->left_->left_,head->left_->right_->left_);
        findAncestorParent(head->left_->left_->left_,head->left_->right_->left_);
        findAncestor(head,head->left_->left_->left_->right_,head->left_->left_->right_);
        findAncestorParent(head->left_->left_->left_->right_,head->left_->left_->right_);
        findAncestor(head,head->left_->left_->left_->right_,head->right_->left_->right_);
    }
}