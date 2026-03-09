#include <cstdlib>
#include <string>
#include <fstream>

#include "DataGenerator.hpp"

int main() {
    int sizes[6] = {10000, 30000, 50000, 100000, 300000, 500000};

    std::string algorithms[] = {
        "selection-sort",
        "insertion-sort",
        "bubble-sort",
        "heap-sort",
        "merge-sort",
        "quick-sort",
        "randomized-quick-sort"
        "counting-sort",
        "radix-sort",
        "flash-sort",
    };

    std::string orders[] = {
        "-rand",
        "-nsorted",
        "-sorted",
        "-rev"
    };

    for (int size : sizes) {
        int* a = new int[size];
        ofstream fout_rand("tests/inp/input_" + std::to_string(size) + "_rand.txt");
        GenerateData(a, size, 0);
        fout_rand << size << endl;
        for (int i = 0; i < size; i++) {
            fout_rand << a[i] << " ";
        }
        ofstream fout_nsorted("tests/inp/input_" + std::to_string(size) + "_nsorted.txt");
        GenerateData(a, size, 3);
        fout_nsorted << size << endl;
        for (int i = 0; i < size; i++) {
            fout_nsorted << a[i] << " ";
        }
        ofstream fout_sorted("tests/inp/input_" + std::to_string(size) + "_sorted.txt");
        GenerateData(a, size, 1);
        fout_sorted << size << endl;
        for (int i = 0; i < size; i++) {
            fout_sorted << a[i] << " ";
        }
        ofstream fout_rev("tests/inp/input_" + std::to_string(size) + "_rev.txt");
        GenerateData(a, size, 2);
        fout_rev << size << endl;
        for (int i = 0; i < size; i++) {
            fout_rev << a[i] << " ";
        }
        delete[] a;
    }

    for (int size : sizes) {
        for (std::string order : orders) {
            for (std::string algorithm : algorithms) {
                std::string cmd = "./Sort -a " + algorithm + " tests/inp/input_" + std::to_string(size) + "_" + order.substr(1) + ".txt -both >> tests/log/output_" + std::to_string(size) + "_" + order.substr(1) + ".txt";
                std::string newline = "echo >> tests/log/output_" + std::to_string(size) + "_" + order.substr(1) + ".txt";
                system(newline.c_str());
                system(cmd.c_str());
            }
        }
    }
    
    
}