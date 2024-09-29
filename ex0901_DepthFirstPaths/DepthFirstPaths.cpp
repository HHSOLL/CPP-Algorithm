#include <iostream>
#include <stack>
#include <vector>

struct Vertex {
  Vertex(int v) { value = v; }

  int value = -1;
  bool visited = false;

  std::vector<Vertex*> out_neighbors;
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
    if (!vertices.empty()) {
      for (int i = 0; i < vertices.size(); i++) {
        delete vertices[i];
      }
    }
  }

  void AddDiEdge(int v, int w) {
    vertices[v]->out_neighbors.push_back(vertices[w]);
  }
  void AddBiEdge(int v, int w) {
    vertices[v]->out_neighbors.push_back(vertices[w]);
    vertices[w]->out_neighbors.push_back(vertices[v]);
  }

  void DFS(int source) {
    std::cout << "Depth-first Search: ";
    for (auto* i : this->vertices) {
      i->visited = false;
    }
    DFS(vertices[source]);
    std::cout << '\n';
  }
  void DFS(Vertex* source) {
    std::cout << source->value << " ";
    source->visited = true;
    for (auto* w : source->out_neighbors) {
      if (!w->visited) DFS(w);
    }
  }

  void DepthFirstPath(int source, int sink) {
    std::cout << "Paths from " << vertices[source]->value << " to "
              << vertices[sink]->value << '\n';

    for (auto* v : this->vertices) {
      v->visited = false;
    }

    DepthFirstPathHelper(vertices[source], vertices[sink],
                         std::vector<Vertex*>());
  }

 private:
  void DepthFirstPathHelper(Vertex* source, Vertex* sink,
                            std::vector<Vertex*> path) {
    path.push_back(source);
    PrintPath(path);

    if (source == sink) {
      std::cout << "Found: ";
      PrintPath(path);
    } else {
      source->visited = true;
      for (auto* v : source->out_neighbors) {
        if (!v->visited) DepthFirstPathHelper(v, sink, path);
      }
      source->visited = false;
    }
  }

  void PrintPath(std::vector<Vertex*> path) {
    for (auto& a : path) {
      std::cout << a->value;
      if (&a != &path.back()) std::cout << " -> ";
    }
    std::cout << '\n';
  }

  std::vector<Vertex*> vertices;
};

int main() {
  //   {
  //     Graph g(3);
  //     g.AddDiEdge(0, 1);
  //     g.AddDiEdge(1, 2);
  //     g.AddDiEdge(0, 2);

  //     g.DFS(0);
  //     g.DepthFirstPath(0, 2);
  //   }

  // Sedgewick Algorithm 4.1 p.536 (조금 달라요)
  {
    Graph g(6);

    g.AddDiEdge(0, 2);
    g.AddDiEdge(2, 1);
    g.AddDiEdge(2, 3);
    g.AddDiEdge(3, 4);
    g.AddDiEdge(1, 5);
    g.AddDiEdge(2, 4);
    g.AddBiEdge(3, 5);  // 주의: 양방향 간선

    g.DFS(2);
    g.DepthFirstPath(2, 4);
  }

  return 0;
}