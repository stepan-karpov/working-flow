#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct SplayTree {
  // use when smb has no parent/son
  static const int kNoValue = 1e9;
  struct Node {
    std::string key = "", value = "";
    int left = kNoValue;
    int right = kNoValue;
    int parent = kNoValue;
    Node(std::string key, std::string value, int parent)
        : key(key), value(value), parent(parent) {}
  };
  std::vector<Node> tree;

  // returns Grandparent of x
  // UB if x == kNoValue
  int G(int x) {
    if (P(x) == kNoValue) {
      return kNoValue;
    }
    return tree[tree[x].parent].parent;
  }

  // returns Parent of x
  // UB if x == kNoValue
  int P(int x) { return tree[x].parent; }

  void RightZig(int x) {
    int a = x;
    int b = tree[x].right;
    int a_t = tree[x].left;
    int b_t = tree[b].left;
    int c_t = tree[b].right;
    std::swap(tree[a], tree[b]);
    std::swap(a, b);
    tree[b].parent = tree[a].parent;
    tree[a].left = a_t;
    if (a_t != kNoValue) {
      tree[a_t].parent = a;
    }
    tree[a].right = b_t;
    if (b_t != kNoValue) {
      tree[b_t].parent = a;
    }
    tree[b].left = a;
    if (a != kNoValue) {
      tree[a].parent = b;
    }
    tree[b].right = c_t;
    if (c_t != kNoValue) {
      tree[c_t].parent = b;
    }
  }

  void LeftZig(int x) {
    int a = x;
    int b = tree[x].left;
    int a_t = tree[b].left;
    int b_t = tree[b].right;
    int c_t = tree[x].right;
    std::swap(tree[a], tree[b]);
    std::swap(a, b);
    tree[b].parent = tree[a].parent;
    tree[a].left = b_t;
    if (b_t != kNoValue) {
      tree[b_t].parent = a;
    }
    tree[a].right = c_t;
    if (c_t != kNoValue) {
      tree[c_t].parent = a;
    }
    tree[b].left = a_t;
    if (a_t != kNoValue) {
      tree[a_t].parent = b;
    }
    tree[b].right = a;
    if (a != kNoValue) {
      tree[a].parent = b;
    }
  }

  void LeftZigZig(int x) {
    LeftZig(x);
    LeftZig(x);
  }

  void LeftZigZag(int x) {
    int daddy = tree[x].left;
    RightZig(daddy);
    LeftZig(x);
  }

  void RightZigZag(int x) {
    int daddy = tree[x].right;
    LeftZig(daddy);
    RightZig(x);
  }

  void RightZigZig(int x) {
    RightZig(x);
    RightZig(x);
  }

  void Splay(int x) {
    int cur_vertex = x;
    while (cur_vertex != 0) {
      int granny = G(cur_vertex);
      int daddy = P(cur_vertex);
      if (granny == kNoValue && daddy != kNoValue) {
        if (tree[daddy].left == cur_vertex) {
          LeftZig(daddy);
        } else {
          RightZig(daddy);
        }
        cur_vertex = daddy;
        continue;
      }
      // granny definitely exists
      if (tree[granny].left == daddy && tree[daddy].left == cur_vertex) {
        LeftZigZig(granny);
      } else if (tree[granny].left == daddy &&
                 tree[daddy].right == cur_vertex) {
        LeftZigZag(granny);
      } else if (tree[granny].right == daddy &&
                 tree[daddy].right == cur_vertex) {
        RightZigZig(granny);
      } else {
        RightZigZag(granny);
      }
      cur_vertex = granny;
    }
  }

  void Add(std::string& key, std::string& value) { Add(0, key, value); }

  int Add(int root, std::string& key, std::string& value) {
    if (root >= int(tree.size())) {
      tree.push_back({key, value, (root == 0 ? kNoValue : root)});
      return tree.size() - 1;
    }
    if (tree[root].key > key) {
      tree[root].left = Add(tree[root].left, key, value);
      tree[tree[root].left].parent = root;
      return root;
    }
    tree[root].right = Add(tree[root].right, key, value);
    tree[tree[root].right].parent = root;
    return root;
  }

  std::string Get(int root, std::string& key) {
    if (root >= int(tree.size())) {
      return "no_value_exists";
    }
    if (tree[root].key > key) {
      return Get(tree[root].left, key);
    }
    if (tree[root].key < key) {
      return Get(tree[root].right, key);
    }
    std::string answer = tree[root].value;
    Splay(root);
    return answer;
  }

  std::string Get(std::string& key) { return Get(0, key); }
};

int main() {
  Init();
  int n;
  std::cin >> n;

  SplayTree tree;

  for (int i = 0; i < n; ++i) {
    std::string key, value;
    std::cin >> key >> value;
    tree.Add(value, key);
    tree.Add(key, value);
  }

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string key;
    std::cin >> key;
    std::cout << tree.Get(key) << '\n';
  }

  return 0;
}