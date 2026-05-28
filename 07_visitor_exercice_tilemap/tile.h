//
// Created by sebas on 27.05.2026.
//

#ifndef CPLUSPLUS_COURSE_SERIALIZATION_TILE_H
#define CPLUSPLUS_COURSE_SERIALIZATION_TILE_H

#include "loader.h"
#include "saver.h"

#include <string>

class Tile {

public:
  int x = 0;
  int y = 0;
  bool walkable = false;
  std::string biome;


  void Save(std::filesystem::path& path, Saver& v) {
    v.visit(path, *this);
  }

  void Load(std::filesystem::path& path, Loader& v) {
    v.visit(path, *this);
  }

};

#endif // CPLUSPLUS_COURSE_SERIALIZATION_TILE_H
