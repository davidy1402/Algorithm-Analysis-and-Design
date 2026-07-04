#include <iostream>
#include <algorithm> // for sort()
#include <iomanip>   // for setw
using namespace std;

struct Surgery{
    string surgeryID;
    double processing_time;
    int deadline;
    int profit;
};

// comparator: sort() calls this to decide ordering - true means "a comes before b"
// ties on deadline go to the higher-profit surgery, so a shared slot is
// resolved in favor of profit rather than left to chance
bool byDeadline(const Surgery& a, const Surgery& b) {
    if (a.deadline != b.deadline)
        return a.deadline < b.deadline;
    return a.profit > b.profit;
}

void schedule(Surgery surgeries[], int n) {
    sort(surgeries, surgeries + n, byDeadline);

    double currentTime = 0.0;
    int totalProfit = 0;

    Surgery scheduled[10];
    Surgery skipped[10];
    int scheduledCount = 0, skippedCount = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime + surgeries[i].processing_time <= surgeries[i].deadline) {
            scheduled[scheduledCount++] = surgeries[i];
            currentTime += surgeries[i].processing_time;
            totalProfit += surgeries[i].profit;
        } else {
            skipped[skippedCount++] = surgeries[i];
        }
    }

    // i. Scheduled surgeries + details
    cout << "\n=== Scheduled Surgeries ===\n";
    cout << left << setw(8) << "ID" << setw(16) << "Processing Time"
         << setw(10) << "Deadline" << "Profit (RM)" << endl;
    for (int i = 0; i < scheduledCount; i++) {
        cout << left << setw(8) << scheduled[i].surgeryID
             << setw(16) << scheduled[i].processing_time
             << setw(10) << scheduled[i].deadline
             << scheduled[i].profit << endl;
    }
    cout << "Total surgeries scheduled: " << scheduledCount << endl;

    // ii. Total profit
    cout << "\nTotal profit: RM " << totalProfit << endl;

    // iii. Skipped surgeries + loss in profit
    cout << "\n=== Surgeries Not Scheduled ===\n";
    if (skippedCount == 0) {
        cout << "None - all surgeries were completed.\n";
    } else {
        cout << left << setw(8) << "ID" << setw(16) << "Processing Time"
             << setw(10) << "Deadline" << "Loss in Profit (RM)" << endl;
        int totalLoss = 0;
        for (int i = 0; i < skippedCount; i++) {
            cout << left << setw(8) << skipped[i].surgeryID
                 << setw(16) << skipped[i].processing_time
                 << setw(10) << skipped[i].deadline
                 << skipped[i].profit << endl;
            totalLoss += skipped[i].profit;
        }
        cout << "Total loss in profit: RM " << totalLoss << endl;
    }
}


