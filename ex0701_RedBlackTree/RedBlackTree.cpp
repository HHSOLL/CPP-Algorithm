#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using Key = std::string;
using Value = int;

enum Color { kRed, kBlack };

class Node {
 public:
  Key key;
  Value val;
  Color color;
  int size;
  Node* left;
  Node* right;

  Node(Key key, Value val, int N, Color color)
      : key(key),
        val(val),
        size(N),
        color(color),
        left(nullptr),
        right(nullptr) {}

 private:
};

class RedBlackBST {
 public:
  Node* root = nullptr;

  bool IsEmpty() { return root == nullptr; }

  bool IsRed(Node* x) {
    if (x == nullptr) return false;
    return x->color == Color::kRed;
  }

  int Size() { return Size(root); }
  int Size(Node* x) {
    if (x == nullptr) return 0;
    return x->size;
  }

  Value Search(Key key) { return Search(root, key); }
  Value Search(Node* x, Key key) {
    if (x == nullptr) return -1;
    if (key < x->key)
      return Search(x->left, key);
    else if (key > x->key)
      return Search(x->right, key);
    else
      return x->val;

    return -1;
  }

  bool Contains(Key key) { return Contains(root, key); }
  bool Contains(Node* x, Key key) {
    if (x == nullptr) return false;
    if (key < x->key)
      return Contains(x->left, key);
    else if (key > x->key)
      return Contains(x->right, key);
    else
      return true;

    return false;
  }

  Key Min() { return Min(root)->key; }
  Node* Min(Node* x) {
    if (x->left == nullptr)
      return x;
    else
      return Min(x->left);

    return nullptr;
  }

  Key Max() { return Max(root)->key; }
  Node* Max(Node* x) {
    if (x->right == nullptr)
      return x;
    else
      return Max(x->right);

    return nullptr;
  }

  Node* RotateLeft(Node* h) {
    Node* x = h->right;
    h->right = x->left;
    x->left = h;

    x->color = h->color;
    h->color = Color::kRed;

    x->size = h->size;
    h->size = 1 + Size(h->left) + Size(h->right);

    return x;
  }

  Node* RotateRight(Node* h) {
    Node* x = h->left;
    h->left = x->right;
    x->right = h;

    x->color = h->color;
    h->color = Color::kRed;

    x->size = h->size;
    h->size = 1 + Size(h->left) + Size(h->right);

    return x;
  }

  void FlipColors(Color& color) {
    if (color == Color::kBlack)
      color = Color::kRed;
    else
      color = Color::kBlack;
  }

  void FlipColors(Node* h) {
    FlipColors(h->color);
    FlipColors(h->left->color);
    FlipColors(h->right->color);
  }

  Node* Balance(Node* h) {
    assert(h != nullptr);

    if (IsRed(h->left) && IsRed(h->right)) {
      FlipColors(h);
    }
    if (IsRed(h->left) && IsRed(h->left->left)) {
      h = RotateRight(h);
      FlipColors(h);
    }
    if (!IsRed(h->left) && IsRed(h->right)) {
      h = RotateLeft(h);
    }

    h->size = 1 + Size(h->left) + Size(h->right);

    return h;
  }

  void Insert(Key key, Value val) {
    root = Insert(root, key, val);
    root->color = Color::kBlack;
  }
  Node* Insert(Node* h, Key key, Value val) {
    if (h == nullptr) return new Node(key, val, 1, Color::kRed);

    if (key < h->key) {
      h->left = Insert(h->left, key, val);
    } else if (key > h->key) {
      h->right = Insert(h->right, key, val);
    } else {
      h->val = val;
    }

    return Balance(h);
  }

  Node* MoveRedLeft(Node* h) {
    std::cout << "MoveRedLeft() " << h->key << '\n';

    FlipColors(h);

    if (IsRed(h->right->left)) {
      h->right = RotateRight(h->right);
      h = RotateLeft(h);
      FlipColors(h);
    }
    return h;
  }

  Node* MoveRedRight(Node* h) {
    std::cout << "MoveRedRight() " << h->key << '\n';

    FlipColors(h);

    if (IsRed(h->left->left)) {
      h = RotateRight(h);
      FlipColors(h);
    }

    return h;
  }

  void DeleteMin() {
    if (!IsRed(root->left) && !IsRed(root->right)) root->color = Color::kRed;

    root = DeleteMin(root);

    if (!IsEmpty()) root->color = Color::kBlack;
  }
  Node* DeleteMin(Node* h) {
    std::cout << "DeleteMin() " << h->key << '\n';

    if (h->left == nullptr) {
      std::cout << "Delete node " << h->key << '\n';
      delete h;
      return nullptr;
    }

    if (!IsRed(h->left) && !IsRed(h->left->left)) {
      h = MoveRedLeft(h);
      Print2D(h);
    }
    h->left = DeleteMin(h->left);

    return Balance(h);
  }

