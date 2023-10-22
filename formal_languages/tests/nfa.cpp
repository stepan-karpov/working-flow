#pragma once

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

// usefull tool: https://csacademy.com/app/graph_editor/

// symbol ` means eps
const std::string kAlph = "`abcdef";

const bool interface_output = false;
// no bitmasks optimizations
// to support any number of vertexes/edges
struct NFA {
  struct Node {
    std::map<char, std::set<long long>> edges;
    long long output_power = 0;
    bool is_terminal = 0;

    void AddEdge(long long v, char symb) {
      if (edges[symb].find(v) == edges[symb].end()) {
        ++output_power;
      }
      edges[symb].insert(v);
    }

    void OutputEdges(long long me) {
      for (auto edge : edges) {
        for (long long to : edge.second) {
          std::cout << me << " " << to << " " << edge.first << "\n";
        }
      }
    }

    Node() {
      for (size_t i = 0; i < kAlph.size(); ++i) {
        edges[kAlph[i]] = {};
      }
    }

    Node(const Node& old_node,
         const std::map<long long, long long>& compressed_coords) {
      is_terminal = old_node.is_terminal;
      for (auto edge : old_node.edges) {
        edges[edge.first] = {};
        for (long long to : edge.second) {
          if (compressed_coords.contains(to)) {
            edges[edge.first].insert(compressed_coords.at(to));
            ++output_power;
          }
        }
      }
    }

    Node (const Node& other) = default;
    ~Node () = default;
  };

  struct ThompsonNode : public NFA::Node {
    std::set<int> represented_subset;
    ThompsonNode(std::set<int>&& subset)
      : represented_subset(std::move(subset)) {}
    ThompsonNode() = default;
  };

  std::vector<Node> nodes;

  void MarkupDFS(long long vertex, std::vector<bool>& used) {
    if (used[vertex]) { return; }
    used[vertex] = true;
    for (auto edge : nodes[vertex].edges) {
      if (edge.second.empty()) { continue; }
      for (long long to : edge.second) {
        MarkupDFS(to, used);
      }
    }
  }

  void EpsDFS(long long current_vertex, long long parent,
              std::set<long long>& used) {
    if (nodes[current_vertex].is_terminal) {
      nodes[parent].is_terminal = true;
    }
    if (used.find(current_vertex) != used.end()) {
      return;
    }
    used.insert(current_vertex);
    Node& current_node = nodes[current_vertex];
    for (auto edge : current_node.edges) {
      if (edge.second.empty()) { continue; } // debug usefull
      if (edge.first == '`') {
        for (long long to : edge.second) {
          EpsDFS(to, parent, used);
        }
        edge.second.clear();
      } else {
        for (long long to : edge.second) {
          nodes[parent].edges[edge.first].insert(to);
        }
      }
    }
    if (current_vertex == parent) {
      current_node.edges['`'].clear();
    }
  }

  void ClearUseless() {
    std::vector<bool> used(nodes.size(), false);
    MarkupDFS(0, used);

    std::map<long long, long long> compressed_coords;

    long long pointer = 0;
    for (long long i = 0; i < nodes.size(); ++i) {
      bool skip =
        !used[i] || (!nodes[i].is_terminal && nodes[i].output_power == 0);
      if (!skip) {
        compressed_coords[i] = pointer++;
      }
    }

    std::vector<Node> new_nodes;
    new_nodes.reserve(nodes.size());
    for (size_t i = 0; i < nodes.size(); ++i) {
      bool skip =
        !used[i] || (!nodes[i].is_terminal && nodes[i].output_power == 0);
      if (!skip) {
        new_nodes.push_back(Node(nodes[i], compressed_coords));
      }
    }
    nodes = new_nodes;
  }

  void ReadNFA() {
    if (interface_output) {
      std::cout << "\n";
      std::cout << "Input number of edges: ";
    }
    long long edges; std::cin >> edges;
    if (interface_output) {
      std::cout << "Input NFA's edges in the following format:\n";
      std::cout << "$number1$ $number2$ $letter$, where\n";
      std::cout << "$number1$ - number of an outgoing vertex (0-indexation),\n";
      std::cout << "$number2$ - number of an ingoing vertex (0-indexation),\n";
      std::cout << "$letter$ - letter from alphabet (kAlph in code)\n\n";
    }

    for (long long i = 0; i < edges; ++i) {
      long long u, v; char word;
      std::cin >> u >> v >> word;
      nodes[u].AddEdge(v, word);
    }
    if (interface_output) {
      std::cout << "Input number of terminal vertexes: ";
    }
    long long terminal; std::cin >> terminal;
    for (long long i = 0; i < terminal; ++i) {
      long long u; std::cin >> u;
      nodes[u].is_terminal = true;
    }
    ClearUseless(); // legacy code
  }

