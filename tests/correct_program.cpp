#include <iostream>
#include <vector>

const int kMod = 1e9;

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

class AVLTree {
 private:
  static const int kNoSon = 1e9;
  static const int kMin = -1e9;
  static const int kMax = 1e9;
  struct Node {
    int value = -1;
    int size = 1;
    int balance = 0;
    int max_value = kMin;
    int min_value = kMin;
    int left_son = kNoSon, right_son = kNoSon;
    Node(int value) : value(value), max_value(value), min_value(value) {}
  };

  std::vector<Node> tree_;

  void UpdateData(int x) {
    tree_[x].max_value = tree_[x].value;
    tree_[x].min_value = tree_[x].value;
    int size_l = 0;
    int size_r = 0;
    if (tree_[x].left_son != kNoSon) {
      tree_[x].max_value =
          std::max(tree_[x].max_value, tree_[tree_[x].left_son].max_value);
      tree_[x].min_value =
          std::min(tree_[x].min_value, tree_[tree_[x].left_son].min_value);
      size_l =
          (tree_[x].left_son == kNoSon ? 0 : tree_[tree_[x].left_son].size);
    }
    if (tree_[x].right_son != kNoSon) {
      tree_[x].max_value =
          std::max(tree_[x].max_value, tree_[tree_[x].right_son].max_value);
      tree_[x].min_value =
          std::min(tree_[x].min_value, tree_[tree_[x].right_son].min_value);
      size_r =
          (tree_[x].right_son == kNoSon ? 0 : tree_[tree_[x].right_son].size);
    }
    tree_[x].size = std::max(size_l, size_r) + 1;
    tree_[x].balance = size_l - size_r;
  }

  bool Contains(int x, int value) {
    if (x >= int(tree_.size())) {
      return false;
    }
    if (tree_[x].value == value) {
      return true;
    }
    if (value < tree_[x].value) {
      return Contains(tree_[x].left_son, value);
    }
    return Contains(tree_[x].right_son, value);
  }

  void SmallLeftRotation(int x) {
    int a = x;
    int b = tree_[x].right_son;
    int a_t = tree_[x].left_son;
    int b_t = tree_[b].left_son;
    int c_t = tree_[b].right_son;
    std::swap(tree_[a], tree_[b]);
    std::swap(a, b);
    tree_[a].left_son = a_t;
    tree_[a].right_son = b_t;
    tree_[b].left_son = a;
    tree_[b].right_son = c_t;
    UpdateData(a);
    UpdateData(b);
  }

  void SmallRightRotation(int x) {
    int a = x;
    int b = tree_[x].left_son;
    int a_t = tree_[b].left_son;
    int b_t = tree_[b].right_son;
    int c_t = tree_[x].right_son;
    std::swap(tree_[a], tree_[b]);
    std::swap(a, b);
    tree_[a].left_son = b_t;
    tree_[a].right_son = c_t;
    tree_[b].left_son = a_t;
    tree_[b].right_son = a;
    UpdateData(a);
    UpdateData(b);
  }

  void BigLeftRotation(int x) {
    SmallRightRotation(tree_[x].right_son);
    SmallLeftRotation(x);
  }

  void BigRightRotation(int x) {
    SmallLeftRotation(tree_[x].left_son);
    SmallRightRotation(x);
  }

  int Add(int x, int value) {
    if (x >= int(tree_.size())) {
      tree_.push_back(value);
      return int(tree_.size() - 1);
    }
    if (value < tree_[x].value) {
      tree_[x].left_son = Add(tree_[x].left_son, value);
    } else {
      tree_[x].right_son = Add(tree_[x].right_son, value);
    }
    UpdateData(x);
    if (tree_[x].balance == -2) {
      if (tree_[tree_[x].right_son].balance != 1) {
        SmallLeftRotation(x);
      } else {
        BigLeftRotation(x);
      }
    }
    if (tree_[x].balance == 2) {
      if (tree_[tree_[x].left_son].balance != -1) {
        SmallRightRotation(x);
      } else {
        BigRightRotation(x);
      }
    }
    return x;
  }

  int LowerBound(int x, int value) {
    if (x >= int(tree_.size())) {
      return -1;
    }
    int max_l =
        (tree_[x].left_son != kNoSon ? tree_[tree_[x].left_son].max_value
                                     : kMin);
    if (max_l >= value) {
      int ans = LowerBound(tree_[x].left_son, value);
      return (ans == -1 && tree_[x].value >= value ? tree_[x].value : ans);
    }
    if (tree_[x].value >= value) {
      return tree_[x].value;
    }
    int ans = LowerBound(tree_[x].right_son, value);
    return (ans == -1 && tree_[x].value >= value ? tree_[x].value : ans);
  }

 public:
  bool Contains(int value) { return Contains(0, value); }
  void Add(int value) {
    if (Contains(value)) {
      return;
    }
    Add(0, value);
  }
  int LowerBound(int value) {
    if (int(tree_.size()) == 0) {
      return -1;
    }
    if (tree_[0].max_value < value) {
      return -1;
    }
    return LowerBound(0, value);
  }
};

int main() {
  Init();
  int n;
  std::cin >> n;

  AVLTree tree;

  int y = 0;
  for (int i = 0; i < n; ++i) {
    std::string cmd;
    std::cin >> cmd;
    int value;
    std::cin >> value;
    if (cmd == "+") {
      tree.Add((value + y) % kMod);
      y = 0;
    } else if (cmd == ">") {
      if (tree.Contains(value)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    } else {
      y = tree.LowerBound(value);
      std::cout << y << '\n';
    }
  }
  return 0;
}