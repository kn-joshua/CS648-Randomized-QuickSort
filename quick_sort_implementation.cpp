#include <iostream>
#include <vector>
#include <random>
using namespace std;;

// Function to perform QuickSort (this handles duplicates as well)
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        thread_local std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<int> pivotDist{ low, high };
        int pivotIndex = pivotDist(mt); //Randomly choose a pivot

        int pivotOriginalIndex = pivotIndex; //Store the pivot location  

        int pivotValue = arr[pivotIndex]; //Store the pivot value
        std::swap(arr[pivotIndex], arr[high]);  // Move pivot to end
        
        int i = low - 1;
        for (int j = low; j < high; ++j) {

            // Swap if element is less than pivot OR equal to pivot and originally to the left of pivot
            if (arr[j] < pivotValue || (arr[j] == pivotValue && j < pivotOriginalIndex)) {
                std::swap(arr[++i], arr[j]);
            } // This creates the left partition , remaining are on the right of i

        }
        std::swap(arr[i + 1], arr[high]);  // Restore pivot
        
        quickSort(arr, low, i); //Sort the left parititon
        quickSort(arr, i + 2, high);//Sort the right parition
    }
}

int main() {
    vector<int> arr={1,-5,3,5,4,3,1,9,10,14,12,12,85,62};
    quickSort(arr.data(),0,14-1);
    for (int i=0;i<14;i++)
    std::cout<<arr[i]<<" ";

    return 0;
}