#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <queue>
using namespace std;

inline static int verbose = 0;

template <typename T>
struct Node {
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
    T data_;
    Node(T d): data_(d) {}
};

using nodeT = Node<int>;
using nodePtr = shared_ptr<nodeT>;

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

using levelT = vector<vector<int>>;

levelT createLevelLinkedList(nodePtr head) {
    levelT res;
    int level = 0;
    vector<nodePtr> q,child;
    q.push_back(head);//1
    while (!q.empty()) {
        while (res.size() < level + 1) {
            res.push_back({});
        }
        for (auto n:q) { //2,3
            res.back().push_back(n->data_); // 1 - 2,3 - 4,5,6,7
            if (n->left_)
                child.push_back(n->left_); //2 - 4 - 4,5,6
            if (n->right_)
                child.push_back(n->right_); //2,3 - 4,5 - 4,5,6,7
        }
        level++;
        q = move(child);
    }
    return res;
}

//    1
//  2   3
// 4 5 6 7

void print(levelT levels) {
    for (auto l:levels) {
        for (auto n:l) {
            cout << n << " ";
        }
        cout << endl;
    }
}

int main() {
    print(createLevelLinkedList(createTree({1,2,3,4,5,6,7})));
    print(createLevelLinkedList(createTree({1,2,3,4,5,-1,7})));
    print(createLevelLinkedList(createTree({1,2,3,4,5,-1,7,8,})));
}