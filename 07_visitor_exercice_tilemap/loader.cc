//
// Created by sebas on 28.05.2026.
//

#include "loader.h"

#include "tilemap.h"
#include "tile.h"

#include <filesystem>
#include <sstream>
#include <string>

void Loader::open(std::filesystem::path & path) {
  ifs.open(path);
}
void Loader::close() {
  ifs.close();
}

void  Loader::visit(std::filesystem::path&, Tile &tile) {
  std::string line;
  if (!std::getline(ifs, line)) return;

  std::stringstream ss(line);
  std::string field;
  std::getline(ss, field, ';'); tile.x = std::stoi(field);
  std::getline(ss, field, ';'); tile.y = std::stoi(field);
  std::getline(ss, field, ';'); tile.walkable = std::stoi(field);
  std::getline(ss, field, ';'); tile.biome = field;

}

void Loader::visit(std::filesystem::path& path, Tilemap &tilemap) {

  open(path);

  std::string header;
  if (!std::getline(ifs, header)) return;

  std::stringstream ss(header);
  std::string field;
  std::getline(ss, field, ';'); tilemap.sizeX = std::stoi(field);
  std::getline(ss, field, ';'); tilemap.sizeY = std::stoi(field);

  while (ifs.peek() != EOF) {
    Tile newTile;
    visit(path, newTile);
    tilemap.tiles.emplace_back(newTile);
  }

  close();

}