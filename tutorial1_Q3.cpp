#include <iostream>
#include <string>
using namespace std;

double calculateDamageProtection(int cost){
    return cost * 0.01;
}

double calculateTotalCost(double cost, double shipping_fee, double insurance_fee , double discount_price){
    return cost + shipping_fee + insurance_fee - discount_price;
}

double calculatePercentage(int number, int percentage){
    return (number * percentage) / 100;
}

int main(){
    double cost, shipping_method, damage_protection_cost, discount_applied = 0, insurance_applied = 0, discount_price;
    cout << "Please input the cost of the item: $ "; 
    cin >> cost;
    cout << "Shipping methods:\n  1. Saver ($ 4.90)\n  2. Standard ($ 6.90)\n  3. Courier ($ 10.50)\nPlease select your shipping method (1, 2 or 3): ";
    cin >> shipping_method;
    while (shipping_method != 1 && shipping_method != 2 && shipping_method != 3){
        cout << "Invalid input. Please select your shipping method (1, 2 or 3): ";
        cin >> shipping_method;
    }
    cout << "Please enter the discount code if you have (Enter N to skip): ";
    string discount_code;
    cin >> discount_code;
    if (discount_code != "N"){
        if (discount_code == "0909CARNIVAL") {
            if (cost > 50){
                cout << "Discount of 5% is applied!";
                discount_price = calculatePercentage(cost, 5);
                discount_applied = 1;

            } else {
                cout << "Sorry you do not meet the minimum spend.";
            }
        }
        if (discount_code == "AUTUMNISHERE"){
            if (cost > 150){
                cout << "Discount of $ 15 is applied!";
                discount_price = 15;
                discount_applied = 1;
            } else {
                cout << "Sorry you do not meet the minimum spend.";
            }
        }
        if (discount_code == "FREESHIPPING"){
            if (cost > 300 && shipping_method != 3){
                cout << "Your shipping fee is free!";
                discount_price = (shipping_method == 1 ? 4.90 : shipping_method == 2 ? 6.90: 0);
                discount_applied = 1;

            } else {
                cout << "Sorry you do not meet the minimum spend or this voucher does not apply to your current shipping method.";
            }
        }
        cout << endl;
    } 
    if (cost > 250){
        damage_protection_cost = calculateDamageProtection(cost);
        cout << "Do you want to purchase an optional insurance ($ " << damage_protection_cost << ") for your item? (Y/N) ";
        char damage_protection_choice;
        cin >> damage_protection_choice;
        if (damage_protection_choice == 'Y') {
            cout << "Insurance applied successfully!\n";
            insurance_applied = 1;
        }
    }

    cout << "\n----------------------------Checking-------------------------------------\n";
    cout << "Subtotal of your item = $ " << cost << "\n";
    double shipping_fee = (shipping_method == 1 ? 4.90 : shipping_method == 2 ? 6.90 : 10.50);
    cout << "Shipping Fee = $ " << shipping_fee << "\n";
    if (insurance_applied){
        cout << "Damage Protection Fee  = $ " << damage_protection_cost << "\n";
    }
    if (discount_applied){
        cout << "Discount Voucher  = -$ " << discount_price << "\n";
    }
    double total_cost = calculateTotalCost(cost, shipping_fee, (insurance_applied ? damage_protection_cost : 0), (discount_applied ? discount_price : 0));
    cout << "Total cost = $ " << total_cost << "\n";
    
}