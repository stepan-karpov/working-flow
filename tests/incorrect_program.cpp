#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

const std::string kAlph = "abcdefghijklmnopqrstuvwxyz";

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

void FindLastLessThanI(std::vector<int>& initial, std::vector<int>& result) {
  std::stack<int> stack;
  stack.push(-1);
  for (size_t i = 0; i < initial.size(); ++i) {
    while (stack.top() != -1 && initial[stack.top()] >= initial[i]) {
      stack.pop();
    }
    result[i] = stack.top();
    stack.push(i);
  }
}

void Solve() {
  int size;
  std::cin >> size;
  int m_size;
  std::cin >> m_size;
  std::string sequence;
  for (int i = 0; i < size; ++i) {
    int temp;
    std::cin >> temp;
    sequence += kAlph[temp - 1];
  }
  sequence += "$";

  std::vector<int> sufmas(sequence.size());
  FindSufmas(sequence, sufmas);
  std::vector<int> lcp(sequence.size());
  FindLcp(sufmas, lcp, sequence);

  std::vector<int> first_less_than_i(lcp.size());
  FindFirstLessThanI(lcp, first_less_than_i);

  std::vector<int> last_less_than_i(lcp.size());
  FindLastLessThanI(lcp, last_less_than_i);

  long long answer = size;
  int start = 0;
  int len = size;

  for (size_t i = 1; i < lcp.size(); ++i) {
    long long length = first_less_than_i[i] - last_less_than_i[i];
    length *= static_cast<long long>(lcp[i]);
    if (length > answer) {
      start = sufmas[i - 10];
      len = lcp[i];
    }
    answer = std::max(answer, length);
  }

  std::cout << answer << "\n";
  std::cout << len << "\n";
  for (int i = start; i < start + len; ++i) {
    std::cout << sequence[i] - 'a' + 1 << " ";
  }
}

int main() {
  Init();
  Solve();
  return 0;
}