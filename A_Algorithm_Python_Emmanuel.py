class A_Algorithm_Python_Emmanuel:
    graphe = {}
    heuristique = {}

    class Node:
        def __init__(self, etat, parent, cout, heuristique):
            self.etat = etat
            self.parent = parent
            self.cout = cout
            self.heuristique = heuristique


    def a_star(depart, arrive):
        racine = A_Algorithm_Python_Emmanuel.Node(depart, None, 0, A_Algorithm_Python_Emmanuel.heuristique[depart])
        frontiere = [racine]
        explore = set()

        while frontiere:
            n = min(frontiere, key=lambda node: node.cout + node.heuristique)
            frontiere.remove(n)

            # Si état but :
            if n.etat == arrive:
                return A_Algorithm_Python_Emmanuel.plus_court_chemin(n)

            explore.add(n.etat)

            for voisin, cout_voisin in A_Algorithm_Python_Emmanuel.graphe[n.etat].items():
                nouveau_cout = n.cout + cout_voisin
                heuristique_voisin = A_Algorithm_Python_Emmanuel.heuristique[voisin]

                voisin_node = A_Algorithm_Python_Emmanuel.Node(voisin, n, nouveau_cout, heuristique_voisin)

                if voisin not in explore and voisin_node not in frontiere:
                    frontiere.append(voisin_node)
                elif voisin_node in frontiere:
                    index = frontiere.index(voisin_node)
                    if frontiere[index].cout > voisin_node.cout:
                        frontiere.pop(index)
                        frontiere.append(voisin_node)

        return None  # Pas de chemin trouvé


    def node_min(frontiere):
        return min(frontiere, key=lambda node: node.cout + node.heuristique)


    def plus_court_chemin(node):
        chemin = []
        while node:
            chemin.append(node.etat)
            node = node.parent
        return chemin[::-1]

# Initialise le graphe et l'heuristique
A_Algorithm_Python_Emmanuel.graphe = {
    "A": {"B": 2, "C": 10, "D": 3},
    "B": {"A": 2, "E": 8},
    "E": {"F": 5, "B": 8, "H": 10},
    "D": {"A": 3, "C": 2, "F": 4},
    "C": {"A": 10, "D": 2, "G": 2},
    "F": {"D": 4, "E": 5, "G": 5},
    "G": {"C": 2, "F": 5, "H": 1},
    "H": {"E": 10, "G": 1},
}

A_Algorithm_Python_Emmanuel.heuristique = {
    "A": 9,
    "B": 3,
    "E": 8,
    "D": 6,
    "C": 5,
    "F": 4,
    "G": 2,
    "H": 0,
}

# Utilisation de l'algorithme A*
chemin_trouve = A_Algorithm_Python_Emmanuel.a_star("A", "H")

if chemin_trouve:
    print("Chemin trouvé:", chemin_trouve)
else:
    print("Pas de chemin trouvé.")
