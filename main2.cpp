#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct MyStruct {
  int x = 123;
  MyStruct() {
    std::cout << "construct\n";
  }
  MyStruct(const MyStruct& init) {
    std::cout << "copy construct\n";
  }
  MyStruct(MyStruct&& init) {
    std::cout << "rvalue construct\n";
  }
  MyStruct& operator=(MyStruct&& init) {
    std::cout << "rvalue operator=\n";
    return *this;
  }
  MyStruct& operator=(const MyStruct& init) {
    std::cout << "operator=\n";
    return *this;
  }
  
};

void Foo(const MyStruct& obj) {
  std::cout << "lvalue Foo\n";
}

void Foo(const MyStruct&& obj) {
  std::cout << "rvalue Foo\n";
}
template <typename T>
void Foo2(T x) {
  std::cout << "is lvalue?: " << std::is_lvalue_reference<T>{} << "\n";
}

template <typename T>
void Foo3(T&& x) {
  std::cout << "is lvalue?: " << std::is_lvalue_reference<T>{} << "\n";
}

int main() {
  Init();

  MyStruct f;

  Foo(f);
  Foo(std::move(f));
  
  Foo2<MyStruct&>(f);
  Foo2<MyStruct&&>(std::move(f));

  Foo3<MyStruct>(f);
  Foo3<MyStruct>(std::move(f));

  // MyStruct f;

  // MyStruct d = std::move(f);

  // // v.push_back(d);
  // v.push_back(std::move(d));

  // d.x = 123;

  return 0;
}