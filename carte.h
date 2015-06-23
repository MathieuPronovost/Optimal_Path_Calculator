/*
  INF3105 -- Structures de données et algorithmes
  UQAM / Département d'informatique
  Hiver 2013
  TP3
  Mathieu Pronovost PROM18118300
  Gregory Pellegrin PELG27129000
*/

#if !defined(__CARTE_H__)
#define __CARTE_H__

#include <istream>
#include <string>
#include <list>
#include <set>
#include "coordonnee.h"
#include <map>

using namespace std;

class Carte{
  public:

    void ajouterLieu(const string& nom, const Coordonnee& c);

    void ajouterRoute(const string& nom, list<string>& noms);

    double calculerTrajet(const string& origine, const list<string>& destination,
                          std::list<string>& out_cheminnoeuds, std::list<string>& out_cheminroutes) const;

  private:
    map<int, string> nomLieu;
    map<int, Coordonnee> coordLieu;

    map<int, string> nomRue;
    map<int, list<string> > pointRue;



  friend istream& operator >> (istream& is, Carte& carte);
};

#endif

