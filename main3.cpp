#include <iostream>
#include <map>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void Input(int n, std::vector<long long>& e) {
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < n; ++j) {
      if (s[j] == '1') {
        e[i] |= (1ll << j);
      }
    }
  }
}

void Precalc(std::map<int, int>& log) {
  for (int i = 0; i < 26; ++i) {
    log[(1ll << i)] = i;
  }
}

int main() {
  Init();
  std::map<int, int> log2;
  Precalc(log2);
  int n;
  std::cin >> n;

  std::vector<long long> e(n + (n % 2), 0);

  Input(n, e);

  long long ans = 1 - (n % 2);
  n += (n % 2);

  int n1 = n / 2;

  std::vector<int> is_click1((1 << n1), 0);
  std::vector<int> is_click2((1 << n1), 0);
  std::vector<int> f((1 << n1), 0);

  is_click1[0] = (1 << n1) - 1;
  is_click2[0] = (1 << n1) - 1;


  // solving before MITM 
  for (int mask = 1; mask < (1 << n1); ++mask) {
    int neig1 = (e[log2[(mask & -mask)]] ^ (mask & -mask));
    int neig2 = (e[log2[(mask & -mask)] + n1] & ((1 << n1) - 1));

    is_click1[mask] = is_click1[mask ^ (mask & -mask)] & neig1;
    is_click2[mask] = is_click2[mask ^ (mask & -mask)] & neig2;

    if ((is_click1[mask] & mask) == mask) {
      f[mask] = 1;
    }
  }

  // SOS dp from cf
  for (int i = 0; i < n1; ++i) {
    for (int mask = 0; mask < (1 << n1); ++mask) {
      if ((mask & (1 << i)) != 0) {
        f[mask] += f[mask ^ (1 << i)];
      }
    }
  }

  ans += f[(1 << n1) - 1];

  for (int mask = 1; mask < (1 << n1); ++mask) {
    int neig = ((e[log2[(mask & -mask)] + n1] >> n1) ^ (mask & -mask));
    is_click1[mask] = is_click1[mask ^ (mask & -mask)] & neig;
    if ((is_click1[mask] & mask) == mask) {
      ans += f[is_click2[mask]] + 1ll;
    }
  }
  std::cout << ans << "\n";
}