#include <iostream>
using namespace std;
#include <vector>
#include <sstream> //for stringstream to format movie IDs
#include <iomanip> //for setw and setfill 
#include <unordered_set> //for tracking used IDs to make sure all movie IDs are unique
#include <chrono> //for measuring how long each sort takes
#include <algorithm> //for swap
#include <random> //for mt19937 and uniform distributions

/*
mt19937 is used instead of rand() because rand() has poor randomness quality and can produce the same sequence each run. mt19937 seeds differently every run.
(cppreference.com, n.d.-b; cppreference.com, n.d.-c)
*/
    random_device rd;
    mt19937 gen(rd());//
    

//display the list of the sorted ratings (descending) and its corresponding sorted movie IDs (ascending order)
bool descendingAscending(const pair<float,string>& a, const pair<float,string>& b)
{
    //sort by rating descending
    if (a.first != b.first)
        return a.first > b.first;// higher rating comes first

    //if same rating, smaller ID first
    return a.second < b.second;
}

/*
Hoare's partitioning scheme: two pointers start from opposite ends and move inward, swapping elements on the wrong side of the pivot until they cross.Returns split point j for the next recursive calls.
(Hoare, 1962)
*/
int hoarePartition(vector<pair<float,string>>& arr, int lo, int hi, pair<float,string> pivot) {
    
    int i = lo - 1; //so first i++ lands on lo
    int j = hi + 1; //so first j-- lands on hi

    do {
        //move i right
        do {
            i++;
        } while (i <= hi && descendingAscending(arr[i], pivot)); //cuz we want descending order, so we skip elements greater than pivot

        //move j left
        do {
            j--;
        } while (j >= lo && descendingAscending(pivot, arr[j])); //skip elements less than pivot

        //if i < j, swap
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    } while (i < j);//repeat until pointers cross
   

    return j; //return split point for recursive calls
    
}

/*----------------------------3 ways to Choose Pivot---------------------------------*/
int partitionFirst(vector<pair<float,string>>& arr, int lo, int hi) {
    // pivot is first element
    return hoarePartition(arr, lo, hi, arr[lo]);
}

int partitionMedian(vector<pair<float,string>>& arr, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;

    //Find median of arr[lo], arr[mid], arr[hi]
    pair<float,string> a = arr[lo];
    pair<float,string> b = arr[mid];
    pair<float,string> c = arr[hi];
    pair<float,string> pivot;

    //Sort a, b, c using descendingAscending so that after sorting: a is largest, b is median, c is smallest
    if (descendingAscending(b, a)) swap(a, b); //ensure a >= b
    if (descendingAscending(c, b)) swap(b, c); //ensure b >= c
    if (descendingAscending(b, a)) swap(a, b); //re-check a >= b after swapping b and c, because b's value may have changed after the previous swap

    //Now a >= b >= c, so b is the median
    pivot = b;

    return hoarePartition(arr, lo, hi, pivot);
}

int partitionRandom(vector<pair<float,string>>& arr, int lo, int hi) {
    //pick random index, then partition
    uniform_int_distribution<int> distribution(lo, hi);//inclusive distribution to get a random index between lo and hi

    int randomIndex = distribution(gen);//get random index in the range [lo, hi]
    return hoarePartition(arr, lo, hi, arr[randomIndex]);
}
/*----------------------------3 ways to Choose Pivot ENDED---------------------------------*/


/*---------- QuickSort ----------*/
void quickSortFirst(vector<pair<float,string>>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int j = partitionFirst(arr, lo, hi);
    quickSortFirst(arr, lo, j);
    quickSortFirst(arr, j+1, hi);
}

void quickSortMedian(vector<pair<float,string>>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int j = partitionMedian(arr, lo, hi);
    quickSortMedian(arr, lo, j);
    quickSortMedian(arr, j+1, hi);
}

void quickSortRandom(vector<pair<float,string>>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int j = partitionRandom(arr, lo, hi);
    quickSortRandom(arr, lo, j);
    quickSortRandom(arr, j+1, hi);
}
/*---------- QuickSort ENDED ----------*/

