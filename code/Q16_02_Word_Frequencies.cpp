#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

using dictT = unordered_map<string,int>;
using char_array = std::vector<char> ;
using bookT = vector<string>;
 
std::string random_string( size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

dictT generateDict(const bookT& book) {
    dictT dict;
    for (auto w:book) {
        auto [it,_] = dict.insert({w,0});
        it->second++;
    }
    return dict;
}

int getFrequency(const dictT& dict, string word) {
    auto it = dict.find(word);
    if (it != dict.end())
        return it->second;
    return 0;
}

int main() {
    bookT book;
    for (int i=0;i<100000;i++) {
        book.push_back(random_string(3));
    }
    auto dict = generateDict(book);
    cout << getFrequency(dict,"abc") << endl;
}