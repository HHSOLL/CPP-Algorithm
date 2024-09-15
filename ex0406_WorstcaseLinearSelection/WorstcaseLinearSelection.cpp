#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

void Print(std::vector<int> v, int low, int high, std::string sep = "") {
  using namespace std;
  cout << "Index: ";
  for (int i = 0; i < v.size(); i++) cout << setfill(' ') << setw(3) << i;
  cout << endl;

  cout << "Value: ";
  for (int i = 0; i < v.size(); i++) {
    if (low <= i && i <= high)
      cout << setfill(' ') << setw(3) << v[i] << sep;
    else
      cout << "   ";
  }
  cout << endl;
}

void PrintGroups(std::vector<int>& v, int low, int g) {
  using namespace std;
  for (int j = low; j <= low + g - 1; j++) {
    cout << "Group " << j - low + 1 << " : ";
    for (int l = 0; l < 5; l++) cout << v[j + l * g] << " ";
    cout << endl;
  }
}

int Partition(std::vector<int>& v, int low, int high) {
  int x = v[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (v[i] <= x) {
      i++;
      std::swap(v[i], v[j]);
    }
  }
  std::swap(v[i + 1], v[high]);
  return i + 1;
}

void SelectionSortPass(std::vector<int>& v, int low, int high, int stride = 1) {
  int min_index = low;
  for (int j = low + stride; j <= high; j += stride)
    if (v[j] < v[min_index]) min_index = j;
  std::swap(v[low], v[min_index]);
}

struct Pair {
  int index;
  int value;
};

Pair Select(std::vector<int>& v, int low, int high, int k) {
  std::cout << "n = " << high - low + 1 << ", low = " << low
            << ", high = " << high << ", k = " << k << '\n';
  Print(v, low, high);

  // 5로 나눠서 떨어지지 않는 경우에는 정렬해서 범위를 줄이기
  while ((high - low + 1) % 5 != 0) {
    SelectionSortPass(v, low, high);
    if (k == 1) return {low, v[low]};
    low += 1;
    k -= 1;
  }

  int g = (high - low + 1) / 5;  // 그룹의 개수

  PrintGroups(v, low, g);

  for (int j = low; j < high; j++) {
    SelectionSortPass(v, j, high, g);
  }

  PrintGroups(v, low, g);

  Pair x = Select(v, low + 2 * g, low + 3 * g - 1, std::ceil(g / 2.0));

  std::cout << "low = " << low << ", high = " << high
            << ", Median of medians = " << x.value << '\n';

  std::swap(v[x.index], v[high]);

  int index = Partition(v, low, high);

  if (index - low == k - 1)
    return Pair{index, v[index]};
  else if (k - 1 < index - low)
    return Select(v, low, index - 1, k);
  else
    return Select(v, index + 1, high, k - index + low - 1);
}

int SelectionBySorting(std::vector<int> v, int k) {
  std::sort(v.begin(), v.end());
  return v[k - 1];
}

struct Sample {
  int n;
  double duration;
};

int main(void) {
  std::vector<int> my_vector(25);
  std::iota(my_vector.begin(), my_vector.end(), 0);
  std::reverse(my_vector.begin(), my_vector.end());

  std::cout << "Median = "
            << Select(my_vector, 0, my_vector.size() - 1,
                      std::ceil(my_vector.size() / 2.0))
                   .value
            << '\n';
}