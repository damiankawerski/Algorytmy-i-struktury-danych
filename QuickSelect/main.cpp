#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;


// Sprawdza czy jest liczba pierwsza
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Sprawdza czy liczba ma parzystą ilość czynników pierwszych
bool even_prime_factors(int n) {
    int counter = 0;
    for(int i = 2 ; i <= n ; i++) {
        if(n % i == 0 && is_prime(i)) {
            counter++;
        }
    }
    return counter % 2 == 0;
}

// Podziel
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


// Wybierz k-ty element
int quick_select(vector<int>& arr, int low, int high, int k) {
    if (low == high) {
        return arr[low];
    }

    int pivot_i = partition(arr, low, high);

    if (pivot_i == k) {
        return arr[pivot_i];
    } else if (k < pivot_i) {
        return quick_select(arr, low, pivot_i - 1, k);
    } else {
        return quick_select(arr, pivot_i + 1, high, k);
    }
}

void print_vector(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> stable_numbers;
        for (int i = 0;  i < n ; i++) {
            int temp;
            cin >> temp;
            if(even_prime_factors(temp)) {
                stable_numbers.push_back(temp);
            }
        }
        int k;
        cin >> k;

        if (k >= stable_numbers.size()) {
            cout << "BRAK DANYCH\n";
            continue;
        }

        //print_vector(stable_numbers);

        cout << quick_select(stable_numbers, 0, stable_numbers.size() - 1, k) << endl;
    }
}