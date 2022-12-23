#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <cassert> // to assert division by zero
#include <sstream>

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

using std::vector;

template<size_t M, size_t N, typename Field = Rational>
class Matrix;

template<size_t N>
class Residue {
 private:
  size_t value_;
  bool is_prime_ = false;

  static bool checkPrime(size_t num) {
    for (size_t i = 2; i < sqrt(num) + 1; ++i) {
      if (num % i == 0) {
        return false;
      }
    }
    return true;
  }

 public:
  Residue(int value);
  Residue() : value_(0), is_prime_(checkPrime(N)) {}

  const size_t Value() const { return value_; }
  size_t& Value() { return value_; }

  Residue<N>& operator+=(const Residue<N>& to_add);
  Residue<N>& operator-=(const Residue<N>& to_add);
  Residue<N>& operator*=(const Residue<N>& to_add);
  Residue<N>& operator/=(const Residue<N>& to_add);
  
  Residue<N>& operator++();
  Residue<N> operator++(int);
  Residue<N>& operator--();
  Residue<N> operator--(int);
  
  explicit operator int() const {
    return value_;
  }
};


template<size_t N>
Residue<N>& Residue<N>::operator++() {
  *this += 1;
  return *this;
}

template<size_t N>
Residue<N> Residue<N>::operator++(int) {
  Residue copy = *this;
  ++*this;
  return copy;
}

template<size_t N>
Residue<N>& Residue<N>::operator--() {
  *this -= 1;
  return *this;
}

template<size_t N>
Residue<N> Residue<N>::operator--(int) {
  Residue copy = *this;
  --*this;
  return copy;
}

template<size_t N>
Residue<N> operator-(const Residue<N>& value) {
  return N - value.Value();
}

template<size_t N>
Residue<N>& Residue<N>::operator+=(const Residue<N>& to_add) {
  value_ += to_add.value_;
  value_ %= N;
  return *this;
}

template<size_t N>
Residue<N>& Residue<N>::operator*=(const Residue<N>& to_add) {
  value_ *= to_add.value_;
  value_ %= N;
  return *this;
}

template<size_t N>
Residue<N>& Residue<N>::operator/=(const Residue<N>& divider) {
  assert(is_prime_ && "division not in the field!!!");
  assert(divider.value_ != 0 && "division by zero!!!");
  size_t x = divider.value_;
  size_t n = N - 2;
  size_t res = 1;
  while (n != 0) {
    if (n & 1) {
      res = res * x % N;
    }
    x = x * x % N;
    n >>= 1;
  }
  value_ = res * value_ % N;
  return *this;
}

template<size_t N>
Residue<N>& Residue<N>::operator-=(const Residue<N>& to_add) {
  value_ += (-to_add).value_;
  value_ %= N;
  return *this;
}

template<size_t N>
Residue<N> operator+(Residue<N> value1, const Residue<N>& value2) {
  value1 += value2;
  return value1;
}

template<size_t N>
Residue<N> operator/(Residue<N> value1, const Residue<N>& value2) {
  value1 /= value2;
  return value1;
}

template<size_t N>
Residue<N> operator-(Residue<N> value1, const Residue<N>& value2) {
  value1 -= value2;
  return value1;
}

template<size_t N>
Residue<N> operator*(Residue<N> value1, const Residue<N>& value2) {
  value1 *= value2;
  return value1;
}

template<size_t N>
std::ostream& operator<<(std::ostream& output, const Residue<N>& to_output) {
  output << to_output.Value();
  return output;
}

// template<size_t N>
// std::istream& operator>>(std::istream& input, Residue<N>& to_input) {
//   input >> to_input.value;
//   return input;
// }

template<size_t N>
Residue<N>::Residue(int to_init) : is_prime_(checkPrime(N)) {
  if (to_init >= 0) {
    value_ = to_init % N;
  } else {
    to_init = (-to_init) % N;
    value_ = N - to_init;
  }
}

