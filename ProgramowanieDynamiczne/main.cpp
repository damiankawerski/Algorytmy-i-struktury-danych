#include <iostream>
#include <vector>
#include <stack>
using namespace std;


void fill_dynamic_table(vector<vector<int>> &arr, vector<vector<int>> &dp, int N, bool &one_in_corner) {
    dp[0][0] = arr[0][0];
    for (int i = 1; i < N; ++i) {
        dp[i][0] = dp[i-1][0] + arr[i][0];
        dp[0][i] = dp[0][i-1] + arr[0][i];
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + arr[i][j];
        }
    }

    if(dp[N - 1][N - 1] > dp[N - 2][N - 1] && dp[N - 1][N - 1] > dp[N - 1][N - 2]) {
        one_in_corner = true;
    } else {
        one_in_corner = false;
    }
}

void take_down_ones(vector<vector<int>> &arr, vector<vector<int>> &dp, int N, bool one_in_corner) {
    if(one_in_corner) {
        arr[0][0] = 0;
    }

    int i = N - 1;
    int j = N - 1;

    while(i > 0 || j > 0) {
        arr[i][j] = 0;

        if(i > 0 && j > 0) {
            // Wybieramy kierunek, skąd przyszliśmy
            if(dp[i-1][j] > dp[i][j-1]) {
                i--;
            } else {
                j--;
            }
        } else if(i > 0) {
            i--;
        } else {
            j--;
        }
    }

    // Zerowanie pozostałych elementów, jeśli jeden z indeksów doszedł do zera
    if(i == 0) {
        for(int k = 0; k <= j; k++) {
            arr[i][k] = 0;
        }
    }
}

void print_matrix(vector<vector<int>> &arr, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int N;
    cin >> N;

    vector<vector<int>> macierz(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int temp;
            cin >> temp;
            macierz[i][j] = temp;
        }
    }
    bool one_in_corner;


    vector<vector<int>> dp(N, vector<int>(N, 0));
    fill_dynamic_table(macierz, dp, N, one_in_corner);
    take_down_ones(macierz, dp, N, one_in_corner);
    int result = dp[N - 1][N - 1];
    fill_dynamic_table(macierz, dp, N, one_in_corner);
    result += dp[N - 1][N - 1];
    cout << result << endl;


    return 0;
}
