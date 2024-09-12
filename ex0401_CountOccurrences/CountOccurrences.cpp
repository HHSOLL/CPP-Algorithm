#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

void Print(vector<int>& v) {
  int n = v.size();
  for (int i = 0; i < n; i++) {
    cout << v[i] << " ";
  }
  cout << '\n';
}

int Count1(const vector<int>& v, int x) {
  int n = v.size();
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (v[i] == x) count++;
  }
  return count;
}

int BinarySearch(const vector<int>& v, int low, int high, int x) {
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}
int Count2(const vector<int>& v, int x) {
  int n = v.size();
  int i = BinarySearch(v, 0, n - 1, x);

  if (i == -1) return 0;

  int count = 1;

  int index = i;
  while (true) {
    if (v[--index] == x)
      count++;
    else
      break;
  }

  index = i;
  while (true) {
    if (v[++index] == x)
      count++;
    else
      break;
  }
  return count;
}

int FindFirst(const vector<int>& v, int low, int high, int x) {
  while (low <= high) {
    int mid = (low + high) / 2;
    if (mid == 0 || x == v[mid] && v[mid - 1] < x)
      return mid;
    else if (x > v[mid])
      return FindFirst(v, mid + 1, high, x);
    else
      return FindFirst(v, low, mid - 1, x);
  }
  return -1;
}

int FindLast(const vector<int>& v, int low, int high, int x) {
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (mid == v.size() - 1 || x == v[mid] && x < v[mid + 1])
      return mid;
    else if (x < v[mid])
      return FindLast(v, low, mid - 1, x);
    else
      return FindLast(v, mid + 1, high, x);
  }
  return -1;
}

int Count3(const vector<int>& v, int x) {
  int n = v.size();
  int i = FindFirst(v, 0, n - 1, x);
  if (i == -1) return 0;
  int j = FindLast(v, 0, n - 1, x);
  int count = j - i + 1;

  return count;
}

int main(void) {
  random_device rd;
  mt19937 gen(rd());

  const int n = 20;
  vector<int> my_vector(n);

  int x = 6;  // target to find

  for (int r = 0; r < 100; r++) {
    uniform_int_distribution<int> value_distribution(1, 10);
    generate(my_vector.begin(), my_vector.end(),
             [&]() { return value_distribution(gen); });
    sort(my_vector.begin(), my_vector.end());

    Print(my_vector);

    const int expected_count =
        std::count(my_vector.begin(), my_vector.end(), x);

    cout << "Expected count = " << expected_count << endl;

    // 1. O(n) brute force
    if (Count1(my_vector, x) != expected_count) {
      cout << "Wrong count1: " << Count1(my_vector, x) << endl;
      exit(-1);
    } else
      cout << "1 is right" << '\n';

    // 2. O(log(n) + count)
    if (Count2(my_vector, x) != expected_count) {
      cout << "Wrong count2: " << Count2(my_vector, x) << endl;
      exit(-1);
    } else
      cout << "2 is right" << '\n';

    // 3. O(log(n))
    if (Count3(my_vector, x) != expected_count) {
      cout << "Wrong count3: " << Count3(my_vector, x) << endl;
      exit(-1);
    } else
      cout << "3 is right" << '\n';
  }

  cout << "Good!" << endl;

  return 0;
}