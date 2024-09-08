#include <iostream>
#include <vector>

bool CheckSorted(std::vector<int>& arr) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void Print(std::vector<int>& arr) {
  for (auto v : arr) {
    std::cout << v << " ";
  }
  std::cout << '\n';
}

int main(void) {
  std::vector<int> a = {6, 4, 3, 8, 5};

  int N = a.size();
  for (int i = 1; i < N; i++) {
    for (int j = i; j > 0 && a[j - 1] > a[j]; j--) {
      std::swap(a[j - 1], a[j]);
    }

    Print(a);
  }
}