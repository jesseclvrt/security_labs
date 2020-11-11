/*
 * Jesse Calvert
 * 4/18/2019
 * CS430
 * 
 * PROGRAM OUTPUT
 * 
 * Point (2,7) is on E.
 * Alice sends Bob 153, 36
 * Bob sends Alice 103, 153
 * The shared secret is 137, 54
 */

#include <iostream>

#define pX 2
#define pY 7
#define mod 167
#define secretA 12
#define secretB 31
#define curveA 11
#define curveB 19

bool partA();
bool partB();

int modulo(int a, int modulo);
void elliMult(int coeff, int p[2]);
int modInverse(int a, int modulo);

using namespace std;

int main() {
    if (!partA() || !partB()) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool partA() {
    int lhs = modulo(pY*pY, mod);
    int rhs = modulo(pX*pX*pX + pX*curveA + curveB, mod);
    if (lhs != rhs) {
        cout << "Point (2,7) is not on E." << endl;
        return false;
    }
    cout << "Point (2,7) is on E." << endl;
    return true;
}

bool partB() {
    int alice[2] = {pX, pY};
    int bob[2] = {pX, pY};
    elliMult(secretA, alice);
    elliMult(secretB, bob);
    cout << "Alice sends Bob " << alice[0] << ", " << alice[1] << endl;
    cout << "Bob sends Alice " << bob[0] << ", " << bob[1] << endl;
    elliMult(secretB, alice);
    elliMult(secretA, bob);
    if (alice[0] != bob[0] || alice[1] != bob[1]) {
        cout << "Error in math." << endl;
        return false;
    }
    cout << "The shared secret is " << alice[0] << ", " << alice[1] << endl;
    return true;
}

int modulo(int a, int modulo) {
    return (a % modulo + modulo) % modulo;
}

void elliMult(int coeff, int p[2]) {
    int xp = p[0];
    int yp = p[1];
    for (int i = 0; i < coeff - 1; i++) {
        int m;
        int xq = p[0];
        int yq = p[1];
        if (xq == 0 && yq == 0) {
            p[0] = xp;
            p[1] = yp;
            continue;
        }
        if (xp == xq && yp == yq) m = modulo((3*xp*xp+curveA)*modInverse(2*yp, mod), mod);
        else m = modulo((yq-yp)*modInverse(modulo(xq - xp, mod), mod), mod);
        p[0] = modulo(m * m - xp - xq, mod);
        p[1] = modulo(m * (xp - p[0]) - yp, mod);
    }
}

int modInverse(int a, int modulo) {
    a = a % modulo;
    for (int x = 1; x < modulo; x++)
       if ((a * x) % modulo == 1)
          return x;
}