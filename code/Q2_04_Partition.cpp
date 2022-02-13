#include <memory>
#include <iostream>
#include <vector>
using namespace std;

struct node {
    int data_;
    shared_ptr<node> next_;
    node(int d):data_(d){}
};
using nodePtr = shared_ptr<node>;

shared_ptr<node> create(vector<int> nodes) {
    shared_ptr<node> head = make_shared<node>(nodes.front());
    auto prev = head;
    for (int i=1;i<nodes.size();i++) {
        auto n = make_shared<node>(nodes[i]);
        prev->next_ = n;
        prev = prev->next_;
    }
    return head;
}

nodePtr partition(nodePtr node,int p) {
    nodePtr gt,gth;
    nodePtr ls,lsh;
    nodePtr curr = node;
    while (curr) {
        if (curr->data_ < p) {
            if (!lsh) {
                lsh = curr;
            } else {
                ls->next_ = curr;
            }
            ls = curr;
        } else {
            if (!gth) {
                gth = curr;
            } else {
                gt->next_ = curr;
            }
            gt = curr;
        }
        curr = curr->next_;
    }
    ls->next_ = gth;
    gt->next_ = nullptr;
    return lsh;
}

void print(nodePtr node) {
    while (node) {
        cout << node->data_ << " ";
        node = node->next_;
    }
    cout << endl;
}

int main() {
    auto node = create({3,5,8,5,10,2,1});
    print(partition(node,5));
}