#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void Input(int* ptrs[], const int max_size, const int sizes[]) {
  for (int i = 0; i < max_size - 1; ++i) {
    ptrs[i] = new int[sizes[i]];
    for (int j = 0; j < sizes[i]; ++j) {
      std::cin >> ptrs[i][j];
    }
  }
}

int MaxValue(const int max_size, const int sizes[]) {
  int ans = -1e9;
  for (int i = 0; i < max_size - 1; ++i) {
    ans = std::max(ans, sizes[i]);
  }
  return ans;
}

long long Backtrack(const int max_size, int** const ptrs, const int sizes[], int nums[], int depth) {
  if (depth == max_size - 1) {
    long long cur_mult = 1;
    for (int i = 0; i < max_size - 1; ++i) {
      cur_mult *= ptrs[i][nums[i]];
    }
    return cur_mult;
  }
  
  long long ans = 0;
  for (int i = 0; i < sizes[depth]; ++i) {
    nums[depth] = i;
    bool is_ok = true;
    for (int j = 0; j < depth; ++j) {
      if (nums[j] == nums[depth]) {
        is_ok = false;
        break;
      }
    }
    if (!is_ok) continue;
    ans += Backtrack(max_size, ptrs, sizes, nums, depth + 1);
  }
  return ans;
}

void ClearMemory(int* ptrs[], int nums[], int argc, int sizes[]) {
  for (int i = 0; i < argc - 1; ++i) {
    delete[] ptrs[i];
  }
  delete[] ptrs;
  delete[] nums;
  delete[] sizes;
}

int main(int argc, char* argv[]) {
  Init();

  int* sizes = new int[argc - 1];
  for (int i = 1; i < argc; ++i) {
    sizes[i - 1] = atoi(argv[i]); 
  }

  int** ptrs = new int*[argc - 1];
  Input(ptrs, argc, sizes);

  int* nums = new int[MaxValue(argc, sizes)];
  long long ans = Backtrack(argc, ptrs, sizes, nums, 0);
  std::cout << ans << '\n';

  ClearMemory(ptrs, nums, argc, sizes);
  return 0;
}