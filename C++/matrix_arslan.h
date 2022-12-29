#ifndef MATRIX__MATRIX_H_
#define MATRIX__MATRIX_H_
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <sstream>
#include <string>
//#include <cassert>

using std::cin, std::cout, std::vector, std::string;

const vector<long long> pws10{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

class BigInteger {
 public:
  // public fields
  int sign = 1;
  vector<long long> arr;

 private:
  // private fields
  int BASE = 100000000;
  int BASE_CNT = 8;

  // private methods
  static int getIntLen(long long a) {
    if (a == 0) {
      return 1;
    }
    int cnt = 0;
    while (a != 0) {
      ++cnt;
      a /= 10;
    }

    return cnt;
  }

  [[nodiscard]] int getSize() const {
    return static_cast<int>(arr.size());
  }

  void normalise() {
    int new_size = getSize();
    for (int i = getSize() - 1; i >= 0; --i) {
      if (arr[i] == 0) {
        new_size = i;
      } else {
        break;
      }
    }
    arr.resize(new_size);
  }

  void rShift() {
    if (arr.empty()) {
      arr.push_back(0);
      return;
    }
    arr.push_back(arr[arr.size() - 1]);

    for (int i = getSize() - 2; i > 0; --i) {
      arr[i] = arr[i - 1];
    }

    arr[0] = 0;
  }

 public:
  // public methods
  [[nodiscard]] int cmp_wo_sign(const BigInteger& other) const {
    if (getSize() == 0 && other.getSize() == 0) {
      return 0;
    }
    if (getSize() == 0) {
      return -1;
    }
    if (other.getSize() == 0) {
      return 1;
    }

    if (getSize() < other.getSize()) {
      return -1;
    } else if (getSize() > other.getSize()) {
      return 1;
    } else {
      for (int i = getSize() - 1; i >= 0; --i) {
        if (arr[i] < other.arr[i]) {
          return -1;
        } else if (arr[i] > other.arr[i]) {
          return 1;
        }
      }
    }

    return 0;
  }

  [[nodiscard]] string toString() const {
    std::ostringstream oss;

    if (cmp_wo_sign(0) == 0) {
      oss << 0;
      return oss.str();
    }

    if (sign == -1) {
      oss << '-';
    }
    bool zero_flag = true;
    for (int i = getSize() - 1; i >= 0; --i) {
      if (zero_flag && arr[i] == 0) {
        // do nothing
      } else {
        if (!zero_flag) {
          for (int j = 0; j < (BASE_CNT - getIntLen(arr[i])); ++j) {
            oss << 0;
          }
        }
        oss << arr[i];
        zero_flag = false;
      }
    }

    return oss.str();
  }

  // constructors
  BigInteger() = default;

  BigInteger(const int other) {
    if (other == 0) {
      return;
    }
    arr.push_back(abs(other));
    sign = (other >= 0) ? 1 : -1;
  }

  explicit BigInteger(const string str) {
    if (str == "0" || str == "-0") {
      return;
    }

    long long cell = 0;
    int cnt = 0;

    for (int i = static_cast<int>(str.size()) - 1; i > 0; --i) {
      cell = (str[i] - '0') * pws10[cnt] + cell;
      ++cnt;

      if (cnt == BASE_CNT) {
        arr.push_back(cell);
        cell = 0;
        cnt = 0;
      }
    }
    if (str[0] == '-') {
      sign = -1;
    } else {
      cell = (str[0] - '0') * pws10[cnt] + cell;
      ++cnt;
    }

    if (cnt != 0) {
      arr.push_back(cell);
    }
  }

  // assignment operators
  BigInteger& operator=(int other) {
    arr.clear();
    if (other == 0) {
      sign = 1;
      return *this;
    }
    sign = (other >= 0) ? 1 : -1;
    arr.push_back(abs(other));

    return *this;
  }

  // conversion operators

  explicit operator bool() const {
    return !(*this == 0);
  }

  // binary operators
  bool operator==(const BigInteger& right) const {
    if (sign != right.sign) {
      return false;
    }
    if (cmp_wo_sign(right) == 0) {
      return true;
    }

    return false;
  }

  bool operator<(const BigInteger& right) const {
    if (sign != right.sign) {
      return (sign == -1);
    }
    if (cmp_wo_sign(right) == -1) {
      return (sign == 1);
    }

    return false;
  }

  bool operator!=(const BigInteger& right) const {
    return !(*this == right);
  }

  bool operator<=(const BigInteger& right) const {
    return (*this < right || *this == right);
  }

  bool operator>(const BigInteger& right) const {
    return !(*this <= right);
  }

  bool operator>=(const BigInteger& right) const {
    return !(*this < right);
  }

  // arithmetic operators
  BigInteger& operator+=(const BigInteger& other) {
    size_t max_size = std::max(arr.size(), other.arr.size());
    if (sign != other.sign) {
      sign = other.sign;
      (*this) -= other;
      sign = (sign == 1) ? -1 : 1;
      if (cmp_wo_sign(0) == 0) {
        sign = 1;
      }
    } else {
      arr.resize(max_size + 2);
      for (int i = 0; i < getSize(); ++i) {
        arr[i] += (i < other.getSize()) ? other.arr[i] : 0;
      }

      for (int i = 0; i < getSize() - 1; ++i) {
        if (arr[i] >= BASE) {
          arr[i] -= BASE;
          arr[i + 1]++;
        }
      }
      normalise();
    }
    if (cmp_wo_sign(0) == 0) {
      sign = 1;
    }
    return *this;
  }

  BigInteger& operator-=(const BigInteger& other) {
    vector<long long> other_arr = other.arr;

    if (sign != other.sign) {
      sign = other.sign;
      (*this) += other;
      sign = (sign == 1) ? -1 : 1;
      if (cmp_wo_sign(0) == 0) {
        sign = 1;
      }
    } else {
      if (cmp_wo_sign(other) == 0) {
        arr.resize(0);
        sign = 1;
        return *this;
      } else if (cmp_wo_sign(other) == -1) {
        other_arr = arr;
        arr = other.arr;
        sign = (sign == 1) ? -1 : 1;
      }
      size_t max_size = std::max(arr.size(), other_arr.size());
      arr.resize(max_size + 2);
      for (int i = 0; i < getSize(); ++i) {
        arr[i] -= (i < static_cast<int>(other_arr.size())) ? other_arr[i] : 0;
      }

      for (int i = 0; i < getSize() - 1; ++i) {
        if (arr[i] < 0) {
          arr[i] += BASE;
          arr[i + 1]--;
        }
      }

      normalise();
      if (cmp_wo_sign(0) == 0) {
        sign = 1;
      }
    }

    return *this;
  }

  BigInteger& operator*=(const BigInteger& other) {
    *this = (*this) * other;

    return *this;
  }

  BigInteger& operator/=(const int other) {
    long long carry = 0;
    for (int i = getSize() - 1; i >= 0; --i) {
      long long cur = arr[i] + carry * 1ll * BASE;
      arr[i] = cur / other;
      carry = cur % other;
    }
    normalise();

    return *this;
  }

  BigInteger& operator/=(const BigInteger& other) {
    *this = (*this) / other;

    return *this;
  }

  BigInteger& operator%=(const BigInteger& other) {
    *this = (*this) % other;

    return *this;
  }

  BigInteger operator*(const BigInteger& right) const {
    BigInteger res;

    if (cmp_wo_sign(0) == 0 || right.cmp_wo_sign(0) == 0) {
      return res;
    }

    if (sign != right.sign) {
      res.sign = -1;
    }

    res.arr.resize(getSize() + right.getSize() + 1);
    for (int i = 0; i < getSize(); i++) {
      for (int j = 0; j < right.getSize(); j++) {
        res.arr[i + j] += (arr[i] * right.arr[j]);
      }
    }

    for (int i = 0; i < res.getSize() - 1; ++i) {
      long long p_to_next = res.arr[i] / BASE;
      if (p_to_next != 0) {
        res.arr[i] %= BASE;
        res.arr[i + 1] += p_to_next;
      }
    }
    res.normalise();

    return res;
  }

  BigInteger operator/(const BigInteger& right) const {
    //assert(right != 0);
    BigInteger b = right;
    b.sign = 1;
    BigInteger res, curr;
    res.arr.resize(arr.size());
    for (int i = getSize() - 1; i >= 0; --i) {
      curr.rShift();
      curr.arr[0] = arr[i];
      curr.normalise();

      int x = 0, l = 0, r = BASE;
      while (l <= r) {
        int m = (l + r) / 2;
        BigInteger t = b * m;

        if (t <= curr) {
          x = m;
          l = m + 1;
        } else {
          r = m - 1;
        }
      }

      res.arr[i] = x;
      curr = curr - b * x;
    }

    res.sign = (sign != right.sign) ? -1 : 1;
    res.normalise();
    return res;
  }

  BigInteger operator+(const BigInteger& right) const {
    BigInteger res = *this;

    res += right;

    return res;
  }

  BigInteger operator-(const BigInteger& right) const {
    BigInteger res = *this;

    res -= right;

    return res;
  }

  BigInteger operator%(const BigInteger& right) const {
    return *this - right * (*this / right);
  }

  BigInteger& operator++() {
    *this += 1;
    return *this;
  }

  BigInteger operator++(int) {
    *this += 1;
    return (*this - 1);
  }

  BigInteger& operator--() {
    *this -= 1;
    return *this;
  }

  BigInteger operator--(int) {
    *this -= 1;
    return (*this + 1);
  }

  BigInteger operator-() const {
    BigInteger res = *this;
    res.sign = (res.sign == 1) ? -1 : 1;

    return res;
  }

  // i/o operators
  friend std::istream& operator>>(std::istream& in, BigInteger& num) {
    string str;
    in >> str;

    num = BigInteger(str);

    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const BigInteger& num) {
    string str = num.toString();

    out << str;
    return out;
  }
};

// literal operator overloading
BigInteger operator "" _bi(const char* ch_arr, unsigned long) {
  BigInteger obj(ch_arr);

  return obj;
}

BigInteger gcd(BigInteger a, BigInteger b) {
  if (a == 0 || b == 0) {
    return 0;
  }
  a.sign = 1;
  b.sign = 1;

  BigInteger ans = 1;
  while (a != b) {
    bool ab = a.arr[0] % 2 == 0, bb = b.arr[0] % 2 == 0;
    if (ab && bb) {
      a /= 2;
      b /= 2;
      ans *= 2;
    } else if (ab) {
      a /= 2;
    } else if (bb) {
      b /= 2;
    } else {
      if (a > b) {
        a -= b;
      } else {
        b -= a;
      }
    }
  }
  return ans * a;
}

class Rational {
 public:
  BigInteger num = 0;
  BigInteger denom = 1;

 private:
  // private methods
  void reduct() {
    if (num == 0) {
      denom = 1;
      return;
    }
    if (num == 1) {
      return;
    }

    if (num == denom) {
      num = 1;
      denom = 1;
      return;
    }

    BigInteger dlt = gcd(num, denom);
    //assert(dlt > 0);
    //assert(denom.sign == 1);

    if (dlt > 1) {
      num /= dlt;
      denom /= dlt;
    }
  }

  void normaliseSigns() {
    num.sign *= denom.sign;
    denom.sign = 1;
  }

 public:
  // public methods
  [[nodiscard]] string toString() const {
    std::ostringstream oss;

    oss << num;
    if (denom != 1) {
      oss << '/' << denom;
    }
    return oss.str();
  }

  [[nodiscard]] string asDecimal(size_t precision = 0) const {
    if (precision == 0) {
      return (num / denom).toString();
    }
    BigInteger n_num = num;
    vector<int> nums;
    BigInteger whl = (n_num / denom);
    n_num.sign = 1;
    n_num %= denom;
    int i = 0;
    ++precision;
    while (i < static_cast<int>(precision)) {
      if (n_num == 0) {
        nums.push_back(0);
      } else {
        n_num *= 10;
        while (n_num < denom) {
          n_num *= 10;
          nums.push_back(0);
        }
        if (i < static_cast<int>(precision)) {
          nums.push_back(static_cast<int>((n_num / denom).arr[0]));
        }
        n_num %= denom;
      }
      ++i;
    }

    if (nums[precision - 1] >= 5) {
      ++nums[precision - 2];
      for (size_t j = nums.size() - 2; j > 0; --j) {
        if (nums[j] >= 10) {
          nums[j] -= 10;
          ++nums[j - 1];
        } else {
          break;
        }
      }
      if (nums[0] >= 10) {
        nums[0] -= 10;
        ++whl;
      }

    }
    string str = (num.sign == -1) ? "-" : "";
    str += whl.toString();
    str += '.';
    for (size_t j = 0; j < precision - 1; ++j) {
      str += std::to_string(nums[j]);
    }

    return str;
  }

  // constructors
  Rational() = default;

  Rational(BigInteger num, BigInteger denom) : num(std::move(num)), denom(std::move(denom)) {
    reduct();
  }

  Rational(const BigInteger& other) {
    num = other;
  }

  Rational(const int other) {
    num = other;
  }

  // binary operators
  bool operator==(const Rational& right) const {
    return (this->num * right.denom) == (this->denom * right.num);
  }

  bool operator<(const Rational& right) const {
    return (this->num * right.denom) < (this->denom * right.num);
  }

  bool operator!=(const Rational& right) const {
    return !(*this == right);
  }

  bool operator<=(const Rational& right) const {
    return (*this < right || *this == right);
  }

  bool operator>(const Rational& right) const {
    return !(*this <= right);
  }

  bool operator>=(const Rational& right) const {
    return !(*this < right);
  }

  // arithmetic operators
  Rational& operator+=(const Rational& other) {
    if (denom == other.denom) {
      num += other.num;
      reduct();
      return *this;
    }

    num *= other.denom;
    num += (other.num * denom);
    denom *= other.denom;

    reduct();

    return *this;
  }

  Rational& operator-=(const Rational& other) {
    if (denom == other.denom) {
      num -= other.num;
      return *this;
    }

    num *= other.denom;
    num -= (other.num * denom);
    denom *= other.denom;

    reduct();

    return *this;
  }

  Rational& operator*=(const Rational& other) {
    num *= other.num;
    denom *= other.denom;

    reduct();

    return *this;
  }

  Rational& operator/=(const Rational& other) {
    if (this->num == 0) {
      return *this;
    }
    //assert(other.num != 0);

    num *= other.denom;
    denom *= other.num;

    normaliseSigns();
    //assert(denom.sign == 1);
    reduct();

    return *this;
  }

  Rational operator+(const Rational& other) const {
    Rational res = *this;

    res += other;

    return res;
  }

  Rational operator-(const Rational& other) const {
    Rational res = *this;

    res -= other;

    return res;
  }

  Rational operator*(const Rational& other) const {
    Rational res = *this;

    res *= other;

    return res;
  }

  Rational operator/(const Rational& other) const {
    Rational res = *this;

    res /= other;

    return res;
  }

  Rational operator-() const {
    Rational res = *this;
    res.num.sign = (res.num.sign == 1) ? -1 : 1;

    return res;
  }

  // conversion operators
  explicit operator double() const {
    std::istringstream iss(asDecimal(53));

    double res;
    iss >> res;

    return res;
  }

  // i/o operators
  friend std::istream& operator>>(std::istream& in, Rational& real) {
    in >> real.num;
    real.denom = 1;

    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const Rational& real) {
    out << real.toString();

    return out;
  }
};

Rational abs(Rational v) {
  v.num.sign = 1;

  return v;
}

template<unsigned long Value>
struct Sqrt {
  template<int64_t L, int64_t R>
  struct SqrtHelper {
    static const int64_t M = (L + R + 1) / 2;
    static const bool COND = M * M < Value;
    static const bool STOP_POINT = L + 1 >= R;
    static const int64_t N = R * R > Value ? L : R;
    static const int64_t value = SqrtHelper<STOP_POINT ? N : (COND ? M : L),
                                        STOP_POINT ? N : (COND ? R : M)>::value;
  };
  template<int64_t M>
  struct SqrtHelper<M, M> {
    static const int64_t value = M;
  };
  static const int64_t value = SqrtHelper<0, V>::value;
};

template<int64_t N, int64_t K>
struct IsPrimeHelper {
  static const bool value = N % K != 0 && IsPrimeHelper<N, K - 1>::value;
};

template<int64_t N>
struct IsPrimeHelper<N, 2> {
  static const bool value = N % 2 != 0;
};

template<int64_t N>
struct IsPrimeHelper<N, 1> {
  static const bool value = N % 2 != 0;
};

template<unsigned long Value>
struct isPrime {
  static const bool value = IsPrimeHelper<V, Sqrt<V>::value>::value;
};

template<>
struct isPrime<2> {
  static const bool value = true;
};

template<size_t N>
class Residue {
  int value = 0;

 public:
  const static size_t N_ = N;

  Residue() = default;

  static int normaliseValue(const int _value) {
    return (_value % static_cast<int>(N) + static_cast<int>(N)) % static_cast<int>(N);
  }

  explicit Residue(const int other) {
    value = normaliseValue(other);
  }

  explicit operator int() const {
    return value;
  }

  Residue<N>& operator+=(const Residue<N>& other) {
    value += other.value;
    value = normaliseValue(value);

    return *this;
  }

  Residue<N>& operator-=(const Residue<N>& other) {
    value -= other.value;
    value = normaliseValue(value);

    return *this;
  }

  Residue<N>& operator*=(const Residue<N>& other) {
    value *= other.value;
    value = normaliseValue(value);

    return *this;
  }

  Residue<N>& operator/=(const Residue<N>& other) {
    static_assert(isPrime<N>::value, "Division in residue field with non-prime base.");
    //assert(other.value != 0);

    int inv_v = other.getInvertedValue();

    value *= inv_v;
    value = normaliseValue(value);

    return *this;
  }

  Residue<N> operator+(const Residue<N>& other) const {
    Residue<N> new_val = *this;
    new_val += other;

    return new_val;
  }

  Residue<N> operator-(const Residue<N>& other) const {
    Residue<N> new_val = *this;
    new_val -= other;

    return new_val;
  }

  Residue<N> operator*(const Residue<N>& other) const {
    Residue<N> new_val = *this;
    new_val *= other;

    return new_val;
  }

  Residue<N> operator/(const Residue<N>& other) const {
    Residue<N> new_val = *this;
    new_val /= other;

    return new_val;
  }

  Residue<N> operator-() const {
    Residue<N> res = *this;
    res.value = normaliseValue(-res.value);

    return res;
  }

  bool operator==(const Residue<N>& other) const {
    return value == other.value;
  }

  bool operator<(const Residue<N>& other) const {
    return value < other.value;
  }

  bool operator>(const Residue<N>& other) const {
    return value > other.value;
  }

  bool operator<=(const Residue<N>& other) const {
    return value <= other.value;
  }

  bool operator>=(const Residue<N>& other) const {
    return value >= other.value;
  }

  bool operator!=(const Residue<N>& other) const {
    return value != other.value;
  }

  friend std::ostream& operator<<(std::ostream& out, const Residue<N> rsd) {
    out << rsd.value;

    return out;
  }

  int ex_gcd(int a, int b, int& x, int& y) const {
    if (a == 0) {
      x = 0;
      y = 1;
      return b;
    }
    int x1, y1;
    int d = ex_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
  }

  [[nodiscard]] int getInvertedValue() const {
    int u, v;
    ex_gcd(value, static_cast<int>(N), u, v);
    //assert(res_gcd == 1);

    int res_v = normaliseValue(u);
    //assert(normaliseValue(value * res_v) == 1);

    return normaliseValue(res_v);
  }

  Residue<N> rabs() const {
    Residue<N> res = *this;
    res.value = std::abs(res.value);

    return res;
  }
};

template<size_t N>
Residue<N> abs(const Residue<N> obj) {
  return obj.rabs();
}

template<size_t M, size_t N, typename Field=Rational>
class Matrix {
 public:
  vector<vector<Field>> vec = vector<vector<Field>>(M, vector<Field>(N, Field(0)));

  template<typename T>
  Matrix(std::initializer_list<std::initializer_list<T>> lst) {
    ////std::cerr << M << " " << N << "| ";
    int i = 0, j = 0;
    for (auto& rw: lst) {
      for (auto& obj: rw) {
        vec[i][j] = Field(obj);
        ++j;
      }
      ++i;
      j = 0;
    }
  }

  Matrix() = default;

  vector<Field> operator[](const size_t index) const {
    return vec[index];
  }

  vector<Field>& operator[](const size_t index) {
    return vec[index];
  }

  Matrix<M, N, Field>& operator+=(const Matrix<M, N, Field>& other) {
    for (int i = 0; i < static_cast<int>(M); ++i) {
      for (int j = 0; j < static_cast<int>(N); ++j) {
        vec[i][j] += other.vec[i][j];
      }
    }

    return *this;
  }

  Matrix<M, N, Field> operator+(const Matrix<M, N, Field>& other) const {
    Matrix<M, N, Field> res = *this;
    res += other;

    return res;
  }

  Matrix<M, N, Field>& operator-=(const Matrix<M, N, Field>& other) {
    for (int i = 0; i < static_cast<int>(M); ++i) {
      for (int j = 0; j < static_cast<int>(N); ++j) {
        vec[i][j] -= other.vec[i][j];
      }
    }

    return *this;
  }

  Matrix<M, N, Field> operator-(const Matrix<M, N, Field>& other) const {
    Matrix<M, N, Field> res = *this;
    res -= other;

    return res;
  }

  Matrix<M, N, Field>& operator*=(const Field other) {
    for (int i = 0; i < static_cast<int>(M); ++i) {
      for (int j = 0; j < static_cast<int>(N); ++j) {
        vec[i][j] *= other;
      }
    }

    return *this;
  }

  Matrix<M, N, Field>& operator/=(const Field other) {
    *this *= (Field(1) / other);

    return *this;
  }

  Matrix<M, N, Field> operator*(const Field other) const {
    Matrix<M, N, Field> res = *this;
    res *= other;

    return res;
  }

  Matrix<M, N, Field> operator/(const Field other) const {
    Matrix<M, N, Field> res = *this;
    res /= other;

    return res;
  }

  bool operator==(const Matrix<M, N, Field>& other) const {
    for (int i = 0; i < static_cast<int>(M); ++i) {
      for (int j = 0; j < static_cast<int>(N); ++j) {
        if (vec[i][j] != other[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix<M, N, Field>& other) const {
    return !(*this == other);
  }

  template<size_t K>
  Matrix<M, K, Field> operator*(const Matrix<N, K, Field>& other) const {
    Matrix<M, K, Field> res;
    for (int i = 0; i < static_cast<int>(M); ++i) {
      for (int j = 0; j < static_cast<int>(K); ++j) {
        Field val = Field(0);
        for (int k = 0; k < static_cast<int>(N); ++k) {
          val += vec[i][k] * other.vec[k][j];
        }
        res[i][j] = val;
      }
    }

    return res;
  }

  template<size_t K>
  Matrix<M, K, Field>& operator*=(const Matrix<N, K, Field>& other) {
    *this = (*this) * other;

    return *this;
  }

 private:
  // private methods
  void putCofactor(Matrix<M - 1, M - 1, Field>& t, int q_row, int q_col) const {
    static_assert(N == M, "Cofactor can be calculated only for square matrix.");
    int i = 0;
    int j = 0;

    for (int row = 0; row < static_cast<int>(M); ++row) {
      for (int col = 0; col < static_cast<int>(M); ++col) {
        if (row != q_row && col != q_col) {
          t[i][j++] = vec[row][col];

          if (j == M - 1) {
            j = 0;
            ++i;
          }
        }
      }
    }
  }

  static void swap(vector<vector<Field>> vec_c, int row1, int row2, int col) {
    for (int i = 0; i < col; ++i) {
      std::swap(vec_c[row1][i], vec_c[row2][i]);
    }
  }

 public:
  // public methods
  Field det() const {
    static_assert(M == N, "Determinant can be calculated only for square matrix.");

    vector<vector<Field>> vec_c = vec;
    Field val = Field(1);

    for (int i = 0; i < static_cast<int>(M); ++i) {
      int k = i;
      for (int j = i + 1; j < static_cast<int>(M); ++j) {
        if (abs(vec_c[j][i]) > abs(vec_c[k][i])) {
          // todo: create abs func for Residue
          k = j;
        }
      }
      if (vec_c[k][i] == Field(0)) {
        val = Field(0);
        break;
      }

      std::swap(vec_c[i], vec_c[k]);
      if (i != k) {
        val = -val;
        // todo: overload unary minus for Residue
      }
      val *= vec_c[i][i];
      for (int j = i + 1; j < static_cast<int>(M); ++j) {
        vec_c[i][j] /= vec_c[i][i];
      }
      for (int j = 0; j < static_cast<int>(M); ++j) {
        if (j != i && vec_c[j][i] != Field(0)) {
          for (int l = i + 1; l < static_cast<int>(M); ++l) {
            vec_c[j][l] -= vec_c[i][l] * vec_c[j][i];
          }
        }
      }
    }

    return val;
  }

  Matrix<N, M, Field> transposed() const {
    Matrix<N, M, Field> matrixToTranspose;
    for (int i = 0; i < static_cast<int>(M); ++i) {
      for (int j = 0; j < static_cast<int>(N); ++j) {
        matrixToTranspose[j][i] = vec[i][j];
      }
    }

    return matrixToTranspose;

  }

  Matrix<M, M, Field> getAdjoint() const {
    static_assert(N == M, "Adjoint matrix can be calculated only for square matrix.");

    int sign;
    Matrix<M, M, Field> adjointMatrix;
    if (M == 1) {
      adjointMatrix[0][0] = Field(1);
      return adjointMatrix;
    }
    Matrix<M - 1, M - 1, Field> holderMatrix;

    for (int row = 0; row < static_cast<int>(M); ++row) {
      for (int col = 0; col < static_cast<int>(M); ++col) {
        putCofactor(holderMatrix, row, col);

        sign = ((row + col) % 2 == 0) ? 1 : -1;

        adjointMatrix[col][row] = holderMatrix.det() * Field(sign);
      }
    }

    return adjointMatrix;
  }

  [[nodiscard]] int rank() const {
    vector<vector<Field>> vec_c = vec;
    int rank = static_cast<int>(N);

    for (int row = 0; row < rank; ++row) {
      if (vec_c[row][row] != Field(0)) {
        for (int col = 0; col < static_cast<int>(M); ++col) {
          if (col != row) {
            Field mult = vec_c[col][row] / vec_c[row][row];

            for (int i = 0; i < rank; ++i) {
              vec_c[col][i] -= mult * vec_c[row][i];
            }
          }
        }
      } else {
        bool reduce = true;

        for (int i = row + 1; i < static_cast<int>(M); ++i) {
          if (vec_c[i][row] != Field(0)) {
            swap(vec_c, row, i, rank);
            reduce = false;
            break;
          }
        }

        if (reduce) {
          --rank;

          for (int i = 0; i < static_cast<int>(M); ++i) {
            vec_c[i][row] = vec_c[i][rank];
          }
        }

        --row;
      }
    }

    return rank;
  }

  void invert() {
    static_assert(N == M, "Only square matrix can be inverted.");
    //assert(det() != Field(0));

    *this = this->inverted();
  }

  Matrix<M, M, Field> inverted() const {
    static_assert(N == M, "Only square matrix can be inverted.");
    int M_ = static_cast<int>(M);
    vector<vector<Field>> vec_c(M, vector<Field>(2 * M, Field(0)));
    for (int i = 0; i < M_; ++i) {
      for (int j = 0; j < M_; ++j) {
        vec_c[i][j] = vec[i][j];
      }
    }

    Field val;
    for (int i = 0; i < M_; ++i) {
      for (int j = 0; j < M_; ++j) {
        if (i == j) {
          vec_c[i][j + M_] = Field(1);
        } else {
          vec_c[i][j + M_] = Field(0);
        }
      }
    }

    for (int i = 0; i < M_; ++i) {
      //assert(vec_c[i][i] != Field(0));

      for (int j = 0; j < M_; ++j) {
        if (i != j) {
          val = vec_c[j][i] / vec_c[i][i];
          for (int k = 0; k < 2 * M_; ++k) {
            vec_c[j][k] -= val * vec_c[i][k];
          }
        }

      }
    }

    for (int i = 0; i < M_; ++i) {
      for (int j = M_; j < 2 * M_; ++j) {
        vec_c[i][j] /= vec_c[i][i];
      }
    }

    Matrix<M, M, Field> ans;
    for (int i = 0; i < M_; ++i) {
      for (int j = M_; j < 2 * M_; ++j) {
        ans[i][j - M_] = vec_c[i][j];
      }
    }

    return ans;
  }

  Field trace() const {
    static_assert(N == M, "Trace can be calculated only for square matrix.");

    Field val = Field(0);
    for (int i = 0; i < static_cast<int>(M); ++i) {
      val += vec[i][i];
    }

    return val;
  }

  vector<Field> getRow(size_t row) {
    //assert(row >= 0 && row < M);
    return vec[row];
  }

  vector<Field> getColumn(size_t col) {
    //assert(col >= 0 && col < N);
    vector<Field> columnVec(N);
    for (int i = 0; i < static_cast<int>(N); ++i) {
      columnVec[i] = vec[col][i];
    }

    return columnVec;
  }

  // i/o operators overloading
  friend std::ostream& operator<<(std::ostream& out, Matrix<M, N, Field> mtr) {
    for (int i = 0; i < static_cast<int>(M); ++i) {
      for (int j = 0; j < static_cast<int>(N); ++j) {
        out << mtr[i][j] << " ";
      }
      out << "\n";
    }

    return out;
  }
};

template<size_t M, size_t N, typename Field=Rational>
Matrix<M, N, Field> operator*(const Field left, const Matrix<M, N, Field> right) {
  return right * left;
}

template<size_t N, typename Field=Rational>
using SquareMatrix = Matrix<N, N, Field>;

#endif //MATRIX__MATRIX_H_


