#include <iostream>
#include <fstream>
using namespace std;

#include "Capacitor.h"
#include "TRandom3.h"

int main(){
    
    // predisposition for TRandom3 random number generator
    TRandom3* gen = new TRandom3();
    gen->SetSeed(0);
    
    // predisposition for output file
    ofstream outputFile;
    outputFile.open("true_values.txt");
    outputFile << "#All the are expressed in picoFarad" << endl;
    outputFile << "#c1\tc_equivalent\t" << endl;

    // creating 4 capacitors
    Capacitor* c1 = new Capacitor();
    Capacitor* c2 = new Capacitor();
    Capacitor* c3 = new Capacitor();
    Capacitor* c4 = new Capacitor();

    // setting 3 fixed capacitance values
    c2->setCapacitance(10e-12);
    c3->setCapacitance(3e-12);
    c4->setCapacitance(15e-12);

    // number of generated Data
    int numberData = 1000;
    // maximum and minimum values for generated capacitance
    double minC = 1e-12, maxC = 100e-12;
    // total equivalent capacitance of the circuit
    double totalC;
    //useful
    Capacitor* c5 = new Capacitor();
    (*c5) = (*c3)||(*c4);

    // loop over the generations
    for (int i = 0; i < numberData; i++){

        // generation of random capacitances in the choosen inerval
        c1->setCapacitance(minC + (maxC - minC)*gen->Rndm());
        // evaluation of euqivalent capacitance
        totalC = (( (*c1) || (*c2) ) + (*c5) ).capacitance();
        // writing in output file (in picoFarad)
        outputFile << c1->capacitance()*1e12 << "\t" << totalC*1e12 << endl;;
    }

    // removing objects pointers
    delete c5;
    delete c4;
    delete c3;
    delete c2;
    delete gen;
    outputFile.close();
    return EXIT_SUCCESS;
}