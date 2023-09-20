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

const std::string kAlph = "01";

struct Node {
  std::vector<int> to;
  std::vector<int> nums;
  bool terminate = false;
  int link = -1;
  int comp = 0;
  int comp_count = 0;
  Node() { to.assign(kAlph.size(), -1); }
};

void BuildSceleton(std::vector<std::string>& dict, std::vector<Node>& trie) {
  trie.reserve(2 * dict.size());
  trie.push_back(Node());

  for (size_t i = 0; i < dict.size(); ++i) {
    std::string& current_string = dict[i];
    int current_vertex = 0;
    for (size_t j = 0; j < current_string.size(); ++j) {
      if (trie[current_vertex].to[current_string[j] - '0'] == -1) {
        trie.push_back(Node());
        trie[current_vertex].to[current_string[j] - '0'] = trie.size() - 1;
      }
      current_vertex = trie[current_vertex].to[current_string[j] - '0'];
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

bool CheckCycles(int current_vertex, int comp_count, std::vector<Node>& trie,
                 std::vector<int>& used, std::vector<int>& parent) {
  int comp_link = trie[current_vertex].comp;
  if (trie[comp_link].terminate) {
    ++comp_count;
  }
  trie[current_vertex].comp_count = comp_count;
  used[current_vertex] = 1;

  bool ok = false;

  for (int i = 0; i < kAlph.size(); ++i) {
    if (trie[current_vertex].to[kAlph[i] - '0'] != -1) {
      int to = trie[current_vertex].to[kAlph[i] - '0'];
      if (used[to] == 1) {
        parent[to] = current_vertex;
        int res1 = trie[to].comp_count;
        int res2 = trie[current_vertex].comp_count;
        if (res1 == res2) {
          return true;
        }
      } else if (used[to] == 0) {
        ok = ok || CheckCycles(to, comp_count, trie, used);
      }
    }
  }

  if (trie[current_vertex].link != -1) {
    int to = trie[current_vertex].link;
    if (used[to] == 1) {
      int res1 = trie[to].comp_count;
      int res2 = trie[current_vertex].comp_count;
      if (res1 == res2) {
        return true;
      }
    } else if (used[to] == 0) {
      ok = ok || CheckCycles(to, comp_count, trie, used);
    }
  }

  used[current_vertex] = 2;
  return false;
}

void Solve() {
  int n_size;
  std::cin >> n_size;
  std::vector<std::string> dict(n_size);
  for (int i = 0; i < n_size; ++i) {
    std::cin >> dict[i];
  }

  std::vector<Node> trie;
  BuildTrie(dict, trie);
  
  std::vector<int> used(trie.size(), 0);

  for (int i = 0; i < trie.size(); ++i) {
    if (used[i] == 0) {
      if (CheckCycles(0, 0, trie, used)) {
        std::cout << "TAK\n";
        return;
      }
    }
  }
  std::cout << "NIE\n";
}

int main() {
  Init();
  Solve();
  return 0;
}