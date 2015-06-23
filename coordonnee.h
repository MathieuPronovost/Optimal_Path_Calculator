/*
  INF3105 -- Structures de données et algorithmes
  UQAM / Département d'informatique
  Hiver 2013
  TP3
*/

#if !defined(__COORDONNEE_H__)
#define __COORDONNEE_H__

#include <iostream>

class Coordonnee {

  public:
    Coordonnee(){}
    Coordonnee(double longitude_, double latitude_);
    Coordonnee(const Coordonnee&);

    double distance(const Coordonnee&) const;

  private:
    double longitude;
    double latitude;

  friend std::ostream& operator << (std::ostream&, const Coordonnee&);
  friend std::istream& operator >> (std::istream&, Coordonnee&);
};

#endif

