#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

struct graphe {
    int node;
    int h;
    std::vector<graphe*> chemin;
    std::vector<int> cout;
};

void A_Etoile(graphe* d){
    int l;
    int index = 0;
    bool fin = false;
    while (!fin) {
        l = 99999;
        for (int i = 0; i < d->chemin.size(); i++) {
            if (d->cout[i] + d->chemin[i]->h < l) {
                l = d->cout[i] + d->chemin[i]->h;
                index = i;
            }
        }
        d->chemin[index]->h = 99999;
        if (d->chemin[index]->node == 8) {
            fin = true;
            printf("noeud trouvé\n");
            break;
        }
        for (int i = 0; i < d->chemin[index]->chemin.size(); i++) {
            d->chemin.push_back(d->chemin[index]->chemin[i]);
            d->cout.push_back(d->chemin[index]->cout[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    graphe A, B, C, D, E, F, G, H;
    A.node = 1;
    B.node = 2;
    C.node = 3;
    D.node = 4;
    E.node = 5;
    F.node = 6;
    G.node = 7;
    H.node = 8;
    A.h = 9;
    B.h = 3;
    C.h = 5;
    D.h = 6;
    E.h = 8;
    F.h = 4;
    G.h = 2;
    H.h = 0;
    A.chemin.push_back(&B);
    A.chemin.push_back(&C);
    A.chemin.push_back(&D);
    printf("nb chemins de A %ld \n",A.chemin.size());
    B.chemin.push_back(&E);
    printf("nb chemins de B %ld \n",B.chemin.size());
    D.chemin.push_back(&C);
    D.chemin.push_back(&F);
    printf("nb chemins de D %ld \n",D.chemin.size());
    C.chemin.push_back(&G);
    printf("nb chemins de C %ld \n",C.chemin.size());
    F.chemin.push_back(&E);
    E.chemin.push_back(&H);
    F.chemin.push_back(&E);
    F.chemin.push_back(&G);
    G.chemin.push_back(&H);
    printf("nb chemins de E %ld \n",E.chemin.size());
    printf("nb chemins de F %ld \n",F.chemin.size());
    printf("nb chemins de G %ld \n",G.chemin.size());
    A.cout.push_back(2);
    A.cout.push_back(10);
    A.cout.push_back(3);
    B.cout.push_back(8);
    D.cout.push_back(2);
    D.cout.push_back(4);
    C.cout.push_back(2);
    F.cout.push_back(5);
    E.cout.push_back(10);
    F.cout.push_back(5);
    F.cout.push_back(5);
    G.cout.push_back(1);
    A_Etoile(&A); 
    return 0;
}
