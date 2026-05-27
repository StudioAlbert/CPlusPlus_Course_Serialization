//
// Created by sebas on 27.05.2026.
//

#ifndef CPLUSPLUS_COURSE_SERIALIZATION_SHAPE_H
#define CPLUSPLUS_COURSE_SERIALIZATION_SHAPE_H

#include "visitor.h"

struct Shape {
  virtual ~Shape() = default;
  virtual double accept(Visitor& v) = 0;
};

struct Circle : Shape {
  double r;
  double accept(Visitor& v) override {
    return v.visit(*this);
  }
};

struct Square : Shape {
  double side;
  double accept(Visitor& v) override {
    return v.visit(*this);
  }
};


#endif // CPLUSPLUS_COURSE_SERIALIZATION_SHAPE_H
