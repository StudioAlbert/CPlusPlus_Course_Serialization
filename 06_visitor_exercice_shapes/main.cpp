// Partie 6 — Le patron Visiteur applique au save/load.
//
// Une SEULE liste de champs par type (la methode serialize templatee).
// Deux visiteurs concrets : Writer (sauvegarde) et Reader (chargement).
// L'ordre ne peut JAMAIS diverger : il n'y a qu'une fonction.
//
// On nomme les contrats avec deux concepts C++20 pour que les signatures
// se documentent elles-memes :
//   - Serializable<T>   : T est un type-feuille streamable dans les deux sens.
//   - FieldVisitor<V>   : V expose un callback make_field(T&).

#include "shape.h"

#include <iostream>

int main() {

    Circle c;
    c.r = 1.2f;

    Square sq;
    sq.side = 2.f;

    AreaVisitor v;
    std::cout << "Area = " << c.accept(v) << '\n';
    std::cout << "Area = " << sq.accept(v) << '\n';

    PerimeterVisitor w;
    std::cout << "Perimeter = " << c.accept(w) << '\n';
    std::cout << "Perimeter = " << sq.accept(w) << '\n';

    return 0;

}
