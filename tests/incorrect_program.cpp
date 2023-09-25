#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const int kNumbers = 10;
const int kMillion = 1'000'010;

void InputString(std::vector<std::string>& sequence) {
  std::string row;
  std::cin >> row;

  row += row;

  int p1 = 0;
  int p2 = row.size() - 1;

  sequence.push_back(row);

  for (size_t i = 0; i < row.size(); ++i) {
    if (i % 2 == 0) {
      sequence[sequence.size() - 1][i] = row[p1];
      ++p1;
    } else {
      sequence[sequence.size() - 1][i] = row[p2];
      --p2;
    }
  }
}

struct Node {
  std::vector<int> to;
  int term_power = 0;
  int parent_power = 0;
  int depth = 0;
  Node() { to.assign(kNumbers, -1); }
};

int CountDynamics(int current_vertex, int depth, std::vector<Node>& bruh,
                  int group_size, std::vector<int>& answers) {
  int answer = bruh[current_vertex].term_power;
  for (int i = 0; i < kNumbers; ++i) {
    if (bruh[current_vertex].to[i] != -1) {
      answer += CountDynamics(bruh[current_vertex].to[i], depth + 1, bruh,
                              group_size, answers);
    }
  }
  bruh[current_vertex].parent_power = answer;
  bruh[current_vertex].depth = depth;
  if (depth % 2 == 0 && answer >= group_size) {
    ++answers[depth / 2];
  }
  return answer;
}

void BuildBruh(std::vector<Node>& bruh, std::vector<std::string>& sequence) {
  for (size_t i = 0; i < sequence.size(); ++i) {
    int current_pointer = 0;
    for (size_t j = 0; j < sequence[i].size(); ++j) {
      int current_to = sequence[i][j] - '0';
      if (bruh[current_pointer].to[current_to] == -1) {
        bruh.push_back(Node());
        bruh[current_pointer].to[current_to] = bruh.size() - 1;
      }
      current_pointer = bruh[current_pointer].to[current_to];
    }
    ++bruh[current_pointer].term_power;
  }
}

void Solve() {
  int n_size;
  std::cin >> n_size;
  int group_size;
  std::cin >> group_size;
  std::vector<std::string> sequence;
  for (int i = 0; i < n_size; ++i) {
    InputString(sequence);
  }

  std::vector<Node> bruh(1);

  std::vector<int> answers(kMillion, 0);

  BuildBruh(bruh, sequence);
  CountDynamics(0, 0, bruh, group_size, answers);

  int queries;
  std::cin >> queries;

  for (int i = 0; i < queries; ++i) {
    int current_l;
    std::cin >> current_l;
    std::cout << answers[current_l] << "\n";
  }
}

int main() {
  Init();
  Solve();
  return 0;
}