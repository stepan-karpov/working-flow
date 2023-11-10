#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const int kMod = 7'340'033;
const int kRoot = 5;
const int kRoot1 = 4404020;
const int kRootpw = 1 << 20;
const int kMod7 = 7;
const int kMod21 = 21;

void Output(std::vector<int>& to_output) {
  std::cout << int(to_output.size()) - 1 << " ";
  for (size_t i = 0; i < to_output.size(); ++i) {
    std::cout << to_output[i] << " ";
  }
  std::cout << "\n";
}

int BinPow(int aa, int xx, int mod) {
  if (xx == 0) {
    return 1;
  }
  if (xx % 2 == 0) {
    long long temp = BinPow(aa, xx / 2, mod);
    return (temp * temp) % mod;
  }
  long long t1 = aa;
  long long t2 = BinPow(aa, xx - 1, mod);
  return (t1 * t2) % mod;
}

void Prepare(std::vector<int>& aa) {
  int nn = aa.size();

  for (int i = 1, j = 0; i < nn; ++i) {
    int bit = nn >> 1;
    for (; j >= bit; bit >>= 1) {
      j -= bit;
    }
    j += bit;
    if (i < j) {
      std::swap(aa[i], aa[j]);
    }
  }
}

void Fft(std::vector<int>& aa, bool invert) {
  int nn = aa.size();

  Prepare(aa);

  for (int len = 2; len <= nn; len <<= 1) {
    int wlen = invert ? kRoot1 : kRoot;
    for (int i = len; i < kRootpw; i <<= 1) {
      wlen = (int)(wlen * 1LL * wlen % kMod);
    }
    for (int i = 0; i < nn; i += len) {
      long long ww = 1;
      for (int j = 0; j < len / 2; ++j) {
        long long uu = aa[i + j];
        long long vv = (int)(aa[i + j + len / 2] % kMod * 1LL * ww % kMod);
        vv %= kMod;
        aa[i + j] = uu + vv < kMod ? uu + vv : uu + vv - kMod;
        aa[i + j + len / 2] = uu - vv >= 0 ? uu - vv : uu - vv + kMod;
        ww = int(ww * 1LL * wlen % kMod);
      }
    }
  }
  if (invert) {
    int nrev = BinPow(nn, kMod - 2, kMod);
    for (int i = 0; i < nn; ++i) {
      aa[i] = int(aa[i] % kMod * 1LL * nrev % kMod);
    }
  }
}

std::vector<int> Multiply(std::vector<int>& aa, std::vector<int>& bb) {
  std::vector<int> res;
  std::vector<int> array1(aa.begin(), aa.end());
  std::vector<int> array2(bb.begin(), bb.end());

  int nn = 1;
  int max_size = std::max(aa.size(), bb.size());
  while (nn < max_size) {
    nn *= 2;
  }
  nn *= 2;

  array1.resize(nn);
  array2.resize(nn);
  res.resize(nn);

  Fft(array1, false);
  Fft(array2, false);

  for (int i = 0; i < nn; ++i) {
    array1[i] = (array1[i] * 1LL * array2[i]) % kMod;
  }

  Fft(array1, true);

  for (int i = 0; i < nn; ++i) {
    res[i] = array1[i] % kMod7;
  }
  return res;
}

