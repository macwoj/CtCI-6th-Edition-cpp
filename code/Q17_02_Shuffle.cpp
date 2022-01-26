#include <vector>
#include <string>
#include <iostream>
using namespace std;
using deckT = vector<int>;

void shuffleDeck(deckT& deck) {
    srand(time(0));
    for (int i=0;i<deck.size();i++) {
        int k = rand()%(i+1);
        swap(deck[i],deck[k]);
    }
}

int main() {
    deckT deck = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                   9, 10, 11, 12, 13, 14, 15,
                   16, 17, 18, 19, 20, 21, 22,
                   23, 24, 25, 26, 27, 28, 29,
                   30, 31, 32, 33, 34, 35, 36,
                   37, 38, 39, 40, 41, 42, 43,
                   44, 45, 46, 47, 48, 49, 50, 
                   51};
    shuffleDeck(deck);
    for (auto c:deck)
        cout << c << " ";
    cout << endl;
}