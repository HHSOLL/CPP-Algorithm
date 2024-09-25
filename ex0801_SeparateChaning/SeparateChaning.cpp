#include <iostream>
#include <list>
#include <random>
#include <vector>

template <typename T_KEY, typename T_VALUE>
class SequentialSearch {
 public:
  struct Node {
    T_KEY key;
    T_VALUE val;
  };

  Node* Find(T_KEY k) {
    for (auto& i : list) {
      if (i.key == k) {
        return &i;
      }
    }
    // std::cout << "Cannot Found" << '\n';
    return nullptr;
  }

  void Insert(Node n) {
    if (Find(n.key)) return;

    list.push_back(n);
  }

  void Reset() { list.clear(); }

  void Print() {
    for (auto& k : list) {
      std::cout << "( " << k.key << " , " << k.val << " )->";
    }
    std::cout << '\n';
  }

  int Size() { return int(list.size()); }

 private:
  std::list<Node> list;
};

template <typename T_KEY, typename T_VALUE>
class SeparateChaining {
 public:
  typedef typename SequentialSearch<T_KEY, T_VALUE>::Node Node;

  SeparateChaining(int c) {
    st.resize(c);
    Reset();
  }

  Node* Find(T_KEY k) { return st[HashFunc(k)].Find(k); }

  void Insert(Node n) { st[HashFunc(n.key)].Insert(n); }

  void Reset() {
    for (auto& i : st) i.Reset();
  }

  void Print() {
    for (int i = 0; i < st.size(); i++) {
      std::cout << i << ": ";
      st[i].Print();
    }
  }

 private:
  std::vector<SequentialSearch<T_KEY, T_VALUE>> st;

  int HashFunc(int key) { return key % st.size(); }
};

int main(void) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::uniform_int_distribution<int> dist(1, 365);

  int num_people = 0;
  std::cout << "Input Num_People : ";
  std::cin >> num_people;
  SeparateChaining<int, int> map(num_people);
  int num_try = 100000;
  int all_samebirthday_count = 0;

  for (int t = 0; t < num_try; t++) {
    int samebirthday_count = 0;

    for (int i = 0; i < num_people; i++) {
      int birthday = dist(g);

      auto* n = map.Find(birthday);

      if (n) {
        samebirthday_count += 1;
        n->val += 1;
      } else
        map.Insert({birthday, 1});
    }

    if (samebirthday_count > 0) all_samebirthday_count += 1;

    // map.Print();
    // std::cout << "-------------------" << '\n';
    map.Reset();
  }
  std::cout << (all_samebirthday_count * 100.0 / num_try) << " % " << '\n';

  return 0;
}