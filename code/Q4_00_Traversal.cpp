#include <memory>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

template<typename T>
struct Node {
    T data_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
    Node(T d):data_(d) {}
    Node(T d,shared_ptr<Node<T>> left,shared_ptr<Node<T>> right):data_(d),left_(left),right_(right) {}
};

using nodeT = Node<string>;
using nodePtr = shared_ptr<nodeT>;

void inOrderTraversal(nodePtr node) {
    if (node) {
        inOrderTraversal(node->left_);
        cout << node->data_ << " ";
        inOrderTraversal(node->right_);
    }
}

void inOrderTraversalNoRec(nodePtr node) {
    if (!node) return;
    stack<nodePtr> sta;
    auto pushLeft = [&](auto node) {
        while (node) {
            sta.push(node);
            node = node->left_;
        }
    };
    pushLeft(node);
    while(!sta.empty()) {
        auto top = sta.top();
        cout << top->data_ << " ";
        sta.pop();
        if (top->right_)
            pushLeft(top->right_);

    }
}

void preOrderTraversal(nodePtr node) {
    if (node) {
        cout << node->data_ << " ";
        preOrderTraversal(node->left_);
        preOrderTraversal(node->right_);
    }
}

void postOrderTraversal(nodePtr node) {
    if (node) {
        postOrderTraversal(node->left_);
        postOrderTraversal(node->right_);
        cout << node->data_ << " ";
    }
}

int main() {
    {
        nodePtr node = 
        make_shared<nodeT>(
            "a",
            make_shared<nodeT>(
                "b",
                make_shared<nodeT>("d"),
                make_shared<nodeT>("e")
                ),
            make_shared<nodeT>(
                "c",
                nullptr,
                make_shared<nodeT>("f"))
            );
        inOrderTraversal(node);
        cout << endl;
        inOrderTraversalNoRec(node);
        cout << endl;
        preOrderTraversal(node);
        cout << endl;
        postOrderTraversal(node);
        cout << endl;
    }
}