#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

using matrixT = vector<vector<int>>;
using vecT = vector<bool>;

void zeroRow(matrixT& m,int r) {
    for (auto& i:m[r]) {
        i = 0;
    }
}

void zeroCol(matrixT& m,int c) {
    for (int i=0;i<m.size();i++) {
        m[i][c] = 0;
    }
}

void zero(matrixT& m) {
    if (m.empty() || m[0].empty())
        return;
    vecT rows(m.size(),false);
    vecT cols(m[0].size(),false);
    for (int r=0;r<m.size();r++) {
        for (int c=0;c<m[0].size();c++) {
            if (m[r][c] == 0) {
                rows[r] = true;
                cols[c] =  true;
                cout << r << " " << c << endl;
            }
        }
    }

    for (int r=0;r<rows.size();r++) {
        if (rows[r])
            zeroRow(m,r);
    }
    for (int c=0;c<cols.size();c++) {
        if (cols[c])
            zeroCol(m,c);
    }
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
        matrixT m {
            {1,2,3,4},
            {0,6,7,8},
            {9,10,11,0},
            {13,14,15,16}
        };
        print(m);
        zero(m);
        print(m);
    }
}