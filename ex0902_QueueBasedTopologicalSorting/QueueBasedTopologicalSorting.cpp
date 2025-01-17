#include <assert.h>

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

  std::vector<Vertex*> out_neighbors;
  std::vector<Vertex*> in_neighbors;
};

class Graph {
 public:
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
          cout << "wrong" << '\n';
          exit(-1);
        } else {
          cout << w->value << ", ";
        }
      }
      cout << '\n';
      v->visited = true;
      my_stack.pop();
    }
    cout << "OK" << '\n';
  }

  stack<Vertex*> QueueBasedTopologicalSort() {
    vector<int> indegree(vertices.size());
    for (auto* v : vertices) {
      for (auto* w : v->out_neighbors) {
        indegree[w->value]++;
      }
    }

    queue<Vertex*> q;

    for (auto* v : vertices) {
      if (indegree[v->value] == 0) q.push(v);
    }

    vector<Vertex*> result;
    while (!q.empty()) {
      Vertex* v = q.front();
      q.pop();

      result.push_back(v);

      for (auto* w : v->out_neighbors) {
        indegree[w->value]--;

        if (indegree[w->value] == 0) q.push(w);
      }
    }

    stack<Vertex*> s;
    for (auto i = result.rbegin(); i != result.rend(); i++) s.push(*i);

    return s;
  }

 private:
  std::vector<Vertex*> vertices;
};

int main() {
  // 간단한 경우
  // {

  //   Graph g(3);
  //   g.AddDiEdge(0, 1);
  //   g.AddDiEdge(1, 2);
  //   g.AddDiEdge(0, 2);

  //   auto my_stack = g.QueueBasedTopologicalSort();

  //   g.PrecedenceCheck(my_stack);

  //   while (!my_stack.empty()) {
  //     cout << my_stack.top()->value;
  //     my_stack.pop();
  //     if (!my_stack.empty()) cout << " -> ";
  //   }
  //   cout << endl;
  // }

  // {
  //   Graph g(6);

  //   g.AddDiEdge(5, 2);
  //   g.AddDiEdge(5, 0);
  //   g.AddDiEdge(0, 2);
  //   g.AddDiEdge(4, 0);
  //   g.AddDiEdge(4, 1);
  //   g.AddDiEdge(2, 3);
  //   g.AddDiEdge(3, 1);

  //   auto my_stack = g.QueueBasedTopologicalSort();
  //   g.PrecedenceCheck(my_stack);

  //   while (!my_stack.empty()) {
  //     cout << my_stack.top()->value;
  //     my_stack.pop();
  //     if (!my_stack.empty()) cout << " -> ";
  //   }
  //   cout << endl;
  // }

  {
    // Sedgewick Ch4.2 p.582 jobs.txt 예제
    // 가장 왼쪽의 과목이 나머지의 선수과목인 예제입니다.
    // 예: "Algorithms"가 "Theoretical CS", "Databases", "ScientificComputing"
    // 세 과목의 선수과목
    vector<vector<string>> jobs = {
        {"Algorithms", "Theoretical CS", "Databases", "ScientificComputing"},
        {"Introduction to CS", "Advanced Programming", "Algorithms"},
        {"Advanced Programming", "Scientific Computing"},
        {"Scientific Computing", "Computational Biology"},
        {"Theoretical CS", "Computational Biology", "ArtificialIntelligence "},
        {"Linear Algebra", "Theoretical CS"},
        {"Calculus", "Linear Algebra"},
        {"Artificial Intelligence", "Neural Networks", "Robotics",
         "Machine Learning"},
        {"Machine Learning", "Neural Networks"}};

    vector<string> values;  // int -> string
    map<string, int> keys;  // string -> int
    for (auto& l : jobs)
      for (auto& s : l)
        if (keys.count(s) == 0) {
          keys[s] = int(values.size());
          values.push_back(s);
          cout << keys[s] << " " << s << endl;
        }

    Graph g(int(keys.size()));

    for (auto& l : jobs) {
      int v = keys[l[0]];
      cout << v << " : ";
      for (int i = 1; i < l.size(); i++) {
        g.AddDiEdge(v, keys[l[i]]);

        cout << keys[l[i]] << ", ";
      }
      cout << endl;
    }

    auto my_stack = g.QueueBasedTopologicalSort();
    g.PrecedenceCheck(my_stack);

    while (!my_stack.empty()) {
      cout << values[my_stack.top()->value] << " " << my_stack.top()->value
           << endl;
      my_stack.pop();
    }
  }

  return 0;
}