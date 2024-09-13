#include <iostream>
#include <vector>

int main() {
  std::vector<int> v = {8, 2, 3, 5, 9, 1, 9, 4, 3, 7, 6, 7};
  int n = v.size();  // 12

  int min = 999;
  int max = 0;

  for (int i = 0; i < n; i += 2) {
    if (v[i] > v[i + 1]) {
      min = std::min(v[i + 1], min);
      max = std::max(v[i], max);
    }
  }

  std::cout << "Min value = " << min << ", Max value = " << max << '\n';
}