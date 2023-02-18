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
  const std::string ALPH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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


  int n = random(1, 10);
  cout << n << "\n";
  // int m = random(1, n);
  // cout << m << "\n";

  vector<int> sequence;

  for (int i = 0; i < n; ++i) {
    sequence.push_back(random(0, 100));
  }

  // sort(sequence.begin(), sequence.end());

  for (int i = 0; i < n; ++i) {
    std::cout << sequence[i] << " ";
  }
  std::cout << "\n";

  
  // for (int i = 0; i < m; ++i) {
  //   std::cout << random(0, 5) << " ";
  // }
  // std::cout << "\n";
  
  return 0;
}