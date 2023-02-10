#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

std::list<int>::iterator getNext(std::list<int>& list, std::list<int>::iterator it) {
  ++it;
  if (it == list.end()) {
    it = list.begin();
  }
  return it;
} 

void output(std::list<int>& to_output) {
  auto it = to_output.begin();
  while (it != to_output.end()) {
    std::cout << *it << " ";
    ++it;
  }
  std::cout << "\n";
}

void fill(std::list<int>& to_fill, int start, int n) {
  auto it = to_fill.begin();
  
  for (int i = 0; i < start; ++i) {
    ++it;
  }

  int p = 0;

  for (int i = 0; i < n; ++i) {
    *it = p;
    it = getNext(to_fill, it);
    p += 2;
  }
}

std::list<int>::iterator getStart(std::list<int>& list) {
  auto it = list.begin();

  for (int i = 0; i < int(list.size()); ++i) {
    int current_value = *it;
    auto next_it = getNext(list, it);
    int next_value = *next_it;
    if (current_value > next_value) {
      return next_it;
    }
    it = next_it;
  }

  return list.begin();
}

void insertValue(std::list<int>& list, std::list<int>::iterator start,
                 int value) {
  auto it = start;
  for (int i = 0; i < (list.size()); ++i) {
    auto next = getNext(list, it);
    if (*it == value) {
      list.insert(next, value);
      return;
    }
    if (*it < value && value < *next) {
      list.insert(next, value);
      return;
    }
    it = next;
  }
  list.insert(it, value);
}

int main() {
  srand(time(NULL));
  Init();
  
  int n = 10;

  std::list<int> a;
  a.resize(n);

  fill(a, rand() % n, n);
  output(a);
  auto start = getStart(a);
  insertValue(a, start, 7);
  output(a);

  return 0;
}