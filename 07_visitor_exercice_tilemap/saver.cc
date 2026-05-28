//
// Created by sebas on 28.05.2026.
//

#include "saver.h"
#include "tile.h"
#include "tilemap.h"

void Saver::visit(std::filesystem::path& path, Tile& tile) {
  ofs << tile.x << ";" << tile.y << ";" << tile.walkable << ";" << tile.biome << "\n";
}

void Saver::visit(std::filesystem::path& path, Tilemap& tilemap) {

  open(path);

  ofs << tilemap.sizeX << ";" << tilemap.sizeY << "\n";
  for (auto& tile : tilemap.tiles) {
    visit(path, tile);
  }

  close();

}

void Saver::open(std::filesystem::path& path) {
  ofs.open(path);
}

void Saver::close() {
  ofs.close();
}