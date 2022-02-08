#include "Integration.h"
#include <iostream>
#include <string>
#include <cmath>

#define EPS 0.001

using namespace std;

// ABSTRACT CLASSES:
Integrator::Integrator(Function* function){
    f_ = function;
}

// Integrator
void Integrator::setIntegrand(Function* function){
    f_ = function;
}

Function* Integrator::integrand() const { return f_; }

double Integrator::integrandValue(const double& x) const {
    return f_->value(x);
}

double Integrator::Maximum(const double& xlow, const double& xhigh) const {
    double maximum = f_->value(xlow);
    double DeltaX = xhigh-xlow;
    double point;
    for(int i = 0; i<round(DeltaX/EPS); ++i){
        point = f_->value(xlow + DeltaX*EPS*i);
        if(point > maximum) maximum = point;
    }
    return maximum;
}

double Integrator::Minimum(const double& xlow, const double& xhigh) const {
    double minimum = f_->value(xlow);
    double DeltaX = xhigh-xlow;
    double point;
    for(int i = 0; i<round(DeltaX/EPS); ++i){
        point = f_->value(xlow + DeltaX*EPS*i);
        if(point < minimum) minimum = point;
    }
    return minimum;
}

// CONCRETE (AND CHILDREN) CLASSES METHODS
// Integration methods

// Monte Carlo method:
MonteCarloMethod::MonteCarloMethod(Function* function, const int& numberOFpoints) : Integrator(function){
    number_points_ = numberOFpoints;
}

//  I will generate random points in the interval [a,b] and I will count the number of points within
//  the area to integrate. Then this number is normalized and multiplied by the area in wich these points
//  are generated. This final result is the value of the integrand
double MonteCarloMethod::integrate(const double& xlow, const double& xhigh) const {

    double counter = 0;
    double DeltaX = xhigh - xlow;
    double x, y;
    for(int i = 0; i < number_points_; ++i){
        // generation of a random number in x axis
        x = xlow + drand48()*DeltaX;
        // generation of a random number in y axis
        y = drand48()*this->Maximum(xlow,xhigh);

        if(integrand()->value(x) > y) counter++;
    }

    double area = this->Maximum(xlow,xhigh)*DeltaX*counter/number_points_;
    return area;
}

// Rectangles method
RectangleMethod::RectangleMethod(Function* function, const int& numberOFpoints) : Integrator(function){
    number_rectangles_ = numberOFpoints;
}

double RectangleMethod::integrate(const double& xlow, const double& xhigh) const {
    double step_dx = (xhigh - xlow)/number_rectangles_;
    double area = 0;
    for (int i = 0; i < number_rectangles_; i++){
        area += step_dx*integrand()->value(xlow + i*step_dx);
    }
    return area;
    
}

// Trapezoids method
TrapezoidMethod::TrapezoidMethod(Function* function, const int& numberOFpoints) : Integrator(function){
    number_trapezoids_ = numberOFpoints;
}

double TrapezoidMethod::integrate(const double& xlow, const double& xhigh) const {
    double step_dx = (xhigh - xlow)/number_trapezoids_;
    double area = 0;
    for (int i = 0; i < number_trapezoids_; i++){
        area += (integrand()->value(xlow + i*step_dx) + integrand()->value(xlow + (i+1)*step_dx))*step_dx/2;
    }
    return area;
}