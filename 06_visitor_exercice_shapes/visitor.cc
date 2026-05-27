//
// Created by sebas on 27.05.2026.
//

#include "visitor.h"
#include "shape.h"
#include "cmath"

double AreaVisitor::visit(Circle& c)
{
  return 3.14f * c.r * c.r;
}
double AreaVisitor::visit(Square& s)
{
  return s.side * s.side;
}

double PerimeterVisitor::visit(Circle& c)
{
  return 2 * 3.14f * c.r;
}
double PerimeterVisitor::visit(Square& s)
{
  return 4 * s.side;
}