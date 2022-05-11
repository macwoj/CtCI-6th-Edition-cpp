#include <iostream>
#include <vector>

using namespace std;

using matrixT = vector<vector<int>>;

bool rotate(matrixT& m) {
    if (m.empty() || m[0].size()!=m.size())
        return false;
    auto n = m.size();
    for (int layer=0;layer < n/2;layer++) {
        auto first = layer;
        auto last = n - 1 - layer;

        for(int i = first; i < last; i++) {
            int offset = i - first;
            int top = m[first][i]; // save top

            // left -> top
            m[first][i] = m[last-offset][first]; 			

            // bottom -> left
            m[last-offset][first] = m[last][last - offset]; 

            // right -> bottom
            m[last][last - offset] = m[i][last]; 

            // top -> right
            m[i][last] = top; // right <- saved top
        }
    }
    return true;
}

void print(matrixT& m) {
    for (auto r:m) {
        for (auto c:r) {
            cout << c << " ";
        }
        cout << endl;
    }
}

int main() {
    {
        matrixT m{
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
            {13,14,15,16}
        };
        print(m);
        rotate(m);
        print(m);
    }

}