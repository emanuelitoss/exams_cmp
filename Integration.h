#include "Functions.h"

#ifndef Integration_h
#define Integration_h

using namespace std;

// ABSTRACT CLASS:
// Integrator
class Integrator{
    public:
    Integrator(Function*);
    virtual ~Integrator(){};
    void setIntegrand(Function*);
    Function* integrand() const;
    double integrandValue(const double&) const;
    virtual double integrate(const double&, const double&) const = 0;
    double Maximum(const double&, const double&) const;
    double Minimum(const double&, const double&) const;

    private:
    Function* f_;
};


// CONCRETE (AND CHILD) CLASSES:
// Monte Carlo method
class MonteCarloMethod:public Integrator{

    public:
    MonteCarloMethod(Function*, const int&);
    void setNumberPoints(const int&);
    virtual ~MonteCarloMethod(){};
    virtual double integrate(const double&, const double&) const;

    private:
    int number_points_;

};

// Rectangles method
class RectangleMethod:public Integrator{

    private:
    int number_rectangles_;

    public:
    RectangleMethod(Function*, const int&);
    void setNumberPoints(const int&);
    virtual ~RectangleMethod(){};
    virtual double integrate(const double&, const double&) const;

};

// Trapezoid method
class TrapezoidMethod:public Integrator{

    private:
    int number_trapezoids_;

    public:
    TrapezoidMethod(Function*, const int&);
    void setNumberPoints(const int&);
    virtual ~TrapezoidMethod(){};
    virtual double integrate(const double&, const double&) const;

};

#endif