//
// Created by Damian on 25.11.2024.
//

#ifndef DZIELIZWYCIEZAJ_TESTING_H
#define DZIELIZWYCIEZAJ_TESTING_H


class Testing {
        private:
        long long *arr;
        long long size;
        long long current_index;

    void fill();

        public:
        Testing();
        ~Testing();

        void print();
        bool answer_check(int answer);

        long long jump(unsigned int x);
};

void next_test();
long long time_jump(unsigned int x);

extern Testing *testing;

#endif //DZIELIZWYCIEZAJ_TESTING_H
