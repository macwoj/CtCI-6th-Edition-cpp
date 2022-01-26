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

template <typename T>
class StackArray {
private:
    shared_ptr<T> data_;
    int size_;
    int index_;
public:
    StackArray(int maxSize):size_(maxSize),index_(-1) {
        data_ = shared_ptr<T>(new T[size_],[](T* p){ delete [] p;});
    }

    bool push(T data) {
        if (index_<size_) {
            index_++;
            data_.get()[index_] = data;
            return true;
        }
        return false;
    }

    T top() {
        if (index_ > -1)
            return data_.get()[index_];
        return {};
    }

    void pop() {
        if (index_>-1)
            index_--;
    }

    bool empty() {
        return index_==-1;
    }

    void print() {
        for (int i=0;i<=index_;i++) {
            cout << data_.get()[i] << " ";
        }
        cout << endl;
    }
};


int main() {
    {
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
    {
        StackArray<int> s(20);
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
}