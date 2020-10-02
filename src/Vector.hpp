#pragma once

#include <math.h>

class Vector3
{
public:
    Vector3()
        : _x(0), _y(0), _z(0)
    { }

    Vector3(double x, double y, double z)
        : _x(x), _y(y), _z(z)
    { }

    Vector3(const Vector3 &v)
        : _x(v._x), _y(v._y), _z(v._z)
    { }

    virtual ~Vector3()
    { }

    double GetX() { return _x; }
    double GetY() { return _y; }
    double GetZ() { return _z; }

    void SetXYZ(double x, double y, double z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    Vector3 normalized()
    {
        return *this / Vector3::Len(*this);
    }

    static double Len(const Vector3 v)
    {
        return sqrt(v._x * v._x +
                    v._y * v._y +
                    v._z * v._z);
    }

    static Vector3 Abs(const Vector3 v)
    {
        Vector3 temp(
            std::abs(v._x),
            std::abs(v._y),
            std::abs(v._z)
        );
        return temp;
    }

    static Vector3 Lerp(const Vector3 v1, const Vector3 v2, double ratio)
    {
        return v1 + ratio * (v2 - v1);
    }

    static Vector3 Max(const Vector3 v, double val)
    {
        Vector3 temp(
            v._x > val ? v._x : val,
            v._y > val ? v._y : val,
            v._z > val ? v._z : val
        );
        return temp;
    }

    Vector3& operator+=(const Vector3& rhs)
    {
        this->_x += rhs._x;
        this->_y += rhs._y;
        this->_z += rhs._z;
        return *this;
    }

    friend Vector3 operator+(const Vector3 &, const Vector3 &);
    friend Vector3 operator+(const Vector3 &v, double);
    friend Vector3 operator+(double, const Vector3 &v);

    friend Vector3 operator-(const Vector3 &, const Vector3 &);
    friend Vector3 operator-(const Vector3 &, double);
    friend Vector3 operator-(double, const Vector3 &);

    friend Vector3 operator%(const Vector3 &, const Vector3 &);
    friend Vector3 operator%(const Vector3 &, double);
    friend Vector3 operator%(double, const Vector3 &);

    friend Vector3 operator*(const Vector3 &, double);
    friend Vector3 operator*(double, const Vector3 &);

    friend Vector3 operator/(const Vector3 &, double);
    friend Vector3 operator/(double, const Vector3 &);

private:
    double _x;
    double _y;
    double _z;
};

Vector3 operator+(const Vector3 &vl, const Vector3 &vr)
{
    double x = vl._x + vr._x;
    double y = vl._y + vr._y;
    double z = vl._z + vr._z;
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator+(const Vector3 &v, double val)
{
    double x = v._x + val;
    double y = v._y + val;
    double z = v._z + val;
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator+(double val, const Vector3 &v)
{
    return v + val;
}

Vector3 operator-(const Vector3 &vl, const Vector3 &vr)
{
    double x = vl._x - vr._x;
    double y = vl._y - vr._y;
    double z = vl._z - vr._z;
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator-(const Vector3 &v, double val)
{
    double x = v._x - val;
    double y = v._y - val;
    double z = v._z - val;
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator-(double val, const Vector3 &v)
{
    return v - val;
}

inline double wrap(double lhs, double rhs)
{
    return lhs - rhs * floor(lhs / rhs);
}

Vector3 operator%(const Vector3 & lhs, const Vector3 & rhs)
{
    double x = wrap(lhs._x, rhs._x);
    double y = wrap(lhs._y, rhs._y);
    double z = wrap(lhs._z, rhs._z);
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator%(const Vector3 & lhs, double rhs)
{
    double x = wrap(lhs._x, rhs);
    double y = wrap(lhs._y, rhs);
    double z = wrap(lhs._z, rhs);
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator%(double lhs, const Vector3 & rhs)
{
    return rhs % lhs;
}


Vector3 operator*(const Vector3 &v, double val)
{
    double x = v._x * val;
    double y = v._y * val;
    double z = v._z * val;
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator*(double val, const Vector3 &v)
{
    return v * val;
}

Vector3 operator/(const Vector3 &v, double val)
{
    double x = v._x / val;
    double y = v._y / val;
    double z = v._z / val;
    Vector3 vec(x, y, z);
    return vec;
}

Vector3 operator/(double val, const Vector3 &v)
{
    return v / val;
}
