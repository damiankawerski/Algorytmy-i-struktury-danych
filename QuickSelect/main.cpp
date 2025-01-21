#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void calculate_prime_factors(vector<int>& prime_factors_count, int max_number) {
    prime_factors_count.assign(max_number + 1, 0);
    for (int i = 2; i <= max_number; ++i) {
        if (prime_factors_count[i] == 0) { // i jest liczbą pierwszą
            for (int j = i; j <= max_number; j += i) {
                prime_factors_count[j]++;
            }
        }
    }
}


int quickselect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];

    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);

    int count = i - left + 1;
    if (k == count - 1) return arr[i];
    else if (k < count - 1) return quickselect(arr, left, i - 1, k);
    else return quickselect(arr, i + 1, right, k - count);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n;

        vector<int> arr(n);
        int max_number = 0;
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
            max_number = max(max_number, arr[i]);
        }
        cin >> k;

        // Obliczenie liczby unikalnych dzielników pierwszych tylko do max_number
        vector<int> prime_factors_count;
        calculate_prime_factors(prime_factors_count, max_number);

        // Filtracja liczb korzystnych
        vector<int> stable_numbers;
        for (int num : arr) {
            if (prime_factors_count[num] % 2 == 0) {
                stable_numbers.push_back(num);
            }
        }

        if (stable_numbers.size() <= k) {
            cout << "BRAK DANYCH\n";
        } else {
            // Znalezienie k-tego najmniejszego elementu
            int result = quickselect(stable_numbers, 0, stable_numbers.size() - 1, k);
            cout << result << "\n";
        }
    }

    return 0;
}
