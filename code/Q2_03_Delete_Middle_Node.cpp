#include <memory>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
struct Node {
    shared_ptr<Node> next;
    T data;
    Node(T d):data(d) {}

    void print() {
        auto n = next;
        cout << data << " ";
        while (n) {
            cout << n->data << " ";
            n = n->next;
        }
        cout << endl;
    }
};

using nodeptr = shared_ptr<Node<int>>;
using nodeT = Node<int>;

nodeptr init(vector<int> vals) {
    nodeptr node,head;
    for (auto i:vals) {
        if (!head) {
            node = make_shared<nodeT>(i);
            head = node;
        } else {
            node->next = make_shared<nodeT>(i);
            node = node->next;
        }
        
    }
    return head;
}

void deleteNode(nodeptr node) {
    if (node && node->next) {
        node->data = node->next->data;
        node->next = node->next->next;
    }
}

int main () {
    vector<vector<int>> tests{
        {0,1,2,3,4},
        {0,1,1,2,3,4,5},
        {0,0,0,1,2,2,2,2,2,2,3,1,1,1,2,3,2,1,12,1,1}
    };
    for (auto test:tests) {
        auto data = init(test);
        data->print();
        deleteNode(data->next->next->next);
        data->print();
    }
}