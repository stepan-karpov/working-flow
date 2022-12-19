#include <iostream>
#include <vector>
#include <cstring>
#pragma once

class String;
bool operator==(const String&, const String&);

class String {
 private:
  char* array_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

 public:
  String(int init_size, char to_fill)
      : array_(allocate_memory(init_size + 1)),
        size_(init_size),
        capacity_(init_size) {
    std::fill(array_, array_ + init_size, to_fill);
    array_[init_size] = '\0';
  }

  String (char new_string)
      : array_(allocate_memory(2)), size_(1), capacity_(1) {
    array_[0] = new_string;
    array_[1] = '\0';
  }

  String(const char* c_style_string)
      : size_(std::strlen(c_style_string)),
        capacity_(size_) {
    array_ = allocate_memory(size_ + 1);
    std::copy(c_style_string, c_style_string + size_, array_);
    array_[size_] = '\0';
  }

  String(const String& initializer_string)
      : array_(allocate_memory(initializer_string.size_ + 1)), 
        size_(initializer_string.size_), 
        capacity_(initializer_string.size_) {
    std::copy(initializer_string.array_, initializer_string.array_ + size_ + 1, array_);
  }

  String() = default;
  ~String() { delete[] array_; }

  char& operator[](int index) { return array_[index]; }
  char operator[](int index) const { return array_[index]; }

  String& operator=(const String& new_string);
  String& operator+=(const String& to_add);
  void swap(String&);

  char* allocate_memory(int size);

  String& operator+=(char to_add);

  void pop_back() { array_[size_--] = '\0'; }
  void push_back(char to_push);
  void shrink_to_fit();
  void clear();
  void resize(size_t new_capacity);

  String substr(int start, int length) const;

  bool does_word_starts_in_position(int position, const String& substring, const String& string) const;
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
    if (does_word_starts_in_position(i, substring, *this)) {
      return i;
    }
  }
  return length();
}

size_t String::find(const String& substring) const {
  if (substring.size() > size_) return length();
  for (size_t i = 0; i <= size_ - substring.size(); ++i) {
    if (does_word_starts_in_position(i, substring, *this)) {
      return i;
    }
  }
  return length();
}

char* String::allocate_memory(int size) { return new char[size]; }

void String::clear() {
  size_ = 0;
  array_[size_] = '\n';
}

String String::substr(int start, int length) const {
  String ans;
  ans.resize(length);
  std::copy(array_ + start, array_ + start + length, ans.array_);
  return ans;
}

bool String::does_word_starts_in_position(int position, const String& substring, const String& string) const {
  for (size_t i = position; i < position + substring.size(); ++i) {
    if (string[i] != substring[i - position]) {
      return false;
    }
  }
  return true;
}

void String::shrink_to_fit() {
  capacity_ = size_;
  char* new_s = allocate_memory(capacity_ + 1);
  std::copy(array_, array_ + size_, new_s);
  delete[] array_;
  array_ = new_s;
  array_[size_] = '\0';
}

void String::resize(size_t new_capacity) {
  char* new_array = allocate_memory(new_capacity + 1);
  capacity_ = new_capacity;
  size_ = new_capacity;
  if (array_ != nullptr) {
    std::copy(array_, array_ + size_, new_array);
    delete array_;
  }
  array_ = new_array;
  array_[size_] = '\0';
}

void String::push_back(char to_push) {
  if (size_ == capacity_) {
    char* new_s = allocate_memory(capacity_ * 2 + 1);
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

String& String::operator+=(char to_add) {
  push_back(to_add);
  return *this;
}

String& String::operator=(const String& new_string) {
  if (*this == new_string) {
    return *this;
  }
  String copy = new_string;
  swap(copy);
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
  char* new_array = allocate_memory(new_size + 1);
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

String operator+(String to_add1, const String& add2) {
  to_add1 += add2;
  return to_add1;
}

bool operator<(const String& string1, const String& string2) {
  for (size_t i = 0; i < std::min(string1.size(), string2.size()); ++i) {
    if (string1[i] < string2[i]) return false;
  }
  return string1.size() < string2.size();
}

bool operator>=(const String& string1, const String& string2) { return !(string1 < string2); }
bool operator>(const String& string1, const String& string2) { return string2 < string1; }
bool operator<=(const String& string1, const String& string2) { return !(string1 > string2); }

bool operator==(const String& string1, const String& string2) {
  if (string1.size() != string2.size()) return false;
  for (int i = 0; i < int(string1.size()); ++i) {
    if (string1[i] != string2[i]) return false;
  }
  return true;
}

bool operator!=(const String& string1, const String& string2) {
  if (string1.size() != string2.size()) return true;
  for (int i = 0; i < int(string1.size()); ++i) {
    if (string1[i] != string2[i]) return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& output, const String& cur_string) {
  output << cur_string.data();
  return output;
}

std::istream& operator>>(std::istream& input, String& cur_string) {
  String temp_output(0, '\0');
  char c;
  c = input.get();
  while (!std::isspace(c)) {
    if (c == '\n' || c == EOF) {
      break;
    }
    temp_output.push_back(c);
    c = input.get();
  }
  cur_string = temp_output;
  return input;
}