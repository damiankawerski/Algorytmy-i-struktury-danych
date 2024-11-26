#include <iostream>
using namespace std;

long long arr[10] = {-1300, -893, -86, 4, 6, 79, 102, 745, 1945, 2345};
long long arr2[5] = {-101, -100, 17, 1900, 2400};
long long pos = 3;
long long *arr_ptr = arr;
int sizet = 10;

void next_test() {
    if(arr_ptr == arr) {
        arr_ptr = arr2;
        pos = 1;
        sizet = 5;
    } else {
        arr_ptr = arr;
        pos = 3;
        sizet = 10;
    }
}

int time_jump(unsigned int x) {
    pos = (pos + x) % sizet;
    return arr_ptr[pos];
}

// działa
long long search(int high, int low) {
    for(int i = low ; i < high ; i++) {
        int current = time_jump(0);
        int next = time_jump(i);
        if(current == next) {
            return i;
        }
    }
    return 0;
}

// {-1300, -893, -86, 4, 6, 79, 102, 745, 1945, 2345}
//{-101, -100, 17, 1900, 2400}

// tutaj powinenm szukac cyklu a NIE DZIAŁA
void get_compartment(long long &high, long long &low) {
    int current = time_jump(0);
    int prev;
    char loop = 'w';
    int jump = 1;

    do {
        prev = current;
        current = time_jump(jump);


        if (prev > current && loop == 'g') {
            high = jump;
            low = jump / 2;
            loop = 'b';
        }

        if (prev > current && loop == 'w') {
            loop = 'g';
        }

        jump *= 2;
    } while (loop != 'b');
}

//long long binary_search() {
//
//}


int main() {

    int T;
    cin >> T;

    cout << "\n";

    long long high, low;

    for(int i = 0; i < T; i++) {
        get_compartment(high, low);
        cout << search(high, low) << " ";
        next_test();
    }

    return 0;

}