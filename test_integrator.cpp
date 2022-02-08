#include "Functions.h"
#include "Integration.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
using namespace std;

int main(){
    
    Exponential* ciccio = new Exponential(1.01, 23, "exp function");
    ciccio->Print();
    ciccio->setParameter(1);
    ciccio->setNormalization(1.10);
    cout << "Provo alcune funzioni della Classe di Gauss:\n"
    << "1)\tMedia e dev std (modificati):\t" << ciccio->Parameter() << ", " << ciccio->Normalization() << "\n"
    << endl;
    ciccio -> Normalize();
    cout << "2)\tNormalizing function...\n" << endl;
    ciccio->Print();
    cout << "4)\tValue:\t" << ciccio->value(200) << "\n"
    << endl;

    TrapezoidMethod* mcint = new TrapezoidMethod(ciccio, 10000);
    cout << "\n\nCiccio è nomralizzato, quindi provo a vedere se l'integrale tra 0 e infinito va a 1"
    << "\n" << "\tINTEGRALE = " << mcint->integrate(0,2) << endl;
    cout << "\tESATTO = " << (1-exp(-ciccio->Parameter()*2)) << endl;
    delete mcint;
    /* PROGRAMMA
    srand48(time(NULL));

    enum algorithm {MonteCarlo, Trapezoids, Rectangles};
    algorithm choice;

    double x_min, x_max;
    int nStepOfIntegration;

    cout << "\n\tTesting the Integrator class ..." << endl;

    vector <Integrator> integrations;
    integrations.push_back(exp);
    
    cout << "Insert the lower bound of integration for decreasing exponential function" << endl;
    cin >> x_min;
    cout << "Insert the upper bound of integration for decreasing exponential function" << endl;
    cin >> x_max;

    int chooseAlgo;
    do{
        cout << "Choose which algoprithm you want to use: MonteCarlo (0), Trapezoids (1), Rectangles (2)" << endl; 
        cin >> chooseAlgo;
    }while(chooseAlgo <=2 && chooseAlgo >=0);

    if(chooseAlgo == MonteCarlo){}
    else if(chooseAlgo == Trapezoids){}
    else if(chooseAlgo == Rectangles){}
    else{}
    */
    return(EXIT_SUCCESS);
}
