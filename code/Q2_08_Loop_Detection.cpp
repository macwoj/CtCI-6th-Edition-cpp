#include <memory>
#include <vector>
#include <iostream>
#include <deque>
#include <tuple>
#include <unordered_set>

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

nodeptr detectLoop(nodeptr head) {
    unordered_set<nodeptr> nodes;
    while (head) {
        auto [it,isNew] = nodes.insert(head);
        if (!isNew)
            return head;
        head = head->next;
    }
    return {};
}

nodeptr go(nodeptr n) {
    if (n && n->next) {
        n = n->next;
    }
    return n;
}

nodeptr detectLoop2(nodeptr head) {
    nodeptr slow = head;
    nodeptr fast = head;
    while (fast && slow) {
        slow = go(slow);
        fast = go(go(fast));
        if (slow == fast)
            break;
    }
    if (!fast || !slow)
        return {};
    slow = head;
    while (slow!= fast) {
        slow = go(slow);
        fast = go(fast);
    }
    return fast;
}

int main() {
    {
        auto n = create({1,2,3,4,5,6});
        n->next->next->next->next->next = n->next->next->next;
        cout << detectLoop(n)->data << endl;
    }
    {
        auto n = create({1,2,3,4,5,6});
        n->next->next->next->next->next = n->next->next->next;
        cout << detectLoop2(n)->data << endl;
    }
}