#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const long long kMod = 7'340'033;
using Complex = std::complex<long double>;

void Output(std::vector<long long>& to_output) {
  for (size_t i = 0; i < to_output.size(); ++i) {
    std::cout << to_output[i] << "*x^" << i << " ";
    if (i != to_output.size() - 1) {
      std::cout << "+ ";
    }
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

const int kRoot = 5;
const int kRoot1 = 4404020;
const int kRootpw = 1 << 20;

void Prepare(std::vector<long long>& aa) {
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

void Fft(std::vector<long long>& aa, bool invert) {
  long long nn = aa.size();

  Prepare(aa);

  for (int len = 2; len <= nn; len <<= 1) {
    long long wlen = invert ? kRoot1 : kRoot;
    for (int i = len; i < kRootpw; i <<= 1) {
      wlen = (long long)(wlen * 1LL * wlen % kMod);
    }
    for (long long i = 0; i < nn; i += len) {
      long long ww = 1;
      for (long long j = 0; j < len / 2; ++j) {
        long long uu = aa[i + j];
        long long vv =
            (long long)(aa[i + j + len / 2] % kMod * 1LL * ww % kMod % kMod);
        aa[i + j] = uu + vv < kMod ? uu + vv : uu + vv - kMod;
        aa[i + j + len / 2] = uu - vv >= 0 ? uu - vv : uu - vv + kMod;
        ww = int(ww * 1LL * wlen % kMod);
      }
    }
  }
  if (invert) {
    long long nrev = BinPow(nn, kMod - 2, kMod);
    for (int i = 0; i < nn; ++i) {
      aa[i] = (long long)(aa[i] % kMod * 1LL * nrev % kMod);
    }
  }
}

void Multiply(std::vector<long long>& aa, std::vector<long long>& bb,
              std::vector<long long>& res) {
  std::vector<long long> array1(aa.begin(), aa.end());
  std::vector<long long> array2(bb.begin(), bb.end());

  long long nn = 1;
  long long max_size = std::max(aa.size(), bb.size());
  while (nn < max_size) {
    nn *= 2;
  }
  nn *= 2;

  array1.resize(nn);
  array2.resize(nn);
  res.resize(nn);

  Fft(array1, false);
  Fft(array2, false);

  for (long long i = 0; i < nn; ++i) {
    array1[i] *= array2[i];
  }

  Fft(array1, true);

  for (long long i = 0; i < nn; ++i) {
    res[i] = array1[i];
    // if (array1[i].real() >= kEps) {
    //   res[i] = ((long long)(array1[i].real() + kBias)) % kMod;
    // } else {
    //   res[i] = ((long long)(array1[i].real() - kBias)) % kMod;
    // }
  }
}

std::vector<long long> Recurs(std::vector<long long>& pp, long long mm) {
  if (mm == 1) {
    return std::vector<long long>(1, BinPow(pp[0], kMod - 2, kMod));
  }

  std::vector<long long> qq = Recurs(pp, mm / 2);
  std::vector<long long> p0(mm / 2);
  std::vector<long long> p1(mm / 2);

  for (int i = 0; i < mm / 2; ++i) {
    if (i < int(pp.size())) {
      p0[i] = pp[i];
    }
    if (i + mm / 2 < int(pp.size())) {
      p1[i] = pp[i + mm / 2];
    }
  }
  // p0 * q == 1 (mod x^(m / 2))
  // p0 * q == 1 + (x^m) * R
  std::vector<long long> temp(mm / 2 + 1);
  Multiply(p0, qq, temp);
  temp[0] = (temp[0] - 1 + kMod) % kMod;

  std::vector<long long> rr(mm / 2 + 1);
  for (int i = mm / 2; i < mm; ++i) {
    rr[i - mm / 2] = temp[i];
  }
  std::vector<long long> temp2(mm + 1);
  std::vector<long long> temp3(mm + 1);
  Multiply(p1, qq, temp2);
  for (int i = 0; i <= mm; ++i) {
    long long add = 0;
    if (i < int(rr.size())) {
      add += rr[i];
    }
    if (i < int(rr.size())) {
      add += temp2[i];
    }
    temp3[i] = (3 * kMod - add) % kMod;
  }
  std::vector<long long> tt(2 * mm);
  Multiply(qq, temp3, tt);
  std::vector<long long> ans(mm + 1, 0);
  for (int i = 0; i < mm / 2; ++i) {
    if (i < int(qq.size())) {
      ans[i] = qq[i];
    }
  }

  for (int i = mm / 2; i <= mm; ++i) {
    if (i - mm / 2 < int(tt.size())) {
      ans[i] = tt[i - mm / 2];
    }
  }
  return ans;
}

void FindReverse(std::vector<long long>& pp, int mm, size_t m_orig) {
  std::vector<long long> answer = Recurs(pp, mm);
  for (size_t i = 0; i < m_orig; ++i) {
    if (i < answer.size()) {
      std::cout << answer[i] << " ";
    } else {
      std::cout << "0 ";
    }
  }
}

void Solve() {
  long long mm;
  long long nn;
  std::cin >> mm >> nn;
  std::vector<long long> pp(nn + 1);
  for (int i = 0; i <= nn; ++i) {
    std::cin >> pp[i];
  }

  if (pp[0] == 0) {
    std::cout << "The ears of a dead donkey\n";
    return;
  }

  long long new_m = 1;
  while (new_m < mm) {
    new_m *= 2;
  }
  FindReverse(pp, new_m, mm);
}

int main() {
  Init();
  Solve();
  return 0;
}