// no_concepts
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const std::string kAlph = "abc";
const int kTen = 10;
const int kThree = 3;

std::unordered_map<std::string, int> numbers;
std::unordered_map<int, int> count;

struct Corasick {
  struct Node {
    int to[kThree];
    int edges[kThree];
    int nums = -1;
    bool terminate = false;
    int link = -1;
    int comp = 0;
    Node() {
      for (int i = 0; i < kThree; ++i) {
        to[i] = -1;
        edges[i] = -1;
      }
    }
  };
  std::vector<Node> trie;

  void BuildSceleton(std::string& text, int number) {
    trie.push_back(Node());

    int current_vertex = 0;
    for (size_t j = 0; j < text.size(); ++j) {
      if (trie[current_vertex].edges[text[j] - 'a'] == -1) {
        trie.push_back(Node());
        trie[current_vertex].edges[text[j] - 'a'] = trie.size() - 1;
      }
      current_vertex = trie[current_vertex].edges[text[j] - 'a'];
    }
    trie[current_vertex].terminate = true;
    trie[current_vertex].nums = number;
  }

  void BuildTrie() {
    for (size_t i = 0; i < trie.size(); ++i) {
      trie[i].comp = 0;
      trie[i].link = -1;
      trie[i].to[0] = trie[i].edges[0];
      trie[i].to[1] = trie[i].edges[1];
      trie[i].to[2] = trie[i].edges[2];
    }
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

  Corasick(std::string& text, int number) {
    trie.clear();
    trie.reserve(text.size() + 1);
    BuildSceleton(text, number);
    BuildTrie();
  }

  void DfsMerge(int old_number, int new_number, Corasick* root) {
    std::vector<Node>& old_trie = root->trie;
    if (old_trie[old_number].terminate) {
      trie[new_number].terminate = true;
      trie[new_number].nums = old_trie[old_number].nums;
    }

    for (size_t i = 0; i < kAlph.size(); ++i) {
      int togo = old_trie[old_number].edges[kAlph[i] - 'a'];
      if (togo == -1) {
        continue;
      }
      if (trie[new_number].edges[kAlph[i] - 'a'] == -1) {
        trie.push_back(Node());
        trie[new_number].edges[kAlph[i] - 'a'] = trie.size() - 1;
      }
      DfsMerge(togo, trie[new_number].edges[kAlph[i] - 'a'], root);
    }
  }

  void Merge(Corasick* root) {
    trie.reserve(trie.size() + root->trie.size() + 1);
    DfsMerge(0, 0, root);
    BuildTrie();
  }

  int Count(std::string& text) {
    int answer = 0;

    int vertex = 0;
    for (size_t i = 0; i < text.size(); ++i) {
      vertex = trie[vertex].to[text[i] - 'a'];
      int current_parent = vertex;
      while (current_parent != 0) {
        if (trie[current_parent].terminate) {
          int current_number = trie[current_parent].nums;
          answer += int(count[current_number] > 0);
        }
        current_parent = trie[current_parent].comp;
      }
    }
    return answer;
  }
};

struct MegaCorasick {
  int size = 1;
  int log_size = 1;
  std::vector<Corasick*> trie;

  MegaCorasick(int n_size) : size(n_size) {
    while ((1 << log_size) <= size) {
      ++log_size;
    }
    trie.assign(log_size + kTen, nullptr);
  }

  void Add(std::string& text, int number) {
    Corasick* pointer = new Corasick(text, number);
    int position = 0;
    while (trie[position] != nullptr) {
      if (trie[position]->trie.size() > pointer->trie.size()) {
        trie[position]->Merge(pointer);
        delete pointer;
        pointer = trie[position];
        trie[position] = nullptr;
      } else {
        pointer->Merge(trie[position]);
        delete trie[position];
        trie[position] = nullptr;
      }

      ++position;
    }
    trie[position] = pointer;
  }

  int Count(std::string& text) {
    int answer = 0;
    for (size_t i = 0; i < trie.size(); ++i) {
      if (trie[i] != nullptr) {
        answer += trie[i]->Count(text);
      }
    }
    return answer;
  }

  ~MegaCorasick() {
    for (size_t i = 0; i < trie.size(); ++i) {
      if (trie[i] != nullptr) {
        delete trie[i];
      }
    }
  }
};

void Shift(std::string& text, int shift) {
  shift = int(shift) % int(text.size());
  std::string ans;
  for (size_t i = shift; i < text.size(); ++i) {
    ans += text[i];
  }
  for (int i = 0; i < shift; ++i) {
    ans += text[i];
  }
  text = ans;
}

void Solve() {
  int queries;
  std::cin >> queries;

  MegaCorasick megamonster(queries + kTen);

  int last_added_number = 0;
  int last_answer = 0;

  for (int i = 0; i < queries; ++i) {
    std::string query;
    std::string text;
    std::cin >> query >> text;
    Shift(text, last_answer);
    if (query == "?") {
      last_answer = megamonster.Count(text);
      std::cout << last_answer << "\n";
    } else if (query == "-") {
      if (numbers.find(text) == numbers.end()) {
        continue;
      }
      int number = numbers[text];
      count[number] = 0;
    } else {
      if (numbers.find(text) != numbers.end()) {
        ++count[numbers[text]];
      } else {
        numbers[text] = last_added_number;
        count[last_added_number] = 1;
        megamonster.Add(text, last_added_number);
        ++last_added_number;
      }
    }
  }
}

int main() {
  Init();
  Solve();
  return 0;
}