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

nodeptr create(vector<int> vals) {
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

int sum(nodeptr node1,nodeptr node2) {
    int mult = 1;
    int overflow = 0;
    int sum = 0;
    while (node1 || node2) {
        auto res = overflow;
        if (node1) {
            res += node1->data;
            node1 = node1->next;
        }
        if (node2) {
            res += node2->data;
            node2 = node2->next;
        }
        sum += (res%10)*mult;
        overflow = res / 10;
        mult *= 10;

    }
    if (overflow>0)
        sum += overflow*mult;
    return sum;
}
//2->3
nodeptr reverse(nodeptr node) {
    if (!node)
        return {};
    nodeptr prev; //n
    while (node) { //3
        auto next = node->next; //n
        node->next = prev; //3->2
        prev = node; //3
        node = next; //n
    }
    return prev;
}

int sumReverse(nodeptr node1,nodeptr node2) {
    auto n1 = reverse(node1);
    auto n2 = reverse(node2);
    return sum(n1,n2);
}

int main() {

    cout << sum(create({1,2,3}),create({2,3})) << endl;
    cout << sum(create({9,9}),create({9,9})) << endl;
    cout << sumReverse(create({1,2,3}),create({2,3})) << endl;

}