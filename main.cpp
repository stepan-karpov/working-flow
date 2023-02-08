#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Init();
  // std::string s1, s2;
  // std::cin >> s1 >> s2;

  // int n = s1.size();
  // int m = s2.size();

  int n;
  std::cin >> n;
  std::vector<int> s1(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s1[i];
  }
  int m;
  std::cin >> m;
  std::vector<int> s2(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> s2[i];
  }

  std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
  std::vector<std::vector<std::pair<int, int>>> parents(m, std::vector<std::pair<int, int>>(n));

  dp[0][0] = int(s1[0] == s2[0]);
  parents[0][0] = {-1, -1};

  for (int i = 1; i < n; ++i) {
    dp[0][i] = dp[0][i - 1];
    parents[0][i] = {0, i - 1};
    if (s2[0] == s1[i]) {
      dp[0][i] = 1;
    }
  }

  for (int i = 1; i < m; ++i) {
    dp[i][0] = dp[i - 1][0];
    parents[i][0] = {i - 1, 0};
    if (s1[0] == s2[i]) {
      dp[i][0] = 1;
    }
  }

  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      dp[i][j] = dp[i - 1][j - 1];
      parents[i][j] = {i - 1, j - 1};
      if (s2[i] == s1[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        parents[i][j] = {i - 1, j - 1};
      } else {
        if (dp[i - 1][j] > dp[i][j]) {
          dp[i][j] = dp[i - 1][j];
          parents[i][j] = {i - 1, j};
        }
        if (dp[i][j - 1] > dp[i][j]) {
          dp[i][j] = dp[i][j - 1];
          parents[i][j] = {i, j - 1};
        }
      }
    }
  }

  int i = m - 1;
  int j = n - 1;

  std::vector<int> sequence1;
  std::vector<int> sequence2;

  while (!(i == -1 && j == -1)) {
    int parent_i = parents[i][j].first;
    int parent_j = parents[i][j].second;
    if (parent_i != -1 && parent_j != -1 && dp[i][j] > dp[parent_i][parent_j]) {
      sequence1.push_back(i);
      sequence2.push_back(j);
    }
    i = parent_i;
    j = parent_j;
  }

  // std::cout << dp[m - 1][n - 1] << "\n";

  for (int i = int(sequence1.size()) - 1; i >= 0; --i) {
    std::cout << s2[sequence1[i]] << " ";
  }

  return 0;
}