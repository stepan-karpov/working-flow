#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

const int kInf = 1e9;

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void RadixSort(std::vector<std::pair<std::pair<int, int>, int>>& pairs,
               int border) {
  std::vector<int> cnt(border + 1);
  std::vector<std::pair<std::pair<int, int>, int>> step1(pairs.size());
  for (size_t i = 0; i < pairs.size(); ++i) {
    ++cnt[pairs[i].first.second];
  }
  std::vector<int> pointers(border + 1);
  pointers[0] = 0;
  for (int i = 1; i < border + 1; ++i) {
    pointers[i] = pointers[i - 1] + cnt[i - 1];
  }
  for (size_t i = 0; i < pairs.size(); ++i) {
    int new_place = pointers[pairs[i].first.second];
    ++pointers[pairs[i].first.second];
    step1[new_place] = pairs[i];
  }
  for (size_t i = 0; i < cnt.size(); ++i) {
    cnt[i] = 0;
  }
  for (size_t i = 0; i < pairs.size(); ++i) {
    ++cnt[step1[i].first.first];
  }
  pointers[0] = 0;
  for (int i = 1; i < border + 1; ++i) {
    pointers[i] = pointers[i - 1] + cnt[i - 1];
  }
  for (size_t i = 0; i < pairs.size(); ++i) {
    int new_place = pointers[step1[i].first.first];
    ++pointers[step1[i].first.first];
    pairs[new_place] = step1[i];
  }
}

void FindSufmas(std::string& sequence, std::vector<int>& sufmas) {
  std::vector<std::pair<int, int>> to_sort(sequence.size());
  std::vector<int> comp(sequence.size());
  {
    // k = 0
    for (size_t i = 0; i < sequence.size(); ++i) {
      to_sort[i] = {sequence[i], i};
    }
    std::sort(to_sort.begin(), to_sort.end());
    comp[to_sort[0].second] = 0;
    for (size_t i = 1; i < sequence.size(); ++i) {
      comp[to_sort[i].second] = comp[to_sort[i - 1].second];
      if (to_sort[i].first != to_sort[i - 1].first) {
        ++comp[to_sort[i].second];
      }
    }
  }
  {
    int step = 0;
    std::vector<std::pair<std::pair<int, int>, int>> pairs(sequence.size());
    while ((1 << step) < static_cast<int>(sequence.size())) {
      int power = (1 << step);
      // k -> k + 1
      int radix_sort_border = 0;
      for (size_t i = 0; i < sequence.size(); ++i) {
        pairs[i].first.first = comp[i];
        pairs[i].first.second = comp[(i + power) % int(sequence.size())];
        radix_sort_border = std::max(
            {radix_sort_border, pairs[i].first.first, pairs[i].first.second});
        pairs[i].second = i;
      }
      RadixSort(pairs, radix_sort_border);
      // std::sort(pairs.begin(), pairs.end());
      comp[pairs[0].second] = 0;
      for (size_t i = 1; i < sequence.size(); ++i) {
        comp[pairs[i].second] = comp[pairs[i - 1].second];
        if (pairs[i].first != pairs[i - 1].first) {
          ++comp[pairs[i].second];
        }
      }
      ++step;
    }
    for (size_t i = 0; i < sequence.size(); ++i) {
      sufmas[i] = pairs[i].second;
    }
  }
}

void FindLcp(std::vector<int>& sufmas, std::vector<int>& lcp,
             std::string& sequence) {
  std::vector<int> permutation(sufmas.size());
  for (size_t i = 0; i < sufmas.size(); ++i) {
    permutation[sufmas[i]] = i;
  }

  int current_counter = 0;
  for (size_t i = 0; i < lcp.size() - 1; ++i) {
    int pi = permutation[i];
    int prev = sufmas[pi - 1];
    while (sequence[i + current_counter] == sequence[prev + current_counter]) {
      ++current_counter;
    }
    lcp[pi] = current_counter;
    current_counter = std::max(current_counter - 1, 0);
  }
}

