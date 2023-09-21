#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Node {
  // ALHPABET IS {a, b}!!!
  // node struct:
  // is_terminated,
  // is edge with 'a' to itself, is edge with 'a' to second node
  // is edge with 'b' to itself, is edge with 'b' to second node
  std::vector<bool> node_states;
  Node(int mask) {
    for (int j = 4; j >= 0; --j) {
      node_states.push_back((mask >> j) & 1);
    }
  }

  void OutputNode(int number) {
    int res_number = 1 - number;
    if (node_states[1]) {
      std::cout << number << " " << number << " a\n";
    }
    if (node_states[2]) {
      std::cout << number << " " << res_number << " a\n";
    }
    if (node_states[3]) {
      std::cout << number << " " << number << " b\n";
    }
    if (node_states[4]) {
      std::cout << number << " " << res_number << " b\n";
    }
  }
};

struct NFA {
  int length_limit = 10;
  Node node1, node2;
  NFA(Node node1, Node node2) : node1(node1), node2(node2) {}

  bool HasEps() {
    return node1.node_states[0];
  }

  bool CheckDfs(Node& node1, Node& node2, int pointer, int word) {
    if (pointer == 0) { return node1.node_states[0]; }
    int current_bit = (word >> pointer) & 1;
    if (current_bit == 0) {
      bool tree_check = false;
      if (node1.node_states[1]) {
        tree_check |= CheckDfs(node1, node2, pointer - 1, word);
      }
      if (node1.node_states[2]) {
        tree_check |= CheckDfs(node2, node1, pointer - 1, word);
      }
      return tree_check;
    }
    bool tree_check = false;
    if (node1.node_states[3]) {
      tree_check |= CheckDfs(node1, node2, pointer - 1, word);
    }
    if (node1.node_states[4]) {
      tree_check |= CheckDfs(node2, node1, pointer - 1, word);
    }
    return tree_check;
  }

  bool CanRecognize(int word, int length) {
    return CheckDfs(node1, node2, length - 1, word);
  }

  bool IsEqualTo(NFA& other) {
    if ((HasEps() && !other.HasEps()) || (!HasEps() && other.HasEps())) {
      return false;
    }

    for (int length = 1; length <= length_limit; ++length) {
      for (int word = 0; word < (1 << length); ++word) {
        bool CanAchieve1 = CanRecognize(word, length);
        bool CanAchieve2 = other.CanRecognize(word, length);
        if (CanAchieve1 != CanAchieve2) {
          return false;
        }
      }
    }
    
    return true;
  }

  void OutputNFA() {
    std::vector<bool> blank(5, 0);
    if (node1.node_states == blank && node2.node_states == blank) {
      std::cout << "blank NFA\n";
      return;
    }
    if (node1.node_states[0]) {
      std::cout << "0 is a terminal\n";
    }
    if (node2.node_states[0]) {
      std::cout << "1 is a terminal\n";
    }
    node1.OutputNode(0);
    node2.OutputNode(1);
  }
};

void Solve() {
  std::vector<NFA> languages;

  for (int mask1 = 0; mask1 < (1 << 5); ++mask1) {
    for (int mask2 = 0; mask2 < (1 << 5); ++mask2) {
      NFA current_nfa({Node(mask1), Node(mask2)});
      bool found = false;
      for (size_t j = 0; j < languages.size(); ++j) {
        if (current_nfa.IsEqualTo(languages[j])) {
          found = true;
          break;
        }
      }
      if (!found) {
        languages.push_back(current_nfa);
      }
    }
  }

  int i = 202;
  languages[i].OutputNFA();
  std::cout << "\n\n\n";
  languages[i + 1].OutputNFA();



  std::cout << languages.size() << "\n";

}

int main() {
  Init();
  Solve();
  return 0;
}