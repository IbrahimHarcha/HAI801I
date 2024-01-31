#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class A_Algorithm_Cpp_Emmanuel {
public:
    struct Node {
        std::string etat;
        Node* parent;
        int cout;
        int heuristique;

        Node(std::string etat, Node* parent, int cout, int heuristique)
            : etat(etat), parent(parent), cout(cout), heuristique(heuristique) {}
    };

    static std::map<std::string, std::map<std::string, int>> graphe;
    static std::map<std::string, int> heuristique;

    static std::vector<std::string> aStar(std::string depart, std::string arrive) {
        Node* racine = new Node(depart, nullptr, 0, heuristique[depart]);
        std::vector<Node*> frontiere;
        std::set<std::string> explore;

        frontiere.push_back(racine);

        while (!frontiere.empty()) {
            Node* n = nodeMin(frontiere);

            frontiere.erase(std::remove(frontiere.begin(), frontiere.end(), n), frontiere.end());

            // Si état but :
            if (n->etat == arrive) {
                return plus_court_chemin(n);
            }

            explore.insert(n->etat);

            for (const auto& voisin : graphe[n->etat]) {
                std::string voisinName = voisin.first;
                int coutVoisin = voisin.second;
                int nouveauCout = n->cout + coutVoisin;
                int heuristiqueVoisin = heuristique[voisinName];

                Node* voisinNode = new Node(voisinName, n, nouveauCout, heuristiqueVoisin);

                if (explore.find(voisinName) == explore.end() &&
                    std::find(frontiere.begin(), frontiere.end(), voisinNode) == frontiere.end()) {
                    frontiere.push_back(voisinNode);
                } else if (std::find(frontiere.begin(), frontiere.end(), voisinNode) != frontiere.end()) {
                    auto newNode = std::find(frontiere.begin(), frontiere.end(), voisinNode);
                    if ((*newNode)->cout > voisinNode->cout) {
                        frontiere.erase(newNode);
                        frontiere.push_back(voisinNode);
                    }
                }
            }
        }

        return {}; // Pas de chemin trouvé
    }

private:
    static Node* nodeMin(const std::vector<Node*>& frontiere) {
        return *std::min_element(frontiere.begin(), frontiere.end(), [](const Node* node1, const Node* node2) {
            return node1->cout + node1->heuristique < node2->cout + node2->heuristique;
        });
    }

    static std::vector<std::string> plus_court_chemin(Node* node) {
        std::vector<std::string> chemin;
        while (node != nullptr) {
            chemin.push_back(node->etat);
            node = node->parent;
        }
        std::reverse(chemin.begin(), chemin.end());
        return chemin;
    }
};

std::map<std::string, std::map<std::string, int>> A_Algorithm_Cpp_Emmanuel::graphe;
std::map<std::string, int> A_Algorithm_Cpp_Emmanuel::heuristique;

int main() {
    // Initialise le graphe et l'heuristique
    A_Algorithm_Cpp_Emmanuel::graphe["A"] = {{"B", 2}, {"C", 10}, {"D", 3}};
    A_Algorithm_Cpp_Emmanuel::graphe["B"] = {{"A", 2}, {"E", 8}};
    A_Algorithm_Cpp_Emmanuel::graphe["E"] = {{"F", 5}, {"B", 8}, {"H", 10}};
    A_Algorithm_Cpp_Emmanuel::graphe["D"] = {{"A", 3}, {"C", 2}, {"F", 4}};
    A_Algorithm_Cpp_Emmanuel::graphe["C"] = {{"A", 10}, {"D", 2}, {"G", 2}};
    A_Algorithm_Cpp_Emmanuel::graphe["F"] = {{"D", 4}, {"E", 5}, {"G", 5}};
    A_Algorithm_Cpp_Emmanuel::graphe["G"] = {{"C", 2}, {"F", 5}, {"H", 1}};
    A_Algorithm_Cpp_Emmanuel::graphe["H"] = {{"E", 10}, {"G", 1}};

    A_Algorithm_Cpp_Emmanuel::heuristique["A"] = 9;
    A_Algorithm_Cpp_Emmanuel::heuristique["B"] = 3;
    A_Algorithm_Cpp_Emmanuel::heuristique["E"] = 8;
    A_Algorithm_Cpp_Emmanuel::heuristique["D"] = 6;
    A_Algorithm_Cpp_Emmanuel::heuristique["C"] = 5;
    A_Algorithm_Cpp_Emmanuel::heuristique["F"] = 4;
    A_Algorithm_Cpp_Emmanuel::heuristique["G"] = 2;
    A_Algorithm_Cpp_Emmanuel::heuristique["H"] = 0;

    // Utilisation de l'algorithme A*
    std::vector<std::string> chemin = A_Algorithm_Cpp_Emmanuel::aStar("A", "H");

    if (!chemin.empty()) {
        std::cout << "Chemin trouvé : ";
        for (const auto& etat : chemin) {
            std::cout << etat << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Pas de chemin trouvé." << std::endl;
    }

    return 0;
}