template<size_t N>
bool operator<(const Residue<N>& value1, const Residue<N>& value2) { 
  return value1.Value() < value2.Value();
}

template<size_t N>
bool operator<(const Residue<N>& value1, int value2) { 
  return value1.Value() < value2;
}

template<size_t N>
bool operator>(const Residue<N>& value1, const Residue<N>& value2) { 
  return value2 < value1;
}

template<size_t N>
bool operator==(const Residue<N>& value1, const Residue<N>& value2) {
  return value2.Value() == value1.Value();
}

template<size_t N>
bool operator==(const Residue<N>& value1, int value2) {
  return value1.Value() == value2;
}

template<size_t N>
bool operator!=(const Residue<N>& value1, const Residue<N>& value2) {
  return !(value1 == value2);
}

template<size_t N>
bool operator!=(const Residue<N>& value1, int value2) {
  return !(value1 == value2);
}

template<size_t N>
bool operator<=(const Residue<N>& value1, const Residue<N>& value2) {
  return !(value1 > value2);
}

template<size_t N>
bool operator<=(const Residue<N>& value1, int value2) {
  return !(value1 > value2);
}

template<size_t N>
bool operator>=(const Residue<N>& value1, const Residue<N>& value2) {
  return !(value1 < value2);
}

template<size_t N>
bool operator>=(const Residue<N>& value1, int value2) {
  return !(value1 < value2);
}


template<size_t M, size_t N, typename Field>
class Matrix {
 private:
  std::array<std::array<Field, N>, M> matrix_;

 public:
  Matrix() {}
  Matrix(std::array<std::array<Field, N>, M> a) : matrix_(a) {}
  Matrix(const std::initializer_list<std::initializer_list<Field>>& a);
  Matrix(const Matrix<M, N, Field>& initial_matrix);

  std::array<Field, N>& operator[](size_t index) { return matrix_[index]; }
  std::array<Field, N> operator[](size_t index) const { return matrix_[index]; }
  Matrix<M, N, Field>& operator*=(const Field& scalar);

  Matrix<M, N, Field>& operator+=(const Matrix<M, N, Field>& to_add);
  std::array<Field, N> getRow(size_t index) { return matrix_[index]; };
  std::array<Field, M> getColumn(size_t index);
  size_t rank() const;
  Field trace();
  Field det() const;
  Matrix<N, M, Field> transposed() const;
  // return number of swaps
  size_t triangulate();

  Matrix<M, N, Field> inverted();
  void invert();
  void annihilate(size_t init, size_t to_annihilate, size_t column);
  void leadToOne(size_t row, size_t column);
  int findNotNullElement(size_t column, size_t start_with); // int, not size_t!! (-1 also possible)
  int findMinElement(size_t column, size_t start_with); // int, not size_t!! (-1 also possible)
};
template<size_t M, size_t N, typename Field>
Matrix<M, N, Field>::Matrix(const Matrix<M, N, Field>& initial_matrix) {
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      matrix_[i][j] = initial_matrix[i][j];
    }
  }
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field>::Matrix(const std::initializer_list<std::initializer_list<Field>>& a) {
  size_t i = 0, j = 0;
  for (auto& row: a) {
    for (auto& obj: row) {
      matrix_[i][j] = Field(obj);
      ++j;
    }
    ++i;
    j = 0;
  }
}

template<size_t M, size_t N, typename Field>
std::array<Field, M> Matrix<M, N, Field>::getColumn(size_t index) {
  std::array<Field, M> ans;
  for (size_t i = 0; i < M; ++i) {
    ans[i] = matrix_[i][index];
  }
  return ans;
}