std::vector<int> Recurs(std::vector<int>& pp, int mm) {
  if (mm == 1) {
    return std::vector<int>(1, BinPow(pp[0], kMod7 - 2, kMod7));
  }
  std::vector<int> qq = Recurs(pp, mm / 2);
  std::vector<int> p0(mm / 2);
  std::vector<int> p1(mm / 2);
  for (int i = 0; i < mm / 2; ++i) {
    if (i < (int)(pp.size())) {
      p0[i] = pp[i];
    }
    if (i + mm / 2 < (int)(pp.size())) {
      p1[i] = pp[i + mm / 2];
    }
  }
  if (mm != 2) {
    qq.pop_back();
  }
  std::vector<int> temp = Multiply(p0, qq);
  temp[0] = (temp[0] - 1 + kMod7) % kMod7;
  std::vector<int> rr(mm / 2 + 1);
  for (int i = mm / 2; i < mm; ++i) {
    rr[i - mm / 2] = temp[i];
  }
  std::vector<int> temp2 = Multiply(p1, qq);
  std::vector<int> temp3(mm + 1);
  for (int i = 0; i <= mm; ++i) {
    int add = 0;
    if (i < (int)(rr.size())) {
      add += rr[i];
    }
    if (i < (int)(rr.size())) {
      add += temp2[i];
    }
    temp3[i] = (3 * kMod7 - add) % kMod7;
  }
  std::vector<int> tt = Multiply(qq, temp3);
  std::vector<int> ans(mm + 1, 0);
  for (int i = 0; i < mm / 2; ++i) {
    if (i < (int)(qq.size())) {
      ans[i] = qq[i];
    }
  }
  for (int i = mm / 2; i <= mm; ++i) {
    if (i - mm / 2 < (int)(tt.size())) {
      ans[i] = tt[i - mm / 2];
    }
  }
  return ans;
}

std::vector<int> FindReverse(std::vector<int>& pp, int mm, size_t m_orig) {
  std::vector<int> answer = Recurs(pp, mm);
  std::vector<int> to_ret;
  for (size_t i = 0; i < m_orig; ++i) {
    if (i < answer.size()) {
      to_ret.push_back(answer[i]);
    } else {
      to_ret.push_back(0);
    }
  }
  return to_ret;
}

std::vector<int> ReversePolyMod(int mm, std::vector<int>& pp) {
  if (pp[0] == 0) {
    return {};
  }

  int new_m = 1;
  while (new_m < mm) {
    new_m *= 2;
  }
  std::vector<int> temp_answer = FindReverse(pp, new_m, mm);
  while (!temp_answer.empty() && temp_answer[temp_answer.size() - 1] == 0) {
    temp_answer.pop_back();
  }
  return temp_answer;
}

void Solve() {
  int n1;
  std::cin >> n1;
  std::vector<int> f_poly_rev(n1 + 1);
  for (int i = 0; i <= n1; ++i) {
    std::cin >> f_poly_rev[i];
  }
  std::vector<int> f_poly = f_poly_rev;
  std::reverse(f_poly.begin(), f_poly.end());
  int n2;
  std::cin >> n2;
  std::vector<int> g_poly_rev(n2 + 1);
  for (int i = 0; i <= n2; ++i) {
    std::cin >> g_poly_rev[i];
  }
  std::vector<int> g_poly = g_poly_rev;
  std::reverse(g_poly.begin(), g_poly.end());
  int mm = n1 - n2 + 1;
  std::vector<int> q_poly = {};
  if (mm > 0) {
    q_poly = ReversePolyMod(mm, g_poly_rev);
    q_poly = Multiply(q_poly, f_poly_rev);
    q_poly.resize(mm);
    std::reverse(q_poly.begin(), q_poly.end());
    while (q_poly.size() > 1 && q_poly[q_poly.size() - 1] == 0) {
      q_poly.pop_back();
    }
    std::reverse(q_poly.begin(), q_poly.end());
    Output(q_poly);
  } else {
    std::cout << "0 0 \n";
  }
  std::reverse(q_poly.begin(), q_poly.end());
  std::vector<int> rem_poly = f_poly;
  std::vector<int> sub = Multiply(g_poly, q_poly);
  rem_poly.resize(std::max(f_poly.size(), sub.size()));
  for (int i = 0; i < int(rem_poly.size()); ++i) {
    int p1 = 0;
    if (i < int(rem_poly.size())) {
      p1 = rem_poly[i];
    }
    int p2 = 0;
    if (i < int(sub.size())) {
      p2 = sub[i];
    }
    rem_poly[i] = (p1 - p2 + kMod21) % kMod7;
  }
  while (rem_poly.size() > 1 && rem_poly[rem_poly.size() - 1] == 0) {
    rem_poly.pop_back();
  }
  std::reverse(rem_poly.begin(), rem_poly.end());
  Output(rem_poly);
}

signed main() {
  Init();
  Solve();
  return 0;
}