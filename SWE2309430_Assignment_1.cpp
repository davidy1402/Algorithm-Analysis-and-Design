#include <iostream>
#include <iomanip>		// To use setw() & setfill()
#include <ctime> 		// To use time() & clock()
#include <cstdlib>		// To use rand() & srand()
#include <vector> 		// To use vector instead of array
#include <algorithm> 	// To use sort()
#include <chrono>			// To use "steady_clock"
using namespace std;
using namespace std::chrono; // To not use "std::chrono::" on the code

//=================================================================================================================================================
//=================================================== STRUCT (To Connect IDs & Revenues) ==========================================================

struct revid{ 		//struct to connect between driver ID and its Revenue
	int id;
	double revenue;
};


//=================================================================================================================================================
//========================================================= Random ID Number Generator ============================================================

int genRandom(){
	return rand() % 1000000; //% 1000000 So that the result is between 0 and 999999
}


//=================================================================================================================================================
//========================================================= Random Revenue Number Generator =======================================================

double genRevenue(){
	int first = rand() % 10000;	//% 10000 so that the result is betwen 0 and 9999
	int last = rand() % 100;	//% 10000 so that the result is betwen 0 and 99

	return first + last / 100.0;

}

//https://www.geeksforgeeks.org/cpp-program-for-quicksort/
//=================================================================================================================================================
//============================================================== QuickSort (Ascending) ============================================================

int partition(revid arr[], int low, int high){

	int pivot = arr[high].id; //Select pivot as the last element in the ID list
	int i = (low - 1); //Left bound

	for (int j = low; j <= high - 1; j++) {
		if(arr[j].id <= pivot){
			i++;
			swap(arr[i].id, arr[j].id);
		}
	}

	swap(arr[i + 1], arr[high]); //Put the pivot to the final position

	return (i + 1); //Return the point of partition

}

void quickSort(revid arr[], int low, int high){

	if (low < high) {

		// 'pi' is Partitioning Index, arr[p] is now at
    // right place
		int pi = partition(arr, low, high);

		// Separately sort elements before and after the
    // Partition Index pi
    quickSort(arr, low, pi - 1);
  	quickSort(arr, pi + 1, high);
	}

}


//=================================================================================================================================================
//============================================================= MAIN FUNCTION =====================================================================
//=================================================================================================================================================
int main(){

	srand(time(0)); //Make sure the seed is always random based on the computer internal clock with the help of "time()"

	int n;
	clock_t time_record;

	//!------ Check validation for the input ------!
	do{
		cout << "Enter number of driver IDs to generate (1 - 1,000,000): ";
		cin >> n;

		if (n < 1 || n > 1000000){
			cout << "Please input a valid number (1 - 1,000,000)!" << endl << endl;
		}

	}while(n < 1 || n > 1000000); //Loops until a valid number is entered

	// !---------------V UNSORTED IDs V---------------!

	// !------------ Random Generated IDs ------------!

	//Use new array for dynamic memory allocation for larger memory size that consist of IDs
	revid* random = new revid[n];

  for (int i = 0; i < n; i++){
		random[i].id = genRandom();					//Access variable "id" inside struct and generate random values
  	random[i].revenue = genRevenue();		//Access variable "revenue" inside struct and generate random values
	}

	// Create arrays for ascending and descending IDs
 	revid* ascending = new revid[n];
  revid* descending = new revid[n];


	// !------------ Ascending IDs ------------------------------------------------!

	//Copy set of IDs to ascending array
	for (int i = 0; i < n; i++){
		ascending[i] = random[i];
	}

	//Sorting the array into ascending order with sort() while comparing the ID
	//https://www.digitalocean.com/community/tutorials/sort-in-c-plus-plus
	sort(ascending, ascending +n, [](revid& a, revid& b){return a.id < b.id; });

	//Copy the values in ascending in a reverse order so it becomes descending
	for (int i = 0; i < n; i++){
		descending[i] = ascending [n - 1 - i];
	}


	// !----------------V SORTED IDs V----------------------------------------------!

	// Timing for random quicksort
	auto start_random = steady_clock::now();
	quickSort(random, 0, n - 1);
	auto end_random = steady_clock::now();
	auto time_random = std::chrono::duration_cast<nanoseconds>(end_random - start_random);
	cout << "Randomized\t: " << fixed << setprecision(10) << time_random.count() << " nanoseconds." << std::endl;

	// Timing for ascending quicksort
	auto start_ascending = steady_clock::now();
	quickSort(ascending, 0, n - 1);
	auto end_ascending = steady_clock::now();
	auto time_ascending = duration_cast<nanoseconds>(end_ascending - start_ascending);
	cout << "Ascending\t: " << fixed << setprecision(10) << time_ascending.count() << " microseconds." << std::endl;

	// Timing for descending quicksort
	auto start_descending = steady_clock::now();
	quickSort(descending, 0, n - 1);
	auto end_descending = steady_clock::now();
	auto time_descending = duration_cast<nanoseconds>(end_descending - start_descending);
	cout << "Descending\t: " << fixed << setprecision(10) << time_descending.count() << " nanoseconds." << std::endl;


	// !----------------V MENU V----------------------------------------------!

	cout << "======================================================" << endl;
	cout << "\t\t\t MENU \t\t\t    ||" << endl;
	cout << "======================================================" << endl;
	int input;

	switch(input){
		case '1':
			cout << "This is one";
		break;
		case '2':
			cout << "This is two";
		break;
		case '3':
			cout << "This is three";
		break;
		case '4':
			cout << "This is four";
		break;
	}




	cout << "\nRandom IDs and Revenues:\n";
  for (int i = 0; i < n; i++) {
    cout << i+1 << ". ID: S" << setw(6) << setfill('0') << random[i].id << "BX, Revenue: RM";
		cout << fixed << setprecision(2) << random[i].revenue << endl;
  }




	//Delete dynamic array
	delete[] random;
	delete[] ascending;
	delete[] descending;



	return 0;
}
