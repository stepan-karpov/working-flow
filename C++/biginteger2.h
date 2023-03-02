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
 
  void Normalise() {
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
      Normalise();
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
 
      Normalise();
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
    Normalise();
 
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
    res.Normalise();
 
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
      curr.Normalise();
 
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
    res.Normalise();
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