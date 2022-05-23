#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <windows.h>
//#include <Python.h>
//#include "matplotlib-cpp\matplotlibcpp.h"
//#include <vector>
//namespace plt = matplotlibcpp;

#include "tube_array.h"
#include "tube_array.tpp"

using namespace std;

void dummyCells(Tube &tube, int k, int i, int j);

int main(){

    // одному дециметру трубы соотвествует одна ячейка

    double lengthMetres; //длина трубы в метрах c точностью до 0.1 метра
    double radiusMetres; //радиус трубы в метрах с точностью до 0.1 метра
    double ratioMetresInts = 10.f;

    lengthMetres = 100;
    radiusMetres = 1;

    int rad = (int)(radiusMetres * ratioMetresInts);
    int len = (int)(lengthMetres * ratioMetresInts); // задание радиуса и длины трубы

    //cout << " rad len      " << rad << '\t' << len << endl;

    Tube tube1 = Tube(rad,len); //создание трубы
    cout << "first tube created" << endl;
    Tube tube2 = Tube(tube1); //создание второй схожей трубы
    cout << "tubes have been made" << endl;

    double tmp;
    double D = 10e-5; // постоянная диффузии
    double time; // время в секундах
    double timeStep ; // шаг по времени 0,012 сек
    double h = 1; //шаг, но он всегда вроде одинаков, смотрю соседние клетки
    double h2 = h * h;
    double C_H = 0.2;


    timeStep = 0.1 * (1.f/ratioMetresInts)*(1.f/ratioMetresInts) / D;
    cout << "timeStep = " <<timeStep << endl;


    // создаем лужу с 30 по 35 метр

    double beginPoolMetres = 30, endPoolMetres = 35;

    int beginPool = (int)(beginPoolMetres * ratioMetresInts);
    int endPool   = (int)(endPoolMetres   * ratioMetresInts); // задание радиуса и длины трубы


    for ( int k = beginPool; k < endPool; k++ ){
        for (int i = tube1.diam() - 1; i > tube1.diam() * 0.7; i--){
            for (int j = 0; j < tube1.diam(); j++){
                if(tube1.at(k, i, j).type()) {
                    tube1.at(k, i ,j ).C(C_H);
                }
            }
        }
    }
    for ( int k = beginPool; k < endPool; k++ ){
        for (int i = (int)(tube1.diam() * 0.7); i > tube1.diam() * 0.5; i--){
            for (int j = 0; j < tube1.rad(); j++){
                if(tube1.at(k, i, j).type() && !tube1.at(k, i, j - 1).type()) {
                    for (int l = j; l < j + 3; l++){
                        tube1.at(k, i ,j ).C(C_H);
                        tube1.at(k, i ,tube1.diam() - l).C(C_H);
                    }
                }
            }
        }
    }
    cout << "border have been made"<<endl;

    tube1.printType("border");

    tube1.printC("concentrate_begin");

    //основной вычислительный процесс

    time = 0;
    double timeMax = timeStep * 20;
    while (time < timeMax) {

        time += timeStep;
        for (int k = 0; k < tube1.len(); k++) {
            for (int i = 0; i < tube1.diam(); i++) {
                for (int j = 0; j < tube1.diam(); j++) {
                    if (tube1.at(k, i, j).type()) {
                        dummyCells(tube1, k, i, j);
                        tmp = tube1.at(k, i, j).C() + D * time * (tube1.at(k - 1,    i,     j  ).C()
                                                                + tube1.at(k + 1,    i,     j  ).C()
                                                                + tube1.at(     k, i - 1,    j  ).C()
                                                                + tube1.at(     k, i + 1,    j  ).C()
                                                                + tube1.at(     k,     i, j - 1 ).C()
                                                                + tube1.at(     k,     i, j + 1 ).C()
                                                                - 6 * tube1.at(k, i, j).C()) / h2;
                        tube2.at(k, i, j).C(tmp);
                    }
                }
            }
        }

        cout << "|";
        time += timeStep;
        for (int k = 0; k < tube2.len(); k++) {
            for (int i = 0; i < tube2.diam(); i++) {
                for (int j = 0; j < tube2.diam(); j++) {
                    if (tube2.at(k, i, j).type()) {
                        tmp = tube2.at(k, i, j).C() + D * time * (tube2.at(k - 1, i, j).C()
                                                                + tube2.at(k + 1, i, j).C()
                                                                + tube2.at(k, i - 1, j).C()
                                                                + tube2.at(k, i + 1, j).C()
                                                                + tube2.at(k, i, j - 1).C()
                                                                + tube2.at(k, i, j + 1).C()
                                                                - 6 * tube2.at(k, i, j).C() ) / h2;
                        tube1.at(k, i, j).C(tmp);
                    }
                }
            }
        }
        cout << "|";
    }
    cout << endl;

   tube1.printC("result");
}

void dummyCells(Tube &tube, int k, int i, int j){

    double tmp = tube.at(k - 1,i,j).C();

    if(!tube.at(k - 1,i,j).type()) {
        tube.at(k - 1,i,j).C(tmp);
    }
    if(!tube.at(k,i - 1,j).type()) {
        tube.at(k,i - 1,j).C(tmp);
    }
    if(!tube.at(k ,i,j - 1).type()) {
        tube.at(k,i,j - 1).C(tmp);
    }
    if(!tube.at(k + 1,i,j).type()) {
        tube.at(k + 1,i,j).C(tmp);
    }
    if(!tube.at(k ,i + 1,j).type()) {
        tube.at(k,i + 1,j).C(tmp);
    }
    if(!tube.at(k ,i,j + 1).type()) {
        tube.at(k,i,j + 1).C(tmp);
    }
}