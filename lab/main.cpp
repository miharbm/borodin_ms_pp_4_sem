#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
//#include <Python.h>
//#include "matplotlib-cpp\matplotlibcpp.h"
//#include <vector>
//namespace plt = matplotlibcpp;

#include "tube_array.h"
#include "tube_array.tpp"

using namespace std;




int main(){

    int rad = 20, len = 5;//задание радиуса и длины трубы

    Tube tube1 = Tube(rad,len); //создание трубы

    Tube tube2 = Tube(tube1); //создание трубы похожей




    double tmp;
    double D = 10 , time;
    int h = 1; //шаг, но он всегда вроде одинаков, смотрю соседние клетки

    //создаем на дне концентрацию равнуюю 100 (пока для примера)
    for (int k = 0 ; k < tube1.len(); k++){
        for (int i = tube1.diam() - 1; i > tube1.diam() * 0.9; i--){
            for (int j = 0; j < tube1.diam(); j++){
                if(tube1.at(k, i, j).type()) {
                    tube1.at(k, i ,j ).C(100);
                }
            }
        }
    }

    /*основной вычислительный процесс

    for (time = 1; time < 10; time = time + 1) {

        for (int k = 0; k < tube1.len(); k++) {
            for (int i = 0; i < tube1.diam(); i++) {
                for (int j = 0; j < tube1.diam(); j++) {
                    if (tube1.at(k, i, j).type()) {
                        tmp = tube1.at(k, i, j).C() + D * time * (tube1.at(k - 1, i, j).C() + tube1.at(k + 1, i, j).C()
                                                                  + tube1.at(k, i - 1, j).C() +
                                                                  tube1.at(k, i + 1, j).C() + tube1.at(k, i, j - 1).C()
                                                                  + tube1.at(k, i, j + 1).C() -
                                                                  6 * tube1.at(k, i, j).C()) / h;
                        tube2.at(k, i, j).C(tmp);
                    }
                }
            }
        }

        time = time + 1;

        for (int k = 0; k < tube2.len(); k++) {
            for (int i = 0; i < tube2.diam(); i++) {
                for (int j = 0; j < tube2.diam(); j++) {
                    if (tube2.at(k, i, j).type()) {
                        tmp = tube2.at(k, i, j).C() + D * time * (tube2.at(k - 1, i, j).C() + tube2.at(k + 1, i, j).C()
                                                                  + tube2.at(k, i - 1, j).C() +
                                                                  tube2.at(k, i + 1, j).C() + tube2.at(k, i, j - 1).C()
                                                                  + tube2.at(k, i, j + 1).C() -
                                                                  6 * tube2.at(k, i, j).C()) / h;
                        tube1.at(k, i, j).C(tmp);
                    }
                }
            }
        }
    }
   tube1.printC("result");


}

