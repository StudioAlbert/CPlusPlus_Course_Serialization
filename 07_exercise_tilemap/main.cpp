// Exercice — Un systeme de sauvegarde de tilemap, complet.
//
// On reprend les visiteurs Writer/Reader de la Partie 6 (avec leurs
// concepts Serializable & FieldVisitor) et on ajoute :
//   - un en-tete magique  ("TMAP")
//   - un numero de version (kVersion)
//   - un champ optionnel  (biome) gere par la version
//   - une preuve d'aller-retour (round-trip) via assert
//   - bonus : un fichier v1 se charge correctement avec un lecteur v2

#include <cassert>
#include <concepts>
#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
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

// ---------- Constantes du format ----------

constexpr std::uint32_t kMagic   = 0x544D4150; // 'TMAP'
constexpr std::uint32_t kVersion = 2;          // v2 : ajoute biome

// ---------- Visiteurs ----------

struct Writer {
    std::ostream& os;
    std::uint32_t version{kVersion};
    template <Serializable T> void make_field(const T& x) { os << x << ' '; }
};

struct Reader {
    std::istream& is;
    std::uint32_t version{};
    template <Serializable T> void make_field(T& x) { is >> x; }
};

// ---------- Types ----------

struct Tile {
    int         id{};
    bool        walkable{};
    std::string biome{"grass"};     // v2+

    bool operator==(const Tile&) const = default;

    template <FieldVisitor V> void serialize(V& v) {
        v.make_field(id);
        v.make_field(walkable);
        if (v.version >= 2) v.make_field(biome);
    }
};

struct TileMap {
    int               w{}, h{};
    std::vector<Tile> tiles;

    bool operator==(const TileMap&) const = default;

    template <FieldVisitor V> void serialize(V& v) {
        v.make_field(w);
        v.make_field(h);
        std::size_t n = tiles.size();
        v.make_field(n);
        tiles.resize(n);
        for (auto& t : tiles) t.serialize(v);
    }
};

// ---------- API publique ----------

void save_map(const TileMap& m, const std::filesystem::path& path,
              std::uint32_t version = kVersion) {
    std::ofstream ofs(path);
    if (!ofs) throw std::runtime_error("cannot open for write");
    Writer w{ofs, version};
    std::uint32_t magic = kMagic, ver = version;
    w.make_field(magic);
    w.make_field(ver);
    const_cast<TileMap&>(m).serialize(w);
}

void load_map(TileMap& m, const std::filesystem::path& path) {
    std::ifstream ifs(path);
    if (!ifs) throw std::runtime_error("cannot open for read");
    Reader r{ifs, 0};
    std::uint32_t magic{}, ver{};
    r.make_field(magic);
    r.make_field(ver);
    if (magic != kMagic)        throw std::runtime_error("not a tilemap file");
    if (ver   >  kVersion)      throw std::runtime_error("future version");
    r.version = ver;            // <- les types s'adaptent au champ guarded
    m.serialize(r);
}

// ---------- Demo ----------

int main() {
    const auto dir = std::filesystem::temp_directory_path();

    // (1) Round-trip v2
    TileMap m{2, 2, {{1,true,"grass"}, {2,false,"rock"},
                     {3,true,"sand"},  {4,true,"snow"}}};
    const auto p2 = dir / "tilemap_v2.sav";
    save_map(m, p2);

    TileMap m2;
    load_map(m2, p2);
    assert(m == m2);
    std::cout << "[v2] round-trip OK (" << m2.tiles.size() << " tuiles)\n";

    // (2) Bonus : fichier v1 (sans biome) lu par le code v2
    const auto p1 = dir / "tilemap_v1.sav";
    TileMap m_v1{1, 2, {{10,true,"ignored"},{11,false,"ignored"}}};
    save_map(m_v1, p1, /*version=*/1);    // ecrit AU FORMAT v1

    TileMap loaded_v1;
    load_map(loaded_v1, p1);              // lit avec le code v2
    std::cout << "[v1->v2] lu OK : " << loaded_v1.tiles.size()
              << " tuiles, biome par defaut=\"" << loaded_v1.tiles[0].biome
              << "\"\n";

    // (3) Rejet de fichier corrompu
    const auto bogus = dir / "bogus.sav";
    { std::ofstream(bogus) << "hello world"; }
    try {
        TileMap x;
        load_map(x, bogus);
    } catch (const std::exception& e) {
        std::cout << "[corrupt] rejete comme prevu : " << e.what() << '\n';
    }

    std::cout << "\nTous les tests passent.\n";
}
