#include <iostream>
#include <cstdio>
#include <cmath>

// Funkcja do zamiany wartości
void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

// Implementacja algorytmu CountingSort dla liczb zmiennoprzecinkowych
void countingSort(double* arr, int n) {
    // Znajdź zakres wartości
    double minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        minVal = std::min(minVal, arr[i]);
        maxVal = std::max(maxVal, arr[i]);
    }

    // Oblicz zakres i przesunięcie
    double range = maxVal - minVal;

    // Jeśli wszystkie wartości są takie same, nie ma potrzeby sortowania
    if (range == 0) return;

    // Alokacja pamięci dla bucket'ów
    int bucketCount = std::min(n, 10000);
    double* buckets = new double[bucketCount]();
    int* bucketSizes = new int[bucketCount]();

    // Rozłóż elementy do bucket'ów
    for (int i = 0; i < n; i++) {
        int bucketIndex = static_cast<int>((arr[i] - minVal) / range * (bucketCount - 1));
        buckets[bucketIndex * n + bucketSizes[bucketIndex]] = arr[i];
        bucketSizes[bucketIndex]++;
    }

    // Sortowanie każdego bucket'a (np. insertion sort)
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 1; j < bucketSizes[i]; j++) {
            double key = buckets[i * n + j];
            int k = j - 1;
            while (k >= 0 && buckets[i * n + k] > key) {
                buckets[i * n + k + 1] = buckets[i * n + k];
                k--;
            }
            buckets[i * n + k + 1] = key;
        }
    }

    // Kopiowanie posortowanych elementów z powrotem do oryginalnej tablicy
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index++] = buckets[i * n + j];
        }
    }

    // Zwolnienie pamięci
    delete[] buckets;
    delete[] bucketSizes;
}

int main() {
    // Wczytanie liczby słupków
    int n;
    std::scanf("%d", &n);

    // Tablica do przechowywania pozycji słupków
    double* pozycje = new double[n];

    // Wczytanie pozycji słupków
    for (int i = 0; i < n; i++) {
        std::scanf("%lf", &pozycje[i]);
    }

    // Sortowanie liniowe (Bucket Sort)
    countingSort(pozycje, n);

    // Obliczenie maksymalnej długości przęsła
    double maxPrzesl = 0.0;
    for (int i = 1; i < n; i++) {
        maxPrzesl = std::max(maxPrzesl, std::abs(pozycje[i] - pozycje[i-1]));
    }

    // Wypisanie wyniku z dokładnością do 4 miejsc po przecinku
    printf("%.4f\n", maxPrzesl);

    // Zwolnienie pamięci
    delete[] pozycje;

    return 0;
}