#include "complex.h"
#include <iostream>
using namespace std;

int main(){

    Complex z(1.2, -0.6), w, y;
    const Complex i(0,1);

    w = z + 2*i;
    cout << w << endl;

    y = (w*i)/1.5;
    cout << y << endl;

    Complex inv = 3.2/w;
    cout << inv << endl;

    Complex sum = -2.5 + i*2 +  Complex(4,-3);
    cout << sum << endl;

    return(0);
}