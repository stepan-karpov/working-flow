#pragma once
#include <iostream>
#include <vector>
#include <cstring>


class String {
 private:
  char* array_;
  size_t size_;
  size_t capacity_;

 public:
  String(size_t init_size, char to_fill)
      : array_(new char[init_size + 1]),
        size_(init_size),
        capacity_(init_size) {
    std::fill(array_, array_ + init_size, to_fill);
    array_[init_size] = '\0';
  }

  String (char new_string)
      : array_(new char[2]), size_(1), capacity_(1) {
    array_[0] = new_string;
    array_[1] = '\0';
  }

  String(const char* c_style_string)
      : size_(std::strlen(c_style_string)),
        capacity_(size_) {
    array_ = new char[size_ + 1];
    std::copy(c_style_string, c_style_string + size_, array_);
    array_[size_] = '\0';
  }

  String(const String& initializer_string)
      : array_(new char[initializer_string.size_ + 1]), 
        size_(initializer_string.size_), 
        capacity_(initializer_string.size_) {
    std::copy(initializer_string.array_,
              initializer_string.array_ + size_ + 1, array_);
  }

  String() : array_(new char[1]), size_(0), capacity_(0) { array_[0] = '\0'; };
  
  ~String() { delete[] array_; }

  char& operator[](int index) { return array_[index]; }
  char operator[](int index) const { return array_[index]; }

  String& operator=(const String& new_string);
  String& operator+=(const String& to_add);
  void swap(String&);

  char* relocate_memory(char* old_array, size_t new_size, size_t old_size);

  String& operator+=(char to_add);

  void pop_back() { array_[size_--] = '\0'; }
  void push_back(char to_push);
  void shrink_to_fit();
  void clear();
  void resize(size_t new_capacity);

  String substr(size_t start, size_t length) const;

  bool is_word(int, const String&, const String&) const;
  size_t find(const String& substring) const;
  size_t rfind(const String& substring) const;

  size_t length() const { return size_; }
  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  char& front() { return array_[0]; }
  const char& front() const { return array_[0]; }
  char& back() { return array_[size_ - 1]; }
  const char& back() const { return (array_[size_ - 1]); }
  char* data() { return array_; }
  const char* data() const { return array_; }
  bool empty() const { return (size_ == 0); }

};

size_t String::rfind(const String& substring) const {
  if (substring.size() > size_) return length();
  for (int i = size_ - substring.size(); i >= 0; --i) {
    if (is_word(i, substring, *this)) {
      return i;
    }
  }
  return length();
}

size_t String::find(const String& substring) const {
  if (substring.size() > size_) return length();
  for (size_t i = 0; i <= size_ - substring.size(); ++i) {
    if (is_word(i, substring, *this)) {
      return i;
    }
  }
  return length();
}

char* String::relocate_memory(char* old_array, size_t new_size, size_t old_size) {
  char* new_link = new char[new_size];
  std::copy(old_array, old_array + old_size, new_link);
  delete[] old_array;
  return new_link;
}

void String::clear() {
  size_ = 0;
  array_[size_] = '\n';
}

String String::substr(size_t start, size_t length) const {
  String ans(length, '0');
  std::copy(array_ + start, array_ + start + length, ans.array_);
  return ans;
}

bool String::is_word(int position,
             const String& substring, const String& string) const {
  for (size_t i = position; i < position + substring.size(); ++i) {
    if (string[i] != substring[i - position]) {
      return false;
    }
  }
  return true;
}

void String::shrink_to_fit() {
  capacity_ = size_;
  array_ = relocate_memory(array_, capacity_ + 1, size_);
  array_[size_] = '\0';
}

void String::resize(size_t new_capacity) {
  char* new_array = new char[new_capacity + 1];
  capacity_ = new_capacity;
  size_ = new_capacity;
  if (array_ != nullptr) {
    std::copy(array_, array_ + size_, new_array);
    delete[] array_;
  }
  array_ = new_array;
  array_[size_] = '\0';
}

void String::push_back(char to_push) {
  if (size_ == capacity_) {
    array_ = relocate_memory(array_, capacity_ * 2 + 1, size_);
    capacity_ *= 2;
    array_[size_++] = to_push;
    array_[size_] = '\0';
  } else {
    array_[size_++] = to_push;
    array_[size_] = '\0';
  }
}

String& String::operator+=(char to_add) {
  push_back(to_add);
  return *this;
}

String& String::operator+=(const String& to_add) {
  size_t new_size = size_ + to_add.size_;
  if (capacity_ >= new_size) {
    std::copy(to_add.array_, to_add.array_ + to_add.size_, array_ + size_);
    array_[new_size] = '\0';
    size_ = new_size;
    return *this;
  }
  char* new_array = new char[new_size + 1];
  std::copy(array_, array_ + size_, new_array);
  std::copy(to_add.array_, to_add.array_ + to_add.size_, new_array + size_);
  new_array[new_size] = '\0';
  delete[] array_;
  array_ = new_array;
  size_ = new_size;
  capacity_ = new_size;
  return *this;
}

void String::swap(String& to_swap) {
  std::swap(array_, to_swap.array_);
  std::swap(size_, to_swap.size_);
  std::swap(capacity_, to_swap.capacity_);
}

String operator+(String current_string, const String& to_add) {
  current_string += to_add;
  return current_string;
}

bool operator<(const String& first, const String& second) {
  for (size_t i = 0; i < std::min(first.size(), second.size()); ++i) {
    if (first[i] < second[i]) return false;
  }
  return first.size() < second.size();
}

bool operator>=(const String& first, const String& second)
               { return !(first < second); }
bool operator>(const String& first, const String& second)
              { return second < first; }
bool operator<=(const String& first, const String& second)
               { return !(first > second); }

bool operator==(const String& first, const String& second) {
  if (first.size() != second.size()) return false;
  for (size_t i = 0; i < first.size(); ++i) {
    if (first[i] != second[i]) return false;
  }
  return true;
}

bool operator!=(const String& first, const String& second) {
  if (first.size() != second.size()) return true;
  for (size_t i = 0; i < first.size(); ++i) {
    if (first[i] != second[i]) return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& output, const String& to_output) {
  output << to_output.data();
  return output;
}

std::istream& operator>>(std::istream& input, String& to_input) {
  String answer(0, '\0');
  char c;
  c = input.get();
  while (!std::isspace(c) && c != EOF) {
    answer.push_back(c);
    c = input.get();
  }
  to_input = answer;
  return input;
}

String& String::operator=(const String& new_string) {
  if (*this == new_string) {
    return *this;
  }
  if (capacity_ >= new_string.size_) {
    std::copy(new_string.data(), new_string.data() + new_string.size(),
              array_);
    size_ = new_string.size_;

  }
  String copy = new_string;
  swap(copy);
  return *this;
}