  void DeleteMax() {
    if (!IsRed(root->left) && !IsRed(root->right)) root->color = Color::kRed;

    root = DeleteMax(root);

    if (!IsEmpty()) root->color = Color::kBlack;
  }
  Node* DeleteMax(Node* h) {
    std::cout << "DeleteMax() " << h->key << '\n';

    if (IsRed(h->left)) h = RotateRight(h);

    if (h->right == nullptr) {
      std::cout << "Delete node " << h->key << '\n';
      delete h;
      return nullptr;
    }

    if (!IsRed(h->right) && !IsRed(h->right->left)) {
      h = MoveRedRight(h);
      Print2D(h);
    }
    h->right = DeleteMax(h->right);

    return Balance(h);
  }

  void Delete(Key key) {
    if (!Contains(key)) return;

    if (!IsRed(root->left) && !IsRed(root->right)) root->color = Color::kRed;

    root = Delete(root, key);

    if (!IsEmpty()) root->color = Color::kBlack;
  }
  Node* Delete(Node* h, Key key) {
    if (key < h->key) {
      if (!IsRed(h->left) && !IsRed(h->left->left)) {
        h = MoveRedLeft(h);
      }
      h->left = Delete(h->left, key);
    } else {
      if (IsRed(h->left)) {
        h = RotateRight(h);
      }

      if (key == h->key && h->right == nullptr) {
        std::cout << "Delete node " << h->key << '\n';
        delete h;
        return nullptr;
      }

      if (!IsRed(h->right) && !IsRed(h->right->left)) {
        h = MoveRedRight(h);
      }

      if (key == h->key) {
        h->key = Min(h->right)->key;
        h->val = Min(h->right)->val;
        h->right = DeleteMin(h->right);
      } else {
        h->right = Delete(h->right, key);
      }
    }
    return Balance(h);
  }

  int Height() { return Height(root); }
  int Height(Node* x) {
    if (!x) return -1;
    return 1 + std::max(Height(x->left), Height(x->right));
  }

  std::vector<std::string> screen;
  void PrintLine(int x, std::string s, std::string& line) {
    for (const auto c : s) line[x++] = c;
  }
  void Print2D() { Print2D(root); }
  void Print2D(Node* root) {
    if (!root)
      std::cout << "Empty" << '\n';
    else {
      int h = Height(root) + 1, w = 4 * int(pow(2, h - 1));
      screen.clear();
      screen.resize(h * 2, std::string(w, ' '));
      Print2D(root, w / 2 - 2, 0, h - 1);
      for (const auto& l : screen) std::cout << l << '\n';
    }
  }
  void Print2D(Node* n, int x, int level, int s) {
    // cout << x << " " << level << " " << s << endl;
    PrintLine(x, (IsRed(n) ? "*" : " ") + n->key, screen[2 * level]);
    x -= int(pow(2, s));
    if (n->left) {
      PrintLine(x, "  /", screen[2 * level + 1]);
      Print2D(n->left, x, level + 1, s - 1);
    }
    if (n->right) {
      PrintLine(x + 2 * int(pow(2, s)), "\\", screen[2 * level + 1]);
      Print2D(n->right, x + 2 * int(pow(2, s)), level + 1, s - 1);
    }
  }

 private:
};

int main() {
  // SEARCHXMPL 순서로 추가
  {
    RedBlackBST bst;

    std::string keys = std::string("SEARCHXMPL");

    for (char c : keys) {
      std::cout << "Insert: " << std::string(1, c) << '\n';
      bst.Insert(std::string(1, c), int(c));
      //   bst.Print2D();
    }

    //// Search 테스트
    // for (char c : keys) {
    //   std::cout << c << " " << int(c) << " " << bst.Search(std::string(1, c))
    //             << '\n';
    // }

    bst.Print2D();

    for (char c : keys) {
      std::cout << "Delete: " << std::string(1, c) << '\n';
      bst.Delete(std::string(1, c));
      bst.Print2D();
    }
    return 0;

    // while (!bst.IsEmpty()) {
    //   std::cout << "DeleteMin: " << bst.Min() << '\n';
    //   bst.DeleteMin();
    //   bst.Print2D();
    // }
    // std::cout << '\n';

    // while (!bst.IsEmpty()) {
    //   std::cout << "DeleteMax: " << bst.Max() << '\n';
    //   bst.DeleteMax();
    //   bst.Print2D();
    // }
    std::cout << '\n';
  }

  // ACEHLMPRSX 순서로 추가
  //{
  //	RedBlackBST bst;

  //	for (char c : string("ACEHLMPRSX"))
  //	{
  //		cout << "Insert: " << string(1, c) << endl;
  //		bst.Insert(string(1, c), int(c));
  //		bst.Print2D();
  //	}
  //}

  return 0;
}