/*
  INF3105 -- Structures de données et algorithmes.
  UQAM / Département d'informatique -- Automne 2012.
  Squelette à compléter pour TP3.
*/

#include <assert.h>
#include <math.h>
#include "coordonnee.h"

#define PI 3.14159265359
#define RAYONTERRE 6371000

Coordonnee::Coordonnee(const Coordonnee& coor)
    : longitude(coor.longitude), latitude(coor.latitude) {
}

Coordonnee::Coordonnee(double longitude_, double latitude_)
    : longitude(longitude_), latitude(latitude_) {
}

double Coordonnee::distance(const Coordonnee& coor) const {
    double s1 = sin((coor.latitude-latitude)/2);
    double s2 = sin((coor.longitude-longitude)/2);

    return 2*RAYONTERRE * asin(sqrt(s1*s1 + cos(latitude)*cos(coor.latitude)*s2*s2));
}

std::ostream& operator << (std::ostream& os, const Coordonnee& coor) {
    os << "("
    << (coor.longitude / 180.0 * PI)
    << ","
    << (coor.latitude / 180.0 * PI)
    << ")";
    return os;
}

std::istream& operator >> (std::istream& is, Coordonnee& coor) {
    char po, vir, pf;
    is >> po;
    if(is) {
        is >> coor.longitude >> vir >> coor.latitude >> pf;
        assert(po=='(');
        assert(vir==',');
        assert(pf==')');
        coor.longitude *= PI / 180.0;
        coor.latitude  *= PI / 180.0;
    }
    return is;
}


