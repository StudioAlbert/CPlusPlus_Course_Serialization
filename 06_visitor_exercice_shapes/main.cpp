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

#include <concepts>
#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>

struct Shape  { virtual ~Shape() = default; };
struct Circle : Shape { double r; };
struct Square : Shape { double side; };


int main() {

    return 0;
}
