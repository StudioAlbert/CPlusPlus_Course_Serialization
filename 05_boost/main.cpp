// Partie 5 — Boost.Serialization : une fonction, deux directions.
//
// Compile uniquement si Boost est trouvé par CMake. Sous vcpkg :
//     vcpkg install boost-serialization
// Sous Debian/Ubuntu :
//     sudo apt install libboost-serialization-dev

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Tile {
public:
  Tile() = default;
  Tile(int id, bool walkable, std::string biome = "grass")
      : id_(id), walkable_(walkable), biome_(std::move(biome)) {}

  int id() const { return id_; }
  bool walkable() const { return walkable_; }
  const std::string &biome() const { return biome_; }

private:
  friend class boost::serialization::access;

  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & id_;
    ar & walkable_;
    if (version > 0)
      ar & biome_; // champ ajoute en v1
  }

  int id_{};
  bool walkable_{};
  std::string biome_{"grass"};
};

BOOST_CLASS_VERSION(Tile, 1)

struct TileMap {
  int w{}, h{};
  std::vector<Tile> tiles;

  template <class Archive>
  void serialize(Archive &ar, const unsigned int /*version*/) {
    ar & w;
    ar & h;
    ar & tiles; // Boost gere std::vector automatiquement
  }
};

int main() {
  TileMap m{2,
            2,
            {Tile(1, true, "grass"), Tile(2, false, "rock"),
             Tile(3, true, "sand"), Tile(4, true, "snow")}};


  const auto path = "D:/_dev/repos/C++/CPlusPlus_Course_Serialization/assets/level.txt";
  {
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << m;
  }
  std::cout << "Enregistrement OK " << path << "(" << m.tiles.size() << " tuiles)\n";

  TileMap m2;
  {
  std::ifstream ifs(path);
  boost::archive::text_iarchive ia(ifs);
  ia >> m2;
}

  std::cout << "Recharge " << m2.tiles.size() << " tuiles (" << m2.w << 'x'
            << m2.h << "):\n";
  for (const auto &t : m2.tiles)
    std::cout << "  id=" << t.id() << " walkable=" << t.walkable()
              << " biome=" << t.biome() << '\n';

  std::cout << "\nLecon : une seule fonction serialize, deux directions,\n"
               "+ versioning et collections geres pour vous.\n";

}
