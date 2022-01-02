#include <iostream>
#include <memory>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

struct Node {
    shared_ptr<Node> next;
    int data;
    Node(int d):data(d){}

    void print() {
        shared_ptr<Node> n = next;
        cout << data << " ";
        while (n) {
            cout << n->data << " ";
            n = n->next;
        }
        cout << endl;
    }
};

using nodeptr = shared_ptr<Node>;

void deleteDups(nodeptr n) {
    unordered_set<int> vals;
    nodeptr prev;
    while (n) {
        auto [it,isNotDup] = vals.insert(n->data);
        if (!isNotDup) {
            prev->next = n->next;
            n=prev->next;
        } else {
            prev=n;
            n=n->next;
        }
    }
}

void deleteDups1(nodeptr n) {
    nodeptr prev;
    nodeptr next;
    while (n) {
        next = n->next;
        prev = n;
        while(next) {
            if (n->data==next->data) {
                prev->next = next->next;
                next=prev->next;
            } else {
                prev = next;
                next = next->next;
            }
        }
        n = n->next;
    }
}

nodeptr init(vector<int> vals) {
    nodeptr node,head;
    for (auto i:vals) {
        if (!head) {
            node = make_shared<Node>(i);
            head = node;
        } else {
            node->next = make_shared<Node>(i);
            node = node->next;
        }
        
    }
    return head;
}

int main() {
    vector<vector<int>> tests{
        {0,1,2,3,4},
        {0,1,1,1,1,2,3,4},
        {0,0,0,1,2,2,2,2,2,2,3,1,1,1,2,3,2,1,12,1,1}
    };
    for (auto test:tests) {
        {
            auto data = init(test);
            data->print();
            deleteDups(data);
            data->print();
        }
        {
            auto data = init(test);
            deleteDups1(data);
            data->print();
        }
    }

}