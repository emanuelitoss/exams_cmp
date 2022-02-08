#include "Functions.h"
#include "Integration.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

#define RED "\033[0;31m"
#define BOLD_CYAN "\033[1;36m"
#define RESET_COLOR "\033[0m"

int main(){

    // initializing random generator
    //srand48(time(NULL));

    // variables of the problem
    double x_min, x_max;
    int nStepOfIntegration;
    double integralMC, integralTrap, integralRect;

    // message to the user
    cout << RED << "\n\tTesting the Integrator class ...\n" << RESET_COLOR << endl;

    // different mathematical functions
    vector <Function*> functions;

    // parameters to set the mathematical functions
    double parameter1 = 0, parameter2 = 0;

    // Gaussian function
    cout << "Insert mean of Gaussian function: ";
    cin >> parameter1;
    cout << "Instert standard deviation of Gaussian function: ";
    cin >> parameter2;
    cout << endl;
    functions.push_back(new Gauss(parameter1, parameter2,"gaussian"));

    // Decreasing exponential function
    cout << "Insert coefficient alpha of the function N*exp(-alpha*x): ";
    cin >> parameter1;
    cout << "Insert coefficient N of the function N*exp(-alpha*x): ";
    cin >> parameter2;
    cout << endl;
    functions.push_back(new Exponential(parameter1, parameter2,"exponential"));

    // Line function
    cout << "Insert coefficient of a line function: ";
    cin >> parameter1;
    cout << "Instert quote deviation of Gaussian function: ";
    cin >> parameter2;
    cout << endl;
    functions.push_back(new Line(parameter1, parameter2,"lineFunction"));
    
    // Loop over the functions
    for (int i = 0; i < functions.size(); i++){

        // output file 
        ofstream outputFile;
        string outputName = functions[i]->Name() + "_data.txt";
        outputFile.open(outputName);
        functions[i]->Print(outputFile);

        cout << "Choose lower bound for integration interval of the function \"" << functions[i]->Name() << "\": ";
        cin >> x_min;
        cout << "Choose upper bound for integration interval of the function \"" << functions[i]->Name() << "\": ";
        cin >> x_max;
        cout << endl;

        outputFile << "#Integration range: [" << setprecision(3) << x_min << ", " << x_max << "]" << endl;
        outputFile << "#Number i\tMonteCarlo\tTrapezoids\tRectangles" << endl;

        MonteCarloMethod* mc_int = new MonteCarloMethod(functions[i], nStepOfIntegration);
        TrapezoidMethod* trap_int = new TrapezoidMethod(functions[i], nStepOfIntegration);
        RectangleMethod* rect_int = new RectangleMethod(functions[i], nStepOfIntegration);

        cout << "\nIntegration function \"" << BOLD_CYAN << functions[i]->Name() << RESET_COLOR << "\"\033[0m" << " in interval ["
            << setprecision(4) << x_min << ", " << x_max << "] using three methods:" << endl;

        for (int nStepOfIntegration = 10; nStepOfIntegration <= 1E6; nStepOfIntegration*=10){

            mc_int->setNumberPoints(nStepOfIntegration);
            trap_int->setNumberPoints(nStepOfIntegration);
            rect_int->setNumberPoints(nStepOfIntegration);

            integralMC = mc_int->integrate(x_min,x_max);
            integralTrap = trap_int->integrate(x_min,x_max);
            integralRect = rect_int->integrate(x_min,x_max);

            cout << "\n\t1) Monte Carlo method with " << nStepOfIntegration << " step of integration:\t" << scientific << integralMC << endl;
            cout << "\t2) Trapezoids method with " << nStepOfIntegration << " step of integration:\t" << scientific << integralTrap << endl;
            cout << "\t3) Rectangeles method with " << nStepOfIntegration << " step of integration:\t" << scientific << integralRect << "\n" << endl;

            outputFile << nStepOfIntegration << "\t\t\t" << integralMC << "\t\t\t" << integralTrap << "\t\t" << integralRect << endl;

        }
        
        delete mc_int;
        delete trap_int;
        delete rect_int;

        outputFile.close();

    }
    
    return(EXIT_SUCCESS);
}
