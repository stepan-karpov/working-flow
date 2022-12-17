#include <iostream>

typedef const int* ptr_to_const_int;

void foo(int** const ptr) {
  std::cout << "f";
}

int main() {
    int ** v = new int * [10];
    foo(v);

    return 0;
}