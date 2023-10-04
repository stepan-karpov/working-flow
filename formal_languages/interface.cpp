#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>



int main() {
  if (interface_output) {
    std::cout << "!the initial automaton vertex should have number 0\n";
    std::cout << "Input number of vertexes: ";
  }
  long long vertexes; std::cin >> vertexes;
  DFA nfa(vertexes);
  nfa.ReadNFA();
  std::cout << "===========\n\ninitializing eps-removing algorithm\n";
  nfa.RemoveEps();
  std::cout << "\neps-free graph\n\n";
  nfa.OutputGraph();
  std::cout << "===========\n\ninitializing Thompson's construction\n";
  nfa.InitializeThompsonsAlgorithm();
  std::cout << "\nDKA graph\n\n";
  nfa.OutputGraph();
  std::cout << "===========\n\ninitializing DFA->MIN-CDFA algorithm\n";
  nfa.MakeComplete();
  nfa.Minimize();
  std::cout << "\nmin CDFA graph\n\n";
  nfa.OutputGraph();
}