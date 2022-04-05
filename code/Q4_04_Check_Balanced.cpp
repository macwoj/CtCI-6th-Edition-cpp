#include <iostream>
#include <tuple>
#include <memory>
#include <queue>

inline static int verbose = 0;

using namespace std;

template <typename T>
struct Node {
    shared_ptr<Node<T>> left_;
    shared_ptr<Node<T>> right_;
    T data_;
    Node(T d): data_(d) {}
};

using nodeT = Node<int>;
using nodePtr = shared_ptr<nodeT>;
using resT = tuple<bool,int>;

resT isBalancedImpl(nodePtr node) {
    if (node == nullptr)
        return {true,0};
    auto left = isBalancedImpl(node->left_);
    auto right = isBalancedImpl(node->right_);
    if (get<0>(left) && get<0>(right)) {
        bool isValid = abs(get<1>(left) - get<1>(right)) <= 1;
        if (isValid) {
            auto depth = max(get<1>(left),get<1>(right))+1;
            return {true,depth};
        }
    }

    return {false,0};
}

bool isBalanced(nodePtr node) {
    auto [res,_] = isBalancedImpl(node);
    return res;
}

void print(nodePtr node,string prefix="",bool isLeft=false) {
    if (node) {
        std::cout << prefix << (isLeft ? "├──" : "└──" );
        // print the value of the node
        std::cout << node->data_;
        cout << std::endl;
        // enter the next tree level - left and right branch
        print(node->left_,prefix + (isLeft ? "│  " : "   "), true);
        print(node->right_, prefix + (isLeft ? "│  " : "   "),false);
    }
}

void clean(nodePtr node) {
    if (node!=nullptr) {
        if (node->left_) {
            if (node->left_->data_ < 0)
                node->left_ = nullptr;
            else
                clean(node->left_);
        }
        if (node->right_) {
            if (node->right_->data_ < 0)
                node->right_ = nullptr;
            else
                clean(node->right_);
        }
    }
}

nodePtr createTree(const vector<int> values) {
    auto it = values.begin();
    it++;
    nodePtr head = make_shared<nodeT>(values.front());
    queue<nodePtr> currLevel,nextLevel;
    currLevel.push(head);
    for (;it!=values.end();++it) {
        if (verbose > 0)
            cout << *it << endl;
        if (currLevel.empty())
            currLevel = move(nextLevel);
        if (!currLevel.empty()) {
            auto node = make_shared<nodeT>(*it);
            nextLevel.push(node);
            auto front = currLevel.front();
            if (!front->left_)
                front->left_ = node;
            else if(!front->right_) {
                front->right_ = node;
                currLevel.pop();
            }
        }
    }
    clean(head);
    print(head);
    return head;
}

int main() {
    {
        auto root = createTree({1,2,3,4,5,6,7});
        cout << "isBalanced=" << isBalanced(root) << endl;
    }
    {
        auto root = createTree({1,-1,3,4,5,6,7});
        cout << "isBalanced=" << isBalanced(root) << endl;
    }
}
