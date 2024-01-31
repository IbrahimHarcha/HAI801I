def aStar(depart, objectif, graphe, heuristiques):

    front = [(heuristiques[depart], 0, depart)]
    came_from = {}
    cost_so_far = {depart: 0}
    
    path = [depart]
    
    while front:
        _, current_cost, current = front.pop(0)

        if current == objectif:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            return path[::-1]

        for neighbor in graphe[current]:
            new_cost = current_cost + graphe[current][neighbor]
            if neighbor not in cost_so_far or new_cost < cost_so_far[neighbor]:
                cost_so_far[neighbor] = new_cost
                priority = new_cost + heuristiques[neighbor]
                front.append((priority, new_cost, neighbor))
                came_from[neighbor] = current

    return None

graph = {'A': {'B':2,'C':10,'D':3},
         'B': {'A':2,'E':8},
         'E': {'F':5,'B':8,'H':10},
         'D': {'A':3,'C':2,'F':4},    
         'C': {'A':10,'D':2,'G':2}, 
         'F': {'D':4,'E':5,'G':5}, 
         'G': {'C':2,'F':5,'H':1},
         'H': {'E':10,'G':1} }  

heuristics = {'A': 9,
              'B': 3,
              'E': 8,
              'D': 6,
              'C': 5,
              'F': 4,
              'G': 2,
              'H': 0 }


path = a_star('A', 'H', graph, heuristics)
path.insert(0, 'A')
print("Chemin: ", path)

