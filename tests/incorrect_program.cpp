#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const std::pair<long long, long long> kPrimes = {29, 31};
const std::pair<long long, long long> kRems = {1'000'000'007, 1'000'000'009};

struct Hash {
  std::vector<std::pair<long long, long long>> hashes;
  std::vector<std::pair<long long, long long>> primes_powers;

  Hash(std::string& text) {
    hashes.assign(text.size(), {0, 0});
    primes_powers.assign(text.size(), {1, 1});
    primes_powers[0].first = 1;
    primes_powers[0].second = 1;
    hashes[0].first = text[0] - 'a' + 1;
    hashes[0].second = text[0] - 'a' + 1;

    for (size_t i = 1; i < text.size(); ++i) {
      long long current_value = text[i] - 'a' + 1;
      hashes[i].first =
          (hashes[i - 1].first * kPrimes.first + current_value) % kRems.first;
      hashes[i].second =
          (hashes[i - 1].second * kPrimes.second + current_value) %
          kRems.second;
      primes_powers[i].first =
          (primes_powers[i - 1].first * kPrimes.first) % kRems.first;
      primes_powers[i].second =
          (primes_powers[i - 1].second * kPrimes.second) % kRems.second;
    }
  }

  std::pair<long long, long long> GetHash(int left, int right) {
    std::pair<long long, long long> answer = hashes[right];

    if (left > 0) {
      answer.first -=
          (hashes[left - 1].first * primes_powers[right - left + 1].first) %
          kRems.first;
      answer.second -=
          (hashes[left - 1].second * primes_powers[right - left + 1].second) %
          kRems.second;
    }
    answer.first = (answer.first + kRems.first) % kRems.first;
    answer.second = (answer.second + kRems.first) % kRems.second;
    return answer;
  }
};

bool CanFind(std::vector<std::pair<long long, long long>>& used,
             std::pair<long long, long long> value) {
  int left = 0;
  int right = used.size();

  while (right - left > 1) {
    int mid = (left + right) / 2;
    if (used[mid] > value) {
      right = mid;
    } else {
      left = mid;
    }
  }
  if (left >= 0 && used[left] == value) {
    return true;
  }
  return (right < int(used.size()) && used[right] == value);
}

void Solve() {
  std::string pattern;
  std::string text;
  std::cin >> pattern;
  std::cin >> text;

  int n_size = pattern.size();

  pattern += pattern;

  Hash pattern_hash(pattern);
  Hash text_hash(text);

  std::vector<std::pair<long long, long long>> used;

  for (size_t i = 0; i < pattern.size(); ++i) {
    if (int(i + n_size - 1) >= int(pattern.size())) {
      break;
    }
    used.push_back(pattern_hash.GetHash(i, i + n_size - 1));
  }
  std::sort(used.begin(), used.end());

  int answer = 0;

  for (size_t i = 0; i < text.size(); ++i) {
    if (int(i + n_size - 1) >= int(text.size())) {
      break;
    }
    std::pair<long long, long long> temp = text_hash.GetHash(i, i + n_size - 1);
    if (CanFind(used, temp)) {
      ++answer;
    }
  }

  std::cout << answer << "\n";
}

int main() {
  Init();
  Solve();
  return 0;
}