#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    long arr[n * 2];
    for (int i = 0; i < n * 2; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cout << arr[2*i] + arr[2*i + 1] << endl;
    }
}
