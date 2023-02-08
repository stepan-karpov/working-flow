#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const int INF = 1e9 + 1;

struct Node {
  int sequence = 1;
  int last_max = -INF;
  int prev_max = -INF;
  Node(int sequence, int last_max, int prev_max)
       : sequence(sequence), last_max(last_max), prev_max(prev_max) {}
};

void Init(int n, int m, std::vector<int>& a, std::vector<int>& b,
          std::vector<std::vector<Node>>& dp) {
  if (a[0] == b[0]) {
    dp[0][0] = {1, a[0], -INF};
  } else {
    dp[0][0] = {0, -INF, -INF};
  }

  for (int i = 1; i < n; ++i) {
    dp[i][0] = dp[i - 1][0];
    if (a[i] == b[0]) {
      dp[i][0] = {1, a[i], -INF};
    }
  }
  
  for (int i = 1; i < m; ++i) {
    dp[0][i] = dp[0][i - 1];
    if (a[0] == b[i]) {
      dp[0][i] = {1, a[0], -INF};
    }
  }

}

int main() {
  Init();
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  std::vector<int> b(m);

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  std::vector<std::vector<Node>> dp(n, std::vector<Node>(m, {0, 0, 0}));

  Init(n, m, a, b, dp);

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      dp[i][j] = dp[i - 1][j - 1];
      if (a[i] == b[j]) {
        int last_ans = dp[i - 1][j - 1].sequence;
        int last_max = dp[i - 1][j - 1].last_max;
        int prev_max = dp[i - 1][j - 1].prev_max;
        if (last_max < a[i]) {
          dp[i][j] = {last_ans + 1, a[i], last_max};
        } else if (prev_max < a[i]) {
          std::vector<int> temp = {last_max, a[i], prev_max};
          std::sort(temp.begin(), temp.end());
          dp[i][j].sequence = last_ans;
          dp[i][j].last_max = temp[1];
          dp[i][j].prev_max = temp[0];
        }
      }
      if (dp[i - 1][j].sequence > dp[i][j].sequence) {
        dp[i][j] = dp[i - 1][j];
      } else if (dp[i - 1][j].sequence == dp[i][j].sequence) {
        std::vector<int> temp;
        temp.push_back(dp[i - 1][j].last_max);
        temp.push_back(dp[i][j].last_max);
        temp.push_back(std::min(dp[i][j].prev_max, dp[i - 1][j].prev_max));
        std::sort(temp.begin(), temp.end());
        dp[i][j].last_max = temp[1];
        dp[i][j].prev_max = temp[0];
      }
      if (dp[i][j - 1].sequence > dp[i][j].sequence) {
        dp[i][j] = dp[i][j - 1];
      } else if (dp[i][j - 1].sequence == dp[i][j].sequence) {
        std::vector<int> temp;
        temp.push_back(dp[i][j - 1].last_max);
        temp.push_back(dp[i][j].last_max);
        temp.push_back(std::min(dp[i][j].prev_max, dp[i][j - 1].prev_max));
        std::sort(temp.begin(), temp.end());
        dp[i][j].last_max = temp[1];
        dp[i][j].prev_max = temp[0];
      }
    }
  }


  int answer = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << dp[i][j].sequence << "," << dp[i][j].last_max << "  ";
      answer = std::max(answer, dp[i][j].sequence);
    }
    std::cout << "\n";
  }

  std::cout << answer << "\n";

  return 0;
}