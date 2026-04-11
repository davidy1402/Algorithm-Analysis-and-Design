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

double calculateTotalItemCost(double cost[], int n){
    double sum = 0;
    for (int i = 0; i < n; i++){
        sum += cost[i];
    }
    return sum;
}


int main(){
    int n = 0, i;
    cout << "How many items do you have? ";
    cin >> i;
    double cost[i], shipping_method, damage_protection_cost, discount_applied = 0, insurance_applied = 0, discount_price, total_item_cost; 
    cout << "Please enter the item(s)' cost (Enter -1 to exit) \n";
    do {
        cout << "Please input the cost of the item "<< n + 1<< ": $ "; 
        cin >> cost[n];
        if (cost[n] == -1) break;
        n++;
    } while (n < i);

    total_item_cost = calculateTotalItemCost(cost, i);

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
            if (total_item_cost > 50){
                cout << "Discount of 5% is applied!";
                discount_price = calculatePercentage(total_item_cost, 5);
                discount_applied = 1;

            } else {
                cout << "Sorry you do not meet the minimum spend.";
            }
        }
        if (discount_code == "AUTUMNISHERE"){
            if (total_item_cost > 150){
                cout << "Discount of $ 15 is applied!";
                discount_price = 15;
                discount_applied = 1;
            } else {
                cout << "Sorry you do not meet the minimum spend.";
            }
        }
        if (discount_code == "FREESHIPPING"){
            if (total_item_cost > 300 && shipping_method != 3){
                cout << "Your shipping fee is free!";
                discount_price = (shipping_method == 1 ? 4.90 : shipping_method == 2 ? 6.90: 0);
                discount_applied = 1;

            } else {
                cout << "Sorry you do not meet the minimum spend or this voucher does not apply to your current shipping method.";
            }
        }
        cout << endl;
    } 
    if (total_item_cost > 250){
        damage_protection_cost = calculateDamageProtection(total_item_cost);
        cout << "Do you want to purchase an optional insurance ($ " << damage_protection_cost << ") for your item? (Y/N) ";
        char damage_protection_choice;
        cin >> damage_protection_choice;
        if (damage_protection_choice == 'Y') {
            cout << "Insurance applied successfully!\n";
            insurance_applied = 1;
        }
    }

    cout << "\n----------------------------Checking-------------------------------------\n";
    cout << "Subtotal of your item(s) = $ " << total_item_cost << "\n";
    double shipping_fee = (shipping_method == 1 ? 4.90 : shipping_method == 2 ? 6.90 : 10.50);
    cout << "Shipping Fee = $ " << shipping_fee << "\n";
    if (insurance_applied){
        cout << "Damage Protection Fee  = $ " << damage_protection_cost << "\n";
    }
    if (discount_applied){
        cout << "Discount Voucher  = -$ " << discount_price << "\n";
    }
    double total_cost = calculateTotalCost(total_item_cost, shipping_fee, (insurance_applied ? damage_protection_cost : 0), (discount_applied ? discount_price : 0));
    cout << "Total cost = $ " << total_cost << "\n";
    
    return 0;
}