int main() {
    Surgery datasets[6][10];
    int datasetSize[6] = {0};

    // Sample Dataset: Surgery ID, Processing Time (hours), Deadline (hours from 08:00), Profit (RM)
    datasetSize[0] = 10;
    datasets[0][0] = {"S1",  2.0, 5, 10000};
    datasets[0][1] = {"S2",  1.5, 3, 15000};
    datasets[0][2] = {"S3",  3.0, 6, 20000};
    datasets[0][3] = {"S4",  1.0, 2, 5000};
    datasets[0][4] = {"S5",  2.5, 4, 25000};
    datasets[0][5] = {"S6",  0.5, 1, 8000};
    datasets[0][6] = {"S7",  2.0, 5, 12000};
    datasets[0][7] = {"S8",  1.0, 7, 18000};
    datasets[0][8] = {"S9",  2.0, 8, 30000};
    datasets[0][9] = {"S10", 1.5, 6, 10000};

    // Dataset 2: best case - every surgery can be completed within its deadline
    datasetSize[1] = 6;
    datasets[1][0] = {"S1", 1.0,  2, 8000};
    datasets[1][1] = {"S2", 1.5,  4, 12000};
    datasets[1][2] = {"S3", 1.0,  5, 6000};
    datasets[1][3] = {"S4", 2.0,  8, 15000};
    datasets[1][4] = {"S5", 0.5,  9, 4000};
    datasets[1][5] = {"S6", 1.0, 10, 7000};

    // Dataset 3: trade-off - one big-profit surgery vs several smaller ones that together outweigh it (S1 alone = 30000, but S2+S3+S4+S5 = 36000 and exactly fits the same 4-hour window, so greedily picking S1 first loses)
    datasetSize[2] = 5;
    datasets[2][0] = {"S1", 4.0, 4, 30000};
    datasets[2][1] = {"S2", 1.0, 1, 9000};
    datasets[2][2] = {"S3", 1.0, 2, 9000};
    datasets[2][3] = {"S4", 1.0, 3, 9000};
    datasets[2][4] = {"S5", 1.0, 4, 9000};

    // Dataset 4: two surgeries compete for the same time slot (conflict)
    datasetSize[3] = 5;
    datasets[3][0] = {"S1", 2.0, 2, 10000};
    datasets[3][1] = {"S2", 2.0, 2, 16000};
    datasets[3][2] = {"S3", 1.0, 4, 6000};
    datasets[3][3] = {"S4", 1.5, 5, 9000};
    datasets[3][4] = {"S5", 1.0, 3, 7000};

    // Dataset 5: one long, high-profit surgery whose 4-hour run crowds out several short surgeries with tight deadlines that fall inside that window
    datasetSize[4] = 5;
    datasets[4][0] = {"S1", 4.0, 5, 40000};
    datasets[4][1] = {"S2", 1.0, 1, 5000};
    datasets[4][2] = {"S3", 1.0, 2, 6000};
    datasets[4][3] = {"S4", 1.0, 3, 7000};
    datasets[4][4] = {"S5", 1.0, 4, 8000};

    // Dataset 6: worst case - many surgeries, very tight deadlines
    datasetSize[5] = 10;
    datasets[5][0] = {"S1",  2.0, 2, 10000};
    datasets[5][1] = {"S2",  1.5, 2, 8000};
    datasets[5][2] = {"S3",  2.5, 3, 20000};
    datasets[5][3] = {"S4",  1.0, 1, 5000};
    datasets[5][4] = {"S5",  3.0, 3, 25000};
    datasets[5][5] = {"S6",  2.0, 2, 12000};
    datasets[5][6] = {"S7",  1.5, 2, 9000};
    datasets[5][7] = {"S8",  2.0, 3, 15000};
    datasets[5][8] = {"S9",  1.0, 1, 6000};
    datasets[5][9] = {"S10", 2.5, 2, 18000};

    cout << fixed << setprecision(1);

    int choice;
    do {
        cout << "\n=== Surgery Scheduler ===\n";
        cout << "1. Use existing dataset\n";
        cout << "2. Enter custom data\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int datasetChoice;
            cout << "Choose a dataset (1-6): ";
            cin >> datasetChoice;
            while (datasetChoice < 1 || datasetChoice > 6) {
                cout << "Invalid choice. Enter a number between 1 and 6: ";
                cin >> datasetChoice;
            }
            schedule(datasets[datasetChoice - 1], datasetSize[datasetChoice - 1]);

        } else if (choice == 2) {
            int n;
            cout << "Enter number of surgeries (max 10): ";
            cin >> n;
            while (n < 1 || n > 10) {
                cout << "Invalid input. Enter between 1 and 10: ";
                cin >> n;
            }

            Surgery custom[10];
            for (int i = 0; i < n; i++) {
                cout << "\nSurgery " << i + 1 << ":\n";
                cout << "  Surgery ID: ";
                cin >> custom[i].surgeryID;
                cout << "  Processing time (hours): ";
                cin >> custom[i].processing_time;
                cout << "  Deadline (hours from 08:00): ";
                cin >> custom[i].deadline;
                cout << "  Profit (RM): ";
                cin >> custom[i].profit;
            }
            schedule(custom, n);

        } else if (choice == 3) {
            cout << "Exiting program. Goodbye!\n";

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

