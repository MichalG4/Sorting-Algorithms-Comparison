#include <iostream>
#include <fstream>
#include <chrono>
#include "sorting.h"
//g++ main.cpp sorting.cpp -o main -Wl,--stack,67108864
const unsigned int N=100000; //961532 all data
int main() {
    std::ifstream file("projekt1_dane.csv");
    std::ofstream out("ratings_out.txt");
    std::string line;

    int* array=new int[N];

    std::getline(file, line); // nagłówek
    unsigned int i=N;
    while (std::getline(file, line) && i>0) {
        int lastComma = line.rfind(',');
        std::string rating = line.substr(lastComma + 1);
        if (rating.empty()) continue;
        array[N-i]=(int)std::stof(rating);
        i--;    
        out << (int)std::stof(rating) << "\n";
        //std::cout << (int)std::stof(rating) << "\n";
    }
    // auto start = std::chrono::high_resolution_clock::now();
    // merge_sort(array, N);
    // auto end = std::chrono::high_resolution_clock::now();
    // auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout << ms.count() << " us\n";

    int* arr = new int[N];

    auto benchmark = [&](auto sortFunc, const char* name) {
        memcpy(arr, array, N * sizeof(int));  // przywróć oryginał
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(arr, N);
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << name << ": " << ms.count() << " us\n";
    };

    benchmark(merge_sort,        "merge sort");
    benchmark(quick_sort,        "quick sort");
    benchmark(introspective_sort,"introspective sort");
    benchmark(bucket_sort,       "bucket sort");

    delete[] arr;
    delete[] array;
    return 0;
}