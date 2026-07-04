#include <iostream>
using namespace std;

//implement the greedy algorithm for the change-mkaing problem
//input: A nonnegative integer amount n and a decreasing array of coin denominations D[1..m] (D[1] > D[2] > ... > D[m])
//output: Array C[1..m] of the number of coins of each denomination in the change or the 'no solution' message if the greedy algorithm fails
//for i<-1 to m do
//    C[i] <- n / D[i]  // number of coins of denomination D
//    n <- n mod D[i]  // remaining amount after using coins of denomination D
int Change(int n, int D[], int m) {
    int C[m];
    for (int i = 0; i < m; i++) {
        C[i] = n / D[i];
        n = n % D[i];
    }
    if (n == 0) {
        // cout << "Change can be made with the following coins:" << endl;
        for (int i = 0; i < m; i++) {
            cout << D[i] << " : " << C[i] << endl;
        }
    } else {
        cout << "no solution" << endl;
    }
    return 0;
}

int main() {
    int n;
    int D[] = {50, 20, 10, 5, 1}; 

    cout << "Enter the amount to change: ";
    cin >> n;
    while (n < 0) {
        cout << "Amount cannot be negative." << endl;
        cout << "Enter the amount to change: ";
        cin >> n;
    }
    int m = sizeof(D) / sizeof(D[0]);
    Change(n, D, m);

    return 0;
}