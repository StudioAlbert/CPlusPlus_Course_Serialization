//
// Created by sebas on 27.05.2026.
//

#include "saver.h"
#include "tile.h"
#include "tilemap.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>

int main() {

  Tile t = {6,6,true,"swamp"};
  Tile tLoaded;

  Tilemap map;
  map.sizeX = 10;
  map.sizeY = 30;
  map.tiles.push_back({3,3,true,"grass"});
  map.tiles.push_back({5,5,false,"water"});

  Saver saver;
  std::cout << "Serializing......." << std::endl;
  std::filesystem::path path = "../../assets/00000001.sav";
  map.Save(path, saver);

  Loader loader;
  Tilemap newTilemap;
  newTilemap.Load(path, loader);

  // t.accept(saver);
  // tLoaded.accept(loader);

  return EXIT_SUCCESS;

}
