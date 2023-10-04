#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include "nfa.cpp"

int main() {
  if (interface_output) {
    std::cout << "!the initial automaton vertex should have number 0\n";
    std::cout << "Input number of vertexes: ";
  }
  long long vertexes; std::cin >> vertexes;
  DFA nfa(vertexes);
  nfa.ReadNFA();

  int testsize; std::cin >> testsize;

  for (int i = 0; i < testsize; ++i) {
    std::string text; std::cin >> text;
    if (nfa.CanRecognize(text)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}