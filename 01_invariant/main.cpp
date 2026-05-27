// Partie 1 — L'Unique Invariant : serialize / deserialize sont des miroirs.
// On démontre la désynchronisation silencieuse quand l'ordre des champs
// diffère entre save et load.

#include <iostream>
#include <sstream>

struct Tile {
    int  id{};
    bool walkable{};
};

void save_ok(std::ostream& os, const Tile& t) {
    os << t.id << ' ' << t.walkable << '\n';     // id, puis walkable
}

void load_ok(std::istream& is, Tile& t) {
    is >> t.id >> t.walkable;                    // id, puis walkable
}

void load_buggy(std::istream& is, Tile& t) {
    is >> t.walkable >> t.id;                    // ❌ ordre inversé
}

int main() {
    Tile original{42, true};

    {
        std::stringstream s;
        save_ok(s, original);
        Tile reloaded;
        load_ok(s, reloaded);
        std::cout << "[OK]   id=" << reloaded.id
                  << " walkable=" << reloaded.walkable << '\n';
    }

    {
        std::stringstream s;
        save_ok(s, original);
        Tile reloaded;
        load_buggy(s, reloaded);
        std::cout << "[BUG]  id=" << reloaded.id
                  << " walkable=" << reloaded.walkable
                  << "   <- desync silencieuse, ni exception ni crash\n";
    }
}
