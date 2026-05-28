//
// Created by sebas on 27.05.2026.
//

#ifndef CPLUSPLUS_COURSE_SERIALIZATION_SAVER_H
#define CPLUSPLUS_COURSE_SERIALIZATION_SAVER_H

#include "serializer_visitor.h"

#include <filesystem>
#include <fstream>

class Saver: public SerializerVisitor{

  std::ofstream ofs;
  void open(std::filesystem::path &) override;
  void close() override;

public:
  void visit(std::filesystem::path &, Tile &) override;
  void visit(std::filesystem::path &, Tilemap &) override;

};


#endif