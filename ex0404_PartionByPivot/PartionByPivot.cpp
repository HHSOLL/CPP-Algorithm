#include <iostream>
#include <vector>

void Print(std::vector<int> v) {
  int N = v.size();
  for (int i = 0; i < N; i++) {
    std::cout << v[i] << " ";
  }
  std::cout << '\n';
}

int main(void) {
  std::vector<int> v1 = {5, 2, 7, 3, 8, 5, 6, 4};

  int low = 0;
  int high = v1.size() - 1;
  int x = v1[high];

  int i = low - 1;

  Print(v1);

  for (int j = i + 1; j < high; j++) {
    if (v1[j] <= x) {
      i++;
      std::swap(v1[j], v1[i]);
    }
  }
  std::swap(v1[i + 1], v1[high]);

  Print(v1);

  return 0;
}