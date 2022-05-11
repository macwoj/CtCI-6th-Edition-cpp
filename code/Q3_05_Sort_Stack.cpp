#include <iostream>
#include <stack>

using namespace std;

void print(stack<int> s) {
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

stack<int> sort(stack<int> s){
    stack<int> tmp;
    if (s.empty())
        return {};
    tmp.push(s.top());
    s.pop();
    while (!s.empty()) {
        if (!tmp.empty() && s.top() < tmp.top()) {
            auto top = s.top();
            s.pop();
            while (!tmp.empty() && top<tmp.top()) {
                s.push(tmp.top());
                tmp.pop();
            }
            tmp.push(top);
        } else {
            tmp.push(s.top());
            s.pop();
        }

    }

    return tmp;
}

int main() {
    {
        stack<int> s;
        s.push(3);
        s.push(20);
        s.push(1);
        s.push(19);
        s.push(2);
        s.push(0);
        print(sort(s));
    }

}