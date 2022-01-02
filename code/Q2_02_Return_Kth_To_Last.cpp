#include <vector>
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>

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

tuple<nodeptr,int> nthToLast(nodeptr n,int k) {
    if (!n) {
        return {nullptr,0};
    }
    auto [ptr,depth] = nthToLast(n->next,k);
    depth++;
    if (depth == k) {
        return {n,depth};
    }
    return {ptr,depth};
}

nodeptr nthToLast1(nodeptr n,int k) {
    nodeptr front = n,back = n;
    for (int i=0;i<k;i++) {
        if (front)
            front = front->next;
    }
    while (front) {
        front = front->next;
        back = back->next;
    }
    return back;
}

nodeptr nthToLast2(nodeptr n,int k) {
    unordered_map<int,nodeptr> depth;
    for (int i=0;n;i++,n=n->next) {
        depth.insert({i,n});
    }
    return depth[depth.size() - k];
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
            auto [res,depth] = nthToLast(data,2);
            cout << res->data << endl;
            tie(res,depth) = nthToLast(data,4);
            cout << res->data << endl;
            res = nthToLast1(data,2);
            cout << res->data << endl;
            res = nthToLast1(data,4);
            cout << res->data << endl;
            res = nthToLast2(data,2);
            cout << res->data << endl;
            res = nthToLast2(data,4);
            cout << res->data << endl;
        }
    }
}