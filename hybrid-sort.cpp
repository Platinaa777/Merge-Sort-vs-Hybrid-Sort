#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

// merge sort section
void merge(std::vector<int>& arr, int l1, int r1, int l2, int r2) {
    int start = l1;
    std::vector<int> new_array;
    while (l1 <= r1 && l2 <= r2) {
        if (arr[l2] < arr[l1]) {
            new_array.push_back(arr[l2]);
            ++l2;
        } else {
        new_array.push_back(arr[l1]);
            ++l1;
        }
    }

    while (l1 <= r1) {
       new_array.push_back(arr[l1++]);
    }
    while (l2 <= r2) {
        new_array.push_back(arr[l2++]);
    }
    for (int i = 0; i < new_array.size(); ++i) {
        arr[start] = new_array[i];
        ++start;
    }
}

void MergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {

        MergeSort(arr, left, (left + right) / 2);
        MergeSort(arr, (left + right) / 2 + 1, right);

        merge(arr, left, (left + right) / 2,
                         (left + right) / 2 + 1, right);
    }
}

// insertion sort section
void insertionSort(std::vector<int>& vec, int n)
{
    int key, j;
    for (int i = 1; i < n; i++) {
        key = vec[i];
        j = i - 1;

        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }
}

// hybrid sort section
void HybridSort(std::vector<int>& vec, int n) {
    if (vec.size() < n) {
        insertionSort(vec, vec.size());
    } else {
        MergeSort(vec, 0, vec.size() - 1);
    }
}

std::vector<int> GetRandomVector(int n) {
    std::vector<int> vec(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3000);

    for (int i = 0; i < n; i++) {
        vec[i] = dis(gen);
    }

    return vec;
}

std::vector<int> GetDescendingVector(int n) {
    std::vector<int> vec = GetRandomVector(n); // get random vector in some order

    // then sort it
    sort(vec.begin(), vec.end());
    std::reverse(vec.begin(), vec.end());

    return vec;
}

std::vector<int> GetAlmostSortedVector(int n) {
    std::vector<int> vec = GetRandomVector(n); // get random vector in some order
    sort(vec.begin(), vec.end());
    int numPairsToSwap = (n * 10) / 100;  // 10 % of swapes

    for (int i = 0; i < numPairsToSwap; i++) {
        int index1 = rand() % n;
        int index2 = rand() % n;
        if (vec[index1] < vec[index2] && index1 > index2){
            std::swap(vec[index1], vec[index2]);
        } else if (vec[index1] > vec[index2] && index1 < index2) {
            std::swap(vec[index1], vec[index2]);
        }
    }

    return vec;
}

int main() {

    // case when only random
    for (int i = 500; i < 4001; i = i + 100) {
        std::vector<int> a = GetRandomVector(i);

        // only merge sort
        std::cout << "--------------------------------------\n";
        auto start = std::chrono::high_resolution_clock::now();
        MergeSort(a, 0, a.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        std::cout << "MERGE TOTAL TIME  = " << millisec << " ms for array size " << i << "\n";

         // hybrid sort

        // set high bounder for insertion sort
        long long sum_ms = 0;
        int k = 0;

        for (int bounder = 500; bounder <= i; bounder = bounder + 25) {
            //std::cout << "less or equal " << bounder << " insertion else merge sort\n";
            auto start = std::chrono::high_resolution_clock::now();

            HybridSort(a, bounder);

            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long millisec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            sum_ms += millisec;
            ++k;
            //std::cout << "total time: " << millisec << " ms\n";
        }
        std::cout << "HYBRID TOTAL TIME  = " << (1.0 * sum_ms) / k << '\n';
        std::cout << "--------------------------------------\n";
    }
    return 0;
}