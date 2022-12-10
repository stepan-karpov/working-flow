#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
 
int random(long long low, long long high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

int main() {
 std::mt19937 mt(time(nullptr)); 
  for (int i = 0; i < 2; ++i) {
    std::cout << random(-1e9 - 100, 1e9 + 100) << '\n';
  }
  
  return 0;
}