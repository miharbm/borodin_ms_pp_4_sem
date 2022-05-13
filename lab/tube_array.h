#ifndef LAB_TUBE_ARRAY_H
#define LAB_TUBE_ARRAY_H

#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>

int intsqrt(int i);

class Point{
private:
    bool _type;
    double _concentrate; //concentrate

public:

    void set_type(bool a);
    void set_concentrate( double concentrate);
    double C() const;
    void C(double concentrate_set);
    bool type() const;
    void type(bool type_set);


};

class Tube {
private:
    int _rad, _len, _diam;
    Point *** A;

public:

    //конструктор
    Tube(int rad, int len);
    Tube(const Tube  &tube1);

    int diam() const;
     Point const &at(int i, int j, int k);
    void print();
};

int intsqrt(int i);

#endif //LAB_TUBE_ARRAY_H