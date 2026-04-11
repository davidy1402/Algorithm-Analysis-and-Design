#include <iostream>
using namespace std;

int main(){
    int array[10];
    for (int j = 0; j < 10; j++){
        cout << "Enter number " << j + 1 << ": ";
        cin >> array[j];
        for (int k = 0; k < j; k++){
            if (array[j] == array[k]){
                cout << "Duplicate value detected. Please enter a different number.\n";
                j--; // Decrement j to repeat the input for the current index
                break;
            }
    }
    }

    for (int j = 0; j < 10; j++){
        cout << "Index " << j << ": " << array[j] << endl;
    }
  
}
