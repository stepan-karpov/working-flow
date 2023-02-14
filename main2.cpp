#include <iostream>
#include <vector>
#include <regex>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void PrintMatches(std::string s, std::regex expression) {

  std::sregex_iterator it(s.begin(), s.end(), expression);
  std::sregex_iterator lastMatch;

  while (it != lastMatch) {
    std::cout << it->str() << "\n";
    ++it;
  }

}

int main() {
  Init();
  
  std::string s = "sd2456 sdf sdfhf sdfdf sdsf gff skf";
  std::regex expression("(^| )s[dk]f($| )");
  std::sregex_iterator it(s.begin(), s.end(), expression);
  std::sregex last_match;

  if (it != last_match) {
    std::cout << "ok" << '\n';
  }
  return 0;
}