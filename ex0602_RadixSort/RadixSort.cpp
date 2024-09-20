#include <iostream>
#include <vector>

void Print(std::vector<int>& v) {
  for (auto i : v) {
    std::cout << i << " ";
  }
  std::cout << '\n';
}

void CountingSort(std::vector<int>& v, int k, int exp) {
  std::vector<int> count(k + 1, 0);
  for (int i = 0; i < v.size(); i++) {
    count[v[i] / exp % 10]++;
  }

  for (int i = 1; i < count.size(); i++) {
    count[i] += count[i - 1];
  }

  std::cout << "Count: ";
  Print(count);

  std::vector<int> temp(v.size(), 0);
  for (int i = v.size() - 1; i >= 0; i--) {
    temp[count[v[i] / exp % 10] - 1] = v[i];
    count[v[i] / exp % 10]--;
  }

  std::cout << "Output: ";
  Print(temp);
  v = temp;
}

void RadixSort(std::vector<int>& v) {
  int k = 9;
  int m = *std::max_element(v.begin(), v.end());

  for (int exp = 1; m / exp > 0; exp *= 10) {
    std::cout << "exp = " << exp << '\n';
    CountingSort(v, k, exp);
  }
}

int main() {
  std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
  // vector<int> arr = { 2, 5, 3, 0, 2, 3, 0, 3 };

  Print(arr);

  RadixSort(arr);

  return 0;
}