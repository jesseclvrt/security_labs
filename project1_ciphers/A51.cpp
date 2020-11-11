// Jesse Calvert
// CS430, 4/4/2019

/*
PROGRAM OUTPUT

Next 32 digits: 10000011011100000111100000011001
X: 0001101000000000000
Y: 1111101010101010101010
Z: 01101010111100001010101

Note to TA:
Vector<bool> works on a bit-level, NOT byte.

SOURCE:
https://en.cppreference.com/w/cpp/container/vector_bool

"The manner in which std::vector<bool> is made space efficient (as well as
whether it is optimized at all) is implementation defined. One potential
optimization involves coalescing vector elements such that each element occupies
a single bit instead of sizeof(bool) bytes."
*/

#include <vector>
#include <iostream>

using namespace std;

bool maj(bool x, bool y, bool z);
vector<bool> shiftRightOne(vector<bool> v);
void printVec(vector<bool> v);

int main() {
    vector<bool> x = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}; //initial values
    vector<bool> y = {1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
    vector<bool> z = {1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0};
    cout << "Next 32 digits: ";
    for (int i = 0; i < 32; i++) {
        bool m = maj(x[8], y[10], z[10]);
        bool t;
        if (m == x[8]) {
            t = x[13] ^ x[16] ^ x[17] ^ x[18];
            x = shiftRightOne(x);
            x[0] = t;
        }
        if (m == y[10]) {
            t = y[20] ^ y[21];
            y = shiftRightOne(y);
            y[0] = t;
        }
        if (m == z[10]) {
            t = z[7] ^ z[20] ^ z[21] ^ z[22];
            z = shiftRightOne(z);
            z[0] = t;
        }
        cout << (int) (x[18] ^ y[21] ^ z[22]);
    }
    cout << endl;
    cout << "X: "; printVec(x);
    cout << "Y: "; printVec(y);
    cout << "Z: "; printVec(z);
    return EXIT_SUCCESS;
}

//returns majority of 3
bool maj(bool x, bool y, bool z) {
   return (x & y) | (x & z) | (y & z);
}

//shifts all elements to 1 index greater, deleting greatest index
vector<bool> shiftRightOne(vector<bool> v) {
    for (int i = v.size() - 1; i > 0; i--) {
        v[i] = v[i - 1];
    }
    return v;
}

//prints vector with a linebreak
void printVec(vector<bool> v) {
    for (bool element : v) {
        cout << (int) element;
    }
    cout << endl;
}