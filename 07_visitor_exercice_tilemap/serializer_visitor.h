//
// Created by sebas on 27.05.2026.
//

#ifndef CPLUSPLUS_COURSE_SERIALIZATION_SERIALIZER_VISITOR_H
#define CPLUSPLUS_COURSE_SERIALIZATION_SERIALIZER_VISITOR_H

#include <fstream>

class Tile;
class Tilemap;

class SerializerVisitor {
    virtual void open(std::filesystem::path&) = 0;
    virtual void close() = 0;
  public:
    virtual void visit(std::filesystem::path&, Tile&) = 0;
    virtual void visit(std::filesystem::path&, Tilemap&) = 0;
};



#endif // CPLUSPLUS_COURSE_SERIALIZATION_SERIALIZER_VISITOR_H
