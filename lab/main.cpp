#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
//#include <Python.h>
//#include "matplotlib-cpp\matplotlibcpp.h"
//#include <vector>

using namespace std;

//namespace plt = matplotlibcpp;

int intsqrt(int i);
void paint(int ** A);


class Point{
private:
    bool _type;
    double _concentrate; //concentrate

public:

    void set_type(bool a){
        if (a == 0) {//граница или вне
            _type = false;
            set_concentrate(0);
        }
        else if (a == 1) {//точка для рассчета внутри трубы
            _type = true;
        }
        else {return;}
    }
    void set_concentrate( double concentrate){
        _concentrate = concentrate;
    }

    double C() const{
        return _concentrate;
    }

    void C(double concentate_set) {
        set_concentrate(concentate_set);
    }

    bool type(){
        return _type;
    }
    void type(bool type_set){
        set_type(type_set);
    }


};

class Tube{
private:
    int _rad, _len, _diam;
    Point *** A;

public:

    //конструктор
    Tube(int rad, int len) {

        _rad = rad; _len = len;
        cout << "in constructor: rad and _rad = " << rad <<'\t' << _rad << endl;

        _diam = 2 * rad + 1;

        //выделяем память под трубу
        A = new Point **[len];
        for (int j = 0; j < len; j ++){
            A[j] = new Point *[2 * rad + 1];
            for (int i = 0; i < 2 * rad + 1; i++){
                A[j][i] = new Point[2 * rad + 1];
            }
        }


        //заполняем все элементы трубы будто они внутри трубы
        for (int i = 0; i < 2 * rad + 1; i++){
            for (int j = 0; j < 2 * rad + 1; j++){
                for ( int k = 0; k < len; k++){
                    A[k][i][j].type(true);
                }
            }
        }

        //высчитываем границу для одного слоя
        int y;
        for (int i = 0; i<= rad; i += 1) {
            y = intsqrt(rad * rad - i*i );
            A[0][rad - i][rad - y].type(false);
            A[0][rad + i][rad - y].type(false);
            A[0][rad - i][rad + y].type(false);
            A[0][rad + i][rad + y].type(false);
        }

        //дополняем границу для одного слоя
        int j = 0;
        for (int i = 0; i < rad; i++){
            while( A[0][i][j].type() ) {
                A[0][        i     ][        j     ].type(false);
                A[0][diam() - 1 - i][        j     ].type(false);
                A[0][diam() - 1 - i][diam() - 1 - j].type(false);
                A[0][        i     ][diam() - 1 - j].type(false);
                j++;
            }
            j = 0;
        }

        for (int i = 0; i < 2 * rad + 1; i++){
            for (j = 0; j < 2 * rad + 1; j++){
                for ( int k = 0; k < len - 1; k++){
                    //A[k][i][j].C(A[0][i][j].C() );
                    A[k][i][j].type(A[0][i][j].type() );
                }
            }
        }

        for (int i = 0; i < 2 * rad + 1; i++){
            for (j = 0; j < 2 * rad + 1; j++){
                A[0][i][j].type(false);
            }
        }
        for (int i = 0; i < 2 * rad + 1; i++){
            for (j = 0; j < 2 * rad + 1; j++){
                A[_len - 1][i][j].type(false);
            }
        }

    }

    int diam() const{
        return _diam;
    }

    Point &at(int i, int j, int k){
        return A[i][j][k];
    }

    void print(){
        ofstream fout("output.txt");

        cout << " before print rad = " << _rad << endl;

        for (int k = 0; k < _len; k++) {
            for (int i = 0; i < 2 * _rad + 1; i++) {
                for (int j = 0; j < 2 * _rad + 1; j++) {
                    if (!A[k][i][j].type()) {
                        fout << "1";
                    } else {
                        fout << "0";
                    }
                }
                fout << endl;
            }
            fout << endl;
        }
        cout<<endl<<"printed"<<endl;

    }
};



int main(){

   Tube tube1 = Tube(20,4);

   tube1.print();

}


int main1() {


    const int rad = 20;




    /*
    for (int i = 0; i < 2*rad+1; i++){
        for (int j = 0; j < 2*rad+1; j++){
            if (A[i][j] == 1) {
                plt::plot(i,j);
            }

        }
        fout<<std::endl;
    } */

    //plt::savefig("standard.pdf"); //savethefigure
    //plt::show();

    return 0;
}


int intsqrt(int i) {
    double temp = sqrt(i);
    int temp2 = (int) temp;
    if (temp - temp2 > 0.5) temp2 ++;
    return temp2;
}