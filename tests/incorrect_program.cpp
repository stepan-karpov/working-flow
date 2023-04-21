#include <iostream>
#include <map>
#include <vector>

const long long kMinim = -1'000'000'000'000'000'000;

void Floid(std::vector<std::vector<long long>>& matrix,
           std::vector<std::vector<long long>>& parents, long long n_artur) {
  for (long long k = 0; k < n_artur; ++k) {
    for (long long i = 0; i < n_artur; ++i) {
      for (long long j = 0; j < n_artur; ++j) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
          parents[i][j] = k;
          matrix[i][j] = std::max(matrix[k][j] + matrix[i][k], kMinim);
        }
      }
    }
  }
}

void Path(long long from, long long to,
          std::map<std::pair<long long, long long>, long long>& edges,
          std::vector<std::vector<long long>>& parents,
          std::vector<long long>& answer) {
  if (parents[from][to] != -1) {
    Path(from, parents[from][to], edges, parents, answer);
    Path(parents[from][to], to, edges, parents, answer);
  } else {
    answer.push_back(edges[std::make_pair(from, to)]);
  }
}

void Solve() {
  long long n_artur;
  long long m_artur;
  long long k_artur;
  std::cin >> n_artur >> m_artur >> k_artur;
  std::map<std::pair<long long, long long>, long long> edges;
  long long from;
  long long to;
  long long weight;
  std::vector<std::vector<long long>> matrix(
      n_artur, std::vector<long long>(n_artur, INT32_MAX));
  for (long long i = 0; i < m_artur; ++i) {
    std::cin >> from >> to >> weight;
    --from;
    --to;
    weight = -weight;
    edges[std::make_pair(from, to)] = i + 1;
    matrix[from][to] = weight;
  }
  std::vector<long long> needed(k_artur);
  for (long long i = 0; i < k_artur; ++i) {
    std::cin >> needed[i];
    --needed[i];
  }
  std::vector<std::vector<long long>> parents(
      n_artur, std::vector<long long>(n_artur, -1));
  Floid(matrix, parents, n_artur);
  std::vector<std::vector<long long>> copy = matrix;
  Floid(copy, parents, n_artur);
  Floid(copy, parents, n_artur);
  Floid(copy, parents, n_artur);
  Floid(copy, parents, n_artur);
  for (int i = 0; i < needed.size() - 1; ++i) {
    if (matrix[needed[i]][needed[i + 1]] == kMinim ||
        matrix[needed[i]][needed[i + 1]] != copy[needed[i]][needed[i + 1]] && needed[i] != needed[i + 1]) {
      std::cout << "infinitely kind";
      return;
    }
  }
  for (int i = 0; i < needed.size(); ++i) {
    if (copy[needed[i]][needed[i]] < 0) {
      std::cout << "infinitely kind";
      return;
    }
  }
  std::vector<long long> new_needed;
  new_needed.push_back(needed[0]);
  for (int i = 1; i < needed.size(); ++i) {
    if (needed[i] != needed[i - 1]) {
      new_needed.push_back(needed[i]);
    }
  }
  needed = new_needed;
  std::vector<long long> answer;
  for (long long i = 0; i < needed.size() - 1; ++i) {
    Path(needed[i], needed[i + 1], edges, parents, answer);
  }
  std::cout << answer.size() << "\n";
  for (long long i = 0; i < static_cast<long long>(answer.size()); ++i) {
    std::cout << answer[i] << " ";
  }
}

int main() { Solve(); }