template<size_t M, size_t N, size_t K, typename Field>
Matrix<M, K, Field> operator*(const Matrix<M, N, Field>& matrix1,
                              const Matrix<N, K, Field>& matrix2) {
  Matrix<M, K, Field> ans;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < K; ++j) {
      for (size_t k = 0; k < N; ++k) {
        ans[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  return ans;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field>& Matrix<M, N, Field>::operator+=(const Matrix<M, N, Field>& to_add) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix_[i][j] += to_add.matrix_[i][j];
    }
  }
  return *this;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator+(Matrix<M, N, Field> matrix1, const Matrix<M, N, Field>& matrix2) {
  matrix1 += matrix2;
  return matrix1;
}

template<size_t M, size_t N, typename Field>
std::ostream& operator<<(std::ostream& output, const Matrix<M, N, Field>& matrix) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      output << matrix[i][j] << ' ';
    }
    output << '\n';
  }
  return output;
}

template<size_t M, size_t N>
std::ostream& operator<<(std::ostream& output, const Matrix<M, N, Rational>& matrix) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      output << matrix[i][j].asDecimal(4) << ' ';
    }
    output << '\n';
  }
  return output;
}

template<size_t M, size_t N, typename Field>
Field Matrix<M, N, Field>::trace() {
  static_assert(N == M && "can't find a trace in not squared matrix");
  Field ans = 0;
  for (size_t i = 0; i < N; ++i) {
    ans += matrix_[i][i];
  }
  return ans;
}

template<size_t M, size_t N, typename Field>
Matrix<N, M, Field> Matrix<M, N, Field>::transposed() const {
  Matrix<N, M, Field> ans;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      ans[j][i] = matrix_[i][j];
    }
  }
  return ans;
}

template<size_t M, size_t N, typename Field>
size_t Matrix<M, N, Field>::triangulate() {
  size_t swaps = 0;
  size_t to_change = 0;
  for (size_t cur_col = 0; cur_col < N; ++cur_col) {
    int pivot = -1;
    for (size_t k = to_change; k < M; ++k) {
      Field temp = matrix_[k][cur_col];
      bool t = (temp != 0);
      if (t) {
        if (pivot == -1 || matrix_[k][cur_col] > matrix_[pivot][cur_col]) {
          pivot = int(k);
        }
      }
    }
    if (pivot == -1) { continue; }
    std::swap(matrix_[to_change], matrix_[pivot]);
    if (to_change != pivot) {
      ++swaps;
    }

    for (size_t cur_row = to_change + 1; cur_row < M; ++cur_row) {
      Field cur_delta = -(matrix_[cur_row][cur_col] / matrix_[to_change][cur_col]);
      for (size_t k = 0; k < N; ++k) {
        matrix_[cur_row][k] += matrix_[to_change][k] * cur_delta;
      }
    }
    ++to_change;
  }
  size_t to_swap = 0;

  for (size_t cur_col = 0; cur_col < N; ++cur_col) {
    bool contains_not_null = false;
    for (size_t cur_row = 0; cur_row < M; ++cur_row) {
      if (matrix_[cur_row][cur_col] != 0) {
        contains_not_null = true;
        break;
      }
    }
    if (!contains_not_null) {
      for (size_t cur_row = 0; cur_row < M; ++cur_row) {
        std::swap(matrix_[cur_row][to_swap], matrix_[cur_row][cur_col]);
        ++swaps;
      }
      ++to_swap;
    }
  }
  return swaps;
}

template<size_t M, size_t N, typename Field>
size_t Matrix<M, N, Field>::rank() const {
  Matrix<M, N, Field> temp_matrix = *this;
  temp_matrix.triangulate();
  size_t ans = 0;
  size_t cur_col = 0;
  for (size_t cur_row = 0; cur_row < M; ++cur_row) {
    while (cur_col < N && temp_matrix[cur_row][cur_col] == 0) {
      ++cur_col;
    }
    if (cur_col < N && temp_matrix[cur_row][cur_col] != 0) {
      ++ans;
    }
  }
  return ans;
}

