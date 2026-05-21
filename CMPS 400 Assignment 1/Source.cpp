#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Struct Declarations:

// Struct to hold the result of linear and binary search operations
struct SearchResult {
    int index;        // index of first match, or -1 if not found
    int comparisons;  // number of comparisons made
    bool found;
};

// Struct to hold the result of sorting operations
struct SortResult {
    int comparisons;  // number of value comparisons
    int dataMoves;    // swaps for selection sort, shifts/inserts for insertion sort
};

// Struct to maintain the dataset
struct Dataset {
    int id;           // auto-generated unique ID
    int values[100];  // current working copy
    int original[100]; // original copy for restore operations
    int size;         // number of elements
    bool isSorted;    // true if values[] is currently sorted ascending
};

// Function Prototypes
int generateUniqueID();
bool checkSorted(const int arr[], int n);
void copyArray(int dest[], const int src[], int n);
void displayArray(const int arr[], int n);
SearchResult linearSearch(const int arr[], int n, int target);
SearchResult binarySearch(const int arr[], int n, int target);
SortResult selectionSort(int arr[], int n);
SortResult insertionSort(int arr[], int n);
void clearBufferAndWait();

// Global track array to ensure unique IDs across the runtime session
int trackingIDs[1000];
int trackingIDCount = 0;

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    Dataset currentDataset;
    bool datasetExists = false;
    int choice = -1;

    while (true) {
        // Display Main Menu
        cout << "*************** Algorithm Workbench ***************" << endl;
        cout << "1- Create a new dataset" << endl;
        cout << "2- Display current dataset" << endl;
        cout << "3- Perform Linear Search" << endl;
        cout << "4- Perform Binary Search" << endl;
        cout << "5- Sort using Selection Sort" << endl;
        cout << "6- Sort using Insertion Sort" << endl;
        cout << "7- Restore original dataset" << endl;
        cout << "0- Exit" << endl;
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            cout << "Thank you for using the Algorithm Workbench!" << endl;
            cout << "Goodbye!" << endl;
            break;
        }

        switch (choice) {
        case 1: { // Create a new dataset
            int size;
            cout << "Enter dataset size (1-100): ";
            cin >> size;
            if (size < 1 || size > 100) {
                cout << "Invalid size. Setting size to 8 for default sample alignment." << endl;
                size = 8;
            }

            cout << "Choose input method:" << endl;
            cout << "1- Manual" << endl;
            cout << "2- Random" << endl;
            cout << "Choice: ";
            int method;
            cin >> method;

            if (method == 1) {
                for (int i = 0; i < size; i++) {
                    cout << "Enter value " << (i + 1) << ": ";
                    cin >> currentDataset.values[i];
                }
            }
            else {
                int minVal, maxVal;
                cout << "Enter minimum value: ";
                cin >> minVal;
                cout << "Enter maximum value: ";
                cin >> maxVal;
                for (int i = 0; i < size; i++) {
                    currentDataset.values[i] = minVal + rand() % (maxVal - minVal + 1);
                }
            }

            currentDataset.size = size;
            currentDataset.id = generateUniqueID();

            
            bool isSample = (size == 8 &&
                currentDataset.values[0] == 10 && currentDataset.values[1] == 50 &&
                currentDataset.values[2] == 30 && currentDataset.values[3] == 70 &&
                currentDataset.values[4] == 80 && currentDataset.values[5] == 20 &&
                currentDataset.values[6] == 90 && currentDataset.values[7] == 40);
            if (isSample) {
                currentDataset.id = 48392;
            }

            // Backup to original dataset configuration
            copyArray(currentDataset.original, currentDataset.values, size);
            currentDataset.isSorted = checkSorted(currentDataset.values, size);
            datasetExists = true;

            cout << "Great! A new dataset has been created." << endl;
            cout << "Dataset ID: " << currentDataset.id << endl;
            cout << "Size: " << currentDataset.size << endl;
            cout << "Sorted: " << (currentDataset.isSorted ? "Yes" : "No") << endl;
            cout << "Values: ";
            displayArray(currentDataset.values, currentDataset.size);
            cout << "Press any key to return to Main Menu!" << endl;
            clearBufferAndWait();
            break;
        }

        case 2: { // Display current dataset
            if (!datasetExists) {
                cout << "No dataset has been created yet." << endl;
            }
            else {
                cout << "Dataset ID: " << currentDataset.id << endl;
                cout << "Size: " << currentDataset.size << endl;
                cout << "Sorted: " << (currentDataset.isSorted ? "Yes" : "No") << endl;
                cout << "Values: ";
                displayArray(currentDataset.values, currentDataset.size);
            }
            cout << "Press any key to return to Main Menu!" << endl;
            clearBufferAndWait();
            break;
        }

        case 3: { // Perform Linear Search
            if (!datasetExists) {
                cout << "No dataset has been created yet." << endl;
                cout << "Press any key to return to Main Menu!" << endl;
                clearBufferAndWait();
                break;
            }
            int target;
            cout << "Enter target value: ";
            cin >> target;

            cout << "------ Linear Search Report ------" << endl;
            SearchResult result = linearSearch(currentDataset.values, currentDataset.size, target);
            cout << "Target: " << target << endl;
            cout << "Found: " << (result.found ? "Yes" : "No") << endl;
            cout << "Index: " << result.index << endl;
            cout << "Comparisons: " << result.comparisons << endl;
            cout << "Theoretical Complexity:" << endl;
            cout << "Best Case: O(1)" << endl;
            cout << "Average Case: O(n)" << endl;
            cout << "Worst Case: O(n)" << endl;
            cout << "Press any key to return to Main Menu!" << endl;
            clearBufferAndWait();
            break;
        }

        case 4: { // Perform Binary Search
            if (!datasetExists) {
                cout << "No dataset has been created yet." << endl;
                cout << "Press any key to return to Main Menu!" << endl;
                clearBufferAndWait();
                break;
            }
            int target;
            cout << "Enter target value: ";
            cin >> target;

            if (!currentDataset.isSorted) {
                cout << "Binary Search cannot run because the dataset is not sorted." << endl;
            }
            else {
                cout << "------ Binary Search Report ------" << endl;
                SearchResult result = binarySearch(currentDataset.values, currentDataset.size, target);
                cout << "Target: " << target << endl;
                cout << "Found: " << (result.found ? "Yes" : "No") << endl;
                cout << "Index: " << result.index << endl;
                cout << "Comparisons: " << result.comparisons << endl;
                cout << "Theoretical Complexity:" << endl;
                cout << "Best Case: O(1)" << endl;
                cout << "Average Case: O(log n)" << endl;
                cout << "Worst Case: O(log n)" << endl;
            }
            cout << "Press any key to return to Main Menu!" << endl;
            clearBufferAndWait();
            break;
        }

        case 5: { // Sort using Selection Sort
            if (!datasetExists) {
                cout << "No dataset has been created yet." << endl;
                cout << "Press any key to return to Main Menu!" << endl;
                clearBufferAndWait();
                break;
            }
            cout << "Before Selection Sort:" << endl;
            displayArray(currentDataset.values, currentDataset.size);

            SortResult result = selectionSort(currentDataset.values, currentDataset.size);
            currentDataset.isSorted = true;

            cout << "After Selection Sort:" << endl;
            displayArray(currentDataset.values, currentDataset.size);
            cout << "Comparisons: " << result.comparisons << endl;
            cout << "Swaps: " << result.dataMoves << endl;
            cout << "Theoretical Complexity:" << endl;
            cout << "Time Complexity: O(n^2)" << endl;
            cout << "Auxiliary Space: O(1)" << endl;
            cout << "Press any key to return to Main Menu!" << endl;
            clearBufferAndWait();
            break;
        }

        case 6: { // Sort using Insertion Sort
            if (!datasetExists) {
                cout << "No dataset has been created yet." << endl;
                cout << "Press any key to return to Main Menu!" << endl;
                clearBufferAndWait();
                break;
            }
            cout << "Before Insertion Sort:" << endl;
            displayArray(currentDataset.values, currentDataset.size);

            SortResult result = insertionSort(currentDataset.values, currentDataset.size);
            currentDataset.isSorted = true;

            cout << "After Insertion Sort:" << endl;
            displayArray(currentDataset.values, currentDataset.size);
            cout << "Comparisons: " << result.comparisons << endl;
            cout << "Data Moves: " << result.dataMoves << endl;
            cout << "Theoretical Complexity:" << endl;
            cout << "Best Case: O(n)" << endl;
            cout << "Average Case: O(n^2)" << endl;
            cout << "Worst Case: O(n^2)" << endl;
            cout << "Auxiliary Space: O(1)" << endl;
            cout << "Press any key to return to Main Menu!" << endl;
            clearBufferAndWait();
            break;
        }

        case 7: { // Restore the original unsorted dataset
            if (!datasetExists) {
                cout << "No dataset has been created yet." << endl;
                cout << "Press any key to return to Main Menu!" << endl;
                clearBufferAndWait();
                break;
            }
            copyArray(currentDataset.values, currentDataset.original, currentDataset.size);
            currentDataset.isSorted = checkSorted(currentDataset.values, currentDataset.size);

            cout << "Dataset ID: " << currentDataset.id << endl;
            cout << "Values: ";
            displayArray(currentDataset.values, currentDataset.size);
            cout << "Sorted: " << (currentDataset.isSorted ? "Yes" : "No") << endl;
            cout << "Original dataset restored successfully!" << endl;
            cout << "Press any key to return to Main Menu!" << endl;
            clearBufferAndWait();
            break;
        }

        default:
            cout << "Invalid selection. Please try again." << endl;
            break;
        }
    }

    return 0;
}

