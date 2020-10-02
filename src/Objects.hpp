#pragma once

#include "Vector.hpp"


class BaseObject
{
public:
  BaseObject(Vector3 pos)
    : _pos(pos)
  {  }

  BaseObject(double x, double y, double z)
    : _pos(x, y, z)
  {  }

  void Offset(double x, double y, double z)
  {
    Vector3 temp(x, y, z);
    _pos += temp;
  }

  virtual double DE(Vector3 p) const = 0;

protected:
  Vector3 _pos;
};


class Sphere : public BaseObject
{
public:
  Sphere(Vector3 pos, double radius)
    : BaseObject(pos)
    , _radius(radius)
  {  }

  Sphere(double x, double y, double z, double radius)
    : BaseObject(x, y, z)
    , _radius(radius)
  {  }

  double DE(Vector3 p) const
  {
    return Vector3::Len(_pos - p) - _radius;
  }

private:
  double _radius;
};


class Box : public BaseObject
{
public:
  Box(Vector3 pos, double w, double h, double l)
    : BaseObject(pos)
    , _dim(w, h, l)
  {  }

  Box(double x, double y, double z, double w, double h, double l)
    : BaseObject(x, y, z)
    , _dim(w, h, l)
  {  }

  double DE(Vector3 p) const
  {
    return Vector3::Len(
      Vector3::Max(
        Vector3::Abs(_pos - p) - _dim, 0.0
      )
    );
  }

private:
  Vector3 _dim;
};
