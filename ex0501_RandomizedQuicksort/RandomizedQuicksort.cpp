#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

void Print(std::vector<int>& v, int low, int high, std::string sep = "") {
  std::cout << "Value: ";
  int n = v.size();
  for (int i = 0; i < n; i++) {
    if (low <= i && i <= high) {
      std::cout << std::setfill(' ') << std::setw(3) << v[i] << sep;
    } else {
      std::cout << "   ";
    }
  }
  std::cout << '\n';
}

int Partition(std::vector<int>& v, int low, int high) {
  std::cout << "Pivot = " << v[high] << '\n';

  int x = v[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (v[j] <= x) {
      i++;
      std::swap(v[i], v[j]);
    }
  }
  std::swap(v[i + 1], v[high]);
  Print(v, low, high);
  return i + 1;
}

int RandomizedPartition(std::vector<int>& v, int low, int high) {
  int random = low + rand() % (high - low + 1);
  std::swap(v[random], v[high]);
  return Partition(v, low, high);
}

void RandomizedQuicksort(std::vector<int>& v, int low, int high) {
  Print(v, low, high);

  if (low < high) {
    int mid = RandomizedPartition(v, low, high);
    RandomizedPartition(v, low, mid - 1);
    RandomizedPartition(v, mid + 1, high);
  }
}

int main() {
  srand(2);

  std::vector<int> v = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  RandomizedQuicksort(v, 0, v.size() - 1);

  Print(v, 0, v.size() - 1);

  return 0;
}