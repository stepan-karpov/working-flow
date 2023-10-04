#include <bits/stdc++.h>
using namespace std;

const std::string kAlph = "`ab";

using ll = long long;

std::random_device rd;
std::mt19937 gen(rd());

// returns random value from [low, high]
int random(long long low, long long high) {
  std::uniform_int_distribution<> dist(low, high);
  return dist(gen);
}

std::string CreateString(int size) {
  std::string ans = "";

  for (int i = 0; i < size; ++i) {
    ans += kAlph[random(0, kAlph.size() - 1)];
  }

  return ans;
}

int main() {
  std::mt19937 mt(time(nullptr)); 

  int vertex_size = random(3, 3);
  int edges_size = random(4, 10);

  std::cout << vertex_size << "\n" << edges_size << "\n";

  for (int i = 0; i < edges_size; ++i) {
    int u = random(0, vertex_size - 1);
    int v = random(0, vertex_size - 1);
    int symb = random(0, kAlph.size() - 1);
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

  int queries = 50;

  std::cout << queries << "\n";

  for (int i = 0; i < queries; ++i) {
    std::cout << CreateString(random(1, 6)) << "\n";
  }

  return 0;
}