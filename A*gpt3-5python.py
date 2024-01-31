import heapq

def astar(graphe, heuristique, depart, objectif):
    ouvert = [(0, depart)]
    ferme = set()
    g_score = {noeud: float('inf') for noeud in graphe}
    g_score[depart] = 0
    
    while ouvert:
        _, actuel = heapq.heappop(ouvert)
        
        if actuel == objectif:
            chemin = [actuel]
            while actuel != depart:
                actuel = came_from[actuel]
                chemin.append(actuel)
            return chemin[::-1]
        
        ferme.add(actuel)
        
        for voisin, cout in graphe[actuel].items():
            if voisin in ferme:
                continue
            
            tentative_g_score = g_score[actuel] + cout
            
            if tentative_g_score < g_score.get(voisin, float('inf')):
                g_score[voisin] = tentative_g_score
                f_score = g_score[voisin] + heuristique[voisin]
                heapq.heappush(ouvert, (f_score, voisin))
                came_from[voisin] = actuel
    
    return None

if __name__ == "__main__":
    graphe = {
        'A': {'B':2,'C':10,'D':3},
        'B': {'A':2,'E':8},
        'E': {'F':5,'B':8,'H':10},
        'D': {'A':3,'C':2,'F':4},
        'C': {'A':10,'D':2,'G':2},
        'F': {'D':4,'E':5,'G':5},
        'G': {'C':2,'F':5,'H':1},
        'H': {'E':10,'G':1}
    }

    heuristique = {
        'A': 9,
        'B': 3,
        'E': 8,
        'D': 6,
        'C': 5,
        'F': 4,
        'G': 2,
        'H': 0
    }

    depart = 'A'
    objectif = 'H'
    came_from = {}
    chemin_optimal = astar(graphe, heuristique, depart, objectif)

    if chemin_optimal:
        print("Chemin optimal de {} à {}: {}".format(depart, objectif, ' -> '.join(chemin_optimal)))
    else:
        print("Aucun chemin trouvé de {} à {}.".format(depart, objectif))
