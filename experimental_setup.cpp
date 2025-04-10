#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <omp.h>
#include <random>
using namespace std;

// Function to perform QuickSort. This doesnt handle duplicates, since its not required in our experimental setup
void quickSort(int arr[], int low, int high, long long &comp) {
    if (low < high) {
        thread_local std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<int> pivot{ low, high };
        int pivotIndex = pivot(mt);
        int pivotValue = arr[pivotIndex];
        std::swap(arr[pivotIndex], arr[high]);  // Move pivot to end
        
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            ++comp;  // Count each comparison
            if (arr[j] < pivotValue) {
                std::swap(arr[++i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);  // Restore pivot
        
        quickSort(arr, low, i, comp); // Sort left partition
        quickSort(arr, i + 2, high, comp); //Sort right partition
    }
}

int main() {
    // Configuration parameters

    int t = 5000; // Number of trials per n
    double eps = 0.1;  // Epsilon for deviation threshold
    double c = 0.3;    // Theoretical constant

    // Open a CSV file for writing the output
    ofstream csvFile("quicksort_results.csv");
    if (!csvFile) {
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }
    csvFile << "n,AverageComparisons,ExperimentalProbability" << endl;
    int step=500;
    int n=500;
    while(n<=5000000){
        // Initialize originalArr with values 1 to n using iota
        vector<int> originalArr(n);
        iota(originalArr.begin(), originalArr.end(), 1);
        // Shuffle the array; Creating a random permutation of {1....n}
        random_shuffle(originalArr.begin(), originalArr.end());

        double total = 0.0; //Stores the total no of comparisons in t trials
        double dev[100]={0}; //Stores the count of deviations

        // First loop: Calculate average comparisons (parallelized). Calculate the average
        #pragma omp parallel for num_threads(15) reduction(+: total) schedule(dynamic)
        for (int ind = 0; ind < t; ind++) {
            vector<int> localArr = originalArr; 
            long long comp = 0;
            quickSort(localArr.data(), 0, n - 1, comp); // Sort using quickSort
            total += comp;
        }
        double avg = total / t;

        // Second loop: Calculate experimental deviation probability (parallelized). Count the deviations
        #pragma omp parallel for num_threads(15) reduction(+: dev) schedule(dynamic)
        for (int ind = 0; ind < t; ind++) {
            vector<int> localArr = originalArr;
            long long comp = 0;
            quickSort(localArr.data(), 0, n - 1, comp);
            for(int eps=1;eps<=100;eps++){
                if(comp > avg + (eps * avg)/100)
                dev[eps-1]=dev[eps-1]+1;
            }
        }

        // Calculate probability
        double pr[100]={0};
        for (int i=0;i<100;i++){
            pr[i]=dev[i]/t;
        }

        // Output results for this n (both screen and file)
        cout << "n = " << n << ", Average Comparisons: " << avg<<"\n";
        csvFile << n << "," 
                << avg;
        for (int i = 0; i < 100; i++) {
            csvFile << "," << pr[i];
        }        
        csvFile << "\n";
        n+=step;        
    }

    csvFile.close();
    cout << "Results saved to quicksort_results.csv" << endl;

    return 0;
}
