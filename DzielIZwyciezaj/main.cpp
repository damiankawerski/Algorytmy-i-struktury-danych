#include <iostream>
#include "Testing.h"

int binary_search(int low, int high, int x) {
    while(low <= high) {
        int mid = low + (high - low) / 2;

        if(testing->time_jump(mid) < x) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    return low;
}


int main() {
    int tests;
    std::cin >> tests;
    std::cout << "\n";

    while(tests--) {


        next_test();
    }

    return 0;
}