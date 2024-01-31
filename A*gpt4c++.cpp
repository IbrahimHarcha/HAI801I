#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
class Node {
public:
    std::string name;
    Node* parent;
    int g;  // Cost from start to current node
    int h;  // Heuristic cost from current node to goal
    int f;  // Total cost

    Node(std::string name, Node* par, int g_cost, int h_cost) 
        : name(name), parent(par), g(g_cost), h(h_cost), f(g_cost + h_cost) {}

    // Override < operator for priority queue
    bool operator<(const Node& other) const {
        return f > other.f;
    }
};

// Function to reconstruct the path from end node to start node
std::vector<std::string> reconstruct_path(Node* end_node) {
    std::vector<std::string> path;
    Node* current = end_node;
    while (current != nullptr) {
        path.push_back(current->name);
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// A* Algorithm
std::vector<std::string> a_star(std::map<std::string, std::map<std::string, int>>& graph, 
                                std::map<std::string, int>& heuristics,
                                std::string start, 
                                std::string goal) {
    std::priority_queue<Node> open_set;
    std::set<std::string> closed_set;

    open_set.emplace(start, nullptr, 0, heuristics[start]);

    while (!open_set.empty()) {
        Node current_node = open_set.top();
        open_set.pop();

        if (current_node.name == goal) {
            return reconstruct_path(&current_node);
        }

        closed_set.insert(current_node.name);

        for (const auto& neighbor : graph[current_node.name]) {
            if (closed_set.find(neighbor.first) != closed_set.end()) continue;

            int tentative_g = current_node.g + neighbor.second;

            // Add to open set if not already in or if has a lower g value
            if (!open_set.empty()) {
                bool should_add = true;
                std::priority_queue<Node> temp;
                while (!open_set.empty()) {
                    Node next = open_set.top();
                    open_set.pop();
                    if (next.name == neighbor.first && tentative_g >= next.g) {
                        should_add = false;
                    }
                    temp.push(next);
                }
                open_set = temp;
                if (should_add) {
                    open_set.emplace(neighbor.first, new Node(current_node), tentative_g, heuristics[neighbor.first]);
                }
            } else {
                open_set.emplace(neighbor.first, new Node(current_node), tentative_g, heuristics[neighbor.first]);
            }
        }
    }

    return std::vector<std::string>(); // return empty path if no path found
}

int main() {
  std::map<std::string, std::map<std::string, int>> graph = {
    {"A", {{"B", 2}, {"C", 10}, {"D", 3}}},
    {"B", {{"A", 2}, {"E", 8}}},
    {"E", {{"F", 5}, {"B", 8}, {"H", 10}}},
    {"D", {{"A", 3}, {"C", 2}, {"F", 4}}},
    {"C", {{"A", 10}, {"D", 2}, {"G", 2}}},
    {"F", {{"D", 4}, {"E", 5}, {"G", 5}}},
    {"G", {{"C", 2}, {"F", 5}, {"H", 1}}},
    {"H", {{"E", 10}, {"G", 1}}}
};

std::map<std::string, int> heuristics = {
    {"A", 9}, {"B", 3}, {"E", 8}, {"D", 6}, {"C", 5},
    {"F", 4}, {"G", 2}, {"H", 0}
};


    std::string start = "A";
    std::string goal = "H";
    std::vector<std::string> path = a_star(graph, heuristics, start, goal);

    std::cout << "Path from " << start << " to " << goal << ": ";
    for (const auto& node : path) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}
