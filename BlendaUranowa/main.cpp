#include <iostream>

struct WorkerDataNode {
    int C;
    int K;
};

int calculateForSingleWorkerInOneSetOfDays(int C, int K, int days) {
    int active_days = days < (C / K + 1) ? days : C / K + 1; // Ile dni pracownik będzie miał wydajność > 0
    return (active_days * (2 * C - (active_days - 1) * K)) / 2; // Suma wydajności w postaci ciągu arytmetycznego
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    unsigned short t; // ilość testów
    std::cin >> t;

    while (t--) {
        int n, d, m;  // ilość pracowników, ilość zapytań o dni, oczekiwana ilość przerobowa
        std::cin >> n >> d >> m;

        WorkerDataNode workers[n];
        for (int i = 0; i < n; i++) {
            std::cin >> workers[i].C >> workers[i].K;
        }

        int counter = 0;
        for (int i = 0; i < d; i++) {
            int days;
            std::cin >> days;
            long sum = 0;
            for (int j = 0; j < n; j++) {
                sum += calculateForSingleWorkerInOneSetOfDays(workers[j].C, workers[j].K, days);
            }
            std::cout << sum << " ";
            if (sum >= m) {
                counter++;
            }
        }
        std::cout << "\n" << counter << "\n";
    }

    return 0;
}