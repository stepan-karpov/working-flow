#include <iostream>
#include <vector>
#include <cmath>
#include <cassert> // to assert division by zero

class BigInteger;

using std::vector;

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

  size_t getSize() const {
    return digits_.size();
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

  

  BigInteger& operator+=(const BigInteger& other) {
    size_t max_size = std::max(digits_.size(), other.digits_.size());
    if (sign_ != other.sign_) {
      sign_ = other.sign_;
      (*this) -= other;
      sign_ = (sign_ == 1) ? -1 : 1;
      if (cmp_wo_sign(0) == 0) {
        sign_ = 1;
      }
    } else {
      digits_.resize(max_size + 2);
      for (int i = 0; i < getSize(); ++i) {
        digits_[i] += (i < other.getSize()) ? other.digits_[i] : 0;
      }
 
      for (int i = 0; i < getSize() - 1; ++i) {
        if (digits_[i] >= BASE_) {
          digits_[i] -= BASE_;
          digits_[i + 1]++;
        }
      }
      normalise();
    }
    if (cmp_wo_sign(0) == 0) {
      sign_ = 1;
    }
    return *this;
  }

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
        if (digits_[i] < other.digits_[i]) {
          return -1;
        } else if (digits_[i] > other.digits_[i]) {
          return 1;
        }
      }
    }
 
    return 0;
  }

  BigInteger& operator-=(const BigInteger& other) {
    vector<long long> other_arr = other.digits_;
    if (sign_ != other.sign_) {
      sign_ = other.sign_;
      (*this) += other;
      sign_ = (sign_ == 1) ? -1 : 1;
      if (cmp_wo_sign(0) == 0) {
        sign_ = 1;
      }
    } else {
      if (cmp_wo_sign(other) == 0) {
        digits_.resize(0);
        sign_ = 1;
        return *this;
      } else if (cmp_wo_sign(other) == -1) {
        other_arr = digits_;
        digits_ = other.digits_;
        sign_ = (sign_ == 1) ? -1 : 1;
      }
      size_t max_size = std::max(digits_.size(), other_arr.size());
      digits_.resize(max_size + 2);
      for (int i = 0; i < getSize(); ++i) {
        digits_[i] -= (i < static_cast<int>(other_arr.size())) ? other_arr[i] : 0;
      }
 
      for (int i = 0; i < getSize() - 1; ++i) {
        if (digits_[i] < 0) {
          digits_[i] += BASE;
          digits_[i + 1]--;
        }
      }
 
      normalise();
      if (cmp_wo_sign(0) == 0) {
        sign_ = 1;
      }
    }

    return *this;
  }

  void normalise() {
    int new_size = getSize();
    for (int i = getSize() - 1; i >= 0; --i) {
      if (digits_[i] == 0) {
        new_size = i;
      } else {
        break;
      }
    }
    digits_.resize(new_size);
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

/*

1) Representing Rational object as Decimal in function asDecimal
always rounds up floating 0.***k5 to 0.***(k + 1)

*/