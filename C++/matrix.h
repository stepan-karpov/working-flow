#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <cassert> // to assert division by zero
#include <sstream>

class BigInteger;

BigInteger operator*(BigInteger, const BigInteger&);
BigInteger operator+(BigInteger, const BigInteger&);
BigInteger operator-(BigInteger, const BigInteger&);
BigInteger operator*(BigInteger, const BigInteger&);
BigInteger operator/(BigInteger, const BigInteger&);
BigInteger operator%(BigInteger, const BigInteger&);

bool operator>=(const BigInteger&, const BigInteger&);
bool operator>(const BigInteger&, const BigInteger&);
bool operator<=(const BigInteger&, const BigInteger&);
bool operator==(const BigInteger&, const BigInteger&);
bool operator!=(const BigInteger&, const BigInteger&);

std::ostream& operator<<(std::ostream&, const BigInteger&);
std::istream& operator>>(std::istream&, BigInteger&);


class BigInteger {
 private:
  std::vector<int> digits_;
  short sign_ = 1;
  static const int BASE_ = 1'000'000'000;
  static const int MAX_DIGITS_ = 9; // 9 is log10(BASE_)
  // 1 is positive or 0
  // -1 is negative

  // this function is auxiliary to implement division
  // it finds the largest value that can be divided by divider
  // and less than divisible
  // it works not for all numbers, but it works well if we're using it in division function
  int FindMaxMult(const BigInteger& divisible, const BigInteger& divider) {
    int l = -1;
    int r = 1'000'000'000;
    
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (divider * m > divisible) {
        r = m;
      } else {
        l = m;
      }
    }
    return l;
  }

  void DeleteLeadingZeros() {
    while (!digits_.empty() && digits_[digits_.size() - 1] == 0) {
      digits_.pop_back();
    }
  }

  BigInteger& FindSum(const BigInteger& addition) {
    // since now both values are positive
    while (digits_.size() < addition.digits_.size()) {
      digits_.push_back(0);
    }
    digits_.push_back(0);
    for (int i = 0; i < int(digits_.size()); ++i) {
      int cur_addition = 0;
      if (i < int(addition.digits_.size())) {
        cur_addition = addition.digits_[i];
      }
      digits_[i] += cur_addition;
    }
    int in_mind = 0;
    for (int i = 0; i < int(digits_.size()); ++i) {
      digits_[i] += in_mind;
      in_mind = digits_[i] / BASE_;
      digits_[i] %= BASE_;
    }
    this->DeleteLeadingZeros();
    return *this;
  }

  BigInteger& FindDifference(const BigInteger& addition) {
    // since now both values are positive ans this - addition >= 0
    for (int i = 0; i < int(digits_.size()); ++i) {
      if (i >= int(addition.digits_.size())) { break; }
      if (digits_[i] < addition.digits_[i]) {
        int j = i + 1;
        while (digits_[j] == 0) {
          ++j;
        }
        --digits_[j];
        for (int k = i; k < j; ++k) {
          digits_[k] += BASE_ - 1;
        }
        ++digits_[i];
        digits_[i] -= addition.digits_[i];
      } else {
        digits_[i] -= addition.digits_[i];
      }
    }
    this->DeleteLeadingZeros();
    return *this;
  }

  // returns true if |a| > |b|
  bool ModuloComparison(const BigInteger& a, const BigInteger& b) {
    if (b.digits_.size() != a.digits_.size()) {
      return (b.digits_.size() < a.digits_.size());
    }
    for (int i = int(b.digits_.size()) - 1; i >= 0; --i) {
      if (b.digits_[i] != a.digits_[i]) {
        return (b.digits_[i] < a.digits_[i]);
      }
    }
    return false;
  }

 public:
  // some constructors
  
  BigInteger(long long x) {
    sign_ = (x >= 0 ? 1 : -1);
    x = abs(x);
    while (x != 0) {
      digits_.push_back(x % BASE_);
      x /= BASE_;
    }
  }

  // BigInteger(const BigInteger& init)  = default;
  BigInteger()  = default;

  // some operator redefinitions 

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  friend std::istream& operator>>(std::istream&, BigInteger&);


  BigInteger& operator+=(const BigInteger& addition) {
    if (*this == 0) {
      *this = addition; // this copying is necessary
      return *this;
    }
    if (addition == 0) {
      return *this;
    }

    if (*this > 0 && addition > 0) {
      this->FindSum(addition);
      return *this;
    }
    if (*this < 0 && addition < 0) {
      this->FindSum(addition);
      return *this;
    }

    if (this->ModuloComparison(*this, addition)) {
      this->FindDifference(addition);
      return *this;
    }

    BigInteger temp = addition; // this copying is unavoidable
    temp.FindDifference(*this);
    *this = temp;
    return *this;
  }

  BigInteger& operator-=(const BigInteger& addition) {
    if (addition == 0) {
      return *this;
    }
    if (*this == 0) {
      *this = -addition; // this copying is necessary
      return *this;
    }

    if (*this < 0 && addition > 0) {
      this->FindSum(addition);
      return *this;
    }
    if (*this > 0 && addition < 0) {
      this->FindSum(addition);
      return *this;
    }

    if (this->ModuloComparison(*this, addition)) {
      this->FindDifference(addition);
      return *this;
    }

    BigInteger temp = addition;
    temp.FindDifference(*this);
    *this = temp;
    if (int(digits_.size()) != 0) {
      this->sign_ = -this->sign_;
    }
    return *this;
  }

  BigInteger& operator*=(const BigInteger& multiplier) { // simple silly multiplication
    // this multiplication has O(digits_.size() * multiplier.digits_.size()) complexity
    if (multiplier == 0 || *this == 0) {
      *this = 0;
      return *this;
    }
    int v1 = digits_.size();
    int v2 = multiplier.digits_.size();
    std::vector<long long> answer(v1 + v2 + 2, 0);
    for (int i = 0; i < v2; ++i) {
      int cur_pos = i;
      for (int j = 0; j < v1; ++j) {
        long long temp = digits_[j];
        temp *= multiplier.digits_[i];
        answer[cur_pos] += temp;
        ++cur_pos;
      }
      long long in_mind = 0;
      for (int j = 0; j < v1 + v2 + 2; ++j) {
        answer[j] += in_mind;
        in_mind = answer[j] / BASE_;
        answer[j] %= BASE_;
      }
    }
    digits_.resize(v1 + v2 + 2);
    std::copy(answer.begin(), answer.end(), digits_.begin());
    this->DeleteLeadingZeros();
    if (multiplier.sign_ == -1) {
      sign_ = -sign_;
    }
    return *this;
  }

  BigInteger& operator/=(const BigInteger& divider_const) {
    assert(divider_const != 0 && "division by zero!!");
    if (*this == 0) {
      *this = 0;
      return *this;
    }

    int s1 = sign_;
    BigInteger divider = divider_const;
    int s2 = divider_const.sign_;
    sign_ = 1;
    divider.sign_ = 1;

    // since now code works like both values are positive
    std::vector<int> answer;
    BigInteger t = digits_[digits_.size() - 1];
    for (int i = (digits_.size() - 2); i >= -1; --i) {
      long long min_mult = FindMaxMult(t, divider);
      BigInteger max_value = divider * min_mult;
      answer.push_back(min_mult);
      t -= max_value;
      if (i >= 0) {
        t *= BASE_;
        t += digits_[i];
      }
    }
    digits_.clear();
    for (int i = int(answer.size()) - 1; i >= 0; --i) {
      digits_.push_back(answer[i]);
    }
    while (!digits_.empty() && digits_[digits_.size() - 1] == 0) {
      digits_.pop_back();
    }
    // sign corrections
    if (s1 * s2 == -1) {
      sign_ = -1;
    }
    return *this;
  }


  BigInteger& operator%=(const BigInteger& divider) {
    BigInteger temp = (*this / divider);
    *this -= temp * divider;
    return *this;
  }
  
  BigInteger operator-() const {
    BigInteger answer = *this;
    if (int(digits_.size()) == 0) {
      return answer;
    }
    answer.sign_ = -(answer.sign_);
    return answer;
  }

  // this is prefix increment
  BigInteger& operator++() {
    *this += 1;
    return *this;
  }

  // this is postfix increment
  BigInteger operator++(int) {
    BigInteger copy = *this;
    ++*this;
    return copy;
  }
  
  // this is prefix decrement
  BigInteger& operator--() {
    *this -= 1;
    return *this;
  }

  // this is postfix decrement
  BigInteger operator--(int) {
    BigInteger copy = *this;
    --*this;
    return copy;
  }

  explicit operator bool() const {
    return (*this != 0);
  }

  explicit operator int() const {
    long long x = (long long) (*this);
    return x;
  }

  explicit operator long long() const {
    long long x = 0;
    for (int i = int(digits_.size()) - 1; i >= 0; --i) {
      x *= BASE_;
      x += digits_[i];
    }
    if (sign_ == -1) {
      x = -x;
    }
    return x;
  }

  // some built-in functions for extended functional

  std::string toString() const {
    std::string answer = "";
    if (*this == 0) {
      return "0";
    }
    if (*this < 0) {
      answer = "-";
    }
    std::ostringstream output;
    output << *this;
    return output.str();
  }
  
  // some comparisons

  friend bool operator<(const BigInteger& value1, const BigInteger& value2);
  friend bool operator==(const BigInteger& value1, const BigInteger& value2);

};

