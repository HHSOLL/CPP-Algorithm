#include <iostream>
#include <vector>

void Print(std::vector<float>& v) {
  for (auto& a : v) {
    std::cout << a << " ";
  }
  std::cout << '\n';
}

void PrintBucket(std::vector<std::vector<float>>& v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << i << ": ";
    for (int j = 0; j < v[i].size(); j++) {
      std::cout << v[i][j] << " ";
    }
    std::cout << '\n';
  }
}

void InsertionSort(std::vector<float>& v) {
  for (int i = 0; i < v.size(); i++) {
    float key = v[i];
    int j = i - 1;
    while (j >= 0 && v[j] > key) {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = key;
  }
}

void BucketSort(std::vector<float>& v, int num_buckets) {
  std::vector<std::vector<float>> buckets(num_buckets);

  for (auto a : v) {
    int idx = int(num_buckets * a);
    buckets[idx].push_back(a);
  }

  std::cout << "Before sorting" << '\n';
  PrintBucket(buckets);

  for (int i = 0; i < num_buckets; i++) {
    InsertionSort(buckets[i]);
  }

  std::cout << "After sorting" << '\n';
  PrintBucket(buckets);

  int index = 0;
  for (int i = 0; i < num_buckets; i++) {
    for (auto j : buckets[i]) {
      v[index++] = j;
    }
  }
}

int main() {
  std::vector<float> arr = {0.78f, 0.17f, 0.39f, 0.26f, 0.72f,
                            0.94f, 0.21f, 0.12f, 0.23f, 0.67f};

  Print(arr);

  BucketSort(arr, 10);

  Print(arr);

  return 0;
}