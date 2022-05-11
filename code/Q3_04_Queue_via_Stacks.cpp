#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class MyQueue {
    stack<T> stack_;

    stack<T> reverse(stack<T>& sta) {
        stack<T> tmp;
        while (!sta.empty()) {
            tmp.push(sta.top());
            sta.pop();
        }
        return tmp;
    }
public:
    void push(T val) {
        stack_.push(val);
    }

    void pop() {
        auto tmp = reverse(stack_);
        tmp.pop();
        stack_ = reverse(tmp);
    }

    T top() {
        auto tmp = reverse(stack_);
        auto val = tmp.top();
        stack_ = reverse(tmp);
        return val;
    }
};

int main() {
    {
        MyQueue<int> q;
        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);
        cout << q.top() << endl; q.pop();
        cout << q.top() << endl; q.pop();
        cout << q.top() << endl; q.pop();
        cout << q.top() << endl; q.pop();
    }

}