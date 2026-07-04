#include <iostream>

using namespace std;

void ComputingTheSumOfTwoNumbers(int num1, int num2) {
   
    cout << num1 + num2 << endl;
}

void EuclidsAlgorithm (int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    cout << "GCD: " << a << endl;
}

void SortAnArrayOfNumbers(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void findTheLargestElementInAListOfNumbers(int arr[], int size) {
    // state, in one sentence its basic operation:
    // initialize the largest element as the first element of the array, then iterate through the array comparing each element with the current largest and updating it if a larger element is found.
}

void computingNFactorialOfANumber(int n) {
       // state, in one sentence its basic operation:
    // initialize a variable to store the factorial result, then multiply it by each integer from 1 to n in a loop, and return the final result.
}

int main() {
    int num1 = 5, num2 = 10;  
    ComputingTheSumOfTwoNumbers(num1, num2);

    EuclidsAlgorithm(num1, num2);
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    SortAnArrayOfNumbers(arr, size);

    computingNFactorialOfANumber(num1);

    
}