//
// Created by Damian on 25.11.2024.
//

#include "Testing.h"

#include <iostream>
#include <random>
#include <algorithm>

void Testing::fill() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> content_gen(-1000000000, 1000000000);

    for(int i = 0 ; i < size ; i++) {
        arr[i] = content_gen(gen);
    }
}

Testing::Testing() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> size_gen(1, 100000);

    size = size_gen(gen);

    std::uniform_int_distribution<long long> start_index_gen(0, size);

    arr = new long long[size];
    fill();
    std::sort(arr, arr + size);
    current_index = start_index_gen(gen);
}

Testing::~Testing() {
    delete[] arr;
}

void Testing::print() {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << "\n";
    }
}

bool Testing::answer_check(int answer) {
    if(answer == size) {
        std::cout << "Correct answer: " << answer << std::endl;
        return true;
    }
    std::cout << "Wrong answer: " << answer << " should be: " << size << std::endl;
    return false;
}

long long Testing::time_jump(unsigned int x) {
    current_index = (current_index + x) % size;
    return arr[current_index];
}

Testing *testing = new Testing();

void next_test() {
    delete testing;
    testing = new Testing();
}



