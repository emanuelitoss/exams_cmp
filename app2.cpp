#include "Capacitor.h"
#include <iostream>
using namespace std;

int main(){

    cout << "This app shows the methods of the class \"Capacitor\"" << endl;
    
    Capacitor c1;
    c1.print();
    c1.setArea(1e-4);
    c1.print();

    Capacitor* c2 = new Capacitor(3e-6, 1.2e-6);
    c2->print();
    Capacitor* c3 = new Capacitor(3e-6, 1.2e-6);
    c2->print();

    delete c3;

    return EXIT_SUCCESS;
}