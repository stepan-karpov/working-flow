#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const std::string kAlph = "abcdefghijklmnopqrstuvwxyz";
const int kAlphSize = 26;

struct Node {
  int to[kAlphSize];
  std::vector<int> nums;
  bool terminate = false;
  int link = -1;
  int comp = 0;
  Node() {
    for (int i = 0; i < kAlphSize; ++i) {
      to[i] = -1;
    }
  }
};

void BuildSceleton(std::vector<std::string>& dict, std::vector<Node>& trie) {
  trie.reserve(dict.size() * 2);
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

void CountTable(std::vector<std::string>& main_map,
                std::vector<std::string>& patterns,
                std::vector<std::vector<int>>& coord1) {
  int n_size = main_map.size();

  std::vector<Node> trie;
  BuildTrie(patterns, trie);

  for (int j = 0; j < n_size; ++j) {
    int vertex = 0;
    for (size_t i = 0; i < main_map[j].size(); ++i) {
      vertex = trie[vertex].to[main_map[j][i] - 'a'];
      int current_parent = vertex;
      while (current_parent != 0) {
        if (trie[current_parent].terminate) {
          for (size_t k = 0; k < trie[current_parent].nums.size(); ++k) {
            int current_number = trie[current_parent].nums[k];
            int start_pos = i - patterns[current_number].size() + 1;
            int row_start = j - current_number;
            if (row_start >= 0) {
              ++coord1[row_start][start_pos];
            }
          }
        }
        current_parent = trie[current_parent].comp;
      }
    }
  }
}

void Transpose(std::vector<std::string>& sequence) {
  std::vector<std::string> answer;
  answer.reserve(sequence.size());

  for (size_t i = 0; i < sequence[0].size(); ++i) {
    answer.push_back("");
    for (size_t j = 0; j < sequence.size(); ++j) {
      answer[i] += sequence[j][i];
    }
  }
  sequence = answer;
}

int CountTables(std::vector<std::vector<int>>& coord1,
                std::vector<std::string>& patterns,
                std::vector<std::vector<int>>& coord2) {
  int answer = 0;
  int n_size = coord1.size();
  int m_size = coord1[0].size();
  int size = patterns[0].size();
  int size_m = patterns.size();

  for (int i = 0; i <= n_size - size; ++i) {
    for (int j = 0; j <= m_size - size_m; ++j) {
      if (coord1[i][j] == size ||
          coord1[i][j] + coord2[j][i] == size + size_m - 2) {
        ++answer;
      }
    }
  }
  return answer;
}

void Solve() {
  int n_size;
  int m_size;
  std::cin >> n_size >> m_size;
  std::vector<std::string> main_map(n_size);
  for (int i = 0; i < n_size; ++i) {
    std::cin >> main_map[i];
  }

  int a_size;
  int b_size;
  std::cin >> a_size >> b_size;
  std::vector<std::string> patterns(a_size);

  for (int i = 0; i < a_size; ++i) {
    std::cin >> patterns[i];
  }

  std::vector<std::vector<int>> coord1(n_size, std::vector<int>(m_size, 0));
  CountTable(main_map, patterns, coord1);

  Transpose(main_map);
  Transpose(patterns);

  std::vector<std::vector<int>> coord2(m_size, std::vector<int>(n_size, 0));
  CountTable(main_map, patterns, coord2);

  std::cout << CountTables(coord1, patterns, coord2) << "\n";
  return;
  for (int i = 0; i < n_size; ++i) {
    for (int j = 0; j < m_size; ++j) {
      std::cout << coord1[i][j] << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\n";
  std::cout << "\n";

  for (int i = 0; i < m_size; ++i) {
    for (int j = 0; j < n_size; ++j) {
      std::cout << coord2[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  Init();
  Solve();
  return 0;
}