void FindFirstLessThanI(std::vector<int>& initial, std::vector<int>& result) {
  initial.push_back(-1);
  std::stack<int> stack;
  stack.push(initial.size() - 1);

  for (int i = int(initial.size()) - 2; i >= 0; --i) {
    while (initial[stack.top()] >= initial[i]) {
      stack.pop();
    }
    result[i] = stack.top();
    stack.push(i);
  }
  initial.pop_back();
}

struct SegTree {
  struct Node {
    int max_value = -kInf;
    int min_value = +kInf;
    Node() = default;
    Node(int init) : max_value(init), min_value(init) {}
  };
  int size = 1;
  std::vector<Node> tree;
  SegTree(int n) {
    while (size < n) {
      size *= 2;
    }
    tree.assign(2 * size - 1, Node());
  }

  Node static Combine(Node& first, Node& second) {
    Node answer;
    answer.min_value = std::min(first.min_value, second.min_value);
    answer.max_value = std::max(first.max_value, second.max_value);
    return answer;
  }

  void Set(int ind, int value, int lx, int rx, int x_size) {
    if (rx - lx == 1) {
      tree[x_size] = Node(value);
      return;
    }
    int mid = (lx + rx) / 2;
    if (ind < mid) {
      Set(ind, value, lx, mid, 2 * x_size + 1);
    } else {
      Set(ind, value, mid, rx, 2 * x_size + 2);
    }
    tree[x_size] = Combine(tree[2 * x_size + 1], tree[2 * x_size + 2]);
  }

  void Set(int ind, int value) { Set(ind, value, 0, size, 0); }

  Node Get(int left_border, int right_border, int lx, int rx, int x_cnt) {
    if (left_border <= lx && rx <= right_border) {
      return tree[x_cnt];
    }
    if (left_border >= rx || lx >= right_border) {
      Node null;
      null.max_value = -kInf;
      null.min_value = +kInf;
      return null;
    }
    int mid = (lx + rx) / 2;
    Node ans1 = Get(left_border, right_border, lx, mid, 2 * x_cnt + 1);
    Node ans2 = Get(left_border, right_border, mid, rx, 2 * x_cnt + 2);
    return Combine(ans1, ans2);
  }

  int GetMin(int left_border, int right_border) {
    return Get(left_border, right_border, 0, size, 0).min_value;
  }
  int GetMax(int left_border, int right_border) {
    return Get(left_border, right_border, 0, size, 0).max_value;
  }
};

long long CountBestAnswer(std::vector<int>& first_less_than_i,
                          std::vector<int>& sufmas, SegTree& tree,
                          std::vector<int>& lcp) {
  size_t size = lcp.size();
  long long ans = sufmas.size() - 1;

  for (size_t i = 1; i < size - 1; ++i) {
    long long right_border = first_less_than_i[i + 1];
    long long min_pos = tree.GetMin(i, right_border);
    long long max_pos = tree.GetMax(i, right_border);
    long long current_pos = sufmas[i];
    long long tem = lcp[i + 1];
    long long substring_size =
        std::max(current_pos - min_pos, max_pos - current_pos) + tem;
    long long temp = tem * tem;
    ans = std::max(substring_size + temp, ans);
  }

  return ans;
}

void Solve() {
  std::string sequence;
  std::cin >> sequence;
  sequence += "$";

  std::vector<int> sufmas(sequence.size());
  FindSufmas(sequence, sufmas);
  std::vector<int> lcp(sequence.size());
  FindLcp(sufmas, lcp, sequence);

  std::vector<int> first_less_than_i(lcp.size());
  FindFirstLessThanI(lcp, first_less_than_i);

  SegTree tree(sufmas.size());
  for (size_t i = 0; i < sufmas.size(); ++i) {
    tree.Set(i, sufmas[i]);
  }

  std::cout << CountBestAnswer(first_less_than_i, sufmas, tree, lcp) << "\n";
}

int main() {
  Init();
  Solve();
  return 0;
}