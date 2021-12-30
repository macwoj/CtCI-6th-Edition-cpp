#include <string>
#include <iostream>

using namespace std;

string URLify(string str,int size) {
    if (str.empty())
        return str;
    auto it = str.begin() + size - 1;
    auto end = str.end();
    end--;
    do {
        if (*it == ' ') {
            *end = '0';
            end--;
            *end='2';
            end--;
            *end='%';
            end--;
            it--;
        } else {
            *end = *it;
            it--;
            end--;
        }
    } while (it != str.begin());
    return str;
}

int main() {
    cout << URLify("Mr John Smith    ",13) << endl;
    cout << URLify("MrJohnSmith",11) << endl;
    cout << URLify("Mr John Smith       ",14) << endl;
}