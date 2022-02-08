#include "Functions.h"
#include "Integration.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
using namespace std;

int main(){
    
    /*
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
    */

    srand48(time(NULL));

    enum algorithm {MonteCarlo, Trapezoids, Rectangles};
    algorithm choice;

    double x_min, x_max;
    int nStepOfIntegration;

    cout << "\n\t\033[31mTesting the Integrator class ...\033[0m\n" << endl;

    vector <Function> functions;
    functions.push_back(Gauss(0,1,"Standard normal distribution"));
    functions.push_back(Exponential(1,1,"Normalized decreasing exponential"));
    functions.push_back(Line(1,0,"Line bisection I-IV"));
    
    for (int i = 0; i < functions.size(); i++){
        cout << "Choose lower bound for integration interval of the function \"" << functions[i].Name() << "\": ";
        cin >> x_min;
        cout << endl;

        cout << "Choose upper bound for integration interval of the function \"" << functions[i].Name() << "\": ";
        cin >> x_max;
        cout << endl;

        MonteCarloMethod* mc_int = new MonteCarloMethod(&functions[i], nStepOfIntegration);
        TrapezoidMethod* trap_int = new TrapezoidMethod(&functions[i], nStepOfIntegration);
        RectangleMethod* rect_int = new RectangleMethod(&functions[i], nStepOfIntegration);

        for (int nStepOfIntegration = 10; nStepOfIntegration <= 1E6; nStepOfIntegration*=10){
            mc_int->setNumberPoints(nStepOfIntegration);
            trap_int->setNumberPoints(nStepOfIntegration);
            rect_int->setNumberPoints(nStepOfIntegration);
        }
        
        delete mc_int;
        delete trap_int;
        delete rect_int;

    }
    
    
    return(EXIT_SUCCESS);
}
