#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

const std::string kALPH = "abcdefghijklmnopqrstuvwxyz";

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Node {
  std::unordered_map<char, int> edges;
  std::unordered_map<char, int> to;
  int link = -1;
  int len = 0;
  std::vector<int> reversed_links;
  std::vector<int> num;
  bool terminate = false;
  int border = 0;
  std::vector<std::pair<int, int>>* path = nullptr;
};

void BuildTrieSceleton(std::vector<std::string>& sequence,
                       std::vector<Node>& trie) {
  for (size_t i = 0; i < sequence.size(); ++i) {
    int current_v = 0;

    for (size_t j = 0; j < sequence[i].size(); ++j) {
      if (trie[current_v].edges.count(sequence[i][j]) == 0) {
        trie.push_back(Node());
        trie[current_v].edges[sequence[i][j]] = trie.size() - 1;
      }
      current_v = trie[current_v].edges[sequence[i][j]];
    }

    trie[current_v].len = sequence[i].size();
    trie[current_v].terminate = true;
    trie[current_v].num.push_back(i);
  }
}

std::vector<Node> BuildTrie(std::vector<std::string>& sequence) {
  std::vector<Node> trie;
  trie.push_back(Node());

  trie[0].link = 0;
  BuildTrieSceleton(sequence, trie);

  for (auto child : kALPH) {
    if (trie[0].edges.count(child) != 0) {
      trie[0].to[child] = trie[0].edges[child];
    } else {
      trie[0].to[child] = 0;
    }
  }
  std::queue<int> queue;
  queue.push(0);

  while (!queue.empty()) {
    int parent = queue.front();
    queue.pop();
    for (auto child : kALPH) {
      int to = trie[parent].to[child];
      if (trie[parent].edges.count(child) == 0) {
        continue;
      }
      if (parent == 0) {
        trie[to].link = 0;
      } else {
        trie[to].link = trie[trie[parent].link].to[child];
      }
      for (auto grandson : kALPH) {
        if (trie[to].edges.count(grandson) != 0) {
          trie[to].to[grandson] = trie[to].edges[grandson];
        } else {
          trie[to].to[grandson] = trie[trie[to].link].to[grandson];
        }
      }
      queue.push(to);
    }
  }

  return trie;
}

void FindSources(int current_v, std::vector<int>& sources,
                 std::vector<Node>& trie) {
  if (trie[current_v].reversed_links.size() == 0) {
    sources.push_back(current_v);
    return;
  }
  for (auto edge : trie[current_v].reversed_links) {
    FindSources(edge, sources, trie);
  }
}

void ReverseLinks(int current_v, std::vector<Node>& trie) {
  if (current_v != 0) {
    int link = trie[current_v].link;
    trie[link].reversed_links.push_back(current_v);
  }
  for (auto edge : trie[current_v].edges) {
    ReverseLinks(edge.second, trie);
  }
}

void MarkUp(int current_v, std::vector<std::pair<int, int>>& path,
            std::vector<Node>& trie) {
  if (current_v == 0) { return; }
  MarkUp(trie[current_v].link, path, trie);
  if (trie[current_v].terminate) {
    for (auto num : trie[current_v].num) {
      path.push_back({num, trie[current_v].len});
    }
  }
  trie[current_v].border = path.size();
  trie[current_v].path = &path;
}

void MarkUpTerminators(std::vector<int>& sources,
                       std::vector<std::vector<std::pair<int, int>>>& terminators,
                       std::vector<Node>& trie) {
  for (int i = 0; i < sources.size(); ++i) {
    MarkUp(sources[i], terminators[i], trie);
  }
}

void Solve() {
  std::string text;
  std::cin >> text;
  int n_size; std::cin >> n_size;
  std::vector<std::string> sequence(n_size);
  for (int i = 0; i < n_size; ++i) {
    std::cin >> sequence[i];
  }
  std::vector<Node> trie = BuildTrie(sequence);

  std::vector<int> sources;

  ReverseLinks(0, trie);
  FindSources(0, sources, trie);
  std::vector<std::vector<std::pair<int, int>>> terminators(sources.size());
  MarkUpTerminators(sources, terminators, trie);

  std::vector<std::vector<int>> answer(sequence.size());

  int current_vertex = 0;
  for (size_t i = 0; i < text.size(); ++i) {
    current_vertex = trie[current_vertex].to[text[i]];
    int parent = current_vertex;
    std::vector<std::pair<int, int>>* path = trie[current_vertex].path;
    int border = trie[current_vertex].border;
    for (int j = 0; j < border; ++j) {
      int num = (*path)[j].first;
      int len = (*path)[j].second;
      int start = i - len + 1;
      answer[num].push_back(start + 1);
    }
  }
  for (size_t i = 0; i < answer.size(); ++i) {
    std::cout << answer[i].size() << " ";
    for (size_t j = 0; j < answer[i].size(); ++j) {
      std::cout << answer[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  Init();
  Solve();
  return 0;
}