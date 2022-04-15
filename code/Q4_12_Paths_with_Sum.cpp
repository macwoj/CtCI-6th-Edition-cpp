#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <queue>
#include <unordered_map>
#include <sstream>
using namespace std;

inline static int verbose = 0;

using vecT = vector<int>;
using mapT = unordered_map<int,int>;

template<typename T>
struct Node {
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
    T data_;
    Node(T d):data_(d) {}
};

using nodeT = Node<int>;
using nodePtr = shared_ptr<nodeT>;

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
            if (!front->left_) {
                front->left_ = node;
            }
            else if(!front->right_) {
                front->right_ = node;
                currLevel.pop();
            }
        }
    }
    //clean(head);
    return head;
}

vecT pathSum(nodePtr node,mapT& sums) {
    if (!node)
        return {};
    auto left = pathSum(node->left_,sums);
    auto right = pathSum(node->right_,sums);
    for (auto& i:left)
        i+=node->data_;
    for (auto& i:right)
        i+=node->data_;
    left.insert(left.end(),right.begin(),right.end());
    left.push_back(node->data_);
    for (auto i:left)
        sums[i]++;
    return left;
}

int pathSum(nodePtr node,int target) {
    mapT sums;
    auto _ = pathSum(node,sums);
    return sums[target];
}

int pathSum2(nodePtr node,int target, int runningSum, mapT& count) {
    if (!node)
        return 0;
    runningSum += node->data_;
    int sum = runningSum - target;
    auto total = count[sum];
    if (runningSum == target)
        total++;
    count[runningSum]++;
    total += pathSum2(node->left_,target,runningSum,count);
    total += pathSum2(node->right_,target,runningSum,count);
    count[runningSum]--;
    return total;
}

int pathSum2(nodePtr node, int target) {
    mapT count;
    return pathSum2(node,target,0,count);
}

int main() {
    {
        srand(1121212);
        vector<int> tmp;
        for (int i=0;i<1000;i++) {
            tmp.push_back((rand()%21)-10);
        }
        auto node = createTree(tmp);
        //print(node);
        cout << pathSum(node,18) << " " << pathSum2(node,18) << endl << endl;
    }
    {
        auto node = createTree({1,2,3,4,2});
        print(node);
        cout << pathSum(node,4) << " " << pathSum2(node,4) << endl;
    }

}