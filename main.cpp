
#include <bits/stdc++.h>
using namespace std;

bool checkInclusion(string s1, string s2) {
    std::unordered_map<char, int> window;
    std::unordered_map<char, int> s1_map;
    for (int i = 0; i < s1.size(); ++i) {
        ++window[s2[i]];
        ++s1_map[s1[i]];
    }

    if (s1_map == window) { return true; }

    for (int i = s1.size(); i < s2.size(); ++i) {
        --window[s2[i - s1.size()]];
        if (window[s2[i - s1.size()]] == 0) {
          window.erase(s2[i - s1.size()]);
        }
        ++window[s2[i]];
        if (s1_map == window) { return true; }
    }
    return false;
}

int main() {
  std::cout << checkInclusion("ab", "eidbaooo") << "\n";
}