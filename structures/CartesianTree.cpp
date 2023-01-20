#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct CartesianTree {
  struct Node {
    int value = -1;
    int priority = -1;
    long long sum = 0;
    int size = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int value) : value(value), priority(rand() % 10000), sum(value) {}
    Node(int value, int priority)
        : value(value), priority(priority), sum(value) {}
  };

  Node* root = nullptr;
  static const int kNoValue = -1e9;

  void Recalc(Node* root) {
    if (root == nullptr) {
      return;
    }
    root->sum = root->value;
    root->size = 1;
    if (root->left != nullptr) {
      root->sum += root->left->sum;
      root->size += root->left->size;
    }
    if (root->right != nullptr) {
      root->sum += root->right->sum;
      root->size += root->right->size;
    }
  }

  auto Split(Node* root, int key) -> std::pair<Node*, Node*> {
    if (root == nullptr) {
      return {nullptr, nullptr};
    }
    if (root->value < key) {
      auto[left, right] = Split(root->right, key);  // NOLINT
      root->right = left;
      Recalc(root);
      return {root, right};
    }
    auto[left, right] = Split(root->left, key);  // NOLINT
    root->left = right;
    Recalc(root);
    return {left, root};
  }

  auto Merge(Node* left, Node* right) -> Node* {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->priority > right->priority) {
      left->right = Merge(left->right, right);
      Recalc(left);
      return left;
    }
    right->left = Merge(left, right->left);
    Recalc(right);
    return right;
  }

  int GetMin(Node* root) {
    if (root == nullptr) {
      return kNoValue;
    }
    if (root != nullptr && root->left == nullptr) {
      return root->value;
    }
    return GetMin(root->left);
  }

  int GetMax(Node* root) {
    if (root == nullptr) {
      return kNoValue;
    }
    if (root != nullptr && root->right == nullptr) {
      return root->value;
    }
    return GetMax(root->right);
  }

  void Add(int value) {
    if (Contains(value)) {
      return;
    }
    Node* to_add = new Node(value);
    auto[left, right] = Split(root, value);  // NOLINT
    root = Merge(left, Merge(to_add, right));
  }

  // returns first value in a tree which is:
  // >= value if reverse_order = false
  // <= value if reverse_order = true
  int LowerBound(int value, bool reverse_order = false) {
    if (!reverse_order) {
      auto[left, right] = Split(root, value);  // NOLINT
      int ans = GetMin(right);
      root = Merge(left, right);
      return ans;
    }
    auto[left, right] = Split(root, value + 1);  // NOLINT
    int ans = GetMax(left);
    root = Merge(left, right);
    return ans;
  }

  // returns first value in a tree which is:
  // > value if reverse_order = false
  // < value if reverse_order = true
  int UpperBound(int value, bool reverse_order = false) {
    if (!reverse_order) {
      auto[left, right] = Split(root, value + 1);  // NOLINT
      int ans = GetMin(right);
      root = Merge(left, right);
      return ans;
    }
    auto[left, right] = Split(root, value);  // NOLINT
    int ans = GetMax(left);
    root = Merge(left, right);
    return ans;
  }

  void Remove(int value) {
    auto[left, temp_right] = Split(root, value);         // NOLINT
    auto[middle, right] = Split(temp_right, value + 1);  // NOLINT
    root = Merge(left, right);
  }

  int KthStatistics(Node* root, int k) {
    if (k == 1 && root->left == nullptr) {
      return root->value;
    }
    int size_left = (root->left == nullptr ? 0 : root->left->size);
    if (k <= size_left) {
      return KthStatistics(root->left, k);
    }
    if (k == size_left + 1) {
      return root->value;
    }
    return KthStatistics(root->right, k - size_left - 1);
  }

  int KthStatistics(int k) {
    int size = 0;
    if (root != nullptr) {
      size = root->size;
    }
    if (!(0 < k && k <= size)) {
      return kNoValue;
    }
    return KthStatistics(root, k);
  }

  long long GetSum(int l, int r) {
    auto[less_l, more_eq_l] = Split(root, l);     // NOLINT
    auto[l_r, more_r] = Split(more_eq_l, r + 1);  // NOLINT
    long long ans = 0;
    if (l_r != nullptr) {
      ans = l_r->sum;
    }
    root = Merge(less_l, l_r);
    root = Merge(root, more_r);
    return ans;
  }

  bool Contains(Node* root, int value) {
    if (root == nullptr) {
      return false;
    }
    if (root->value == value) {
      return true;
    }
    if (root->value > value) {
      return Contains(root->left, value);
    }
    return Contains(root->right, value);
  }

  bool Contains(int value) { return Contains(root, value); }

  void ClearTree(Node* root) {
    if (root == nullptr) {
      return;
    }
    ClearTree(root->left);
    ClearTree(root->right);
    delete root;
  }

  ~CartesianTree() { ClearTree(root); }
};

int main() {
  Init();

  int n;
  std::cin >> n;

  CartesianTree a;

  for (int i = 0; i < n; ++i) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "+") {
      int value;
      std::cin >> value;
      a.Add(value);
    } else if (cmd == "?") {
      int value;
      std::cin >> value;
      if (a.Contains(value)) {
        std::cout << "YES\n"; 
      } else {
        std::cout << "NO\n";
      }
    } else if (cmd == "-") {
      int value;
      std::cin >> value;
      a.Remove(value);
    } else if (cmd == ">=") {
      int value;
      std::cin >> value;
      int ans = a.LowerBound(value);
      if (ans == -1000000000) {
        std::cout << "none\n";
      } else {
        std::cout << ans << '\n';
      }
    } else if (cmd == ">") {
      int value;
      std::cin >> value;
      int ans = a.UpperBound(value);
      if (ans == -1000000000) {
        std::cout << "none\n";
      } else {
        std::cout << ans << '\n';
      }
    } else if (cmd == "<=") {
      int value;
      std::cin >> value;
      int ans = a.LowerBound(value, true);
      if (ans == -1000000000) {
        std::cout << "none\n";
      } else {
        std::cout << ans << '\n';
      }
    } else if (cmd == "<") {
      int value;
      std::cin >> value;
      int ans = a.UpperBound(value, true);
      if (ans == -1000000000) {
        std::cout << "none\n";
      } else {
        std::cout << ans << '\n';
      }
    } else if (cmd == "*") {
      int l, r;
      std::cin >> l >> r;
      std::cout << a.GetSum(l, r) << '\n';
    } else if (cmd == "stat") {
      int value;
      std::cin >> value;
      std::cout << a.KthStatistics(value) << '\n';
    }
  }

  return 0;
}