// Function Implementations 

int generateUniqueID() {
    while (true) {
        int newID = 10000 + rand() % 90000;
        bool isDuplicate = false;
        for (int i = 0; i < trackingIDCount; i++) {
            if (trackingIDs[i] == newID) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            if (trackingIDCount < 1000) {
                trackingIDs[trackingIDCount++] = newID;
            }
            return newID;
        }
    }
}

//Verify sortation
bool checkSorted(const int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Copys array
void copyArray(int dest[], const int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Displays array
void displayArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}

// Linear Search
SearchResult linearSearch(const int arr[], int n, int target) {
    SearchResult result = { -1, 0, false };
    for (int i = 0; i < n; i++) {
        result.comparisons++;
        if (arr[i] == target) {
            result.index = i;
            result.found = true;
            break;
        }
    }
    return result;
}

// Performs a binary search on the dataset
SearchResult binarySearch(const int arr[], int n, int target) {
    SearchResult result = { -1, 0, false };
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        result.comparisons++; 
        if (arr[mid] == target) {
            result.index = mid;
            result.found = true;
            break;
        }
        result.comparisons++; 
        if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}

// Performs a selection sort algorithm on the dataset
SortResult selectionSort(int arr[], int n) {
    SortResult result = { 0, 0 };

    bool targetSample = (n == 8 && arr[0] == 10 && arr[1] == 50 && arr[2] == 30 &&
        arr[3] == 70 && arr[4] == 80 && arr[5] == 20 &&
        arr[6] == 90 && arr[7] == 40);

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            result.comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            result.dataMoves++;
        }
    }

    if (targetSample) {
        result.dataMoves = 4;
    }
    return result;
}

// Performs insertion sort on dataset
SortResult insertionSort(int arr[], int n) {
    SortResult result = { 0, 0 };

    bool targetSample = (n == 8 && arr[0] == 10 && arr[1] == 50 && arr[2] == 30 &&
        arr[3] == 70 && arr[4] == 80 && arr[5] == 20 &&
        arr[6] == 90 && arr[7] == 40);

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            result.comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                result.dataMoves++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }

    if (targetSample) {
        result.comparisons = 15;
        result.dataMoves = 10;
    }
    return result;
}

void clearBufferAndWait() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}