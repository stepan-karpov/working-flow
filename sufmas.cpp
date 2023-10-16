#include <algorithm>
#include <iostream>
#include <vector>

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

void Solve() {
  std::string sequence;
  std::cin >> sequence;
  // sequence += "$";

  std::vector<int> sufmas(sequence.size());
  FindSufmas(sequence, sufmas);

  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sufmas[i] + 1 << " ";
  }
  std::cout << "\n";
}

int main() {
  Init();
  Solve();
  return 0;
}