  void RemoveEps() {
    for (size_t i = 0; i < nodes.size(); ++i) {
      std::set<long long> used;
      EpsDFS(i, i, used);
    }
  }

  void OutputGraph() {
    std::cout << "Number of vertexes: " << nodes.size() << "\n";
    std::cout << "Edges: " << "\n";
    std::set<long long> terminals;
    for (long long i = 0; i < nodes.size(); ++i ){
      nodes[i].OutputEdges(i);
      if (nodes[i].is_terminal) {
        terminals.insert(i);
      }
    }

    std::cout << "\nNumber of terminal vertexes: ";
    std::cout << terminals.size() << "\n";

    for (auto term_vertex : terminals) {
      std::cout << term_vertex << " ";
    }
    std::cout << "\n";
  }

  bool DfsEps(int current_vertex, std::set<int>& used) {
    if (used.find(current_vertex) != used.end()) { return false; }
    used.insert(current_vertex);
    if (nodes[current_vertex].is_terminal) { return true; }
    for (int to : nodes[current_vertex].edges['`']) {
      if (DfsEps(to, used)) { return true; }
    }
    return false;
  }

  bool DFSRecognize(int current_vertex, int pointer, std::string& word,
                    std::set<std::pair<int, int>>& used) {
    while (pointer < word.size() && word[pointer] == '`') {
      ++pointer;
    }
    if (used.find({pointer, current_vertex}) != used.end()) {
      return false;
    }
    used.insert({pointer, current_vertex});
    if (pointer == word.size()) {
      std::set<int> used;
      return DfsEps(current_vertex, used);
    }
    for (int to : nodes[current_vertex].edges[word[pointer]]) {
      if (DFSRecognize(to, pointer + 1, word, used)) { return true; }
    }
    for (int to : nodes[current_vertex].edges['`']) {
      if (DFSRecognize(to, pointer, word, used)) { return true; }
    }
    return false;
  }

  bool CanRecognize(std::string& word) {
    if (static_cast<int>(nodes.size()) == 0) {
      return false;
    }

    std::set<std::pair<int, int>> used;
    return DFSRecognize(0, 0, word, used);
  }

  NFA(std::vector<ThompsonNode>& new_nodes) {
    nodes.reserve(new_nodes.size());
    for (size_t i = 0; i < new_nodes.size(); ++i) {
      nodes.push_back(new_nodes[i]);
    }
  }
  NFA(long long size) { nodes.assign(size, Node()); }
  ~NFA() = default;
  NFA(const NFA& other) = default;
  NFA(NFA&& other) = default;
};

struct DFA : public NFA {
  void InitializeThompsonsAlgorithm() {
    if (static_cast<int>(nodes.size()) == 0) {
      return;
    }
    std::vector<ThompsonNode> new_nodes;
    new_nodes.push_back(ThompsonNode());
    
    new_nodes[0].represented_subset = {0};
    new_nodes[0].edges = {};
    new_nodes[0].is_terminal = nodes[0].is_terminal;
    new_nodes[0].output_power = nodes[0].output_power;

    std::queue<int> queue;

    queue.push(0);
    std::map<std::set<int>, int> used;
    used[{0}] = 0;

    while (!queue.empty()) {
      int current_number = queue.front();
      queue.pop();

      for (char current_char : kAlph) {
        std::set<int> togo;
        for (int from : new_nodes[current_number].represented_subset) {
          for (int to : nodes[from].edges[current_char]) {
            togo.insert(to); // TODO - write if from == '`'
          }
        }
        if (togo.empty()) { continue; }
        ++new_nodes[current_number].output_power;
        int number;
        if (!used.contains(togo)) {
          used.insert({togo, new_nodes.size()});
          new_nodes.push_back(ThompsonNode(std::move(togo)));
          number = new_nodes.size() - 1;
          queue.push(number);
        } else {
          number = used[togo];
        }
        new_nodes[current_number].edges[current_char].insert(number);
      }
    }

    for (size_t i = 0; i < new_nodes.size(); ++i) {
      ThompsonNode& current_node = new_nodes[i];
      for (auto vertex : current_node.represented_subset) {
        current_node.is_terminal |= nodes[vertex].is_terminal;
      }
    }

    DFA rebuild(new_nodes);
    *this = rebuild;
  }

