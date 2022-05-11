#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template <typename T>
class SetOfStacks {
    int capacity_;
    vector<deque<T>> stacks_;

    void addBack() {
        stacks_.push_back({});
    }

    void leftShift(int index) {
        if (index+1 < stacks_.size()) {
            stacks_[index].push_back(stacks_[index+1].front());
            stacks_[index+1].pop_front();
            leftShift(index+1);
        }
    }
public:
    SetOfStacks(int capacity): capacity_(capacity) {
        addBack();
    }

    void push(T val) {
        if (stacks_.back().size() == capacity_) {
            addBack();
        }
        stacks_.back().push_back(val);
    }

    T pop() {
        T res = {};
        if (!stacks_.empty()) {
            auto& back = stacks_.back();
            if (!back.empty()) {
                res = back.back();
                back.pop_back();
            }
            if (back.empty())
                stacks_.pop_back();
        }
        return res;
    }

    T popAt(int index) {
        if (index < stacks_.size()) {
            auto res = stacks_[index].back();
            stacks_[index].pop_back();
            leftShift(index);
            if (stacks_.back().empty())
                stacks_.pop_back();
            return res;
        }
        return {};
    }
};

int main() {
    {
        SetOfStacks<int> stack(2);
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl << endl;
    }
    {
        SetOfStacks<int> stack(2);
        stack.push(1); //1,2 3,4 5
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);
        cout << stack.popAt(1) << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
    }
}