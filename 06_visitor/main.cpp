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

// ---------- Concepts ----------

template <class T>
concept Serializable = requires(std::ostream& os, std::istream& is, T& x) {
    { os << x };
    { is >> x };
};

template <class V>
concept FieldVisitor = requires(V& v, int& probe) {
    { v.make_field(probe) };
};

// ---------- Visiteurs concrets ----------

struct Writer {
    std::ostream& os;
    template <Serializable T> void make_field(const T& x) { os << x << ' '; }
};

struct Reader {
    std::istream& is;
    template <Serializable T> void make_field(T& x) { is >> x; }
};

// ---------- Types ----------

struct Tile {
    int  id{};
    bool walkable{};

    template <FieldVisitor V> void serialize(V& v) {
        v.make_field(id);
        v.make_field(walkable);
    }
};

struct TileMap {
    int               w{}, h{};
    std::vector<Tile> tiles;

    template <FieldVisitor V> void serialize(V& v) {
        v.make_field(w);
        v.make_field(h);
        std::size_t n = tiles.size();
        v.make_field(n);        // ecrit au save, lu au load
        tiles.resize(n);        // no-op au save, dimensionne au load
        for (auto& t : tiles) t.serialize(v);
    }
};

int main() {
    TileMap original{3, 2, {{1,true},{2,false},{3,true},
                            {4,true},{5,false},{6,true}}};

    std::stringstream buf;
    {
        Writer w{buf};
        original.serialize(w);
    }
    std::cout << "Flux serialise : " << buf.str() << '\n';

    TileMap reloaded;
    {
        Reader r{buf};
        reloaded.serialize(r);
    }

    std::cout << "Recharge " << reloaded.w << 'x' << reloaded.h
              << " = " << reloaded.tiles.size() << " tuiles\n";
    for (const auto& t : reloaded.tiles)
        std::cout << "  (" << t.id << ',' << t.walkable << ")\n";

    std::cout << "\nLecon : une seule liste de champs, deux comportements.\n"
                 "Le piege de desynchronisation a disparu PAR CONSTRUCTION,\n"
                 "et les concepts (Serializable, FieldVisitor) rendent les\n"
                 "contrats visibles dans chaque signature.\n";
}
