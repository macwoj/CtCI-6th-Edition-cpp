#include <vector>
#include <iostream>
using namespace std;

using vecT = vector<int>;

vecT pickMIteratively(const vecT& arr,int m) {
    if (m>arr.size()) return {};
    vecT subset(arr.begin(),arr.begin()+m);
    srand(time(0));
    for (int i=m;i<arr.size();i++) {
        int k = rand()%i;
        if (k<m)
            subset[k] = arr[i];
    }
    return subset;
}

int main() {
    vecT cards = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (auto i:pickMIteratively(cards, 4)) cout << i << " ";
    cout << endl;
}