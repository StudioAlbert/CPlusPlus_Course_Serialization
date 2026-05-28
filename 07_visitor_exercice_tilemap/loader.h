//
// Created by sebas on 27.05.2026.
//
#ifndef CPLUSPLUS_COURSE_SERIALIZATION_LOADER_H
#define CPLUSPLUS_COURSE_SERIALIZATION_LOADER_H

#include "serializer_visitor.h"

#include <fstream>

class Loader : public SerializerVisitor{

  std::ifstream ifs;
  void open(std::filesystem::path &) override;
  void close() override;

public:
  void visit(std::filesystem::path&, Tile&) override;
  void visit(std::filesystem::path&, Tilemap&) override;

};



#endif
