#include <iostream>
#include <set>

int main() {
    // initialization
    int n;
    std::cin >> n;
    long long* array = new long long[n + 1];
    array[0] = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> array[i];
        array[i] += array[i - 1];
    }
    // finding the result
    std::set<long long> s;
    s.insert(0);
    long long result = 0;
    for (int i = 0, j = 1; j <= n; ++j) {
        while (s.find(array[j]) != s.end()) {
            s.erase(array[i]);
            ++i;
        }
        s.insert(array[j]);
        result += (j - i);
    }
    std::cout << (static_cast<long long>(n) * (static_cast<long long>(n) + 1) / 2LL) - result;
    // freeing up memory
    delete[] array;
}
