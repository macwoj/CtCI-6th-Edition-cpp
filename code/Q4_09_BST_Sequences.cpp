#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include <set>
using namespace std;

inline static int verbose = 0;

template<typename T>
struct node {
    shared_ptr<node> left_;
    shared_ptr<node> right_;
    T data_;
    node(T d): data_(d) {}
};

using nodeT = node<int>;
using nodePtr = shared_ptr<nodeT>;
using vecT = vector<int>;
using vvecT = vector<vecT>;

void print(nodePtr node,string prefix="",bool isLeft=false) {
    if (node) {
        std::cout << prefix << (isLeft ? "├──" : "└──" );
        // print the value of the node
        std::cout << node->data_ << std::endl;
        // enter the next tree level - left and right branch
        print(node->left_,prefix + (isLeft ? "│  " : "   "), true);
        print(node->right_, prefix + (isLeft ? "│  " : "   "),false);
    }
}

void print(vecT vect) {
    for (auto e:vect) {
        cout << e << " ";
    }
}

nodePtr create(vecT data) {
    auto head = make_shared<nodeT>(data[0]);
    for (int i=1;i<data.size();i++) {
        auto curr = head;
        while (curr) {
            if (data[i] > curr->data_) {
                if (curr->right_)
                    curr = curr->right_;
                else {
                    curr->right_ = make_shared<nodeT>(data[i]);
                    break;
                }
            } else {
                if (curr->left_)
                    curr = curr->left_;
                else {
                    curr->left_ = make_shared<nodeT>(data[i]);
                    break;
                }
            }
        }
    }
    return head;
}

bool compare(nodePtr left,nodePtr right) {
    bool left_null = left == nullptr;
    bool right_null = right == nullptr;
    if (left_null && right_null)
        return true;
    else if (left_null!=right_null)
        return false;
    if (left->data_!=right->data_)
        return false;
    if (!compare(left->left_,right->left_))
        return false;
    return compare(left->right_,right->right_);
}

vvecT weave(vecT left,vecT right, int start_left=0,int start_right=0) {
    if (start_left >= left.size() || start_right > right.size())
        return {right};

    vvecT result;
    for (int j=start_right;j<=right.size();j++) {
        auto res = weave(left,right,start_left+1,j);
        for (auto& r:res) {
            r.insert(r.begin()+j,left[start_left]);
        }
        result.insert(result.end(),res.begin(),res.end());
    }
    return result;
}

vvecT allSequence(nodePtr node) {
    if (!node)
        return {};
    if (!node->left_ && !node->right_) //leaf node
        return {{node->data_}};
    vvecT left,right;
    if (node->left_)
        left = allSequence(node->left_);
    if (node->right_)
        right = allSequence(node->right_);
    if (verbose>0)
        cout << node->data_ << " left=" << left.size() << " right=" << right.size() << endl;
    vvecT result;
    if (!right.empty() && !left.empty()) {
        for (auto r:right) {
            for (auto l:left) {
                auto res = weave(l,r);
                for (auto& r:res)
                    r.insert(r.begin(),node->data_);
                result.insert(result.end(),res.begin(),res.end());
            }
        }
    } else if (!right.empty()) {
        for (auto& r:right)
            r.insert(r.begin(),node->data_);
        result.insert(result.end(),right.begin(),right.end());
    } else if (!left.empty()) {
        for (auto& r:left)
            r.insert(r.begin(),node->data_);
        result.insert(result.end(),left.begin(),left.end());
    }
    if (verbose>0)
        cout << node->data_ << " weave=" << result.size() << endl;
    return result;
}

void compareAll(vecT v,vvecT vect) {
    auto n = create(v);
    set<vecT> check;
    print(n);
    for (auto e:vect) {
        auto [it,isNew] = check.insert(e);
        auto curr = create(e);
        print(e);
        cout << compare(n,curr) << " " << isNew << endl;
    }
}

int main() {
    verbose = 1;
    {
        auto n = {100, 50, 20, 75, 150, 120, 170};
        compareAll(n,allSequence(create(n)));
    }
    {
        auto n = {100, 50, 20, 75, 150, 120, 170,190};
        compareAll(n,allSequence(create(n)));
    }
}