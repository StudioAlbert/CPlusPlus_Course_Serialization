// Partie 2 — Deux cas d'usage, un seul mécanisme : sauvegarder (temps)
// vs transmettre (espace). Même fonction, contraintes différentes.
//
// Démo :
//   - on sérialise un PlayerState vers un fichier (cas "save")
//   - on sérialise le MÊME PlayerState vers un buffer (cas "transmit")
//   - on prouve que les deux sorties contiennent les mêmes octets

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct PlayerState {
    std::string name;
    int         hp{};
    int         x{}, y{};
};

void serialize(std::ostream& os, const PlayerState& p) {
    // Format texte simple : un champ par ligne, taille du nom devant.
    os << p.name.size() << ' ' << p.name << '\n'
       << p.hp << '\n'
       << p.x << ' ' << p.y << '\n';
}

void deserialize(std::istream& is, PlayerState& p) {
    std::size_t n;
    is >> n;
    is.get(); // espace
    p.name.resize(n);
    is.read(p.name.data(), static_cast<std::streamsize>(n));
    is >> p.hp >> p.x >> p.y;
}

int main() {
    PlayerState player{"Alice", 87, 12, 34};

    // Cas A : sauvegarder à travers le TEMPS (fichier).
    const auto path = std::filesystem::temp_directory_path() / "player.sav";
    {
        std::ofstream ofs(path);
        serialize(ofs, player);
    }

    // Cas B : transmettre à travers l'ESPACE (buffer mémoire vers, p.ex., socket).
    std::stringstream wire;
    serialize(wire, player);

    // Comparaison : le mécanisme est strictement le même.
    std::ifstream ifs(path);
    std::stringstream from_file;
    from_file << ifs.rdbuf();

    std::cout << "Sortie fichier identique a la sortie reseau : "
              << std::boolalpha << (from_file.str() == wire.str()) << '\n';

    PlayerState reloaded;
    std::stringstream copy(wire.str());
    deserialize(copy, reloaded);
    std::cout << "Reloaded: " << reloaded.name
              << " hp=" << reloaded.hp
              << " pos=(" << reloaded.x << ',' << reloaded.y << ")\n";
}
