#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const std::string kAlph = "abcdefghijklmnopqrstuvwxyz";

struct Node {
  std::vector<int> to;
  std::vector<int> nums;
  bool terminate = false;
  int link = -1;
  int comp = 0;
  Node() { to.assign(kAlph.size(), -1); }
};

void BuildSceleton(std::vector<std::string>& dict, std::vector<Node>& trie) {
  trie.push_back(Node());

  for (size_t i = 0; i < dict.size(); ++i) {
    std::string& current_string = dict[i];
    int current_vertex = 0;
    for (size_t j = 0; j < current_string.size(); ++j) {
      if (trie[current_vertex].to[current_string[j] - 'a'] == -1) {
        trie.push_back(Node());
        trie[current_vertex].to[current_string[j] - 'a'] = trie.size() - 1;
      }
      current_vertex = trie[current_vertex].to[current_string[j] - 'a'];
    }
    trie[current_vertex].terminate = true;
    trie[current_vertex].nums.push_back(i);
  }
}

void BuildTrie(std::vector<std::string>& dict, std::vector<Node>& trie) {
  BuildSceleton(dict, trie);

  trie[0].link = 0;

  for (size_t i = 0; i < kAlph.size(); ++i) {
    if (trie[0].to[i] == -1) {
      trie[0].to[i] = 0;
    }
  }

  std::queue<int> queue;
  queue.push(0);

  while (!queue.empty()) {
    int current_vertex = queue.front();
    queue.pop();

    for (size_t i = 0; i < kAlph.size(); ++i) {
      int son = trie[current_vertex].to[i];
      if (trie[son].link != -1) {
        continue;
      }
      trie[son].link =
          current_vertex == 0 ? 0 : trie[trie[current_vertex].link].to[i];
      for (size_t j = 0; j < kAlph.size(); ++j) {
        int grandson = trie[son].to[j];
        if (grandson != -1) {
          continue;
        }
        trie[son].to[j] = trie[trie[son].link].to[j];
      }

      int link = trie[son].link;
      if (trie[link].terminate || link == 0) {
        trie[son].comp = link;
      } else {
        trie[son].comp = trie[link].comp;
      }
      queue.push(son);
    }
  }
}

void Solve() {
  std::string text;
  std::cin >> text;
  int n_size;
  std::cin >> n_size;
  std::vector<std::string> dict(n_size);
  for (int i = 0; i < n_size; ++i) {
    std::cin >> dict[i];
  }

  std::vector<Node> trie;
  BuildTrie(dict, trie);

  std::vector<std::vector<int>> answer(n_size);

  int vertex = 0;
  for (size_t i = 0; i < text.size(); ++i) {
    vertex = trie[vertex].to[text[i] - 'a'];
    int current_parent = vertex;
    while (current_parent != 0) {
      if (trie[current_parent].terminate) {
        for (size_t j = 0; j < trie[current_parent].nums.size(); ++j) {
          int current_number = trie[current_parent].nums[j];
          answer[current_number].push_back(i);
        }
      }
      current_parent = trie[current_parent].comp;
    }
  }

  for (int i = 0; i < n_size; ++i) {
    int current_len = dict[i].size();
    std::cout << answer[i].size() << " ";
    for (size_t j = 0; j < answer[i].size(); ++j) {
      std::cout << answer[i][j] - current_len + 2 << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  Init();
  Solve();
  return 0;
}