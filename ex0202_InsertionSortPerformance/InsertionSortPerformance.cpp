#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

void Print(std::vector<int> v);
bool CheckSorted(std::vector<int>& v);
void InsertionSort(std::vector<int>& v);
void InsertionSort2(std::vector<int>& v);

struct Sample {
  int n;
  double duration;
};

int main(void) {}

void Print(std::vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << '\n';
}

bool CheckSorted(std::vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] > v[i + 1]) return false;
  }
  return true;
}

void InsertionSort(std::vector<int>& v) {}

void InsertionSort2(std::vector<int>& v) {}