#include <iostream>
#include <vector>

void Print(std::vector<int>& v) {
  for (auto i : v) {
    if (i == -1)
      std::cout << "X ";
    else
      std::cout << i << " ";
  }
  std::cout << '\n';
}

std::vector<int> CountingSort(std::vector<int>& v, int k) {
  std::vector<int> count(k + 1, 0);

  for (int i = 0; i < v.size(); i++) {
    count[v[i]]++;
  }

  for (int i = 1; i < count.size(); i++) {
    count[i] += count[i - 1];
  }

  std::cout << "Count: ";
  Print(count);

  std::vector<int> result(v.size(), -1);

  for (int i = result.size() - 1; i >= 0; i--) {
    result[count[v[i]] - 1] = v[i];
    count[v[i]]--;

    std::cout << "Count: ";
    Print(count);

    std::cout << "Result: ";
    Print(result);
  }

  return result;
}

int main() {
  std::vector<int> arr = {2, 5, 3, 0, 2, 3, 0, 3};

  Print(arr);

  int k = *std::max_element(arr.begin(), arr.end());

  std::vector<int> result = CountingSort(arr, k);

  Print(result);

  return 0;
}