#include <iostream>
#include <vector>
#include <stack>
using namespace std;


void fill_dynamic_table_from_top(vector<vector<int>> &arr, vector<vector<int>> &dp, int N) {
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
}

//void fill_dynamic_table_from_bottom(vector<vector<int>> &arr, vector<vector<int>> &dp, int N) {
//    int end = N - 1;
//    dp[end][end] = arr[end][end];
//    for (int i = end - 1; i >= 0; --i) {
//        dp[i][end] = dp[i + 1][end] + arr[i][end];
//        dp[end][i] = dp[end][i + 1] + arr[end][i];
//    }
//
//    for (int i = end - 1; i >= 0; --i) {
//        for (int j = end - 1; j >= 0; --j) {
//            dp[i][j] = max(dp[i+1][j], dp[i][j+1]) + arr[i][j];
//        }
//    }
//}

void take_down_ones(vector<vector<int>> &arr, vector<vector<int>> &dp, int N) {
    int i = N - 1;
    int j = N - 1;

    while(i > 0 || j > 0) {
        arr[i][j] = 0;

        if(i > 0 && j > 0) {
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

    // Zerowanie pierwszego elementu, jeśli nie zostało wcześniej wyzerowane
    arr[0][0] = 0;
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

    vector<vector<int>> dp(N, vector<int>(N, 0));
    fill_dynamic_table_from_top(macierz, dp, N);
    take_down_ones(macierz, dp, N);
    // print_matrix(dp, N);
    int result = dp[N - 1][N - 1];
    fill_dynamic_table_from_top(macierz, dp, N);
    result += dp[N - 1][N - 1];
    cout << result << endl;
    // print_matrix(dp, N);


    return 0;
}
