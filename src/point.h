#pragma once

class Point
{
public:
    int x, y;
    Point() : x(0), y(0) {};
    Point(int x, int y) : x(x), y(y) {};
    Point(const Point &p);
    Point operator+(const Point &p);
    Point operator+(const int &v);
    Point operator-(const Point &p);
    Point operator-(const int &v);
    Point operator*(const int &v);
    Point operator/(const int &v);
    bool operator==(const Point &rv);
    bool operator!=(const Point &rv);
};