  void swap(DFA& other) {
    std::swap(other.nodes, nodes);
  }

  bool isComplete() {
    for (auto& node : nodes) {
      for (char current_char : kAlph) {
        if (current_char == '`') { continue; }
        if (node.edges[current_char].empty()) { return false; }
      }
    }
    return true;
  }

  void MakeComplete() {
    if (isComplete()) { return; }
    nodes.push_back(Node());

    for (auto& node : nodes) {
      for (auto current_char : kAlph) {
        if (current_char == '`') { continue; }
        if (node.edges[current_char].empty()) {
          node.AddEdge(nodes.size() - 1, current_char);
        }
      }
    }
  }

  void FindSimularVertexes(
    std::set<std::pair<int, int>>& storage,
    std::vector<std::map<char, std::set<int>>>& reveresed_edges) {
    std::queue<std::pair<int, int>> pairs;

    for (size_t i = 0; i < nodes.size(); ++i) {
      for (size_t j = i + 1; j < nodes.size(); ++j) {
        Node& node1 = nodes[i], node2 = nodes[j];
        if (node1.is_terminal != node2.is_terminal) {
          pairs.push({i, j});
          storage.insert({i, j});
        }
      }
    }

    for (size_t i = 0; i < nodes.size(); ++i) {
      Node& node = nodes[i];
      for (auto current_char : kAlph) {
        for (int to : node.edges[current_char]) {
          if (!reveresed_edges[to].contains(current_char)) {
            reveresed_edges[to][current_char] = {};
          }
          reveresed_edges[to][current_char].insert(i);
        }
      }
    }

    while (!pairs.empty()) {
      int x = pairs.front().first, y = pairs.front().second;
      pairs.pop();
      for (auto current_char : kAlph) {

        for (int a : reveresed_edges[x][current_char]) {
          for (int b : reveresed_edges[y][current_char]) {
            std::pair<int, int> temp = {std::min(a, b), std::max(a, b)};
            if (storage.find(temp) == storage.end()) {
              storage.insert(temp);
              pairs.push(temp);
            }
          }
        }
      }
    }
  }

  void Minimize() {
    if (nodes.size() == 0) { return; }
    if (!isComplete()) {
      std::cout << "ERROR ERROR ERROR ERROR ERROR ERROR Not complete!\n";
      return;
    }

    int last_size = 100'500;

    while (last_size > nodes.size()) {
      last_size = nodes.size();
      std::vector<std::map<char, std::set<int>>> reveresed_edges(nodes.size());
      std::set<std::pair<int, int>> storage;
      FindSimularVertexes(storage, reveresed_edges);

    
      std::vector<bool> deleted(nodes.size());
      for (int first_vertex = 0; first_vertex < nodes.size(); ++first_vertex) {
        for (int second_vertex = first_vertex + 1; second_vertex < nodes.size(); ++second_vertex) {
          if (storage.find({first_vertex, second_vertex}) != storage.end()) { continue; }
          if (!deleted[first_vertex] && !deleted[second_vertex]) {
            for (auto current_char : kAlph) {
              for (int parent : reveresed_edges[second_vertex][current_char]) {
                reveresed_edges[first_vertex][current_char].insert(parent);
                nodes[parent].edges[current_char].erase(second_vertex);
                nodes[parent].AddEdge(first_vertex, current_char);
              }
            }
          }
        }
      }

      ClearUseless();
    }
  }

  DFA(std::vector<ThompsonNode>& nodes) : NFA(nodes) {}
  DFA(int size) : NFA(size) {}
  ~DFA() = default;
  DFA(const DFA& other) = default;
  DFA& operator=(const DFA& other) {
    DFA copy = other;
    swap(copy);
    return *this;
  }
  DFA(DFA&& other) = default;
};