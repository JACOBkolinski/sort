// for testing the sorting algorithms and generating input/output files only, not for command line usage

#include "Sort.cpp"
#include <fstream>
#include <algorithm>
#include <string>

int main() {
    int sizes[] = {500000};

    std::string algorithms[] = {
        "selection-sort",
        "insertion-sort",
        "bubble-sort",
        "binary-insertion-sort",
        "shaker-sort",
        "shell-sort",
        "heap-sort",
        "merge-sort",
        "quick-sort",
        "randomized-quick-sort",
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

    for (auto& size : sizes) {
        for (auto& order : orders) {

            std::string input_path =
                "tests/inp/input_" + std::to_string(size) + "_" + order.substr(1) + ".txt";

            std::string output_path =
                "tests/out/output_" + std::to_string(size) + "_" + order.substr(1) + ".txt";

            std::ofstream input_file(input_path);
            std::ofstream output_file(output_path);

            int* original = new int[size];

            if (order == "-rand") {
                GenerateData(original, size, 0);
            }
            else if (order == "-sorted") {
                GenerateData(original, size, 1);
            }
            else if (order == "-rev") {
                GenerateData(original, size, 2);
            }
            else if (order == "-nsorted") {
                GenerateData(original, size, 3);
            }

            input_file << size << '\n';
            for (int i = 0; i < size; i++) {
                input_file << original[i] << ' ';
            }
            input_file << '\n';

            for (auto& algorithm : algorithms) {

                int* a = new int[size];
                std::copy(original, original + size, a);

                auto result = Sort(a, size, algorithm);
                auto runtime = result.first;
                auto comparisons = result.second;

                output_file << "ALGORITHM MODE\n";
                output_file << "Algorithm: " << algorithm << '\n';
                output_file << "Input file: " << input_path << '\n';
                output_file << "-------------------------\n";
                output_file << "Running time: " << runtime << " ms\n";
                output_file << "Comparisions: " << comparisons << "\n\n";

                delete[] a;
            }

            delete[] original;
        }
    }

    return 0;
}