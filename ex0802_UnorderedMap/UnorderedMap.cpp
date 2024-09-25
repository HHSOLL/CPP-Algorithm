#include <iostream>
#include <list>
#include <map>
#include <random>
#include <unordered_map>

template <typename T_KEY, typename T_VALUE>

void Print(const std::unordered_map<T_KEY, T_VALUE>& map) {
  for (int i = 0; i < map.bucket_count(); i++) {
    auto b = map.bucket(i);
    std::cout << i << ": ";
    for (auto j = map.begin(b); j != map.end(b); j++) {
      std::cout << "(" << j->first << ", " << j->second << ")->";
    }
    std::cout << '\n';
  }
}

int main(void) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::uniform_int_distribution<int> dist(1, 365);

  int num_people = 23;

  std::unordered_map<int, int> map(num_people);

  int num_try = 1000;
  int all_samebirthday_count = 0;

  for (int t = 0; t < num_try; t++) {
    int samebirthday_count = 0;

    for (int i = 0; i < num_people; i++) {
      int birthday = dist(g);

      auto n = map.find(birthday);

      if (n != map.end()) {
        samebirthday_count += 1;
        n->second += 1;
      } else {
        map.insert({birthday, 1});
      }
    }

    if (samebirthday_count > 0) all_samebirthday_count += 1;

    map.clear();
  }
  std::cout << (all_samebirthday_count * 100 / num_try) << "%" << '\n';

  return 0;
}