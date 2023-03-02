#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void InitializeBorders(std::vector<std::vector<int>>& dp,
                       std::vector<std::vector<std::pair<int, int>>>& parents,
                       std::string& s1, std::string& s2) {
  int n = s1.size();
  int m = s2.size();

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
}

void RestoreAnswers(std::vector<int>& sequence1, std::vector<int>& sequence2,
                    std::vector<std::vector<std::pair<int, int>>>& parents,
                    std::vector<std::vector<int>>& dp) {
  int i = dp.size() - 1;
  int j = dp[0].size() - 1;

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

  if (dp[0][0] == 1) {
    sequence1.push_back(0);
    sequence2.push_back(0);
  }
}

void solve() {
  std::string s1, s2;
  std::cin >> s1 >> s2;

  int n = s1.size();
  int m = s2.size();

  std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
  std::vector<std::vector<std::pair<int, int>>> parents(
      m, std::vector<std::pair<int, int>>(n));

  InitializeBorders(dp, parents, s1, s2);

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

  std::vector<int> sequence1;
  std::vector<int> sequence2;

  RestoreAnswers(sequence1, sequence2, parents, dp);

  std::string common;

  for (int i = int(sequence1.size()) - 1; i >= 0; --i) {
    common += s2[sequence1[i]];
  }

  std::string templ;

  int p1 = 0;
  int p2 = 0;
  int p = 0;

  while (p < common.size() && p1 < s1.size() && p2 < s2.size()) {
    while (p1 < s1.size() && s1[p1] != common[p]) {
      if (templ.empty() || templ[templ.size() - 1] != '*') {
        templ += "*";
      }
      ++p1;
    }
    while (p2 < s2.size() && s2[p2] != common[p]) {
      if (templ.empty() || templ[templ.size() - 1] != '*') {
        templ += "*";
      }
      ++p2;
    }
    templ += common[p];
    ++p1; ++p2; ++p;
  }
  if (p1 < s1.size()) {
    if (templ.empty() || templ[templ.size() - 1] != '*') {
      templ += "*";
    }
  }
  if (p2 < s2.size()) {
    if (templ.empty() || templ[templ.size() - 1] != '*') {
      templ += "*";
    }
  }

  int cnt_star = 0;
  int cnt_not_star = 0;

  for (int i = 0; i < templ.size(); ++i) {
    if (templ[i] == '*') {
      ++cnt_star;
    } else {
      ++cnt_not_star;
    }
  }

  if (cnt_star <= cnt_not_star) {
    std::cout << "YES\n";
    // std::cout << templ << "\n";
  } else {
    std::cout << "NO\n";
  }
}

int main() {
  Init();

  int t = 1;
  // std::cin >> t;


  for (int i = 0; i < t; ++i) {
    solve();
  }
  
  return 0;
}