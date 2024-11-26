
#include "Testing.h"


#include <iostream>


int search(int start_value) {
    int jump = 1;
    long long current_value = start_value;
    long long high = start_value;
    long long low = start_value;
    int jump_to_high = 0;
    int jump_to_low = 0;
    int temp_jump;

    // ile trzeba skoków żeby przekroczyło
    while(current_value > start_value) {
        current_value = time_jump(jump);
        jump *= 2;
    }

    jump_to_high = jump;
    jump = 1;

    // szukamy dokładnej ilości skoków do ostatniego elementu
    while(true) {
        temp_jump = jump_to_high - jump;
        current_value = time_jump(temp_jump);
        jump *= 2;
        if(time_jump(temp_jump + 1) < start_value && current_value > start_value) {
            high = current_value;
            jump_to_high = temp_jump;
            low = time_jump(temp_jump + 1);
            break;
        }
    }

    jump = 1;

    // szukamy ile trzeba skoków żeby przekroczyło start_value
    current_value = low;
    while(current_value < start_value) {
        current_value = time_jump(jump_to_high + jump + 1);
        jump *= 2;
    }

    jump_to_low = jump;
    jump = 1;


    // szukamy dokładnej ilości skoków żeby dosięgneło start_value
    while(true) {
        temp_jump = jump_to_low - jump;
        current_value = time_jump(jump_to_high + temp_jump + 1);
        jump *= 2;
        if(time_jump(jump_to_high + temp_jump + 1) == start_value) {
            low = current_value;
            jump_to_low = temp_jump;
            break;
        }
    }

    return jump_to_high + jump_to_low + 1;
}

int main() {
    int tests;
    std::cin >> tests;
    std::cout << "\n";

    while(tests--) {

        long long result = search(time_jump(0));
        testing->answer_check(result);

        next_test();
    }

    return 0;
}