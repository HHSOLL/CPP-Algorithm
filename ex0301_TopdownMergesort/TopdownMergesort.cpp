#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

void Print(std::vector<int>& v, int lo, int hi) {
  for (int i = 0; i < lo; i++) std::cout << "   ";
  for (int i = lo; i <= hi; i++) {
    std::cout << std::setfill(' ') << std::setw(3) << v[i];
  }
  std::cout << '\n';
}

bool CheckSorted(std::vector<int>& v) {
  int n = v.size();
  for (int i = 0; i < n - 1; i++) {
    if (v[i] > v[i + 1]) return false;
  }
  return true;
}

class TopDownMerge {
 public:
  void Sort(std::vector<int>& v) {
    count = 0;
    aux.resize(v.size());

    SortHelper(v, 0, v.size() - 1);
  }

 private:
  void Merge(std::vector<int>& v, int lo, int mid, int hi) {
    std::cout << "Before: ";
    Print(v, lo, hi);

    int i = lo;
    int j = mid + 1;

    if (v[mid] <= v[j]) return;

    for (int k = lo; k <= hi; k++) {
      aux[k] = v[k];
    }

    for (int k = lo; k <= hi; k++) {
      if (i > mid)
        v[k] = aux[j++];
      else if (j > hi)
        v[k] = aux[i++];
      else if (aux[j] < aux[i])
        v[k] = aux[j++];
      else
        v[k] = aux[i++];
    }

    std::cout << "After: ";
    Print(v, lo, hi);
  }
  void SortHelper(std::vector<int>& v, int lo, int hi) {
    if (lo >= hi) return;

    int mid = lo + (hi - lo) / 2;

    SortHelper(v, lo, mid);
    SortHelper(v, mid + 1, hi);
    Merge(v, lo, mid, hi);
  }
  std::vector<int> aux;
  int count = 0;
};

int main(void) {
  std::vector<int> my_vector(16);
  std::iota(my_vector.begin(), my_vector.end(), 0);
  std::reverse(my_vector.begin(), my_vector.end());

  std::cout << "        ";
  Print(my_vector, 0, my_vector.size() - 1);

  TopDownMerge merge;
  merge.Sort(my_vector);

  std::cout << "        ";
  Print(my_vector, 0, my_vector.size() - 1);
}