//generates n unique movie entries with random IDs and ratings
vector<pair<float, string>> generateMovies(int n) {
    //distributions for generating random movie IDs and ratings
    uniform_int_distribution<int> idDistribution(0,9999999); //7-digit IDs from 0000000 to 9999999 
    uniform_int_distribution<int> ratingDistribution(10, 100);//ratings from 1.0 to 10.0 with one decimal place, so we generate an int from 10 to 100 and divide by 10 later to get one decimal place
 
    vector<pair<float, string>> movieList;
    unordered_set<int> usedIDs;
 
    while ((int)movieList.size() < n) {
        int id = idDistribution(gen);
 
        if (usedIDs.find(id) == usedIDs.end()) {
            usedIDs.insert(id);
 
            float rating = ratingDistribution(gen) / 10.0f;
 
            stringstream ss;//format ID as "MOVxxxxxxx" with leading zeros
            ss << "MOV" << setw(7) << setfill('0') << id;
            string movieID = ss.str();//e.g. if id is 123, movieID becomes "MOV0000123"
 
            movieList.emplace_back(rating, movieID);//
        }
    }
 
    return movieList;
}
 
//prints rating and movieID for each entry in the list
void displayMovies(const vector<pair<float, string>>& movieList) {
    cout << left << setw(12) << "Rating" << "MovieID" << endl;
    for (const auto& movie : movieList) {
        cout << left << setw(12) << fixed << setprecision(1) << movie.first
             << movie.second << endl;
    }
}

//generates movies, runs all 3 quickSort variants, displays timing and passes sorted result back via movies1 reference for display in menu
void generateAndSort(int n,
    vector<pair<float,string>>& movies,
    vector<pair<float,string>>& movies1) {

    movies = generateMovies(n);
 
    movies1 = movies; //movies1 is for first pivot
    vector<pair<float,string>> movies2 = movies; //movies2 is for median pivot
    vector<pair<float,string>> movies3 = movies; //movies3 is for random pivot
 
    auto start1 = chrono::high_resolution_clock::now();
    quickSortFirst(movies1, 0, n-1);
    auto end1 = chrono::high_resolution_clock::now();
    double time1 = chrono::duration<double, milli>(end1 - start1).count();
 
    auto start2 = chrono::high_resolution_clock::now();
    quickSortMedian(movies2, 0, n-1);
    auto end2 = chrono::high_resolution_clock::now();
    double time2 = chrono::duration<double, milli>(end2 - start2).count();
 
    auto start3 = chrono::high_resolution_clock::now();
    quickSortRandom(movies3, 0, n-1);
    auto end3 = chrono::high_resolution_clock::now();
    double time3 = chrono::duration<double, milli>(end3 - start3).count();
 
    cout << "===== Sorting complete. =====" << endl;
    cout << "First pivot:     " << time1 << " ms" << endl;
    cout << "Median-of-three: " << time2 << " ms" << endl;
    cout << "Random pivot:    " << time3 << " ms" << endl;
}


int main(){   

    int n, choice;
    cout << "===== MovieFlix=====" << endl;
    cout << "Please enter number of movies to generate (max 1,000,000): ";
    cin >> n;

        //assume that a maximum of 1,000,000 movie IDs can be generated. 
        while (n > 1000000 || n <= 0) {
            cout << "Invalid input. Please enter between 1 and 1,000,000: ";
            cin >> n; //keep asking until user inputs a valid number
        }

    vector<pair<float,string>> movies;
    vector<pair<float,string>> movies1;
 
    generateAndSort(n, movies, movies1);//movies1 is passed by reference and will contain the sorted list for display in menu
 
    do {
        cout << "\n===== Menu =====" << endl;
        cout << "1. Display unsorted list" << endl;
        cout << "2. Display sorted list" << endl;
        cout << "3. Enter a new number of movies to generate" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
 

    switch (choice) {
            case 1:
                cout << "\nUnsorted Movies:\n";
                displayMovies(movies);
                break;
            case 2:
                cout << "\nSorted Movies:\n";
                displayMovies(movies1);
                break;
            case 3:
                cout << "Please enter number of movies to generate (max 1,000,000): ";
                cin >> n;
                while (n > 1000000 || n <= 0) {
                    cout << "Invalid input. Please enter between 1 and 1,000,000: ";
                    cin >> n;
                }
                generateAndSort(n, movies, movies1);
                break;
            case 4:
                cout << "Exiting program. See ya!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}