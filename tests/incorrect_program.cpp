#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}


int main() {
  Init();
  long long n, m;
  std::cin >> n >> m;

  std::vector<long long> a(n + 1);

  for (long long i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }

  std::vector<std::vector<std::pair<long long, long long>>> dp(m + 1,
    std::vector<std::pair<long long, long long>>(n + 1, {1e9, 1e9}));

  for (long long i = 0; i <= m; ++i) {
    dp[i][i] = {0, i};
  }

  for (long long i = 2; i <= n; ++i) {
    long long best_var = 0;
    long long best_delta = 1e9;
    for (long long j = 1; j <= i; ++j) {
      long long current_delta = 0;
      for (long long k = 1; k <= i; ++k) {
        current_delta += abs(a[k] - a[j]);
      }
      if (current_delta < best_delta) {
        best_delta = current_delta;
        best_var = j;
      }
    }
    dp[1][i] = {best_delta, best_var};
  }

  for (long long i = 2; i <= m; ++i) {
    for (long long r = i + 1; r <= n; ++r) {
      long long sum = 0;
      for (long long current_place = r; current_place >= 1; --current_place) {
        long long current_value = dp[i - 1][current_place - 1].first;
        current_value += sum - a[current_place] * (r - current_place);
        if (current_value == 1e9) {
          break;
        }
        long long last_index = dp[i - 1][current_place - 1].second;
        for (long long k = last_index + 1; k < current_place; ++k) {
          current_value -= abs(a[k] - a[last_index]);
          current_value += std::min(abs(a[k] - a[last_index]), abs(a[k] - a[current_place]));
        }
        if (current_value < dp[i][r].first) {
          dp[i][r] = {current_value, current_place};
        }
        sum += a[current_place];
      }
    }
  }

  for (long long i = 0; i <= m; ++i) {
    for (long long j = 0; j <= n; ++j) {
      if (dp[i][j].first == 1e9) {
        std::cout << "i  " << " ";
      } else {
        std::cout << dp[i][j].first << " ";
        if (dp[i][j].first < 10) {
          std::cout << " ";
        }
        if (dp[i][j].first < 100) {
          std::cout << " ";
        }
      }
    }
    std::cout << "\n";
  }

  long long start_i = m;
  long long start_j = dp[m][n].second;
  long long answer = dp[m][n].first;

  std::cout << answer << "\n";
  
  std::vector<long long> sequence;

  while (start_i != 0) {
    sequence.push_back(a[start_j]);
    start_j = dp[start_i][start_j].second - 1;
    start_j = dp[start_i - 1][start_j].second;
    --start_i;
  }

  std::sort(sequence.begin(), sequence.end());

  // for (long long i = 0; i < sequence.size(); ++i) {
  //   std::cout << sequence[i] << " ";
  // }
  // std::cout << "\n";

  return 0;
}