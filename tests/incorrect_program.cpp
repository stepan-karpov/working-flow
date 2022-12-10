#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <utility>

const int MAX = 1e9 + 1;

struct Node {
  int value;
  int priority;
  int number_of_children;
  Node *left_child;
  Node *right_child;

  Node() : value(0), priority(rand()), number_of_children(0), left_child(nullptr), right_child(nullptr) {}
};

int NumberOfChildren(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->number_of_children;
}

std::pair<Node *, Node *> Split(Node *top, int value) {
  if (top == nullptr) {
    return std::pair<Node *, Node *>(top, nullptr);
  }
  if (value >= top->value) {
    std::pair<Node *, Node *> new_tops = Split(top->right_child, value);
    top->right_child = std::get<0>(new_tops);
    top->number_of_children = NumberOfChildren(top->left_child) + NumberOfChildren(top->right_child);
    if (top->left_child != nullptr) {
      ++top->number_of_children;
    }
    if (top->right_child != nullptr) {
      ++top->number_of_children;
    }
    return std::pair<Node *, Node *>(top, std::get<1>(new_tops));
  }
  std::pair<Node *, Node *> new_tops = Split(top->left_child, value);
  top->left_child = std::get<1>(new_tops);
  top->number_of_children = NumberOfChildren(top->left_child) + NumberOfChildren(top->right_child);
  if (top->left_child != nullptr) {
    ++top->number_of_children;
  }
  if (top->right_child != nullptr) {
    ++top->number_of_children;
  }
  return std::pair<Node *, Node *>(std::get<0>(new_tops), top);
}

Node *Merge(Node *first, Node *second) {
  if (second == nullptr) {
//    delete second;
    return first;
  }
  if (first == nullptr) {
//    delete first;
    return second;
  }
  if (first->priority > second->priority) {
    first->right_child = Merge(first->right_child, second);
    first->number_of_children = NumberOfChildren(first->left_child) + NumberOfChildren(first->right_child);
    if (first->left_child != nullptr) {
      ++first->number_of_children;
    }
    if (first->right_child != nullptr) {
      ++first->number_of_children;
    }
    return first;
  }
  second->left_child = Merge(first, second->left_child);
  second->number_of_children = NumberOfChildren(second->left_child) + NumberOfChildren(second->right_child);
  if (first->left_child != nullptr) {
    ++first->number_of_children;
  }
  if (first->right_child != nullptr) {
    ++first->number_of_children;
  }
  return second;
}

bool IsEmpty(Node *top) { return (top->right_child == nullptr && top->left_child == nullptr); }

bool Exists(Node *top, int x) {
  if (top == nullptr) {
    return false;
  }
  if (IsEmpty(top)) {
    return top->value == x;
  }
  if (top->value == x) {
    return true;
  }
  if (top->value > x) {
    return Exists(top->left_child, x);
  }
  return Exists(top->right_child, x);
}

void Insert(Node *&top, int x) {
  if (top == nullptr) {
    top = new Node;
    top->value = x;
    return;
  }
  if (!Exists(top, x)) {
    Node *new_node = new Node;
    new_node->value = x;
    std::pair<Node *, Node *> new_tops = Split(top, x);
    Node *first = std::get<0>(new_tops);
    Node *second = std::get<1>(new_tops);
    first = Merge(first, new_node);
    top = Merge(first, second);
  }
}

void Delete(Node *&top, int x) {
  if (Exists(top, x)) {
    std::pair<Node *, Node *> new_tops = Split(top, x - 1);
    Node *first = std::get<0>(new_tops);
    Node *second = std::get<1>(new_tops);
    new_tops = Split(second, x);
    top = Merge(first, std::get<1>(new_tops));
    delete std::get<0>(new_tops);
  }
}

int Next(Node *&top, int x) {
  if (top == nullptr) {
    return MAX;
  }
  if (top->value <= x) {
    return Next(top->right_child, x);
  }
  if (top->left_child == nullptr || top->left_child->value <= x) {
    return top->value;
  }
  return Next(top->left_child, x);
}

int Prev(Node *&top, int x) {
  if (top == nullptr) {
    return MAX;
  }
  if (top->value >= x) {
    return Prev(top->left_child, x);
  }
  if (top->right_child == nullptr || top->right_child->value >= x) {
    return top->value;
  }
  return Prev(top->right_child, x);
}

int Kth(Node *&top, int k) {
  if (k >= NumberOfChildren(top) + 1) {
    return MAX;
  }
  int left_children = NumberOfChildren(top->left_child);
  if (top->left_child != nullptr) {
    ++left_children;
  }
  int right_children = NumberOfChildren(top->right_child);
  if (top->right_child != nullptr) {
    ++right_children;
  }
  if (k == left_children) {
    return top->value;
  }
  if (k < left_children) {
    return Kth(top->left_child, k);
  }
  return Kth(top->right_child, k - left_children - 1);
}

void DeleteAll(Node *&top) {
  if (top->right_child == nullptr && top->left_child == nullptr) {
    delete top;
    return;
  }
  if (top->right_child == nullptr) {
    DeleteAll(top->left_child);
    delete top;
    return;
  }
  if (top->left_child == nullptr) {
    DeleteAll(top->right_child);
    delete top;
    return;
  }
  DeleteAll(top->right_child);
  DeleteAll(top->left_child);
  delete top;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
//  srand(time(nullptr));
  Node *top = nullptr;
  std::string input;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> input;
    int x;
    std::cin >> x;
    if (input == "insert") {
      Insert(top, x);
    } else if (input == "delete") {
      Delete(top, x);
    } else if (input == "exists") {
      bool ans = Exists(top, x);
      if (ans) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (input == "next") {
      int ans = Next(top, x);
      if (ans == MAX) {
        std::cout << "none\n";
      } else {
        std::cout << ans << "\n";
      }
    } else if (input == "prev") {
      int ans = Prev(top, x);
      if (ans == MAX) {
        std::cout << "none\n";
      } else {
        std::cout << ans << "\n";
      }
    } else if (input == "kth") {
      int ans = Kth(top, x);
      if (ans == MAX) {
        std::cout << "none\n";
      } else {
        std::cout << ans << "\n";
      }
    }
  }
  DeleteAll(top);
//  delete top;
  return 0;
}