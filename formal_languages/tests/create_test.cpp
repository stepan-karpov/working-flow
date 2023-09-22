#include <bits/stdc++.h>
using namespace std;

using ll = long long;

std::random_device rd;
std::mt19937 gen(rd());

// returns random value from [low, high]
int random(long long low, long long high) {
  std::uniform_int_distribution<> dist(low, high);
  return dist(gen);
}

std::string CreateString(int size) {
  const std::string ALPH = "ab";
  // const std::string ALPH = "abcdefghijklmopq";
  std::string ans = "";

  for (int i = 0; i < size; ++i) {
    ans += ALPH[random(0, ALPH.size() - 1)];
  }

  return ans;
}

bool is_prime(int n){
  bool f = true;
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0){
      f = false;
      break;
    }
  }
  return f;   
}

int main() {
  std::mt19937 mt(time(nullptr)); 

  const std::string kAlph = "`abcdef";
  int vertex_size = random(2, 2);
  int edges_size = random(2, 5);

  std::cout << vertex_size << "\n" << edges_size << "\n";

  for (int i = 0; i < edges_size; ++i) {
    int u = random(0, vertex_size - 1);
    int v = random(0, vertex_size - 1);
    int symb = random(0, 2);
    std::cout << u << " " << v << " " << kAlph[symb] << "\n";
  }

  int term = random(0, vertex_size);
  std::cout << term << "\n";
  std::set<int> term_vertex;

  while (term_vertex.size() != term) {
    term_vertex.insert(random(0, vertex_size - 1));
  }

  for (auto ind : term_vertex) {
    std::cout << ind << " ";
  }

  int queries = 1000;

  std::cout << queries << "\n";

  for (int i = 0; i < queries; ++i) {
    std::cout << CreateString(random(0, 15)) << "\n";
  }

  return 0;
}