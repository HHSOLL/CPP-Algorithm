#include <iostream>
#include <vector>

template <typename T>
void Print(std::vector<T>& v) {
  for (auto i : v) {
    std::cout << i << " ";
  }
  std::cout << '\n';
}

void CountingSort(std::vector<std::string>& v, int k, int d) {
  std::vector<int> count(k, 0);
  std::vector<std::string> Output(v.size(), "0");

  for (int i = 0; i < v.size(); i++) {
    count[v[i][d] - 65]++;
  }

  for (int i = 1; i < count.size(); i++) {
    count[i] += count[i - 1];
  }

  std::cout << "Count: ";
  Print(count);

  for (int i = v.size() - 1; i >= 0; i--) {
    Output[count[v[i][d] - 65] - 1] = v[i];
    count[v[i][d] - 65]--;
  }

  std::cout << "Output: ";
  Print(Output);

  v = Output;
}

void RadixSort(std::vector<std::string>& v) {
  int k = 26;
  int d = 1;
  for (int i = 0; i < v.size() - 1; i++) {
    d = std::max(v[i].length(), v[i + 1].length()) - 1;
  }

  for (int i = d; i >= 0; i--) {
    std::cout << "Digit = " << i << '\n';
    CountingSort(v, k, i);
  }
}

int main(void) {
  std::vector<std::string> v = {"COW", "DOG", "SEA", "RUG", "ROW", "MOB",
                                "BOX", "TAB", "BAR", "EAR", "TAR", "DIG",
                                "BIG", "TEA", "NOW", "FOX"};

  Print(v);
  RadixSort(v);
  Print(v);

  return 0;
}