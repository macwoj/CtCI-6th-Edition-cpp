#include <memory>
#include <iostream>

using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        shared_ptr<Node> next;
        Node(T d): data(d) {}
    };
    shared_ptr<Node> top_;
public:
void push(T data) {
    auto node = make_shared<Node>(data);
    node->next = top_;
    top_ = node;
}
T top() {
    if (top_)
        return top_->data;
    return {};
}

void pop() {
    if (top_) {
        top_ = top_->next;
    }
}

bool empty() {
    return top_ == nullptr;
}

void print() {
    auto n = top_;
    while (n) {
        cout << n->data << " ";
        n = n->next;
    }
    cout << endl;
}

};


int main() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.print();
    cout << "peek " << s.top() << " " << s.empty() << endl;
    s.pop();
    cout << "peek " << s.top() << " " << s.empty() << endl;
    s.pop();
    s.push(23);
    cout << "peek " << s.top() << " " << s.empty() << endl;
    s.pop();
    cout << "peek " << s.top() << " " << s.empty() << endl;
    s.pop();
    cout << "peek " << s.top() << " " << s.empty() << endl;
    s.pop();
}