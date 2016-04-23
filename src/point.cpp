#include "point.h"

Point::Point(const Point &p)
{
    this->x = p.x;
    this->y = p.y;
}

Point Point::operator+(const Point &p)
{
    return Point(this->x + p.x, this->y + p.y);
}

Point Point::operator+(const int &v)
{
    return Point(this->x + v, this->y + v);
}

Point Point::operator-(const Point &p)
{
    return Point(this->x - p.x, this->y - p.y);
}

Point Point::operator-(const int &v)
{
    return Point(this->x - v, this->y - v);
}

Point Point::operator*(const int &v)
{
    return Point(this->x * v, this->y * v);
}

Point Point::operator/(const int &v)
{
    return Point(this->x / v, this->y / v);
}

bool Point::operator==(const Point &p)
{
    return (this->x == p.x) && (this->y == p.y);
}

bool Point::operator!=(const Point &p)
{
    return (this->x != p.x) || (this->y != p.y);
}
