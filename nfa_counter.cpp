#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  std::vector<bool> config;
  Node(int mask) {
    config.push_back((mask >> 4) & 1);
    config.push_back((mask >> 3) & 1);
    config.push_back((mask >> 2) & 1);
    config.push_back((mask >> 1) & 1);
    config.push_back((mask >> 0) & 1);
  }
  void OutputNode(int number) {
    int res_number = 1 - number;
    if (config[1]) {
      std::cout << number << " " << number << " a\n";
    }
    if (config[2]) {
      std::cout << number << " " << res_number << " a\n";
    }
    if (config[3]) {
      std::cout << number << " " << number << " b\n";
    }
    if (config[4]) {
      std::cout << number << " " << res_number << " b\n";
    }
  }
};

struct NFA {
  static const int max_length_check = 11;
  Node node1, node2;
  NFA(Node&& node1, Node&& node2)
    : node1(std::move(node1)), node2(std::move(node2)) {}

  bool RecognizeDfs(Node& first_node, Node& second_node,
                    int pointer, int word) {
    if (pointer == -1) { return first_node.config[0]; }
    int bit = (word >> pointer) & 1;

    if (bit == 0) {
      bool tree_check = false;
      if (first_node.config[1]) {
        tree_check =
          (tree_check | RecognizeDfs(first_node, second_node, pointer - 1, word));
      }
      if (first_node.config[2]) {
        tree_check =
          (tree_check | RecognizeDfs(second_node, first_node, pointer - 1, word));
      }
      return tree_check;
    }
    bool tree_check = false;
    if (first_node.config[3]) {
      tree_check =
        (tree_check | RecognizeDfs(first_node, second_node, pointer - 1, word));
    }
    if (first_node.config[4]) {
      tree_check =
        (tree_check | RecognizeDfs(second_node, first_node, pointer - 1, word));
    }
    return tree_check;
  }

  bool CanRecognize(int word, int length) {
    return RecognizeDfs(node1, node2, length - 1, word);
  }

  bool isEquals(NFA& other) {
    for (int length = 0; length <= max_length_check; ++length) {
      for (int word = 0; word < (1 << length); ++word) {
        bool can_recognize1 = CanRecognize(word, length);
        bool can_recognize2 = other.CanRecognize(word, length);
        if (can_recognize1 != can_recognize2) {
          return false;
        }
      }
    }
    return true;
  }
  
  bool isDFA() {
    if (node1.config[1] != 0 && node1.config[2] != 0) {
      return false;
    }
    if (node2.config[3] != 0 && node2.config[4] != 0) {
      return false;
    }
    return true;
  }

  void OutputNFA() {
    std::vector<bool> blank(5, 0);
    if (node1.config == blank && node2.config == blank) {
      std::cout << "blank NFA\n";
      return;
    }
    if (node1.config[0]) {
      std::cout << "0 is a terminal\n";
    }
    if (node2.config[0]) {
      std::cout << "1 is a terminal\n";
    }
    node1.OutputNode(0);
    node2.OutputNode(1);
  }
};

void CountNFA(bool check_dfa = false) {
  std::vector<NFA> languages;

  for (int mask1 = 0; mask1 < (1 << 5); ++mask1) {
    for (int mask2 = 0; mask2 < (1 << 5); ++mask2) {
      NFA current_nfa(std::move(Node(mask1)), std::move(Node(mask2)));
      if (check_dfa && !current_nfa.isDFA()) { continue; }
      bool found = false;
      for (size_t j = 0; j < languages.size(); ++j) {
        if (current_nfa.isEquals(languages[j])) {
          found = true;
          break;
        }
      }
      if (!found) {
        languages.push_back(current_nfa);
      }
    }
  }

  // to output all different nfa uncomment the following code: 
  // for (int i = 0; i < 20; ++i) {
  //   languages[i].OutputNFA();
  //   std::cout << "\n\n========\n\n";
  // }
  std::string output_text = "number of nfa: ";
  if (check_dfa) {
    output_text = "number of dfa: ";
  }
  std::cout << output_text << languages.size() << "\n";
}

int main() {
  /* 
    some notes: 
      -this codes works ~5 sec on my machine (Mac M2, 8 cores)

      -function isEquals() implies that if 
      each of the word from {a, b}^(NFA.max_length_check) has
      equal recognition from two different nka then two nfa are equal

      -answer doesn't depend on max_length_check (if it is >= 5)
  */
  CountNFA(false);
  CountNFA(true);

  return 0;
}