#ifndef LAB_TUBE_ARRAY_H
#define LAB_TUBE_ARRAY_H

#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>

int intsqrt(int i);

class Point{
private:
    bool _type; // false - граница или вне трубы
    double _concentrate; //concentrate

public:

    void set_type(bool a);
    void set_concentrate( double concentrate);
    [[nodiscard]] double C() const;
    void C(double concentrate_set);
    [[nodiscard]] bool type() const;
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

    [[nodiscard]] int diam() const;
    [[nodiscard]] int rad() const;
    [[nodiscard]] int len() const;
    [[nodiscard]] Point &at(int k, int i, int j) const;
    void print(const std::string& via) const;
    void printC(const std::string& via) const;
};



#endif //LAB_TUBE_ARRAY_H