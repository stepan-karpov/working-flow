#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const long long kPrime = 19;
const long long kRemainder = 2000000011;

std::vector<long long> PolynomialHash(std::string& pattern) {
  std::vector<long long> hash(pattern.size());
  hash[0] = pattern[0] - 'a' + 1;

  for (size_t i = 1; i < pattern.size(); ++i) {
    hash[i] = (hash[i - 1] * kPrime + int(pattern[i] - 'a' + 1)) % kRemainder;
  }
  return hash;
}

std::vector<long long> PPowers(int size) {
  std::vector<long long> answer(size, 0);
  answer[0] = 1;
  for (int i = 1; i < size; ++i) {
    answer[i] = (answer[i - 1] * kPrime) % kRemainder;
  }
  return answer;
}

int GetHash(std::vector<long long>& hash, std::vector<long long>& p_powers,
            long long left_border, long long right_border) {
  long long answer = hash[right_border];
  if (left_border > 0LL) {
    answer = answer - (hash[left_border - 1] *
                       p_powers[right_border - left_border + 1]) %
                          kRemainder;
    answer = (answer + kRemainder) % kRemainder;
  }
  return answer;
}

void Solve() {
  std::string pattern;
  std::string text;
  std::cin >> pattern;
  std::cin >> text;

  long long n_size = pattern.size();
  pattern = pattern + pattern;

  std::vector<long long> p_powers =
      PPowers(std::max(pattern.size(), text.size()));

  std::vector<long long> pattern_hash = PolynomialHash(pattern);

  std::vector<long long> text_hash = PolynomialHash(text);

  std::set<long long> found;

  for (size_t i = 0; i < pattern.size(); ++i) {
    size_t start = i;
    size_t end = i + n_size - 1;
    if (end >= pattern.size()) {
      break;
    }
    found.insert(GetHash(pattern_hash, p_powers, start, end));
  }

  long long ans = 0;

  for (size_t i = 0; i < text.size(); ++i) {
    size_t start = i;
    size_t end = i + n_size - 1;
    if (end >= text.size()) {
      break;
    }
    long long current_hash = GetHash(text_hash, p_powers, start, end);
    if (found.find(current_hash) != found.end()) {
      ++ans;
    }
  }

  std::cout << ans << "\n";
}

int main() {
  Init();
  Solve();
  return 0;
}