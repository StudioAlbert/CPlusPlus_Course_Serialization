//
// Created by sebas on 27.05.2026.
//

#ifndef CPLUSPLUS_COURSE_SERIALIZATION_TILEMAP_H
#define CPLUSPLUS_COURSE_SERIALIZATION_TILEMAP_H

#include "loader.h"
#include "saver.h"
#include "tile.h"

#include <vector>

class Tilemap {

public:
  int sizeX = 0;
  int sizeY = 0;

  std::vector<Tile> tiles;

  void Save(std::filesystem::path& path, Saver& v) {
    v.visit(path, *this);
  }

  void Load(std::filesystem::path& path, Loader& v) {
    v.visit(path, *this);
  }

};


#endif // CPLUSPLUS_COURSE_SERIALIZATION_TILEMAP_H
