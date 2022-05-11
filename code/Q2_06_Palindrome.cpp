#include <memory>
#include <vector>
#include <iostream>
#include <deque>

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

bool isPalindrome(nodeptr head) {
    auto node = head;
    deque<int> d;
    while(node) {
        d.push_back(node->data);
        node = node->next;
    }
    while (!d.empty()) {
        if (d.front() != d.back())
            return false;
        d.pop_front();
        if (!d.empty())
            d.pop_back();
    }
    return true;
}

bool isPalindromeRecursive(nodeptr node,nodeptr& head) {
    if (!node)
        return true;
    if (node->next) {
        if (!isPalindromeRecursive(node->next,head))
            return false;
    }
    if (node->data != head->data)
        return false;
    head = head->next;
    return true;

}

bool isPalindromeRecursive(nodeptr head) {
    nodeptr n = head;
    return isPalindromeRecursive(head,n);
}

int main() {
    cout << isPalindrome(create({2,3,4,4,3,2})) << endl;
    cout << isPalindrome(create({2,3,4,5,4,3,2})) << endl;
    cout << isPalindrome(create({2,3,4,4,3,7,2})) << endl;
    cout << isPalindromeRecursive(create({2,3,4,4,3,2})) << endl;
    cout << isPalindromeRecursive(create({2,3,4,5,4,3,2})) << endl;
    cout << isPalindromeRecursive(create({2,3,4,4,3,7,2})) << endl;
}