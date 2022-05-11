#include <memory>
#include <vector>
#include <iostream>
#include <deque>
#include <tuple>

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
using resT = tuple<nodeptr,int>;

tuple<nodeptr,nodeptr> create(vector<int> vals) {
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
    return {head,node};
}

resT findTailSize(nodeptr n) {
    int size = 0;
    while (n) {
        size++;
        n = n->next;
    }
    return {n,size};
}

nodeptr findintersection(nodeptr n1,nodeptr n2) {
    auto [tail1,size1] = findTailSize(n1);
    auto [tail2,size2] = findTailSize(n2);
    if (tail1!=tail2) {
        return {};
    }
    while (size1>size2) {
        n1 = n1->next;
        size1--;
    }
    while (size2>size1) {
        n2 = n2->next;
        size2--;
    }
    nodeptr intersection;
    while (n1 && n2) {
        if (n1!=n2) {
            intersection = nullptr;
        } else {
            if (!intersection)
                intersection = n1;
        }
        n1 = n1->next;
        n2 = n2->next;
    }

    return intersection;
}

int main() {
    {
        auto [n1,t1] = create({1,2,3,4,5});
        auto [n2,t2] = create({6,7});
        t2->next = n1->next->next->next;
        cout << findintersection(n1,n2)->data << endl;
    }

}