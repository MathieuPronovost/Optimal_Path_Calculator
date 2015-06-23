/*
  INF3105 -- Structures de données et algorithmes
  UQAM / Département d'informatique
  Hiver 2013
  Squelette pour le TP3
*/


#include <assert.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include "carte.h"

using namespace std;

void tp3(std::istream& entree) {
    Carte carte;
    entree >> carte;

    string position_pizzeria;
    entree >> position_pizzeria;
    // Suggestion :
    //assert(carte.lieuExiste(position_pizzeria));

    {
        string sep;
        entree >> sep;
        assert(sep=="---");
    }

    while(entree) {
        list<string> destinations;
        while(entree) {
            string destination;
            entree >> destination;
            if(destination==";" || !entree) break;
            destinations.push_back(destination);
        }
        if(destinations.empty()) break;

        list<string> chemin_noeuds, chemin_routes;
        double distance = carte.calculerTrajet(position_pizzeria, destinations, chemin_noeuds, chemin_routes);

        for(list<string>::const_iterator iter=chemin_noeuds.begin(); iter!=chemin_noeuds.end(); ++iter)
            cout << *iter << " ";
        cout << endl;
        for(list<string>::const_iterator iter=chemin_routes.begin(); iter!=chemin_routes.end(); ++iter)
            cout << *iter << " ";
        cout << endl;
        cout << round(distance) << " m" << endl;
    }

}

int main(int argc, const char** argv) {
    if(argc>1) {
        // Lecture depuis un fichier.
        std::ifstream entreefichier(argv[1]);
        if(entreefichier.fail())
            cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'!" << std::endl;
        else
            tp3(entreefichier);
    } else {
        // Lecture depuis stdin (console).
        tp3(cin);
    }
    return 0;
}

