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

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc < 2) return 1;

    string mode = argv[1];

    if (mode == "-a") {
        string algorithm = argv[2];

        if (argc == 5) {
            string inputFile = argv[3];
            int* a, n;

            ReadInput(inputFile, a, n);
            auto [runtime, comparisons] = Sort(a, n, algorithm);
            WriteOutput("output.txt", a, n);

            cout << "ALGORITHM MODE" << endl;
            cout << "Algorithm: " << algorithm << endl;
            cout << "Input file: " << inputFile << endl;
            cout << "Input size: " << n << endl;

            string param = argv[4];
            cout << "-------------------------" << endl;
            if (param == "-both") {
                cout << "Running time: " << runtime << " ms" << endl;
                cout << "Comparisions: " << comparisons << endl;
            }
            else if (param == "-time") {
                cout << "Running time: " << runtime << " ms" << endl;
            }
            else if (param == "-comp") {
                cout << "Comparisions: " << comparisons << endl;
            }
            delete[] a;
        }
        else if (argc == 6) {
            int n = stoi(argv[3]);
            int* a = new int[n];

            string gen = argv[4];

            if (gen == "-rand") {
                GenerateData(a, n, 0);
            }
            else if (gen == "-nsorted") {
                GenerateData(a, n, 3);
            }
            else if (gen == "-sorted") {
                GenerateData(a, n, 1);

            }
            else if (gen == "-rev") {
                GenerateData(a, n, 2);
            }

            WriteOutput("input.txt", a, n);
            auto [runtime, comparisons] = Sort(a, n, algorithm);
            WriteOutput("output.txt", a, n);

            cout << "ALGORITHM MODE" << endl;
            cout << "Algorithm: " << algorithm << endl;
            cout << "Input size: " << n << endl;
            cout << "Input order: " << gen << endl;

            string param = argv[5];
            cout << "-------------------------" << endl;
            if (param == "-both") {
                cout << "Running time: " << runtime << " ms" << endl;
                cout << "Comparisions: " << comparisons << endl;
            }
            else if (param == "-time") {
                cout << "Running time: " << runtime << " ms" << endl;
            }
            else if (param == "-comp") {
                cout << "Comparisions: " << comparisons << endl;
            }
            delete[] a;
        }
        else 
            return 1;
    }
    return 0;
}

