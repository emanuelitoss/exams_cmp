#ifndef Capacitor_h
#define Capacitor_h

#include <iostream>
#define EPS_VACUUM 8.854e-12 // Vacuum dielectric constant, expressed in Farad/meter

class Capacitor{

// Capacitor private data members:
private:
    // relative dielectric constant of the material (adimensional)
    double relativeEps_;
    // area of th plane capacitor (meters*meters)
    double area_;
    // distance between the plates (meters)
    double separation_;

// Capacitor public data members:
public:
    // constructors
    Capacitor();
    Capacitor(const double& area, const double& distance);
    Capacitor(const double& area, const double& distance, const double& relativeEps);
    
    // destructor
    ~Capacitor(){};

    // setters   
    void setEps(const double&); // sets relative dielectric constant of the materia between the plates (adimensional)
    void setArea(const double&);    // sets the area of the plates (meters*meters)
    void setSeparation(const double&);  // sets the distance between the plates (meters)
    // getters
    const double& relativeEpsilon() const;  // returns relative dielectric constant of the material between the plates
    const double& area() const; // returns area of the plates in (meters*meters)
    const double& separation() const;   // returns distance between the plates in (meters)
    
    // utility methods
    double capacitance() const;  // returns capacitantance in (Farad)
    void print() const; // prints features of the capacitor
    void setCapacitance(const double& cap); // sets capacitance

    // overloaded operators
    Capacitor operator||(const Capacitor& secondC) const;
    Capacitor operator+(const Capacitor& secondC) const;

};

#endif