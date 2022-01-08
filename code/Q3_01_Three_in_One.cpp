#include <memory>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class MultiStack {
private:
    int stackNum_;
    vector<int> index_;
    vector<T> data_;
public:
    MultiStack(): stackNum_(3), index_(stackNum_,-1) {

    }
    void push(int stack,T data) {
        auto& ind = index_[stack];
        if (ind == -1) {
            ind = stack;
        } else {
            ind += stackNum_;  
        }
        while (ind >= data_.size()) {
            data_.push_back({});
        }
        data_[ind] = data;
    }
    T top(int stack) {
        auto ind = index_[stack];
        if (ind==-1)
            return {};
        return data_[ind];
    }

    void pop(int stack) {
        auto& ind = index_[stack];
        ind -= stackNum_;
        if (ind < 0) {
            ind = -1;
        }
    }

    bool empty(int stack) {
        auto ind = index_[stack];
        return ind == -1;
    }

    void print() {
        for (int i=0;i<stackNum_;i++) {
            cout << "stack " << i << " : ";
            for (int j=i;j<=index_[i];j+=stackNum_) {
                cout << data_[j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    MultiStack<int> s;
    auto tops = [&]() {
        for (int i=0;i<3;i++)
        cout << "top " << i << " " << s.top(i) << " " << s.empty(i) << endl;
    };
    s.push(0,1);
    s.push(1,11);
    s.push(0,2);
    tops();
    s.push(2,21);
    s.push(0,3);
    s.print();
    tops();
    s.pop(0);
    tops();
    s.pop(1);
    tops();
    s.print();
}