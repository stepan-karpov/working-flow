#include <iostream>
#include <random>
#include <chrono>

int BinarySearch(int s, int* arr, int begin, int end) {
    if (s < arr[(begin + end) / 2]) {
        end = (begin + end) / 2;
        BinarySearch(s, arr, begin, end);
    }

    if (s > arr[(begin + end) / 2]) {
        begin = (begin + end) / 2;
        BinarySearch(s, arr, begin, end);
    }

    if (s == arr[(begin + end) / 2]) {
        return 0;
    }
}

void FillWithRandomValues(int n, int* arr) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1'000'000 + 1; // random value from [1, 1e6]
    }
}

void QuickSort(int n, int* arr) {
    if (n <= 1) {
        return;
    }
    int pivot = arr[0];

    int* less = new int[n];
    int* more = new int[n];
    int equals = 0;
    int p1 = 0, p2 = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] == pivot) {
            ++equals;
        } else if (arr[i] < pivot) {
            less[p1] = arr[i];
            ++p1;
        } else {
            more[p2] = arr[i];
            ++p2;
        }
    }

    // for (int i = 0; i < p1; ++i) {
    //     std::cout << less[i] << " ";
    // }
    // std::cout << "\n\n";
    // for (int i = 0; i < p2; ++i) {
    //     std::cout << more[i] << " ";
    // }
    // std::cout << "\n\n";

    // QuickSort(p1, less);
    // QuickSort(p2, more);

    int cur_p = 0;

    for (int i = 0; i < p1; ++i) {
        arr[cur_p] = less[i];
        ++cur_p;
    }
    for (int i = 0; i < equals; ++i) {
        arr[cur_p] = pivot;
        ++cur_p;
    }
    for (int i = 0; i < p2; ++i) {
        arr[cur_p] = more[i];
        ++cur_p;
    }
}

int main() {
    srand(time(NULL));
    int n;
    std::cin >> n;
    int s;
    int* arr = new int[10];
    FillWithRandomValues(10, arr);
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\n\n\n\n\n";
    QuickSort(10, arr);
    std::cout << "ok\n";
    std::cout << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    // s = BinarySearch(n, arr, 0, 9);
    // std::cout << s;
}