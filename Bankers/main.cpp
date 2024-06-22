#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int MAX_PROCESSES = 5;
const int MAX_RESOURCES = 3;

vector<int> available(MAX_RESOURCES);
vector<vector<int>> max_claim(MAX_PROCESSES, vector<int>(MAX_RESOURCES));
vector<vector<int>> allocation(MAX_PROCESSES, vector<int>(MAX_RESOURCES));
vector<vector<int>> need(MAX_PROCESSES, vector<int>(MAX_RESOURCES));

bool is_safe(int process, vector<int>& work, vector<bool>& finish) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (need[process][i] > work[i]) {
            return false;
        }
    }
    return true;
}

bool bankers_algorithm(vector<int>& safe_sequence) {
    vector<int> work = available;
    vector<bool> finish(MAX_PROCESSES, false);

    for (int iteration = 0; iteration < MAX_PROCESSES; ++iteration) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finish[i] && is_safe(i, work, finish)) {
                for (int j = 0; j < MAX_RESOURCES; ++j) {
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
                safe_sequence.push_back(i);
                found = true;
                break;  // Break after finding a safe process
            }
        }
        if (!found) {
            // The system is in an unsafe state
            return false;
        }
    }

    // The system is in a safe state
    return true;
}

void display_status() {
    cout << "Initial Status of the System:" << endl;
    cout << "Available Resources: ";
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        cout << available[i] << " ";
    }
    cout << endl << setw(20) << "Max Claim Matrix" << setw(20) << "Allocation Matrix" << setw(20) << "Need Matrix" << endl;
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cout << setw(5) << max_claim[i][j];
        }
        cout << setw(10) << " ";
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cout << setw(5) << allocation[i][j];
        }
        cout << setw(10) << " ";
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cout << setw(5) << need[i][j];
        }
        cout << endl;
    }
}

int main() {
    // Initialize available resources
    cout << "Enter the available resources:" << endl;
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        cin >> available[i];
    }

    // Initialize maximum claim matrix
    cout << "Enter the maximum claim matrix:" << endl;
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cin >> max_claim[i][j];
        }
    }

    // Initialize allocation matrix
    cout << "Enter the allocation matrix:" << endl;
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cin >> allocation[i][j];
            need[i][j] = max_claim[i][j] - allocation[i][j];
        }
    }

    // Display the initial status
    display_status();

    // Check if the system is in a safe state
    vector<int> safe_sequence;
    if (!bankers_algorithm(safe_sequence)) {
        cout << "The given sequence is not safe." << endl;

        // Attempt to find a safe sequence
        safe_sequence.clear();
        if (bankers_algorithm(safe_sequence)) {
            cout << "\nSafe Sequence: ";
            for (int i = 0; i < MAX_PROCESSES; ++i) {
                cout << "P" << safe_sequence[i];
                if (i != MAX_PROCESSES - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
            cout << "The system is in a safe state." << endl;
        } else {
            cout << "Unable to find a safe sequence." << endl;
        }
    } else {
        cout << "\nSafe Sequence: ";
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            cout << "P" << safe_sequence[i];
            if (i != MAX_PROCESSES - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "The system is in a safe state." << endl;
    }

    return 0;
}
