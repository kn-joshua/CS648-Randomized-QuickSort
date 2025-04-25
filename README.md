# Project Overview
This repository contains code for a course project in CS648: Randomized Algorithms at IIT Kanpur, Winter 2025, focusing on analyzing randomized QuickSort. It includes implementations and experiments to study the algorithm's performance, particularly the number of comparisons and deviation probabilities.

## Repository Contents
* **Files**: Two main files: quick_sort_implementation.cpp and experimental_setup.cpp.
* **Purpose**: quick_sort_implementation.cpp shows QuickSort with random pivots, while experimental_setup.cpp runs experiments to measure performance metrics.

## Cloning Instructions
To get started, clone the repository using this command:
```git clone https://github.com/kn-joshua/CS648-Randomized-QuickSort.git```

## Running the Code
* For quick_sort_implementation.cpp, compile with g++ quick_sort_implementation.cpp -o quicksort and run with ./quicksort. It demonstrates sorting a sample array.
* For experimental_setup.cpp, compile with g++ experimental_setup.cpp -o experiment -std=c++11 and run with ./experiment. It runs experiments, saving results to quicksort_results.csv, which may take time due to many trials.

## Parameters and Usage
* experimental_setup.cpp uses parameters like 5000 trials per array size, array sizes from 500 to 5,000,000 in steps of 500, and calculates deviation probabilities from 1% to 100%.
* Ensure you have a C++ compiler and OpenMP for parallelization when running experiments.

## Detailed Analysis of Randomized QuickSort Repository 
This report provides a comprehensive analysis of the preparation for a README file for a GitHub repository containing experimental code for a course project on randomized algorithms, specifically focusing on QuickSort. 

The project is part of CS648: Randomized Algorithms at IIT Kanpur, offered during Winter 2025, and involves three team members: Aravind Seshadri, Aatman Jain, and Kapu Nirmal Joshua. The repository includes two main files, experimental_setup.cpp and quick_sort_implementation.cpp.
