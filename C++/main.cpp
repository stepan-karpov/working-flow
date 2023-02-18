#include "string.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>  // for std::ignore
#include <type_traits>

void test1() {
    String s("abcdef");
    assert(s.length() == 6);
    assert(s[0] == 'a');
    assert(s[3] == 'd');
    assert(s[5] == 'f');
    assert(s.back() == 'f');
    assert(s.front() == 'a');
    assert(s[6] == '\0');

    s[1] = 'x';
    s.back() = 'y';
    s.front() = 'y';
    assert(s[0] == 'y');
    assert(s[5] == 'y');
    assert(s[1] == 'x');
}

void test2() {
    const String s("abcdef");
    assert(s.length() == 6);
    assert(s[0] == 'a');
    assert(s[3] == 'd');
    assert(s[5] == 'f');
    assert(s.back() == 'f');
    assert(s.front() == 'a');
    assert(s[6] == '\0');

    assert((
        !std::is_assignable_v<decltype(static_cast<const String&>(String())[0]),
                              char>));
    assert((!std::is_assignable_v<
            decltype(static_cast<const String&>(String()).front()), char>));
    assert((!std::is_assignable_v<
            decltype(static_cast<const String&>(String()).back()), char>));

    String s2("abc");
    const String& s3 = s2;
    s2.front() = 'c';
    s2.back() = 'a';
    assert(s3.front() == 'c' && "front() must return a reference");
    assert(s3.back() == 'a' && "back() must return a reference");

    char* data2 = s2.data();
    const char* data3 = s3.data();
    assert(strlen(data2) == 3);
    assert(strlen(data3) == 3);
    data2[0] = 'z';
    assert(*data3 == 'z');
    assert(s2.front() == 'z');
    assert(s3.front() == 'z');
}

