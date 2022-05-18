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

    void set_type(bool type_set);
    void set_concentrate( double concentrate);
    [[nodiscard]] double C() const; //возвращает значение концентрации
    void C(double concentrate_set);
    [[nodiscard]] bool type() const; //возвращает значение типа точки
    void type(bool type_set);


};

class Tube {
private:
    int _rad, _len, _diam; // радиус, длина и диаметр трубы
    Point *** A;

public:

    //конструктор
    Tube(int rad, int len);
    Tube(const Tube  &tube1); // конструктор копирования

    [[nodiscard]] int diam() const; // возвращает диаметр
    [[nodiscard]] int rad() const; // возвращает радиус
    [[nodiscard]] int len() const; // возвращает длину
    [[nodiscard]] Point &at(int k, int i, int j) const; // возвращает класс точки
    void print(const std::string& via) const; // печатает в файл границы
    void printC(const std::string& via) const; // печатает в файл конацентрацию в каждой точке
};

#endif //LAB_TUBE_ARRAY_H