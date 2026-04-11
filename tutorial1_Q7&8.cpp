#include <iostream>
using namespace std;


/*SET binary_representation to an empty string
INPUT decimal_number
WHILE decimal_number > 0 DO
    SET remainder to decimal_number MOD 2
    SET binary_representation equal to the remainder + binary_representation
    SET decimal_number to decimal_number DIV 2
END WHILE
*/

int main(){
    string binary_representation = "";

    int decimal_number;
    cout << "Please enter a decimal number: ";
    cin >> decimal_number;
   
    while (decimal_number > 0) {
        int remainder = decimal_number % 2;
        binary_representation += to_string(remainder);
        decimal_number = decimal_number / 2;
    }
    cout << "Binary representation: " << binary_representation << endl;
}