//
// Created by sebas on 27.05.2026.
//


#ifndef VISITOR_H
#define VISITOR_H

struct Circle;
struct Square;

class Visitor {
public:
  virtual double visit(Circle&) = 0;
  virtual double visit(Square&) = 0;
};

class AreaVisitor : public Visitor {
public:
  double visit(Circle& c) override;
  double visit(Square& s) override;
};

class PerimeterVisitor : public Visitor {
public:
  double visit(Circle& c) override;
  double visit(Square& s) override;
};

#endif