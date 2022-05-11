#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

using vecT = vector<string>;

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

vecT gen(int size = 20) {
    vecT out;
    for (int i=0;i<size;i++)
        out.push_back(gen_random(3 + rand()%5));
    return out;
}

void print(vecT v) {
    for (auto i:v) {
        cout << i << endl;
    }
}

vecT externalSort(const vecT& input,int chunks) {
    vector<vecT> ch;
    int chunkSize = input.size() / chunks; //20/5 = 4
    for (int i=0;i<chunks;i++) {
        auto start = input.begin() + i*chunkSize; //0
        auto end = input.begin() + (i+1)*chunkSize; //4
        if (i==chunks-1)
            end = input.end();
        ch.push_back({start,end});
    }
    vector<vecT::iterator> it;
    for (auto& v:ch) {
        sort(v.begin(),v.end());
        // print(v);
        // cout << "+++++++" << endl;
        it.push_back(v.begin());
    }
    vecT output;

    while(true) {
        int min = -1;
        for (int i=0;i<chunks;i++) {
            if (it[i] != ch[i].end()) {
                // cout << "it[" << i << "]=" << *it[i] << endl;
                if (min == -1 || *(it[i]) < *(it[min])) {
                    min = i;
                }
            }
        }
        if (min == -1)
            break;
        
        output.push_back(*it[min]);
        ++it[min];
    }
    return output;
}

int main() {
    srand(121221);
    {
        auto in = gen();
        print(in);
        cout << "-----" << endl;
        print(externalSort(in,5));
    };
}