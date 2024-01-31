import java.util.*;

public class A_Algorithm_Java_Emmanuel {

    private static Map<String, Map<String, Integer>> graphe = new HashMap<>();
    private static Map<String, Integer> heuristique = new HashMap<>();
    
    public static class Node {
        String etat;
        Node parent;
        int cout;
        int heuristique;

        public Node(String etat, Node parent, int cout, int heuristique){
            this.etat = etat;
            this.parent = parent;
            this.cout = cout;
            this.heuristique = heuristique;
        }
    }

    public static Vector<String> aStar (String depart, String arrive){
        Node racine = new Node(depart, null, 0, heuristique.get(depart));
        Vector<Node> frontiere = new Vector<Node>();

        Set<String> explore = new HashSet<>();

        frontiere.add(racine);

        while (!frontiere.isEmpty()) {
            Node n = nodeMin(frontiere);

            frontiere.remove(n);

            // Si état but :
            if(n.etat.equals(arrive)){
                return plus_court_chemin(n);
            }
            
            explore.add(n.etat);

            for (String voisin : graphe.get(n.etat).keySet()) {

                int coutVoisin = graphe.get(n.etat).get(voisin);
                int nouveauCout = n.cout + coutVoisin;
                int heuristiqueVoisin = heuristique.get(voisin);

                Node voisinNode = new Node(voisin, n, nouveauCout, heuristiqueVoisin);

                if (!explore.contains(voisin) && !frontiere.contains(voisinNode)) {
                    frontiere.add(voisinNode);
                } else if (frontiere.contains(voisinNode)) {
    
                    Node newNode = frontiere.get(frontiere.indexOf(voisinNode));
                    if (newNode.cout > voisinNode.cout) {
                        frontiere.remove(newNode);
                        frontiere.add(voisinNode);
                    }
                }
            }
        }

        return null; // Pas de chemin trouvé
       
    }

    private static Node nodeMin(Vector<Node> frontiere) {
        return Collections.min(frontiere, Comparator.comparingInt(node -> node.cout + node.heuristique));
    }

    private static Vector<String> plus_court_chemin(Node node) {
        Vector<String> chemin = new Vector<>();
        while (node != null) {
            chemin.add(node.etat);
            node = node.parent;
        }
        Collections.reverse(chemin);
        return chemin;
    }

    public static void main(String[] args) {
        // Initialise le graphe et l'heuristique
        graphe.put("A", Map.of("B", 2, "C", 10, "D", 3));
        graphe.put("B", Map.of("A", 2, "E", 8));
        graphe.put("E", Map.of("F", 5, "B", 8, "H", 10));
        graphe.put("D", Map.of("A", 3, "C", 2, "F", 4));
        graphe.put("C", Map.of("A", 10, "D", 2, "G", 2));
        graphe.put("F", Map.of("D", 4, "E", 5, "G", 5));
        graphe.put("G", Map.of("C", 2, "F", 5, "H", 1));
        graphe.put("H", Map.of("E", 10, "G", 1));

        heuristique.put("A", 9);
        heuristique.put("B", 3);
        heuristique.put("E", 8);
        heuristique.put("D", 6);
        heuristique.put("C", 5);
        heuristique.put("F", 4);
        heuristique.put("G", 2);
        heuristique.put("H", 0);

        // Utilisation de l'algorithme A*
        Vector<String> chemin = aStar("A", "H");

        if (chemin != null) {
            System.out.println("Chemin trouvé : " + chemin);
        } else {
            System.out.println("Pas de chemin trouvé.");
        }
    }
}

