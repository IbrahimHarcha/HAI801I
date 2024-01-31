from queue import PriorityQueue

class Node:
    def __init__(self, state, parent=None, cost=0, heuristic=0):
        self.state = state
        self.parent = parent
        self.cost = cost
        self.heuristic = heuristic
        self.total_cost = cost + heuristic

    def __lt__(self, other):
        return self.total_cost < other.total_cost

graph = {
    'A': {'B': 2, 'C': 10, 'D': 3},
    'B': {'A': 2, 'E': 8},
    'E': {'F': 5, 'B': 8, 'H': 10},
    'D': {'A': 3, 'C': 2, 'F': 4},
    'C': {'A': 10, 'D': 2, 'G': 2},
    'F': {'D': 4, 'E': 5, 'G': 5},
    'G': {'C': 2, 'F': 5, 'H': 1},
    'H': {'E': 10, 'G': 1}
}

heuristic = {
    'A': 9,
    'B': 3,
    'E': 8,
    'D': 6,
    'C': 5,
    'F': 4,
    'G': 2,
    'H': 0
}

def a_star(graph, heuristics, start, goal):
    frontier = PriorityQueue()
    frontier.put((0, Node(start, heuristic=heuristics[start])))
    explored = set()

    while not frontier.empty():
        current_cost, current_node = frontier.get()

        if current_node.state == goal:
            path = []
            while current_node:
                path.append(current_node.state)
                current_node = current_node.parent
            return path[::-1]

        explored.add(current_node.state)

        for neighbor, cost in graph[current_node.state].items():
            if neighbor in explored:
                continue

            neighbor_node = Node(neighbor, current_node, current_node.cost + cost, heuristics[neighbor])
            if neighbor_node not in frontier.queue:
                frontier.put((neighbor_node.total_cost, neighbor_node))

    return None

path = a_star(graph, heuristic, 'A', 'H')
print("Path found:", path)
