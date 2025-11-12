/*
 * td3-2: Aladdin Magic Kingdom
 * Autrices :
 * - Hadil ABAHMANE
 * - Oumnia ASMAR
 * - Aminta DIOUF
 * - Arij FELLAH
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoeudVoisin {
    int destination;
    struct NoeudVoisin* suivant;
} NoeudVoisin;

typedef struct ListeAdjacence {
    NoeudVoisin *tete;
} ListeAdjacence;

typedef struct Graphe {
    int nbLieux;
    ListeAdjacence* tableauListes;
} Graphe;

NoeudVoisin* creerNoeudVoisin(int destination) {
    NoeudVoisin* nouveauNoeud = (NoeudVoisin*) malloc(sizeof(NoeudVoisin));
    nouveauNoeud->destination = destination;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

Graphe* creerGraphe(int nbLieux) {
    Graphe* graphe = (Graphe*) malloc(sizeof(Graphe));
    graphe->nbLieux = nbLieux;
    graphe->tableauListes = (ListeAdjacence*) malloc((nbLieux + 1) * sizeof(ListeAdjacence));
    for (int i = 0; i <= nbLieux; ++i) {
        graphe->tableauListes[i].tete = NULL;
    }
    return graphe;
}

void ajouterRoute(Graphe* graphe, int lieu1, int lieu2) {
    NoeudVoisin* nouveauNoeud1 = creerNoeudVoisin(lieu2);
    nouveauNoeud1->suivant = graphe->tableauListes[lieu1].tete;
    graphe->tableauListes[lieu1].tete = nouveauNoeud1;

    NoeudVoisin* nouveauNoeud2 = creerNoeudVoisin(lieu1);
    nouveauNoeud2->suivant = graphe->tableauListes[lieu2].tete;
    graphe->tableauListes[lieu2].tete = nouveauNoeud2;
}

void libererGraphe(Graphe* graphe) {
    for (int i = 1; i <= graphe->nbLieux; i++) {
        NoeudVoisin* actuel = graphe->tableauListes[i].tete;
        while (actuel != NULL) {
            NoeudVoisin* temp = actuel;
            actuel = actuel->suivant;
            free(temp);
        }
    }
    free(graphe->tableauListes);
    free(graphe);
}

 /* PARTIE 1 : COMPTER LES ROYAUMES
 On utilise un Parcours en Profondeur (DFS) */

void parcoursProfondeur(int lieu, bool visite[], Graphe* graphe) {
    visite[lieu] = true;
    NoeudVoisin* voisinActuel = graphe->tableauListes[lieu].tete;
    while (voisinActuel) {
        if (!visite[voisinActuel->destination]) {
            parcoursProfondeur(voisinActuel->destination, visite, graphe);
        }
        voisinActuel = voisinActuel->suivant;
    }
}

int compterRoyaumes(Graphe* graphe) {
    int nbLieuxTotal = graphe->nbLieux;
    bool* visite = (bool*) malloc((nbLieuxTotal + 1) * sizeof(bool));
    for (int i = 1; i <= nbLieuxTotal; i++) {
        visite[i] = false;
    }

    int compteur = 0;
    for (int lieu = 1; lieu <= nbLieuxTotal; lieu++) {
        if (visite[lieu] == false) {
            parcoursProfondeur(lieu, visite, graphe);
            compteur++;
        }
    }
    free(visite);
    return compteur;
}

/* PARTIE 2 : TROUVER LE PLUS COURT CHEMIN
 On utilise un Parcours en Largeur*/ 
int trouverCheminPlusCourt(Graphe* graphe, int depart, int arrivee) {
    if (depart == arrivee) {
        return 0;
    }

    int nbLieuxTotal = graphe->nbLieux;
    int* distance = (int*) malloc((nbLieuxTotal + 1) * sizeof(int));
    int* file = (int*) malloc(nbLieuxTotal * sizeof(int));
    int debutFile = 0, finFile = 0;

    for (int i = 1; i <= nbLieuxTotal; i++) {
        distance[i] = -1;
    }

    distance[depart] = 0;
    file[finFile++] = depart;

    while (debutFile < finFile) {
        int lieuActuel = file[debutFile++];
        NoeudVoisin* voisin = graphe->tableauListes[lieuActuel].tete;
        while (voisin) {
            int destinationVoisin = voisin->destination;
            if (distance[destinationVoisin] == -1) {
                distance[destinationVoisin] = distance[lieuActuel] + 1;
                file[finFile++] = destinationVoisin;

                if (destinationVoisin == arrivee) {
                    int resultat = distance[arrivee];
                    free(distance);
                    free(file);
                    return resultat;
                }
            }
            voisin = voisin->suivant;
        }
    }

    int resultat = distance[arrivee];
    free(distance);
    free(file);
    return resultat;
}

int main() {
    int nombreLieux, nombreRoutes;
    scanf("%d %d", &nombreLieux, &nombreRoutes);

    Graphe* royaume = creerGraphe(nombreLieux);

    for (int i = 0; i < nombreRoutes; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        ajouterRoute(royaume, u, v);
    }

    int palaisAladdin, palaisJasmine;
    scanf("%d %d", &palaisAladdin, &palaisJasmine);

    int nbRoyaumes = compterRoyaumes(royaume);
    printf("%d\n", nbRoyaumes);

    int cheminPlusCourt = trouverCheminPlusCourt(royaume, palaisAladdin, palaisJasmine);
    printf("%d\n", cheminPlusCourt);

    libererGraphe(royaume);

    return 0;
}
