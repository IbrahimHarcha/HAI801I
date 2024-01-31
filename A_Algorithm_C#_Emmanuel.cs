using System;
using System.Collections.Generic;
using System.Linq;

public class A_Algorithm_CSharp_Emmanuel{

    private static Dictionary<string, Dictionary<string, int>> graphe = new Dictionary<string, Dictionary<string, int>>();
    private static Dictionary<string, int> heuristique = new Dictionary<string, int>();

    public class Node{
        public string Etat { get; set; }
        public Node Parent { get; set; }
        public int Cout { get; set; }
        public int Heuristique { get; set; }

        public Node(string etat, Node parent, int cout, int heuristique){
            Etat = etat;
            Parent = parent;
            Cout = cout;
            Heuristique = heuristique;
        }
    }

    public static List<string> AStar(string depart, string arrive){
        Node racine = new Node(depart, null, 0, heuristique[depart]);
        List<Node> frontiere = new List<Node>();
        HashSet<string> explore = new HashSet<string>();

        frontiere.Add(racine);

        while (frontiere.Any()){
            Node n = NodeMin(frontiere);

            frontiere.Remove(n);

            // Si état but :
            if (n.Etat.Equals(arrive)){
                return PlusCourtChemin(n);
            }

            explore.Add(n.Etat);

            foreach (var voisin in graphe[n.Etat]){
                string voisinName = voisin.Key;
                int coutVoisin = voisin.Value;
                int nouveauCout = n.Cout + coutVoisin;
                int heuristiqueVoisin = heuristique[voisinName];

                Node voisinNode = new Node(voisinName, n, nouveauCout, heuristiqueVoisin);

                if (!explore.Contains(voisinName) && !frontiere.Contains(voisinNode)){
                    frontiere.Add(voisinNode);
                }
                else if (frontiere.Contains(voisinNode)){
                    Node newNode = frontiere.First(node => node.Equals(voisinNode));
                    if (newNode.Cout > voisinNode.Cout){
                        frontiere.Remove(newNode);
                        frontiere.Add(voisinNode);
                    }
                }
            }
        }

        return null; // Pas de chemin trouvé
    }

    private static Node NodeMin(List<Node> frontiere){
        return frontiere.OrderBy(node => node.Cout + node.Heuristique).First();
    }

    private static List<string> PlusCourtChemin(Node node){
        List<string> chemin = new List<string>();
        while (node != null){
            chemin.Add(node.Etat);
            node = node.Parent;
        }
        chemin.Reverse();
        return chemin;
    }

    public static void Main(){
        // Initialise le graphe et l'heuristique
        graphe["A"] = new Dictionary<string, int> { { "B", 2 }, { "C", 10 }, { "D", 3 } };
        graphe["B"] = new Dictionary<string, int> { { "A", 2 }, { "E", 8 } };
        graphe["E"] = new Dictionary<string, int> { { "F", 5 }, { "B", 8 }, { "H", 10 } };
        graphe["D"] = new Dictionary<string, int> { { "A", 3 }, { "C", 2 }, { "F", 4 } };
        graphe["C"] = new Dictionary<string, int> { { "A", 10 }, { "D", 2 }, { "G", 2 } };
        graphe["F"] = new Dictionary<string, int> { { "D", 4 }, { "E", 5 }, { "G", 5 } };
        graphe["G"] = new Dictionary<string, int> { { "C", 2 }, { "F", 5 }, { "H", 1 } };
        graphe["H"] = new Dictionary<string, int> { { "E", 10 }, { "G", 1 } };

        heuristique["A"] = 9;
        heuristique["B"] = 3;
        heuristique["E"] = 8;
        heuristique["D"] = 6;
        heuristique["C"] = 5;
        heuristique["F"] = 4;
        heuristique["G"] = 2;
        heuristique["H"] = 0;

        // Utilisation de l'algorithme A*
        List<string> chemin = AStar("A", "H");

        if (chemin != null){
            Console.WriteLine("Chemin trouvé : " + string.Join(" -> ", chemin));
        }
        else{
            Console.WriteLine("Pas de chemin trouvé.");
        }
    }
}
