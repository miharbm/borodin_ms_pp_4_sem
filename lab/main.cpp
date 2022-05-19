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




int main(){

    // одному сантиметру трубы соотвествует одна ячейка

    double length_metres; //длина трубы в метрах c точностью до 0.01 метра
    double radius_metres; //радиус трубы в метрах с точностью до 0.01 метра
    double ratioMetresInts = 10.f;

    length_metres = 100;
    radius_metres = 1;

    int rad = (int)(radius_metres * ratioMetresInts);
    int len = (int)(length_metres * ratioMetresInts); // задание радиуса и длины трубы

    cout << " rad len      " << rad << '\t' << len << endl;

    Tube tube1 = Tube(rad,len); //создание трубы
    cout << "first tube created" << endl;
    Tube tube2 = Tube(tube1); //создание второй схожей трубы
    cout << "tubes have been made" << endl;

    double tmp;
    double D = 10e-5; // постоянная диффузии
    double time; // время в секундах
    double time_step ; // шаг по времени 0,012 сек
    double h = 1; //шаг, но он всегда вроде одинаков, смотрю соседние клетки
    double h2 = h * h;
    double C_H = 0.2;


    time_step = 0.1 * (1.f/ratioMetresInts)*(1.f/ratioMetresInts) / D;
    cout << "time_step = " <<time_step << endl;


    // создаем лужу с 30 по 35 метр

    double begin_pool_metres = 30, end_pool_metres = 35;

    int begin_pool = (int)(begin_pool_metres * ratioMetresInts);
    int end_pool   = (int)(end_pool_metres   * ratioMetresInts); // задание радиуса и длины трубы


    for ( int k = begin_pool; k < end_pool; k++ ){
        for (int i = tube1.diam() - 1; i > tube1.diam() * 0.96; i--){
            for (int j = 0; j < tube1.diam(); j++){
                if(tube1.at(k, i, j).type()) {
                    tube1.at(k, i ,j ).C(C_H);
                }
            }
        }
    }
    for ( int k = begin_pool; k < end_pool; k++ ){
        for (int i = (int)(tube1.diam() * 0.96); i > tube1.diam() * 0.9; i--){
            for (int j = 0; j < tube1.rad(); j++){
                if(tube1.at(k, i, j).type() && !tube1.at(k, i, j - 1).type()) {
                    for (int l = j; l < 3; l++){
                        tube1.at(k, i ,j ).C(C_H);
                        tube1.at(k, i ,tube1.diam() - l).C(C_H);
                    }
                }
            }
        }
    }
    cout << "border have been made"<<endl;


    tube1.printC("ggg");

    //основной вычислительный процесс

    time = 0;
    double time_max = time_step * 20;
    while (time < time_max) {

        time += time_step;
        for (int k = 0; k < tube1.len(); k++) {
            for (int i = 0; i < tube1.diam(); i++) {
                for (int j = 0; j < tube1.diam(); j++) {
                    if (tube1.at(k, i, j).type()) {
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
        time += time_step;
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


   tube1.printC("result");
}

