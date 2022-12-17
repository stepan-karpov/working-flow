#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

class DescartesTreeByImplicitKey {
 private:
  struct Node {
    int value;
    int priority;
    int size = 1;
    int min_value = 1e9;
    int max_value = -1e9;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int value) :
         value(value), priority(rand() % 1000), min_value(value), max_value(value) {}
  };

  Node* root = nullptr;
  static const int kNoValue = -1e9;

  void Recalc(Node* root) {
    if (root == nullptr) {
      return;
    }
    root->size = 1;
    root->min_value = root->value;
    root->max_value = root->value;
    if (root->left != nullptr) {
      root->size += root->left->size;
      root->max_value = std::max(root->max_value, root->left->max_value);
      root->min_value = std::min(root->min_value, root->left->min_value);
    }
    if (root->right != nullptr) {
      root->size += root->right->size;
      root->max_value = std::max(root->max_value, root->right->max_value);
      root->min_value = std::min(root->min_value, root->right->min_value);
    }
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

  // returns std::pair = left, right
  // where all indexes in left < index
  //       all indexes in right >= index
  auto Split(Node* root, int index) -> std::pair<Node*, Node*> {
    if (root == nullptr) {
      return {nullptr, nullptr};
    }
    int size_left = (root->left == nullptr ? 0 : root->left->size);
    if (index < size_left) {
      auto[left, right] = Split(root->left, index);
      root->left = right;
      Recalc(root);
      return {left, root};
    } else if (index == size_left) {
      Node* left = root->left;
      root->left = nullptr;
      Recalc(root);
      return {left, root};
    }
    auto[left, right] = Split(root->right, index - size_left - 1);
    root->right = left;
    Recalc(root);
    return {root, right};
  }

  void ClearTree(Node* root) {
    if (root == nullptr) {
      return;
    }
    ClearTree(root->left);
    ClearTree(root->right);
    delete root;
  }

  // returns a[i] (in 0-numeration)
  int GetKth(Node* root, int index) {
    if (root->left == nullptr && index == 0) {
      return root->value;
    }
    int size_left = (root->left == 0 ? 0 : root->left->size);
    if (index < size_left) {
      return GetKth(root->left, index);
    }
    if (index == size_left) {
      return root->value;
    }
    return GetKth(root->right, index - size_left - 1);
  }

  int CountLessOrEqualThanX(Node* root, int x) {
    if (root == nullptr) {
      return 0;
    }
    if (root->max_value <= x) {
      return root->size;
    }
    if (root->min_value > x) {
      return 0;
    }
    int ans1 = CountLessOrEqualThanX(root->left, x);
    int ans2 = CountLessOrEqualThanX(root->right, x);
    return ans1 + ans2 + (root->value <= x);
  }

 public:

  // returns Size() of array
  int Size() {
    return (root == nullptr ? 0 : root->size);
  }

  // simple push_back
  void PushBack(int value) {
    Node* to_add = new Node(value);
    root = Merge(root, to_add);
  }

  // returns a[i] (in 0-numeration)
  int Get(int index) {
    if (!(0 <= index && index < this->Size())) {
      return kNoValue;
    }
    return GetKth(root, index);
  }

  // a[index] = value
  void Set(Node* root, int index, int value) {
    if (index < 0) {
      return;
    }
    if (root->left == nullptr && index == 0) {
      root->value = value;
      Recalc(root);
    }
    int size_left = (root->left == 0 ? 0 : root->left->size);
    if (index < size_left) {
      Set(root->left, index, value);
    }
    if (index == size_left) {
      root->value = value;
      Recalc(root);
    }
    Set(root->right, index - size_left - 1, value);
    Recalc(root);
  }

  // a[index] = value
  void Set(int index, int value) {
    if (!(0 <= index && index < this->Size())) {
      // assert("Segmentation fault");
      std::cout << "seg fault\n"; 
      return;
    }
    Set(root, index, value);
  }

  // swaps [l1, r1] with [l2, r2]
  void SwapSegments(int l1, int r1, int l2, int r2) {
    auto[less_l1, more_eq_l1] = Split(root, l1);
    auto[l1_r1, more_r1] = Split(more_eq_l1, r1 - l1 + 1);
    auto[r1_l2, more_eq_l2] = Split(more_r1, l2 - r1 - 1);
    auto[l2_r2, more_r2] = Split(more_eq_l2, r2 - l2 + 1);
    root = Merge(less_l1, l2_r2);
    root = Merge(root, r1_l2);
    root = Merge(root, l1_r1);
    root = Merge(root, more_r2);
  }
  
  // pastes element "value" after index
  // in tree
  // index should be among [-1, a.size() - 1]
  void AddAfter(int index, int value) {
    if (!(-1 <= index && index < this->Size())) {
      std::cout << "seg fault\n";
      return;
    }
    auto[left, right] = Split(root, index + 1);
    Node* to_add = new Node(value);
    root = Merge(left, Merge(to_add, right));
  }

  // deletes a[index] from array
  void DeleteElement(int index) {
    if (!(-1 <= index && index < this->Size())) {
      std::cout << "seg fault\n";
      return;
    }
    if (index == 0) {
      auto[left, right] = Split(root, index + 1); // NOLINT
      delete left;
      root = right;
      return;      
    } else if (index == this->Size() - 1) {
      auto[left, right] = Split(root, index); // NOLINT
      root = left;
      delete right;
      return;
    }
    auto[left, right] = Split(root, index); // NOLINT
    auto[to_delete, new_right] = Split(right, 1); // NOLINT
    delete to_delete;
    root = Merge(left, new_right);
  }

  // return number of elements that are <= x
  // search is across all element is segment[l, r]
  int LessEqualXOnSegment(int l, int r, int x) {
    auto[less_l, more_eq_l] = Split(root, l);
    auto[l_r, more_r] = Split(more_eq_l, r - l + 1);
    int ans = CountLessOrEqualThanX(l_r, x);
    root = Merge(less_l, l_r);
    root = Merge(root, more_r);
    return ans;
  }

  ~DescartesTreeByImplicitKey() { ClearTree(root); }
};