template<size_t M, size_t N, typename Field>
Field Matrix<M, N, Field>::det() const {
  static_assert(M == N && "can't find determinant in not squared matrix");
  Matrix<N, N, Field> temp_matrix = *this;
  size_t swaps = temp_matrix.triangulate();
  Field ans = 1;
  for (size_t i = 0; i < N; ++i) {
    ans *= temp_matrix[i][i];
  }
  if (swaps % 2 == 1) {
    ans = -ans;
  }
  return ans;
}

template<size_t M, size_t N, typename Field>
bool operator==(const Matrix<M, N, Field> matrix1, const Matrix<M, N, Field> matrix2) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (matrix1[i][j] != matrix2[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator-(const Matrix<M, N, Field>& matrix1, const Matrix<M, N, Field>& matrix2) {
  Matrix<M, N, Field> ans;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      ans[i][j] = matrix1[i][j] - matrix2[i][j];
    }
  }
  return ans;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field>& Matrix<M, N, Field>::operator*=(const Field& scalar) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix_[i][j] *= scalar;
    }
  }
  return *this;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator*(const Field& scalar, const Matrix<M, N, Field>& matrix) {
  Matrix<M, N, Field> answer = matrix;
  answer *= scalar;
  return answer; 
}

template<size_t M, size_t N, typename Field>
int Matrix<M, N, Field>::findNotNullElement(size_t column, size_t start_with) {
  for (size_t i = start_with; i < M; ++i) {
    if (matrix_[i][column] != 0) {
      return i;
    }
  }
  return -1;
}

template<size_t M, size_t N, typename Field>
int Matrix<M, N, Field>::findMinElement(size_t column, size_t start_with) {
  size_t answer = start_with;
  for (size_t i = start_with; i < M; ++i) {
    if (matrix_[i][column] < matrix_[i][start_with]) {
      answer = start_with;
    }
  }
  return answer;
}

template<size_t M, size_t N, typename Field>
void Matrix<M, N, Field>::annihilate(size_t init, size_t to_annihilate, size_t column) {
  Field to_multiply = -(matrix_[to_annihilate][column] / matrix_[init][column]);
  for (size_t i = 0; i < N; ++i) {
    matrix_[to_annihilate][i] += matrix_[init][i] * to_multiply;
  }
}

template<size_t M, size_t N, typename Field>
void Matrix<M, N, Field>::leadToOne(size_t row, size_t column) {
  Field to_multiply = Field(1) / matrix_[row][column];
  if (to_multiply == 1) { return; }
  for (size_t i = 0; i < N; ++i) {
    matrix_[row][i] *= to_multiply;
  }
}

template<size_t M, size_t N, typename Field>
void Matrix<M, N, Field>::invert() {
  static_assert(N == M && "can't invert not squared matrix");
  // static_assert(det() != 0 && "can't invert matrix with zero determinant");
  
  // assuming that N = M

  Matrix<N, 2 * N, Field> extended_matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      extended_matrix[i][j] = matrix_[i][j];
    }
  }

  for (int i = 0; i < N; ++i) {
    extended_matrix[i][i + N] = 1;
  }

  for (size_t cur_col = 0; cur_col < N; ++cur_col) {
    size_t to_swap = findMinElement(cur_col, cur_col);
    std::swap(matrix_[cur_col], matrix_[to_swap]);
    
    for (size_t cur_row = 0; cur_row < N; ++cur_row) {
      if (cur_col == cur_row) { continue; }
      extended_matrix.annihilate(cur_col, cur_row, cur_col);
    }
    std::cout << "col " << cur_col << "is done ->1 rest\n";
    extended_matrix.leadToOne(cur_col, cur_col);
    std::cout << "col " << cur_col << "is done\n";
  }

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix_[i][j] = extended_matrix[i][j + N];
    }
  }

}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> Matrix<M, N, Field>::inverted() {
  Matrix answer = *this;
  answer.invert();
  return answer;
}