// literal suffixes

BigInteger operator""_bi(unsigned long long x) { return BigInteger(x); }

BigInteger operator""_bi(const char* x) {
  std::istringstream input(x);
  BigInteger temp;
  input >> temp;
  return temp;
}

bool operator<(const BigInteger& value1, const BigInteger& value2) {
  if (value1.sign_ == -1 && value2.sign_ == 1) {
    return true;
  }
  if (value1.sign_ == 1 && value2.sign_ == -1) {
    return false;
  }
  bool reverse = (value1.sign_ == -1 && value1.sign_ == -1);
  if (value1.digits_.size() != value2.digits_.size()) {
    if (reverse) {
      return (value1.digits_.size() > value2.digits_.size());
    }
    return (value1.digits_.size() < value2.digits_.size());
  }
  for (int i = int(value1.digits_.size()) - 1; i >= 0; --i) {
    if (value1.digits_[i] != value2.digits_[i]) {
      if (reverse) {
        return (value1.digits_[i] > value2.digits_[i]);
      }
      return (value1.digits_[i] < value2.digits_[i]);
    }
  }
  return false;
}

BigInteger operator+(BigInteger value1, const BigInteger& value2) {
  value1 += value2;
  return value1;
}
BigInteger operator-(BigInteger value1, const BigInteger& value2) {
  value1 -= value2;
  return value1;
}

