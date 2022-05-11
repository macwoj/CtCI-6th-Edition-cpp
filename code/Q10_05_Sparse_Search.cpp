#include <string>
#include <iostream>
#include <vector>

using namespace std;

using vecT = vector<string>;

int sparseSearch(vecT strings,string target) {
    if (strings.empty() || target.empty())
        return -1;
    int low = 0;
    int high = strings.size()-1;
    while (low<=high) {
        auto mid = (low+high)/2;
        if (strings[mid].empty()) {
            int left = mid - 1;
            int right = mid + 1;
            while (true) {
                if (left < low || right > high)
                    return -1;
                if (!strings[left].empty() || !strings[right].empty())
                    break;
                left--;
                right++;
            }
            if (!strings[right].empty())
                mid = right;
            else if (!strings[left].empty())
                mid = left;
            else
                return -1;
        }
        // cout << "mid=" << mid << endl;
        auto res = strings[mid].compare(target);
        if (res == 0)
            return mid;
        else if (res < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    {
        cout << sparseSearch({"at","","","","ball","","","car","","","dad","",""},"ball") << endl;
        cout << sparseSearch({"at","","","","ball","","","car","","","dad","",""},"dad") << endl;
        cout << sparseSearch({"at","","","","ball","","","car","","","dad","",""},"balls") << endl;
    }
}