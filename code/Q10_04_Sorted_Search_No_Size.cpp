#include <vector>
#include <iostream>

using namespace std;

using vecT = vector<int>;

class Listy {
private:
    vecT arr_;
public:
    Listy(vecT v): arr_(v) {}
    int elementAt(int i) const {
        if (i>=0 && i<arr_.size())
            return arr_[i];
        return -1;
    }
};

int search(const Listy& list,int x) {
    int start = 0;
    int end = 1;
    while (list.elementAt(end) > -1 && list.elementAt(end)<x) {
        end *= 2;
    }
    while (start<=end) {
        auto mid = (start+end)/2;
        if (list.elementAt(mid) == x)
            return mid;
        else if (list.elementAt(mid) < x && list.elementAt(mid)>-1)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return end;
}

int main() {
    {
        cout << search(Listy({1,2,3,4,5}),4) << endl;
        cout << search(Listy({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}),4) << endl;
        cout << search(Listy({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}),1) << endl;
        cout << search(Listy({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}),15) << endl;
    }
}