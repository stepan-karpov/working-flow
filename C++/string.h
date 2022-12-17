#include <iostream>
#include <vector>
#include <cstring>

class String {
 private:
  char* array_ = nullptr;
  int size_ = 0;
  int capacity_ = 0;

 public:
  // Constructors and destructors

  String(int init_size, char to_fill): 
         array_(new char[init_size + 1]), size_(init_size), capacity_(init_size) {
    std::fill(array_, array_ + init_size, to_fill);
    array_[init_size] = '\0';
  }

  String (char new_string) {
    String temp(0, '\0');
    temp.push_back(new_string);
    *this = temp;
  }

  String(const char* c_style_string) {
    size_ = 0;
    while (c_style_string[size_] != '\0') {
      ++size_;
    }
    capacity_ = size_;
    array_ = new char[size_ + 1];
    std::copy(c_style_string, c_style_string + size_, array_);
    array_[size_] = '\0';
  }

  String(const String& initializer_string) :
         array_(new char[initializer_string.size_ + 1]), size_(initializer_string.size_), 
         capacity_(initializer_string.size_) {
    std::copy(initializer_string.array_, initializer_string.array_ + size_ + 1, array_);
  }

  String() {
    String empty = String(0, 'a');
    *this = empty;
  }

  ~String() {
    delete[] array_;
  }

  // Operator's redefinitions

  friend bool operator<(const String&, const String&);

  char& operator[](int index) {
    return array_[index];
  }

  char operator[](int index) const {
    return array_[index];
  }

  
  String& operator=(const String& new_string) {
    if (&new_string == this) return *this;
    if (capacity_ >= new_string.size_) {
      std::copy(new_string.array_, new_string.array_ + size_, array_);
      size_ = new_string.size_;
      return *this;
    } 
    delete[] array_;
    size_ = new_string.size_;
    capacity_ = new_string.size_;
    array_ = new char[size_ + 1];
    std::copy(new_string.array_, new_string.array_ + size_, array_);
    array_[size_] = '\0';
    return *this;
  }

  String& operator+=(const String& to_add) {
    int new_size = size_ + to_add.size_;
    if (capacity_ >= new_size) {
      std::copy(to_add.array_, to_add.array_ + to_add.size_, array_ + size_);
      array_[new_size] = '\0';
      size_ = new_size;
      return *this;
    }
    char* temp = new char[new_size + 1];
    std::copy(array_, array_ + size_, temp);
    std::copy(to_add.array_, to_add.array_ + to_add.size_, temp + size_);
    temp[new_size] = '\0';
    delete[] array_;
    array_ = temp;
    size_ = new_size;
    capacity_ = new_size;
    return *this;
  }

  String& operator+=(char to_add) {
    this->push_back(to_add);
    return *this;
  }

  // Some control functions

  void push_back(char to_push) {
    if (size_ == capacity_) {
      char* new_s = new char[2 * capacity_ + 1];
      capacity_ *= 2;
      std::copy(array_, array_ + size_, new_s);
      delete[] array_;
      array_ = new_s;
      array_[size_++] = to_push;
      array_[size_] = '\0';
    } else {
      array_[size_++] = to_push;
      array_[size_] = '\0';
    }
  }

  void pop_back() {
    array_[size_--] = '\0';
  }

  void shrink_to_fit() {
    capacity_ = size_;
    char* new_s = new char[capacity_ + 1];
    std::copy(array_, array_ + size_, new_s);
    delete[] array_;
    array_ = new_s;
    array_[size_] = '\0';
  }

  void clear() {
    size_ = 0;
    array_[size_] = '\n';
  }

  // Some substr functions

  String substr(int start, int length) const {
    String ans(length, '\0');
    std::copy(array_ + start, array_ + start + length, ans.array_);
    return ans;
  }

  size_t find(String& substring) const {
    if (substring.size() > size_) return length();
    for (int i = 0; i <= size_ - substring.size(); ++i) {
      bool ok = true;
      for (int j = i; j < i + substring.size(); ++j) {
        if (array_[j] != substring[j - i]) {
           ok = false;
           break;
        }
      }
      if (ok) return i;
    }
    return length();
  }

  size_t find(const char* substring) const {
    String t = substring;
    return find(t);
  }

  int rfind(String& substring) const {
    if (substring.size() > size_) return length();
    for (int i = size_ - substring.size(); i >= 0; --i) {
      bool ok = true;
      for (int j = i; j < i + substring.size(); ++j) {
        if (array_[j] != substring[j - i]) {
           ok = false;
           break;
        }
      }
      if (ok) return i;
    }
    return length();
  }

  int rfind(const char* substring) const {
    String t = substring;
    return rfind(t);
  }

  // Some info-functions

  int length() const { return size_; }
  int size() const { return size_; }
  int capacity() const { return capacity_; }
  char& front() { return array_[0]; }
  char front() const { return array_[0]; }
  char& back() { return array_[size_ - 1]; }
  char back() const { return (size_ == 0 ? array_[0] : array_[size_ - 1]); }
  char* data() const { return array_; }
  bool empty() const { return (size_ == 0); }

};

String operator+(String add1, const String& add2) {
  add1 += add2;
  return add1;
}

bool operator<(const String& str1, const String& str2) {
  for (int i = 0; i < std::min(str1.size_, str2.size_); ++i) {
    if (str1[i] == str2[i]) continue;
    return (str1[i] < str2[i] ? true : false);
  }
  return str1.size_ < str2.size_;
}

bool operator>=(const String& str1, const String& str2) {
  return !(str1 < str2);
}

bool operator>(const String& str1, const String& str2) {
  return str2 < str1;
}

bool operator<=(const String& str1, const String& str2) {
  return !(str1 > str2);
}

bool operator==(const String& str1, const String& str2) {
  if (str1.size() != str2.size()) return false;
  for (int i = 0; i < int(str1.size()); ++i) {
    if (str1[i] != str2[i]) return false;
  }
  return true;
}

bool operator!=(const String& str1, const String& str2) {
  if (str1.size() != str2.size()) return true;
  for (int i = 0; i < int(str1.size()); ++i) {
    if (str1[i] != str2[i]) return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& os, const String& cur_string) {
  for (int i = 0; i < int(cur_string.size()); ++i) {
    os << cur_string[i];
  }
  return os;
}

std::istream& operator>>(std::istream& is, String& cur_string) {
  String temp(0, '\0');
  char c;
  while (true) {
    c = is.get();
    if (c == '\n' || c == EOF) {
      break;
    }
    temp.push_back(c);
  }
  cur_string = temp;
  return is;
}