#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

int SelectionBySorting(std::vector<int> v, int k) {
  std::sort(v.begin(), v.end());
  return v[k - 1];
}
void Print(std::vector<int>& v, int low, int high, std::string sep = " ") {
  std::cout << "Value: ";
  for (int i = 0; i < v.size(); i++) {
    if (low <= i && i <= high)
      std::cout << std::setfill(' ') << std::setw(3) << v[i] << sep;
    else
      std::cout << "   ";
  }
  std::cout << '\n';
}
int Partion(std::vector<int>& v, int low, int high) {
  int x = v[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (v[j] <= x) {
      i++;
      std::swap(v[i], v[j]);
    }
  }
  std::swap(v[i + 1], v[high]);
  return i + 1;
}

int g_level = -1;
int RandomizedSelect(std::vector<int>& v, int low, int high, int k) {
  g_level++;

  std::cout << "level = " << g_level << ", n = " << high - low + 1
            << ", low = " << low << ", high = " << high << ", k= " << k << '\n';
  Print(v, low, high);

  if (low == high) return v[low];

  //   int random = low + rand() % (high - low + 1);
  //   std::swap(v[random], v[high]);

  int index = Partion(v, low, high);

  if (index - low == k - 1) {
    return v[index];
  } else if (k - 1 < index - low) {
    return RandomizedSelect(v, low, index - 1, k);
  } else {
    return RandomizedSelect(v, index + 1, high, k - index + low - 1);
  }
}

int main() {
  srand(1);  // 랜덤 피벗을 사용할 때는 숫자를 바꿔가면서 테스트해보세요.

  std::vector<int> my_vector = {6, 19, 4, 12, 14, 9, 15, 7,
                                8, 11, 3, 13, 2,  5, 10};
  //   std::vector<int> my_vector = {4, 19, 4, 12, 2, 9, 15, 2,
  //                                 8, 11, 3, 1,  2, 1, 10};
  //   std::vector<int> my_vector = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  Print(my_vector, 0, my_vector.size() - 1);

  std::cout << RandomizedSelect(my_vector, 0, my_vector.size() - 1,
                                std::ceil(my_vector.size() / 2.0))
            << '\n';

  //   std::random_device rd;
  //   std::mt19937 gen(rd());

  //   for (int n = 1; n <= 10000; n += 1) {
  //     std::vector<int> my_vector(n);

  //     std::uniform_int_distribution<int> value_distribution(0, (n - 1) / 2);
  //     generate(my_vector.begin(), my_vector.end(),
  //              [&]() { return value_distribution(gen); });

  //     std::vector<int> backup = my_vector;

  //     int k = int(my_vector.size() / 2) + 1;
  //     int expected_value = SelectionBySorting(my_vector, k);
  //     int selected_value =
  //         RandomizedSelect(my_vector, 0, my_vector.size() - 1, k);

  //     // Print(my_vector, 0, my_vector.size() - 1);
  //     // cout << expected_value << " " << selected_value << endl;

  //     if (expected_value != selected_value) {
  //       std::cout << "Incorrect. " << expected_value << " " << selected_value
  //                 << '\n';
  //       Print(backup, 0, backup.size() - 1);
  //       Print(my_vector, 0, backup.size() - 1);
  //       exit(-1);
  //     }
  //   }

  //   std::cout << "Good!" << '\n';
}