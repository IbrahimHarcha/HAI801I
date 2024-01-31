# distance g(n)
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

# heuristique h(n)
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

def a_star(graphe, start, but, h_n):
    frontiere = [(0, start)] 
    predecesseur = {} 
    g_n = {ville: float('inf') for ville in graphe}
    g_n[start] = 0

    while frontiere:
        _, curr = frontiere.pop(0)
        if curr == but:
            chemin = []
            while curr in predecesseur:
                chemin.append(curr)
                curr = predecesseur[curr]
            chemin.append(start)
            return chemin[::-1]
        for voisin, cout in graphe[curr].items():
            test_g_n = g_n[curr] + cout
            if test_g_n < g_n[voisin]:
                predecesseur[voisin] = curr
                g_n[voisin] = test_g_n
                f_n = test_g_n + h_n[voisin]
                frontiere.append((f_n, voisin))
    return None


depart = 'A'
arrive = 'H'
plusCourtChemin = a_star(graphe, depart, arrive, heuristique)

if plusCourtChemin:
    print(f"Le chemin le plus court de {depart} à {arrive} est : {plusCourtChemin}")
else:
    print(f"Aucun chemin trouvé de {depart} à {arrive}.")