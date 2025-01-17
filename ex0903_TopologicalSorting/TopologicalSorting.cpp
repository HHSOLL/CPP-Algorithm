#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

struct Vertex {
  Vertex(int v) { value = v; }
  int value = -1;
  bool visited = false;

  vector<Vertex*> out_neighbors;
  vector<Vertex*> in_neighbors;
};

class Graph {
 public:
  queue<Vertex*> pre;
  queue<Vertex*> post;
  stack<Vertex*> revPost;

  Graph(int num_vertices) {
    vertices.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
      vertices[i] = new Vertex(i);
    }
  }

  ~Graph() {
    for (auto* v : vertices) {
      delete v;
    }
  }

  void AddDiEdge(int v, int w) {
    vertices[v]->out_neighbors.push_back(vertices[w]);
    vertices[w]->in_neighbors.push_back(vertices[v]);
  }

  void PrecedenceCheck(stack<Vertex*> my_stack) {
    for (auto* v : this->vertices) v->visited = false;

    while (!my_stack.empty()) {
      Vertex* v = my_stack.top();
      cout << "Precedence check " << v->value << " : ";
      for (auto* w : v->in_neighbors) {
        if (!w->visited) {
          cout << "Wrong" << endl;
          exit(-1);
        } else {
          cout << w->value << ", ";
        }
      }
      cout << endl;
      v->visited = true;
      my_stack.pop();
    }
    cout << "OK" << endl;
  }

  stack<Vertex*> TopologicalSort() {
    pre = queue<Vertex*>();
    post = queue<Vertex*>();
    revPost = stack<Vertex*>();

    for (auto* v : this->vertices) {
      v->visited = false;
    }
    for (auto* v : this->vertices) {
      if (!v->visited) {
        TopologicalSortHelper(v);
      }
    }

    return revPost;
  }

 private:
  vector<Vertex*> vertices;
  void TopologicalSortHelper(Vertex* v) {
    pre.push(v);

    v->visited = true;

    for (auto* w : v->out_neighbors) {
      if (!w->visited) TopologicalSortHelper(w);
    }

    post.push(v);
    revPost.push(v);
  }
};

int main() {
  //   {
  //     Graph g(3);
  //     g.AddDiEdge(0, 1);
  //     g.AddDiEdge(1, 2);
  //     g.AddDiEdge(0, 2);

  //     auto my_stack = g.TopologicalSort();

  //     g.PrecedenceCheck(my_stack);

  //     while (!my_stack.empty()) {
  //       cout << my_stack.top()->value;
  //       my_stack.pop();
  //       if (!my_stack.empty()) cout << " -> ";
  //     }
  //     cout << endl;
  //   }

  //   {
  //     Graph g(6);

  //     g.AddDiEdge(5, 2);
  //     g.AddDiEdge(5, 0);
  //     g.AddDiEdge(0, 2);
  //     g.AddDiEdge(4, 0);
  //     g.AddDiEdge(4, 1);
  //     g.AddDiEdge(2, 3);
  //     g.AddDiEdge(3, 1);

  //     auto my_stack = g.TopologicalSort();
  //     g.PrecedenceCheck(my_stack);

  //     while (!my_stack.empty()) {
  //       cout << my_stack.top()->value;
  //       my_stack.pop();
  //       if (!my_stack.empty()) cout << " -> ";
  //     }
  //     cout << endl;

  //     // Pre-order 확인용
  //     cout << "Preorder: ";
  //     while (!g.pre.empty()) {
  //       cout << g.pre.front()->value << " ";
  //       g.pre.pop();
  //     }
  //     cout << endl;
  //   }

  {
    // Sedgewick Ch4.2 p.582 jobs.txt 예제
    // 가장 왼쪽의 과목이 나머지의 선수과목인 예제입니다.
    // 예: "Algorithms"가 "Theoretical CS", "Databases", "Scientific Computing"
    // 세 과목의 선수과목
    vector<vector<string>> jobs = {
        {"Algorithms", "Theoretical CS", "Databases", "Scientific Computing"},
        {"Introduction to CS", "Advanced Programming", "Algorithms"},
        {"Advanced Programming", "Scientific Computing"},
        {"Scientific Computing", "Computational Biology"},
        {"Theoretical CS", "Computational Biology", "Artificial Intelligence"},
        {"Linear Algebra", "Theoretical CS"},
        {"Calculus", "Linear Algebra"},
        {"Artificial Intelligence", "Neural Networks", "Robotics",
         "Machine Learning"},
        {"Machine Learning", "Neural Networks"}};

    vector<string> values;  // int -> string
    map<string, int> map;   // string -> int
    for (auto& l : jobs)
      for (auto& s : l)
        if (map.count(s) == 0) {
          map[s] = int(values.size());
          values.push_back(s);
          cout << map[s] << " " << s << endl;
        }

    Graph g(int(map.size()));

    for (auto& l : jobs) {
      int v = map[l[0]];
      cout << v << " : ";
      for (int i = 1; i < l.size(); i++) {
        g.AddDiEdge(v, map[l[i]]);

        cout << map[l[i]] << ", ";
      }
      cout << endl;
    }

    auto my_stack = g.TopologicalSort();
    g.PrecedenceCheck(my_stack);

    while (!my_stack.empty()) {
      cout << values[my_stack.top()->value] << " " << my_stack.top()->value
           << endl;
      my_stack.pop();
    }

    // Pre-order 확인용
    cout << "Preorder: ";
    while (!g.pre.empty()) {
      cout << g.pre.front()->value << " ";
      g.pre.pop();
    }
    cout << endl;
  }

  return 0;
}