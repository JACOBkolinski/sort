#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <chrono>

#include "DataGenerator.hpp"
#include "RandomGenerator.hpp"

long long int Heapify(int a[], int n, int root) {
    long long int count = 0;

    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < n) {
            count++;
            if (a[left] > a[largest])
                largest = left;
        }
        if (right < n) {
            count++;
            if (a[right] > a[largest])
                largest = right;
        }

        if (largest == root) break;

        HoanVi(a[root], a[largest]);
        root = largest;
    }
    return count;
}

long long int Merge(int a[], int l, int mid, int r) {
    long long int count = 0;

    int n1 = mid - l + 1;
    int n2 = r - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
        
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        count++;             
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    delete[] L;
    delete[] R;

    return count;
}

//lttung@fit.hcmus.edu.vn
long long int SelectionSort(int a[], int n) {
    long long int count = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            count++;
            if (a[j] < a[min]) 
                min = j;
        }
        if (min != i) 
            HoanVi(a[i], a[min]);
    }
    return count;
}

//lttung@fit.hcmus.edu.vn
long long int InsertionSort(int a[], int n) {
    long long int count = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while(j >= 0) {
            count++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                j--;
            } 
            else break;
        }
        a[j + 1] = key;
    }
    return count;
}

//lttung@fit.hcmus.edu.vn
long long int BubbleSort(int a[], int n) {
    long long int count = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            count++;
            if (a[j] > a[j + 1]) {
                HoanVi(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return count;
}

//lttung@fit.hcmus.edu.vn
long long int BinaryInsertionSort(int a[], int n) {
    long long int count = 0;
    for (int i = 1; i < n; i++) {
        int l = 0, r = i - 1, pos = i, key = a[i];
        while (l <= r) {
            int mid = (l + r) / 2;
            count++;
            if (a[mid] > key) {
                pos = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        int j = i - 1;
        while (j >= pos) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    return count;
}

//lttung@fit.hcmus.edu.vn
long long int ShakerSort(int a[], int n) {
    long long int count = 0;
    int left = 0;
    int right = n - 1;

    while (left < right) {
        bool swapped = false;
        for (int i = left; i < right; i++) {
            count++;
            if (a[i] > a[i + 1]) {
                HoanVi(a[i], a[i + 1]);
                swapped = true;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            count++;
            if (a[i] < a[i - 1]) {
                HoanVi(a[i], a[i - 1]);
                swapped = true;
            }
        }
        left++;
        if (!swapped) break;
    }
    return count;
}

//https://www.geeksforgeeks.org/dsa/quick-sort/
long long QuickSort(int a[], int l, int r) {
    long long count = 0;

    int pivot = a[(l + r) / 2];
    int i = l, j = r;

    while (i <= j) {
        while (a[i] < pivot) {
            count++;
            i++;
        }

        while (a[j] > pivot) {
            count++;
            j--;
        }

        if (i <= j) {
            HoanVi(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (l < j) count += QuickSort(a, l, j);
    if (i < r) count += QuickSort(a, i, r);

    return count;
}

//https://viblo.asia/p/thuat-toan-sap-xep-nhanh-quick-sort-eW65G6ROlDO
long long int RandomizedQuickSort(int a[], int l, int r) {
    long long int count = 0;
    int pivot = a[pcg32_boundedrand(r - l + 1) + l];
    int i = l, j = r;

    while (i <= j) {
        while (a[i] < pivot) {
            count++;
            i++;
        }

        while (a[j] > pivot) {
            count++;
            j--;
        }

        if (i <= j) {
            HoanVi(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (i < r) count += RandomizedQuickSort(a, i, r);
    if (l < j) count += RandomizedQuickSort(a, l, j);
    return count;
}

//https://www.geeksforgeeks.org/dsa/shell-sort/
long long int ShellSort(int a[], int n) {
    long long int count = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j = i;
            while (j >= gap) {
                count++;
                if (a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    j -= gap;
                }
                else break;
            }
            a[j] = temp;
        }
    }
    return count;
}

//https://www.geeksforgeeks.org/dsa/heap-sort/
long long int HeapSort(int a[], int n) {
    long long int count = 0;

    for (int start = n / 2 - 1; start >= 0; start--) {
        count += Heapify(a, n, start);
    }

    for (int end = n - 1; end > 0; end--) {
        HoanVi(a[0], a[end]);
        count += Heapify(a, end, 0);
    }
    return count;
}

//https://www.geeksforgeeks.org/dsa/merge-sort/
long long int MergeSort(int a[], int l, int r) {
    long long int count = 0;

    if (l < r) {
        int mid = (l + r) / 2;

        count += MergeSort(a, l, mid);
        count += MergeSort(a, mid + 1, r);

        count += Merge(a, l, mid, r);
    }

    return count;
}

//https://www.geeksforgeeks.org/dsa/counting-sort/
long long int CountingSort(int a[], int n) {
    long long int count = 0;
    if (n <= 0) return count;

    int minVal = a[0], maxVal = a[0];
    for (int i = 1; i < n; i++) {
        count++;             
        if (a[i] < minVal) {
            minVal = a[i];
        } else {
            count++;             
            if (a[i] > maxVal)
                maxVal = a[i];
        }
    }

    int range = maxVal - minVal + 1;
    int* cnt = new int[range]();
    int* output = new int[n];

    for (int i = 0; i < n; i++)
        cnt[a[i] - minVal]++;

    for (int i = 1; i < range; i++)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[cnt[a[i] - minVal] - 1] = a[i];
        cnt[a[i] - minVal]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];

    delete[] cnt;
    delete[] output;

    return count;
}

//https://www.geeksforgeeks.org/dsa/radix-sort/
long long int RadixSort(int a[], int n) {
    long long int count = 0;
    if (n <= 0) return count;

    int maxVal = a[0];
    for (int i = 1; i < n; i++) {
        count++;               
        if (a[i] > maxVal)
            maxVal = a[i];
    }

    int* output = new int[n];

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int cnt[10] = {0};

        for (int i = 0; i < n; i++)
            cnt[(a[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            cnt[i] += cnt[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int digit = (a[i] / exp) % 10;
            output[cnt[digit] - 1] = a[i];
            cnt[digit]--;
        }

        for (int i = 0; i < n; i++)
            a[i] = output[i];
    }

    delete[] output;
    return count;
}

//https://neubert.net/FSOIntro.html
long long int FlashSort(int a[], int n) {
    long long int count = 0;
    if (n <= 1) return count;

    int m = (int)(0.43 * n);
    if (m <= 2) m = 2;

    int* L = new int[m]();

    int minVal = a[0];
    int maxIndex = 0;

    for (int i = 1; i < n; i++) {
        count++;
        if (a[i] < minVal) {
            minVal = a[i];
        } else {
            count++;
            if (a[i] > a[maxIndex])
                maxIndex = i;
        }
    }

    if (a[maxIndex] == minVal) {
        delete[] L;
        return count;
    }

    double c = (double)(m - 1) / (a[maxIndex] - minVal);

    for (int i = 0; i < n; i++) {
        int k = (int)(c * (a[i] - minVal));
        L[k]++;
    }

    for (int i = 1; i < m; i++)
        L[i] += L[i - 1];

    HoanVi(a[maxIndex], a[0]);

    int move = 0, j = 0, k = m - 1;
    int flash;

    while (move < n - 1) {
        while (j > L[k] - 1) {
            j++;
            k = (int)(c * (a[j] - minVal));
        }

        flash = a[j];

        while (j != L[k]) {
            k = (int)(c * (flash - minVal));
            int temp = a[L[k] - 1];
            a[L[k] - 1] = flash;
            flash = temp;
            L[k]--;
            move++;
        }
    }

    delete[] L;

    count += InsertionSort(a, n);

    return count;
}

pair<double, long long int> Sort(int a[], int n, string algorithm) {
    long long int comparisons = 0;

    auto start = chrono::high_resolution_clock::now();

    if (algorithm == "selection-sort") comparisons = SelectionSort(a, n);
    else if (algorithm == "insertion-sort") comparisons = InsertionSort(a, n);
    else if (algorithm == "bubble-sort") comparisons = BubbleSort(a, n);
    else if (algorithm == "binary-insertion-sort") comparisons = BinaryInsertionSort(a, n);
    else if (algorithm == "shaker-sort") comparisons = ShakerSort(a, n);
    else if (algorithm == "quick-sort") comparisons = QuickSort(a, 0, n - 1);
    else if (algorithm == "randomized-quick-sort") {
        pcg32_srandom((uint64_t)time(NULL), (uint64_t)&pcg32_global);
        comparisons = RandomizedQuickSort(a, 0, n - 1);
    }
    else if (algorithm == "shell-sort") comparisons = ShellSort(a, n);
    else if (algorithm == "heap-sort") comparisons = HeapSort(a, n);
    else if (algorithm == "merge-sort") comparisons = MergeSort(a, 0, n - 1);
    else if (algorithm == "counting-sort") comparisons = CountingSort(a, n);
    else if (algorithm == "radix-sort") comparisons = RadixSort(a, n);
    else if (algorithm == "flash-sort") comparisons = FlashSort(a, n);

    auto end = chrono::high_resolution_clock::now();

    double runtime = chrono::duration<double, milli>(end - start).count();

    return {runtime, comparisons};
}

void ReadInput(const string& filename, int*& a, int& n) {
    ifstream fin(filename);
    
    fin >> n;
    a = new int[n];
    for (int i = 0; i < n; i++)
        fin >> a[i];
    
    fin.close();
}
void WriteOutput(const string& filename, int a[], int n) {
    ofstream fout(filename);

    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << a[i] << " ";

    fout.close();
}

void WriteInput(const string& filename, int a[], int n) {
    ofstream fout(filename);

    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << a[i] << " ";

    fout.close();
}

using namespace std;

int getDataType(const string& order) {
    if (order == "-sorted") return 1;
    if (order == "-nsorted") return 3;
    if (order == "-rev") return 2;
    if (order == "-rand") return 0;
    return -1;
}

void printOutput(double time, long long int comps, const string& outputParam) {
    if (outputParam == "-time") {
        cout << "Running time: " << time << " ms" << endl;
    } else if (outputParam == "-comp") {
        cout << "Comparisions: " << comps << endl;
    } else if (outputParam == "-both") {
        cout << "Running time: " << time << " ms" << endl;
        cout << "Comparisions: " << comps << endl;
    }
}

void command1(const string& algorithm, const string& inputFile, const string& outputParam) {
    int* a = nullptr;
    int n = 0;
    ReadInput(inputFile, a, n);

    int* b = new int[n];
    for (int i = 0; i < n; i++) b[i] = a[i];

    auto result = Sort(b, n, algorithm);

    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << algorithm << "\n";
    cout << "Input file: " << inputFile << "\n";
    cout << "Input size: " << n << "\n";
    cout << "-------------------------\n";
    printOutput(result.first, result.second, outputParam);

    WriteOutput("output.txt", b, n);

    delete[] a;
    delete[] b;
}

void command2(const string& algorithm, int size, const string& order, const string& outputParam) {
    int* a = new int[size];
    int dataType = getDataType(order);
    GenerateData(a, size, dataType);

    WriteInput("input.txt", a, size);

    int* b = new int[size];
    for (int i = 0; i < size; i++) b[i] = a[i];

    auto result = Sort(b, size, algorithm);

    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << algorithm << "\n";
    cout << "Input size: " << size << "\n";
    cout << "Input order: " << order << "\n";
    cout << "-------------------------\n";
    printOutput(result.first, result.second, outputParam);

    WriteOutput("output.txt", b, size);

    delete[] a;
    delete[] b;
}

void command3(const string& algorithm, int size, const string& outputParam) {
    string inputFiles[] = {"input_1.txt", "input_2.txt", "input_3.txt", "input_4.txt"};
    int dataTypes[] = {0, 3, 1, 2}; 

    for (int i = 0; i < 4; i++) {
        int* a = new int[size];
        GenerateData(a, size, dataTypes[i]);
        WriteInput(inputFiles[i], a, size);
        delete[] a;
    }

    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << algorithm << "\n";
    cout << "Input size: " << size << "\n";
    cout << "\n";

    for (int i = 0; i < 4; i++) {
        int* a = nullptr;
        int n = 0;
        ReadInput(inputFiles[i], a, n);

        int* b = new int[n];
        for (int j = 0; j < n; j++) b[j] = a[j];

        auto result = Sort(b, n, algorithm);


        if (i == 0) cout << "Input order: -rand" << endl;
        else if (i == 1) cout << "Input order: -nsorted" << endl;
        else if (i == 2) cout << "Input order: -sorted" << endl;
        else if (i == 3) cout << "Input order: -rev" << endl;
        cout << "-------------------------\n";

        printOutput(result.first, result.second, outputParam);
        cout << endl;

        delete[] a;
        delete[] b;
    }
}

void command4(const string& algorithm1, const string& algorithm2, const string& inputFile) {
    int* a = nullptr;
    int n = 0;
    ReadInput(inputFile, a, n);

    int* b1 = new int[n];
    for (int i = 0; i < n; i++) b1[i] = a[i];
    auto result1 = Sort(b1, n, algorithm1);

    int* b2 = new int[n];
    for (int i = 0; i < n; i++) b2[i] = a[i];
    auto result2 = Sort(b2, n, algorithm2);

    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Input size: " << n << endl;
    cout << "-------------------------\n";
    cout << "Running time: " << result1.first << " ms | " << result2.first << " ms" << endl;
    cout << "Comparisions: " << result1.second << " | " << result2.second << endl;

    delete[] a;
    delete[] b1;
    delete[] b2;
}

void command5(const string& algorithm1, const string& algorithm2, int size, const string& order) {
    int* a = new int[size];
    int dataType = getDataType(order);
    GenerateData(a, size, dataType);

    WriteInput("input.txt", a, size);

    int* b1 = new int[size];
    for (int i = 0; i < size; i++) b1[i] = a[i];
    auto result1 = Sort(b1, size, algorithm1);

    int* b2 = new int[size];
    for (int i = 0; i < size; i++) b2[i] = a[i];
    auto result2 = Sort(b2, size, algorithm2);

    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << endl;
    cout << "Input size: " << size << endl;
    cout << "Input order: ";
    if (order == "-rand") cout << "Random" << endl;
    else if (order == "-sorted") cout << "Sorted" << endl;
    else if (order == "-nsorted") cout << "Nearly Sorted" << endl;
    else if (order == "-rev") cout << "Reversed" << endl;
    cout << "-------------------------\n";
    cout << "Running time: " << result1.first << " ms | " << result2.first << " ms" << endl;
    cout << "Comparisons: " << result1.second << " | " << result2.second << endl;

    delete[] a;
    delete[] b1;
    delete[] b2;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cout << "USAGE:\n";
        cout << "    " << argv[0] << " -a Algorithm Input_file Output_parameter" << endl;
        cout << "    " << argv[0] << " -a Algorithm Input_size Input_order Output_parameter" << endl;
        cout << "    " << argv[0] << " -a Algorithm Input_size Output_parameter" << endl;
        cout << "    " << argv[0] << " -c Algorithm_1 Algorithm_2 Input_file" << endl;
        cout << "    " << argv[0] << " -c Algorithm_1 Algorithm_2 Input_size Input_order" << endl;
        cout << "OPTION:\n";
        cout << "    -mode               -a algorithm mode, -c comparison mode\n";
        cout << "    Algorithm           selection - sort, insertion - sort,...\n";
        cout << "    Input_file          path to user - provided data, with format :\n";
        cout << "                        1 st line: integer n (number of elements)\n";
        cout << "                        2 nd line: n integers, separated by a single space\n";
        cout << "    Input_size          generated data with specified size, Integer (<= 1,000,000)\n";
        cout << "    Input_order         generated data with order : -sorted, -nsorted, -rev, -rand\n";
        cout << "    Output_parameter    -time or -comp or -both\n";
        return 0;
    }

    string mode = argv[1];

    if (mode == "-a") {
        string algorithm = argv[2];
        string next = argv[3];

        if (next.find('.') != string::npos || next.find('/') != string::npos) {
            string inputFile = next;
            string outputParam = argv[4];
            command1(algorithm, inputFile, outputParam);
        } else {
            int size = stoi(next);
            string next2 = argv[4];

            if (next2 == "-sorted" || next2 == "-nsorted" || next2 == "-rev" || next2 == "-rand") {
                string order = next2;
                string outputParam = argv[5];
                command2(algorithm, size, order, outputParam);
            } else {
                string outputParam = next2;
                command3(algorithm, size, outputParam);
            }
        }
    } else if (mode == "-c") {
        string algorithm1 = argv[2];
        string algorithm2 = argv[3];
        string next = argv[4];

        if (next.find('.') != string::npos || next.find('/') != string::npos) {
            string inputFile = next;
            command4(algorithm1, algorithm2, inputFile);
        } else {
            int size = stoi(next);
            string order = argv[5];
            command5(algorithm1, algorithm2, size, order);
        }
    }

    return 0;
}

