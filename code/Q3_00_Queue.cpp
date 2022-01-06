#include <memory>
#include <iostream>

using namespace std;

template <typename T>
class Queue {
private:
struct Node {
    T data_;
    shared_ptr<Node> next_;
    Node(T data): data_(data) {}
};

shared_ptr<Node> front_;
shared_ptr<Node> back_;
public:
void push(T data) {
    auto n = make_shared<Node>(data);
    if (empty()) {
        front_ = n;
        back_ = n;
    } else {
        back_->next_ = n;
        back_ = n;
    }
}
T front() {
    if (front_)
        return front_->data_;
    return {};
}

void pop() {
    if (front_) {
        front_ = front_->next_;
        if (front_ == nullptr)
            back_ = nullptr;
    }
}

bool empty() {
    return front_ == nullptr;
}

void print() {
    auto n = front_;
    while (n) {
        cout << n->data_ << " ";
        n = n->next_;
    }
    cout << endl;
}
};

int main() {
    Queue<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.print();
    cout << "peek " << s.front() << " " << s.empty() << endl;
    s.pop();
    cout << "peek " << s.front() << " " << s.empty() << endl;
    s.pop();
    s.push(23);
    cout << "peek " << s.front() << " " << s.empty() << endl;
    s.pop();
    cout << "peek " << s.front() << " " << s.empty() << endl;
    s.pop();
    cout << "peek " << s.front() << " " << s.empty() << endl;
    s.pop();
}