#include <iostream>
#include <numeric>
#include <random>
#include <vector>

void Print(std::vector<int> v) {
  int n = v.size();
  for (int i = 0; i < n; i++) {
    std::cout << v[i] << " ";
  }
  std::cout << '\n';
}

void SelectionSortPass(std::vector<int>& v, int low, int high) {
  int min_index = low;
  for (int i = low; i <= high; i++) {
    if (v[i] < v[min_index]) {
      std::swap(v[low], v[min_index]);
    }
  }
}

void PartialSelectionSort(std::vector<int>& v, int k) {
  Print(v);
  for (int i = 0; i < k; i++) {
    SelectionSortPass(v, i, v.size() - 1);
    Print(v);
  }
}

int main(void) {
  std::vector<int> my_vector = {7, 10, 4, 3, 20, 15};

  int k = 3;

  PartialSelectionSort(my_vector, k);

  std::cout << my_vector[k - 1] << '\n';

  return 0;
}
