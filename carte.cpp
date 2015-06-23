/*
  INF3105 -- Structures de données et algorithmes
  UQAM / Département d'informatique
  Hiver 2013
  TP3
  Mathieu Pronovost PROM18118300
  Gregory Pellegrin PELG27129000
*/

#include <assert.h>
#include "carte.h"
#include <string>
#include <list>
#include <map>
#include <istream>
#include <set>
#include "coordonnee.h"
#include <map>

using namespace std;

int nbLieu = 0;
int nbRue = 0;

int locA = 0;
int locB = 0;
string txtLieuC = "";
string txtLieuD = "";


void Carte::ajouterLieu(const string& nom, const Coordonnee& c) {
    nomLieu[nbLieu] = nom;
    coordLieu[nbLieu] = c;
    nbLieu++;
}

void Carte::ajouterRoute(const string& nom, list<string>& route) {
    nomRue[nbRue] = nom;
    pointRue[nbRue] = route;
    nbRue++;
}


// Utilise l'algorithme de dijkstra tel que donné dans les notes de cours à la page 125
double Carte::calculerTrajet(const string& origine, const list<string>& destinations,
                             std::list<string>& out_cheminnoeuds, std::list<string>& out_cheminroutes) const {

    map<int, string> nomLieu2 = nomLieu;
    map<int, Coordonnee> coordLieu2 = coordLieu;
    map<int, string> nomRue2 = nomRue;
    map<int, list<string> > pointRue2 = pointRue;

    const string& premieredestination = *destinations.begin();
    int s = 0;
    int dest = 0;
    double distances[nbLieu];
    double distanceFinale = 0;

    for (int i = 0; i < nbLieu; i++) {
        if (nomLieu2[i] == origine) {
            s = i;
        }

        if (nomLieu2[i] == premieredestination) {
            dest = i;
        }

        distances[i] = 9999999;
    }

    string txtLieuA = "";
    string txtLieuB = "";
    int nbLieuA = 0;
    int nbLieuB = 0;
    int nbArrete = 0;
    double distanceAB = 0;

    list<int> listeLieuA;
    list<int> listeLieuB;
    list<double> listeDistanceAB;
    list<string> listeLieu;

    // Calcule la distance des arrêtes
    for (int i = 0; i < nbRue; i++) {
        listeLieu = pointRue2[i];
        while(!listeLieu.empty()) {
            txtLieuA = *listeLieu.begin();
            listeLieu.pop_front();
            if (!listeLieu.empty()) {
                txtLieuB = *listeLieu.begin();
                for (int j = 0; j < nbLieu; j++) {
                    if (nomLieu2[j] == txtLieuA) {
                        nbLieuA = j;
                    }
                    if (nomLieu2[j] == txtLieuB) {
                        nbLieuB = j;
                    }
                }
                distanceAB = coordLieu2[nbLieuA].distance(coordLieu2[nbLieuB]);
                listeLieuA.push_back(nbLieuA);
                listeLieuB.push_back(nbLieuB);
                listeDistanceAB.push_back(distanceAB);
                nbArrete++;
            }
        }
    }


    int E0[nbArrete];
    int E1[nbArrete];
    double E2[nbArrete];

    // Met les list dans des array afin qu'ils soient plus faciles à traiter
    for (int i = 0; i < nbArrete; i++) {
        E0[i] = *listeLieuA.begin();
        listeLieuA.pop_front();
        E1[i] = *listeLieuB.begin();
        listeLieuB.pop_front();
        E2[i] = *listeDistanceAB.begin();
        listeDistanceAB.pop_front();
    }


    distances[s] = 0;

    list<int> Q;
    Q.push_front(s);

    // Met s au début de la liste
    for (int i = 0; i < nbLieu; i++) {
        if (nomLieu2[i] != nomLieu2[s]) {
            Q.push_back(i);
        }
    }

    int stop = nbLieu;
    double d = 0;
    int parents[nbLieu];

    while (stop > 0) {
        for (int j = 0; j < nbArrete; j++) {
            if (E0[j] == *Q.begin()) {
                d = distances[*Q.begin()] + E2[j];
                if (d < distances[E1[j]]) {
                    parents[E1[j]] = *Q.begin();
                    distances[E1[j]] = d;
                }
            }
        }
        Q.pop_front();

        // Place en ordre croissant par rapport à la distance
        list<int> temp;
        temp.push_front(*Q.begin());
        Q.pop_front();
        while(!Q.empty()) {
            if (distances[*Q.begin()] > distances[*temp.begin()]) {
                temp.push_back(*Q.begin());
            } else {
                temp.push_front(*Q.begin());
            }
            Q.pop_front();
        }
        Q = temp;
        stop--;
    }

    distanceFinale += distances[dest];

    // Met le chemin dans out_cheminnoeuds
    out_cheminnoeuds.push_back(origine);
    list<int> chemin;
    int dest2 = dest;
    while (dest2 != s) {
        dest2 = parents[dest2];
        if (dest2 != s) {
            chemin.push_front(dest2);

        }
    }
    while(!chemin.empty()) {
        out_cheminnoeuds.push_back(nomLieu2[*chemin.begin()]);
        chemin.pop_front();
    }
    out_cheminnoeuds.push_back(premieredestination);


    // Recommence pour le retour
    int dest3 = dest;
    dest = s;
    s = dest3;

    for (int i = 0; i < nbLieu; i++) {
        distances[i] = 9999999;
    }

    txtLieuA = "";
    txtLieuB = "";
    nbLieuA = 0;
    nbLieuB = 0;
    nbArrete = 0;
    distanceAB = 0;

    listeLieu.clear();
    listeLieuA.clear();
    listeLieuB.clear();
    listeDistanceAB.clear();

    for (int i = 0; i < nbRue; i++) {
        listeLieu = pointRue2[i];
        while(!listeLieu.empty()) {
            txtLieuA = *listeLieu.begin();
            listeLieu.pop_front();
            if (!listeLieu.empty()) {
                txtLieuB = *listeLieu.begin();
                for (int j = 0; j < nbLieu; j++) {
                    if (nomLieu2[j] == txtLieuA) {
                        nbLieuA = j;
                    }
                    if (nomLieu2[j] == txtLieuB) {
                        nbLieuB = j;
                    }
                }
                distanceAB = coordLieu2[nbLieuA].distance(coordLieu2[nbLieuB]);
                listeLieuA.push_back(nbLieuA);
                listeLieuB.push_back(nbLieuB);
                listeDistanceAB.push_back(distanceAB);
                nbArrete++;
            }
        }
    }



    for (int i = 0; i < nbArrete; i++) {
        E0[i] = *listeLieuA.begin();
        listeLieuA.pop_front();
        E1[i] = *listeLieuB.begin();
        listeLieuB.pop_front();
        E2[i] = *listeDistanceAB.begin();
        listeDistanceAB.pop_front();
    }

    distances[s] = 0;

    Q.clear();
    Q.push_front(s);

    for (int i = 0; i < nbLieu; i++) {
        if (nomLieu2[i] != nomLieu2[s]) {
            Q.push_back(i);
        }
    }

    stop = nbLieu;
    d = 0;

    while (stop > 0) {
        for (int j = 0; j < nbArrete; j++) {
            if (E0[j] == *Q.begin()) {
                d = distances[*Q.begin()] + E2[j];
                if (d < distances[E1[j]]) {
                    parents[E1[j]] = *Q.begin();
                    distances[E1[j]] = d;
                }
            }
        }
        Q.pop_front();

        list<int> temp;
        temp.push_front(*Q.begin());
        Q.pop_front();
        while(!Q.empty()) {
            if (distances[*Q.begin()] > distances[*temp.begin()]) {
                temp.push_back(*Q.begin());
            } else {
                temp.push_front(*Q.begin());
            }
            Q.pop_front();
        }
        Q = temp;
        stop--;
    }

    distanceFinale += distances[dest];

    // Met le reste du chemin dans out_cheminnoeuds
    chemin.clear();
    dest2 = dest;
    while (dest2 != s) {
        dest2 = parents[dest2];
        if (dest2 != s) {
            chemin.push_front(dest2);
        }
    }
    while(!chemin.empty()) {
        out_cheminnoeuds.push_back(nomLieu2[*chemin.begin()]);
        chemin.pop_front();
    }
    out_cheminnoeuds.push_back(origine);


    // Met l'ordre des rues dans out_cheminroutes
    list<string> listeRues = out_cheminnoeuds;
    listeLieu.clear();
    bool okA = false;
    bool okB = false;
    txtLieuA = "";
    txtLieuB = "";
    txtLieuC = "";
    txtLieuD = "";
    while (!listeRues.empty()) {
        txtLieuA = *listeRues.begin();
        listeRues.pop_front();
        if (!listeRues.empty()) {
            txtLieuB = *listeRues.begin();
            for (int i = 0; i < nbRue; i++) {
                listeLieu = pointRue2[i];
                while(!listeLieu.empty()) {
                    txtLieuC = *listeLieu.begin();
                    if (txtLieuA == txtLieuC) {
                        okA = true;
                    }

                    if (txtLieuB == txtLieuC) {
                        okB = true;
                    }

                    listeLieu.pop_front();
                }
                if (okA && okB) {
                    if (nomRue2[i] != txtLieuD) {
                        out_cheminroutes.push_back(nomRue2[i]);
                    }
                    txtLieuD = nomRue2[i];
                    i = nbRue;

                }
                okA = false;
                okB = false;
            }
        }
    }

    return distanceFinale;
}



/* Lire une carte. */
istream& operator >> (istream& is, Carte& carte) {
    // Lire les lieux
    while(is) {
        string nomlieu;
        is >> nomlieu;
        if(nomlieu == "---") break;
        Coordonnee coor;
        is >> coor;

        carte.ajouterLieu(nomlieu, coor);
    }

    // Lire les routes
    while(is) {
        string nomroute;
        is >> nomroute;
        if(nomroute == "---") break;

        char deuxpoints;
        is >> deuxpoints;
        assert(deuxpoints == ':');

        std::list<std::string> listenomslieux;

        while(is) {
            string nomlieu;
            is>>nomlieu;
            if(nomlieu==";") break;
            listenomslieux.push_back(nomlieu);
        }

        carte.ajouterRoute(nomroute, listenomslieux);
    }

    return is;
}

