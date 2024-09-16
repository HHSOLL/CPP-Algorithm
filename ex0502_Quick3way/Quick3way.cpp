#include <iomanip>
#include <iostream>
#include <vector>

void Print(std::vector<int>& v, int low, int high, std::string sep = "") {
  std::cout << "Value: ";
  for (int i = 0; i < v.size(); i++) {
    if (low <= i && i <= high) {
      std::cout << std::setfill(' ') << std::setw(3) << v[i] << sep;
    } else {
      std::cout << "   ";
    }
  }
  std::cout << '\n';
}

void Quick3way(std::vector<int>& v, int low, int high) {
  if (low >= high) return;

  int lt = low;
  int i = low + 1;
  int gt = high;

  int k = v[low];
  std::cout << "Key = " << k << '\n';
  while (i <= gt) {
    if (v[i] < k) {
      std::swap(v[lt], v[i]);
      lt++;
      i++;
    } else if (v[i] > k) {
      std::swap(v[gt], v[i]);
      gt--;
    } else {
      i++;
    }
  }

  Print(v, low, high);
  Quick3way(v, low, lt - 1);
  Quick3way(v, gt + 1, high);
}

int main(void) {
  srand(0);

  std::vector<int> v = {3, 2, 3, 4, 5, 1, 2, 3, 4, 5,
                        1, 2, 3, 2, 3, 4, 5, 1, 3, 5};

  Print(v, 0, v.size() - 1);

  Quick3way(v, 0, v.size() - 1);

  Print(v, 0, v.size() - 1);

  return 0;
}