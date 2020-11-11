#include <iostream>
#include <string>

#define digits 7
#define trials 10
#define range 10


using namespace std;

void main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "\nUsage: " << argv[0] << " program\n\n";
        cout << "where program is the target of linearization attack\n\n";
        exit(0);
    }
    string program = argv[1];
    clock_t average[range];
    clock_t timeStart, timeEnd, sum, longest;
    string serial = "0000000";
    for (int i = 0; i < digits; i++) {
        sum = 0;
        for (int j = 0; j < range; j++) {
            serial[i] = '0' + j;
            for (int k = 0; k < trials; k++) {
                string call = program + " " + serial;
                timeStart = clock();
                system(call.c_str());
                timeEnd = clock();
                sum += timeEnd - timeStart;
            }
            average[j] = sum / trials;
        }
        longest = 0;
        for (int j = 1; j < range; j++) {
            if (average[longest] < average[j])
                longest = j;
        }
        serial[i] = '0' + longest;
        cout << "digit " << i << " is " << longest;
    }
}