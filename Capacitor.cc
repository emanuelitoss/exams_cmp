#include "Capacitor.h"
#include <iostream>
#include <iomanip>

// set of output colors
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

// CONSTRUCTORS

Capacitor::Capacitor(){
    // if not specified I set the vacuum with standard values
    relativeEps_ = 1;
    area_ = 0;
    separation_ = 1E-6;
}

Capacitor::Capacitor(const double& area, const double& distance){
    // if not specified, I choose a ceramic capacitor
    relativeEps_ = 8.35;
    area_ = area;
    separation_ = distance;
}

Capacitor::Capacitor(const double& area, const double& distance, const double& relativeEps){
    if(relativeEps>=1){
        relativeEps_ = relativeEps;
        area_ = area;
        separation_ = distance;
    }else{
        std::cerr << RED << "Error: relative dielectric constant must be greater or equal to 1" << COLOR_RESET << std::endl;
        exit(EXIT_FAILURE);
    }
}

// SETTERS

// sets relative dielectric constant of the materia between the plates (adimensional)
void Capacitor::setEps(const double& epsilon){
    relativeEps_ = epsilon;
}

// sets the area of the plates (meters*meters)
void Capacitor::setArea(const double& area){
    area_ = area;
}

// sets the distance between the plates (meters)
void Capacitor::setSeparation(const double& separation){
    separation_ = separation;
}

// GETTERS

// returns relative dielectric constant of the material between the plates
const double& Capacitor::relativeEpsilon() const {
    return relativeEps_;
}

// returns area of the plates in (meters*meters)
const double& Capacitor::area() const {
    return area_;
}

// returns distance between the plates in (meters)
const double& Capacitor::separation() const {
    return separation_;
}

// UTILITY METHODS

// returns capacitantance in (Farad)
double Capacitor::capacitance() const {
    return EPS_VACUUM*relativeEps_*area_/separation_;
}

// prints features of the capacitor
void Capacitor::print() const {
    std::cout << "Capacitor features:" << std::scientific
    << GREEN << "\n\tRelative dielectric constant:\t" << COLOR_RESET << relativeEps_
    << GREEN << "\n\tArea of the plates:\t" << COLOR_RESET << area_ << " m*m"
    << GREEN << "\n\tSeparation between the plates:\t" << COLOR_RESET << separation_ << " m"
    << GREEN << "\n\tCapacitance:\t" << COLOR_RESET << this->capacitance() << " F"
    << std::endl;
}

// changes value of A in order to return the right Capacitance
void Capacitor::setCapacitance(const double& cap){
    area_ = cap*separation_/EPS_VACUUM/relativeEps_;
}

// OVERLOADED OPERATORS

// constructs a fake capacitor with same capacitance value of the equivalent capacitor
Capacitor Capacitor::operator||(const Capacitor& secondC) const {
    double equivalentC = this->capacitance() + secondC.capacitance();
    Capacitor c3(1, separation_, relativeEps_);
    c3.setCapacitance(equivalentC);
    return c3;
}

// constructs a fake capacitor with same capacitance value of the equivalent capacitor
Capacitor Capacitor::operator+(const Capacitor& secondC) const {
    double equivalentC = this->capacitance()*secondC.capacitance()/(this->capacitance() + secondC.capacitance());
    Capacitor c3(1, separation_, relativeEps_);
    c3.setCapacitance(equivalentC);
    return c3;
}