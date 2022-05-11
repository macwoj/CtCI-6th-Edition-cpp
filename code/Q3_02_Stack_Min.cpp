#include <iostream>
#include <stack>

using namespace std;

template<typename T>
class StackMin {
    stack<T> stack_;
    stack<T> min_;
public:
    void push(T val) {
        stack_.push(val);
        if (min_.empty() || min_.top() >= val)
            min_.push(val);
    }

    T pop() {
        if (!stack_.empty()) {
            auto res = stack_.top();
            stack_.pop();
            if (min_.top() == res)
                min_.pop();
            return res;
        }
        return {};
    }

    T min() {
        if (min_.empty())
            return {};
        return min_.top();
    }
};

int main() {
    {
        StackMin<int> stack;
        stack.push(5); cout << stack.min() << endl;
        stack.push(6); cout << stack.min() << endl;
        stack.push(3); cout << stack.min() << endl;
        stack.push(7); cout << stack.min() << endl;
        cout << stack.pop() << " " << stack.min() << endl;
        cout << stack.pop() << " " << stack.min() << endl;
    }

}