void test3() {
    String s("aaa");
    for (long long i = 0; i < 500'000; ++i) {
        s.push_back('a');
    }
    {
        String ss = s;
        assert(ss.length() == 500'003);
        assert(s[500'000] == 'a');
        ss[500'000] = 'b';
    }
    assert(s.length() == 500'003);
    assert(s[500'000] == 'a');

    String ss = s;
    for (long long i = 0; i < 500'000; ++i) {
        s.pop_back();
    }

    assert(s.length() == 3);
    assert(ss.length() == 500'003);
    ss = s;
    s = String("abc");
    assert(ss.length() == 3);
    assert(ss[2] == 'a');

    for (long long i = 0; i < 500'000; ++i) {
        const String sss(1000, 'a');
        String sz = sss;
        s += sz.back();
    }

    // intended to check: s = s, using "*&" hack to supress the warning :)
    s = *&s;
    assert(s.length() == 500'003);
    assert(s[500'002] == 'a');
    assert(s[266'532] == 'a');

    (s += String(100, 'b')) += String(100, 'c');
    assert(s.length() == 500'203);
    assert(s.back() == 'c');

    for (long long i = 0; i < 150; ++i) {
        s.pop_back();
    }
    assert(s.back() == 'b');

    s = ss = s;
    (ss = s) = ss;
}

void test4() {
    std::istringstream iss("abcdefg\nABCDE");

    String s;
    assert(s.empty());

    iss >> s;
    assert(s.length() == 7);

    String ss;
    iss >> ss;
    assert(!ss.empty());
    assert(ss.length() == 5);
    assert((s + ss).length() == 12);

    auto sum = ss + s;
    sum.pop_back();
    assert(sum.length() == 11);

    sum[0] = 'x';
    assert(ss.length() == 5);
    assert(s.length() == 7);

    std::ostringstream oss;
    oss << ('!' + sum + '?');

    assert(oss.str() == "!xBCDEabcdef?");
}

void test5() {
    String s = "abcde";

    auto& ss = s += 'f';

    ss += 'g';

    std::ostringstream oss;
    oss << ss;

    assert(oss.str() == "abcdefg");
    assert(s.length() == 7);

    {
        auto& ss = (s = *&s);
        assert(ss[5] == 'f');
        auto sss = ss;
        ss.clear();
        assert(sss.length() == 7);
    }
    assert(ss.empty());
}

void test6() {
    const String s = "122333444455555";
    //  0123456789ABCDE

    assert(s.find("44") == 6);
    assert(s.rfind("44") == 8);

    assert(
        s.find("12345") ==
        (std::is_same_v<String, std::string> ? std::string::npos : s.length()));

    assert(s.substr(5, 4) == "3444");

    decltype(s.substr(1, 1)) ss = s;
    ss[0] = '0';
    assert(s[0] == '1');

    decltype(ss = ss) sss = ss;
    sss[0] = '2';
    assert(ss[0] == '2');

    decltype(ss += 'a') ssss = ss;
    ssss.front() = '3';
    assert(ss.front() == '3');

    {
        String s = "###$#$#$#$$###***$*#######@@##???#$$";
        assert(s.find("#$$") == 8);
        assert(s.rfind("#$$") == s.length() - 3);
    }
}

long long number_of_new = 0;  // NOLINT

void* operator new(std::size_t size) {
    ++number_of_new;
    void* p = malloc(size);  // NOLINT
    if (p == nullptr) {
        throw std::bad_alloc();
    }
    return p;
}

void* operator new[](std::size_t size) {
    ++number_of_new;
    void* p = malloc(size);  // NOLINT
    if (p == nullptr) {
        throw std::bad_alloc();
    }
    return p;
}

void* operator new[](std::size_t size,
                     const std::nothrow_t& /*unused*/) noexcept {
    ++number_of_new;
    return malloc(size);  // NOLINT
}
void* operator new(std::size_t size,
                   const std::nothrow_t& /*unused*/) noexcept {
    ++number_of_new;
    return malloc(size);  // NOLINT
}

void operator delete(void* ptr) noexcept {
    free(ptr);  // NOLINT
}
void operator delete(void* ptr, size_t /*unused*/) noexcept {
    free(ptr);  // NOLINT
}
void operator delete(void* ptr, const std::nothrow_t& /*unused*/) noexcept {
    free(ptr);  // NOLINT
}
void operator delete[](void* ptr) noexcept {
    free(ptr);  // NOLINT
}
void operator delete[](void* ptr, size_t /*unused*/) noexcept {
    free(ptr);  // NOLINT
}
void operator delete[](void* ptr, const std::nothrow_t& /*unused*/) noexcept {
    free(ptr);  // NOLINT
}

void test_allocations() {
    number_of_new = 0;

    String s1("abc");
    assert(number_of_new <= 1 && "String s(\"abc\")");
    number_of_new = 0;

    String s2(5, 'c');
    assert(number_of_new <= 1 && "String s(5, \'c\')");
    number_of_new = 0;

    String s3(s2);
    assert(number_of_new <= 1 && "String s(String other)");
    number_of_new = 0;

    s2 = s1;
    assert(number_of_new <= 1 && "s2=s1");
    number_of_new = 0;

    s3.push_back('q');
    assert(number_of_new <= 1 && "push_back");
    number_of_new = 0;

    s3.pop_back();
    assert(number_of_new == 0 && "pop_back");
    number_of_new = 0;

    String s4("a");
    number_of_new = 0;
    s4 += s2;
    assert(number_of_new <= 1 && "s4+=s2");
    s4 += s2 += s2 += s2;
    s4 += "defe";
    String s5("def");
    number_of_new = 0;

    s4.find(s5);
    assert(number_of_new == 0 && "s4.find (s2)");
    number_of_new = 0;

    s4.rfind(s2);
    assert(number_of_new == 0 && "s4.rfind (s2)");
    number_of_new = 0;

    s4.substr(2, 5);
    assert(number_of_new <= 1 && "For substr you need only one allocation");
    number_of_new = 0;

    s4.clear();
    assert(number_of_new == 0 && "You shouldn't reallocate memory on clear()");
    number_of_new = 0;

    String s6("abcdefg");
    for (size_t i = 0; i < 15; ++i) {
        s6.push_back('a');
    }
    number_of_new = 0;
    s6.shrink_to_fit();
    assert(s6.size() == s6.capacity());
    assert(number_of_new <= 1);

    number_of_new = 0;

    std::ignore = s6.data();
    assert(number_of_new == 0 && "You don't need allocations for data() call");
}

void test_comparisons() {
    {
        const String s = "aboba";
        const String t = "abiba";
        assert(t < s);
        assert(!(t > s));
        assert(!(t >= s));
        assert(t <= s);
        assert(!(t == s));
        assert(t != s);

        assert("abiba" < t);
        assert("abuba" > t);
        assert("aboba" == t);
    }

    {
        String s = String("abobabiba");
        String t = String("aboba");
        assert(t < s);
        assert(!(t > s));
        assert(!(t >= s));
        assert(t <= s);
        assert(!(t == s));
        assert(t != s);

        s = String("aboba");
        t = String("");
        assert(t < s);
        assert(!(t > s));
        assert(!(t >= s));
        assert(t <= s);
        assert(!(t == s));
        assert(t != s);
    }

    String s = String(10'000'000, 'a');
    String t = String(5'000'000, 'a');
    for (size_t i = 0; i < 1'000'000; ++i) {
        s[9'999'999 - i] = 'b';
        assert(s != t);
    }
}

long long main() {
    test1();
    std::cerr << "Test 1 (basic) passed." << std::endl;

    test2();
    std::cerr << "Test 2 (constness) passed." << std::endl;

    test3();
    std::cerr << "Test 3 passed." << std::endl;

    test4();
    std::cerr << "Test 4 passed." << std::endl;

    test5();
    std::cerr << "Test 5 passed." << std::endl;

    test6();
    std::cerr << "Test 6 passed." << std::endl;

    test_allocations();
    std::cerr << "Test 7 (allocations) passed." << std::endl;

    std::cout << 0 << std::endl;
}