int main() {
  Init();
  int n, p;
  std::cin >> n >> p;

  DescartesTreeByImplicitKey a;

  long long answer = 0;

  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    a.PushBack(x);
    answer += x * x;
  }

  int q;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    std::cout << answer << '\n';
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "1") {
      int to_fire;
      std::cin >> to_fire;
      --to_fire;
      int cur_length = a.Get(to_fire);
      if (to_fire == 0) {
        answer -= cur_length * cur_length;
        answer -= a.Get(1) * a.Get(1); 
        a.Set(1, a.Get(1) + cur_length);
        answer += a.Get(1) * a.Get(1); 
      } else if (to_fire == a.Size() - 1) {
        answer -= cur_length * cur_length;
        answer -= a.Get(a.Size() - 2) * a.Get(a.Size() - 2); 
        a.Set(a.Size() - 2, a.Get(a.Size() - 2) + cur_length);
        answer += a.Get(a.Size() - 2) * a.Get(a.Size() - 2); 
      } else {
        int p1 = cur_length / 2;
        int p2 = cur_length - p1;
        answer -= cur_length * cur_length;
        answer -= a.Get(to_fire - 1) * a.Get(to_fire - 1);
        answer -= a.Get(to_fire + 1) * a.Get(to_fire + 1);
        a.Set(to_fire - 1, a.Get(to_fire - 1) + p1);
        a.Set(to_fire + 1, a.Get(to_fire + 1) + p2);
        answer += a.Get(to_fire - 1) * a.Get(to_fire - 1);
        answer += a.Get(to_fire + 1) * a.Get(to_fire + 1);
      }
      a.DeleteElement(to_fire);
      // for (int i = 0; i < a.Size(); ++i) {
      //   std::cout << a.Get(i) << ' ';
      // }
      // std::cout << '\n';
    } else if (cmd == "2") {
      int to_fire;
      std::cin >> to_fire;
      --to_fire;
      int cur_length = a.Get(to_fire);
      int p1 = cur_length / 2;
      int p2 = cur_length - p1;
      answer -= cur_length * cur_length;
      a.Set(to_fire, p1);
      a.AddAfter(to_fire, p2);
      answer += p1 * p1;
      answer += p2 * p2;
      // for (int i = 0; i < a.Size(); ++i) {
      //   std::cout << a.Get(i) << ' ';
      // }
      // std::cout << '\n';
    }
  }
  std::cout << answer << '\n';

  return 0;
}