BigInteger operator*(BigInteger value1, const BigInteger& value2) {
  value1 *= value2;
  return value1;
}

BigInteger operator/(BigInteger value1, const BigInteger& value2) {
  value1 /= value2;
  return value1;
}

BigInteger operator%(BigInteger value1, const BigInteger& value2) {
  value1 %= value2;
  return value1;
}

bool operator>=(const BigInteger& value1, const BigInteger& value2) {
  return !(value1 < value2);
}

bool operator>(const BigInteger& value1, const BigInteger& value2) {
  return (value2 < value1);
}

bool operator<=(const BigInteger& value1, const BigInteger& value2) {
  return !(value1 > value2);
}

bool operator==(const BigInteger& value1, const BigInteger& value2) {
  if (value1.digits_.size() != value2.digits_.size()) {
    return false;
  }
  for (int i = 0; i < int(value1.digits_.size()); ++i) {
    if (value1.digits_[i] != value2.digits_[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const BigInteger& value1, const BigInteger& value2) {
  return !(value1 == value2);
}

std::ostream& operator<<(std::ostream& output, const BigInteger& value) {
  if (value.digits_.size() == 0) {
    output << 0;
    return output;
  }
  if (value.sign_ == -1) {
    output << "-";
  }
  if (value.digits_.empty()) {
    std::cout << "0";
    return output;
  }
  for (int i = int(value.digits_.size()) - 1; i >= 0; --i) {
    std::string cur_digit = std::to_string(value.digits_[i]);
    if (i != int(value.digits_.size()) - 1) {
      while (int(cur_digit.size()) < BigInteger::MAX_DIGITS_) {
        cur_digit = "0" + cur_digit;
      }
    }
    output << cur_digit;
  }
  return output;
}

std::istream& operator>>(std::istream& input, BigInteger& value) {
  std::string s;
  input >> s;
  if (int(s.size() > 0)) {
    value.sign_ = (s[0] == '-' ? -1 : 1);
  } else {
    value.sign_ = 1;
  }
  value.digits_.clear();
  std::string cur_digit = "";
  for (int i = int(s.size()) - 1; i >= (s[0] == '-'); --i) {
    if (int(cur_digit.size()) == BigInteger::MAX_DIGITS_) {
      std::reverse(cur_digit.begin(), cur_digit.end());
      value.digits_.push_back(stoi(cur_digit));
      cur_digit = s[i];
    } else {
      cur_digit += s[i];
    }
  }
  if (cur_digit != "") {
    std::reverse(cur_digit.begin(), cur_digit.end());
      value.digits_.push_back(stoi(cur_digit));
  }
  return input;
}

class Rational {
 private:
  // about negative-fraction implementation
  // this class always stores POSITIVE numerator_ and denominator_
  // ans sign_ shows the sign of a fraction
  // it is better not to change sign of numerator_/denominator_
  // but there are some cases where it is possible (like operations with fractions)
  BigInteger numerator_;
  BigInteger denominator_;
  short sign_ = 1;
  static const int DEFAULT_PRECISION_ = 20;
  
  void ReduceFraction() {
    BigInteger gcd = FindGCD(numerator_, denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;
  }

  static BigInteger FindGCD(BigInteger a, BigInteger b) {
    while (b != 0) {
      BigInteger temp = a % b;
      a = b;
      b = temp;
    }
    return a;
  }

 public:
  
  // some constructors

  Rational(const BigInteger& value) {
    if (value < 0) {
      sign_ = -1;
      numerator_ = value;
      numerator_ = -numerator_;
    } else {
      sign_ = 1;
      numerator_ = value;
    }
    denominator_ = 1;
  }
  Rational(const int& value) : numerator_(abs(value)), 
                                      denominator_(1), sign_(value >= 0 ? 1 : -1) {}
  Rational() : numerator_(0), denominator_(1), sign_(1) {}

  // some operator functions

  Rational operator-() const {
    Rational answer = *this;
    if (numerator_ == 0) {
      return answer;
    }
    answer.sign_ = -(answer.sign_);
    return answer;
  }

  Rational& operator/=(const Rational& divider) {
    if (*this == 0) {
      *this = 0;
      return *this;
    }
    numerator_ *= divider.denominator_;
    denominator_ *= divider.numerator_;
    sign_ *= divider.sign_;
    this->ReduceFraction();
    return *this;
  }

  Rational& operator*=(const Rational& divider) {
    numerator_ *= divider.numerator_;
    denominator_ *= divider.denominator_;
    sign_ *= divider.sign_;
    this->ReduceFraction();
    return *this;
  }

  Rational& operator+=(const Rational& addition) {
    if (sign_ < 0 && addition.sign_ < 0) {
      numerator_ = (-numerator_) * addition.denominator_ + denominator_ * (-addition.numerator_);
    } else if (sign_ < 0 && addition.sign_ > 0) {
      numerator_ = (-numerator_) * addition.denominator_ + denominator_ * addition.numerator_;
    } else if (sign_ > 0 && addition.sign_ < 0) {
      numerator_ = numerator_ * addition.denominator_ + denominator_ * (-addition.numerator_);
    } else {
      numerator_ = numerator_ * addition.denominator_ + denominator_ * addition.numerator_;
    }
    denominator_ *= addition.denominator_;
    sign_ = (numerator_ >= 0 ? 1 : -1);
    if (numerator_ < 0) {
      numerator_ = -numerator_;
    }
    if (numerator_ == 0) {
      sign_ = 1;
    }
    this->ReduceFraction();
    return *this;
  }

  Rational& operator-=(const Rational& addition) {
    *this += (-addition);
    return *this;
  }

  friend bool operator<(const Rational&, const Rational&); // this function is friend to decrease time comlexity
  friend bool operator==(const Rational&, const Rational&);  // this function is friend to decrease time comlexity

  // some built-in functions for extended functional

  std::string toString() {
    std::string answer = "";
    if (sign_ == -1) {
      answer = "-";
    }
    this->ReduceFraction();
    answer += numerator_.toString();
    if (denominator_ != 1) {
      answer += "/" + denominator_.toString();
    }

    return answer;
  }

  std::string asDecimal(int precision=0) {
    std::string answer = "";
    if (sign_ == -1) {
      answer = "-";
    }
    this->ReduceFraction();
    if (precision == 0) {
      BigInteger integer_part = numerator_ / denominator_;
      BigInteger remain = numerator_ % denominator_;
      if (remain * 2 >= denominator_) {
        ++integer_part;
      }
      answer += integer_part.toString();
      return answer;
    }
    BigInteger numerator_copy = numerator_;
    BigInteger fraction = numerator_ % denominator_;
    for (int i = 0; i < precision + 1; ++i) {
      numerator_copy *= 10;
    }
    numerator_copy /= denominator_;
    if (numerator_copy % 10 >= 5) {
      numerator_copy /= 10;
      ++numerator_copy;
    } else {
      numerator_copy /= 10;
    }
    std::string num_string = numerator_copy.toString();
    std::string answer_reversed = "";
    int p = num_string.size() - 1;
    for (int i = 0; i < precision; ++i) {
      if (p < 0) {
        answer_reversed += "0";
      } else {
        answer_reversed += num_string[p];
        --p;
      }
    }
    answer_reversed += ".";
    while (p >= 0) {
      answer_reversed += num_string[p];
      --p;
    }
    for (int i = int(answer_reversed.size() - 1); i >= 0; --i) {
      answer += answer_reversed[i];
    }
    if (answer[0] == '.') {
      answer = "0" + answer;
    }
    if (answer[0] == '-' && answer[1] == '.') {
      answer[0] = '0';
      answer = '-' + answer;
    }
    bool not_zero_exists = false;
    for (int i = 0; i < int(answer.size()); ++i) {
      if (answer[i] != '0' && answer[i] != '.' && answer[i] != '-') {
        not_zero_exists = true;
        break;
      }
    }
    if (!not_zero_exists && answer[0] == '-') {
      answer = answer.substr(1, answer.size() - 1);
    }
    return answer;
  }

  explicit operator double() const {
    Rational temp = *this;
    std::string s = temp.asDecimal(DEFAULT_PRECISION_);
    double answer = std::stod(s);
    return answer;
  }
};

bool operator<(const Rational& value1, const Rational& value2) { 
  if (value1.sign_ == -1 && value2.sign_== 1) {
    return true;
  }
  if (value1.sign_ == 1 && value2.sign_ == -1) {
    return false;
  }
  return (value1.numerator_ * value2.denominator_ < value2.numerator_ * value1.denominator_);
}

bool operator>(const Rational& value1, const Rational& value2) { 
  return (value2 < value1);  
}

bool operator==(const Rational& value1, const Rational& value2) {
  // if (value1.numerator_ == 0) {
  //   value1.sign_ = 1;
  // }
  // if (value2.numerator_ == 0) {
  //   value2.sign_ = 1;
  // }
  if (value1.sign_ != value2.sign_) {
    return false;
  }
  return (value1.numerator_ * value2.denominator_ == value2.numerator_ * value1.denominator_);
}

bool operator>=(const Rational& value1, const Rational& value2) {
  return !(value1 < value2);
}

bool operator<=(const Rational& value1, const Rational& value2) {
  return !(value1 > value2);
}

bool operator!=(const Rational& value1, const Rational& value2) {
  return !(value1 == value2);
}

Rational operator/(Rational value1, const Rational& value2) {
  value1 /= value2;
  return value1;
}

Rational operator*(Rational value1, const Rational& value2) {
  value1 *= value2;
  return value1;
}

Rational operator+(Rational value1, const Rational& value2) {
  value1 += value2;
  return value1;
}

Rational operator-(Rational value1, const Rational& value2) {
  value1 -= value2;
  return value1;
}

using std::vector;

template<size_t M, size_t N, typename Field = Rational>
class Matrix;

template<size_t M, size_t N, typename Field>
class Matrix {
 private:
  std::array<std::array<Field, N>, M> matrix_;

 public:
  Matrix() {}
  Matrix(std::array<std::array<Field, N>, M> a) : matrix_(a) {}
  Matrix(vector<vector<Field>>& a);
  Matrix(const Matrix<M, N, Field>& initial_matrix);

  std::array<Field, M>& operator[](size_t index) { return matrix_[index]; }
  std::array<Field, M> operator[](size_t index) const { return matrix_[index]; }

  Matrix<M, N, Field>& operator+=(const Matrix<M, N, Field>& to_add);
  Matrix<M, N, Field>& operator*=(Field to_multiply);
  std::array<Field, N> getRow(size_t index) { return matrix_[index]; };
  std::array<Field, M> getColumn(size_t index);

  // return number of swaps
  size_t triangulate();
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
Matrix<M, N, Field>::Matrix(vector<vector<Field>>& a) {
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      matrix_[i][j] = a[i][j];
    }
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

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field>& Matrix<M, N, Field>::operator*=(Field to_multiply) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix_[i][j] *= to_multiply;
    }
  }
  return *this;
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

template<size_t N, typename Field>
Field trace(const Matrix<N, N, Field>& matrix) {
  Field ans = 0;
  for (size_t i = 0; i < N; ++i) {
    ans += matrix[i][i];
  }
  return ans;
}

template<size_t M, size_t N, typename Field>
Matrix<N, M, Field> transposed(const Matrix<M, N, Field>& matrix) {
  Matrix<N, M, Field> ans;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      ans[j][i] = matrix[i][j];
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
      Rational cur_delta = -(matrix_[cur_row][cur_col] / matrix_[to_change][cur_col]);
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
size_t rank(const Matrix<M, N, Field>& matrix) {
  Matrix<M, N, Field> temp_matrix = matrix;
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

template<size_t N, typename Field>
Field det(const Matrix<N, N, Field>& matrix) {
  Matrix<N, N, Field> temp_matrix = matrix;
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

