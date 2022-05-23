#ifndef LAB_TUBE_ARRAY_TPP
#define LAB_TUBE_ARRAY_TPP

#include "tube_array.h"
using namespace std;

void Point::setType(bool type_set){
    if (!type_set) { //граница или вне
        _type = false;
        setConcentrate(0);
    }
    else { //точка для рассчета внутри трубы
        _type = true;
    }
}

void Point::setConcentrate( double concentrate){
    _concentrate = concentrate;
}

double Point::C() const{
    return _concentrate;
}

void Point::C(double concentrate_set) {
    setConcentrate(concentrate_set);
}

bool Point::type() const{
    return _type;
}

void Point::type(bool type_set){
    setType(type_set);
}

Tube::Tube(int rad, int len) {

    _rad = rad; _len = len;
    //cout << "in constructor: rad and _rad = " << rad <<'\t' << _rad << endl;

    _diam = 2 * rad + 1;

    //выделяем память под трубу
    A = new Point **[_len];
    for (int j = 0; j < _len; j ++){
        A[j] = new Point *[2 * _rad + 1];
        for (int i = 0; i < 2 * _rad + 1; i++){
            A[j][i] = new Point[2 * _rad + 1];
        }
    }

    cout << "memory allocated for first tube" << endl;
    //заполняем все элементы трубы будто они внутри трубы
    for (int i = 0; i < 2 * rad + 1; i++){
        for (int j = 0; j < 2 * rad + 1; j++){
            for ( int k = 0; k < len; k++){
                A[k][i][j].type(true);
                A[k][i][j].C(0);
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

    // размножаем границу на остальные слои
    for (int i = 0; i < 2 * rad + 1; i++){
        for (j = 0; j < 2 * rad + 1; j++){
            for ( int k = 0; k < len - 1; k++){
                //A[k][i][j].C(A[0][i][j].C() );
                A[k][i][j].type(A[0][i][j].type() );
            }
        }
    }

    //создаем сплошную границу на концах трубы
    for (int i = 0; i < 2 * rad + 1; i++){
        for (j = 0; j < 2 * rad + 1; j++){
            A[0][i][j].type(false);
            A[_len - 1][i][j].type(false);
        }
    }
}

Tube::Tube( const Tube &tube1)  {

    _rad = tube1.rad(); _len = tube1.len();
   // cout << "in constructor: rad and _rad = " <<'\t' << _rad << endl;

    _diam = 2 * _rad + 1;

    //выделяем память под трубу
    A = new Point **[_len];
    for (int j = 0; j < _len; j ++){
        A[j] = new Point *[2 * _rad + 1];
        for (int i = 0; i < 2 * _rad + 1; i++){
            A[j][i] = new Point[2 * _rad + 1];
        }
    }

    cout << "memory allocated for second tube" << endl;

    for ( int k = 0; k < _len; k++) {
        for (int i = 0; i < 2 * _rad + 1; i++) {
            for (int j = 0; j < 2 * _rad + 1; j++) {

                A[k][i][j].type(tube1.at(k, i, j).type());

            }
        }
    }
}

int Tube::diam() const{
    return _diam;
}

Point & Tube::at(int k, int i, int j) const {
    return A[k][i][j];
}

void Tube::printType(const string& via) const{
    ofstream fout(via);
   // ofstream fout("output.txt");

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
    cout << endl<<"printed border in "<< via << endl;

}

int Tube::rad() const {
    return _rad;
}

int Tube::len() const {
    return _len;
}

void Tube::printC(const string& via) const {

    ofstream fout(via);
    //ofstream fout("output_conc.txt");

    //cout << "before print rad = " << _rad << endl;

    for (int k = 0; k < _len; k += 10) {
        for (int i = 0; i < 2 * _rad + 1; i++) {
            for (int j = 0; j < 2 * _rad + 1; j++) {
                fout << A[k][i][j].C() << " ";
            }
            fout << endl;
        }
        fout << endl;
    }
    cout<<endl<<"printed C in "<< via << endl;

}



int intsqrt(int i) {
    double temp = sqrt(i);
    int temp2 = (int) temp;
    if (temp - temp2 > 0.5) temp2++;
    return temp2;
}

#endif //LAB_TUBE_ARRAY_TPP