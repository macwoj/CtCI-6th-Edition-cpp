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
            }
            else if(!front->right_) {
                front->right_ = node;
                currLevel.pop();
            }
        }
    }
    clean(head);
    return head;
}

string createTreeString(nodePtr node) {
    if (!node)
        return "X";
    stringstream ss;
    auto left = createTreeString(node->left_);
    auto right = createTreeString(node->right_);
    ss << node->data_ << ',' << left << ',' << right;
    return ss.str();
}


bool checkSubtree(nodePtr tree,nodePtr subtree) {
    auto stree = createTreeString(tree);
    auto ssubtree = createTreeString(subtree);
    auto res = stree.find(ssubtree);
    return res != string::npos;
}

int main() {
    {
        vector<int> t,tt;
        for (int i=0;i<100;i++) {
            t.push_back(i);
            tt.push_back(1000+i);
        }
        auto tree = createTree(t);
        auto sub = createTree(tt);
        cout << checkSubtree(tree,tree->left_->left_) << endl;
        cout << checkSubtree(tree,sub->left_->left_) << endl;
    }

}