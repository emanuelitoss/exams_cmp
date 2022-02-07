#include <iostream>
#include <cmath>
#include <string>

#ifndef Integration_h
#define Integration_h

using namespace std;

// ABSTRACT CLASS:
// Function
class Function{

    public:
    Function(const string& name);
    virtual ~Function();
    virtual double value(const double& x) const = 0;
    virtual double integrate(const double& xlow, const double& xhigh) const = 0;
    virtual void Print() const = 0;

    private:
    string name_;

};

// CONCRETE (AND CHILDREN) CLASSES:
// Gauss
class Gauss:public Function{

    public:
    Gauss(const double&, const double&, const string&);
    virtual ~Gauss();
    void setMean(const double&);
    void setStdDev(const double&);
    const double& Mean() const;
    const double& StdDev() const;
    double SigmasFromMu(const double&) const;
    double FWHM() const;
    virtual double value(const double& x) const;
    virtual void Print() const;

    private:
    double mean_;
    double std_deviation_;

};


// Line
class Line:public Function{

    public:
    Line(const double&, const double&, const string&);
    virtual ~Line();
    void setCoefficient(const double&);
    void setQuote(const double&);
    const double& Coefficient() const;
    const double& Quote() const;
    virtual double value(const double&) const;
    virtual void Print() const; 

    private:
    double coefficient_;
    double quote_;

};

// Exponential
class Exponential:public Function{

    public:
    Exponential(const double&, const string&);
    Exponential(const double&, const double&, const string&);
    virtual ~Exponential();
    void setParameter(const double&);
    void setNormalization(const double&);
    const double& Parameter() const;
    void Normalize();
    virtual double value(const double&) const;
    virtual void Print() const;

    private:
    double parameter_;
    double normalization_;

};

// ABSTRACT CLASS:
// Integrator
class Integrator{
    public:
    Integrator(Function*);
    virtual ~Integrator();
    void setIntegrand(Function*);
    Function* integrand() const;
    double integrandValue(const double&) const;
    virtual double integrate(const double&, const double&) const = 0;
    double Maximum(const double&, const double&) const;

    private:
    Function* f_;
};


// CONCRETE (AND CHILD) CLASSES:
// Monte Carlo method
class MonteCarloMethod:public Integrator{

    public:
    MonteCarloMethod(Function*, const int&);
    virtual ~MonteCarloMethod();
    virtual double integrate(const double&, const double&);

    private:
    int number_points_;
    int counter_;

};

// Rectangles method
class RectangleMethod:public Integrator{

    private:
    int number_rectangles_;

    public:
    RectangleMethod(Function*, const int&);
    virtual ~RectangleMethod();
    virtual double integrate(const double&, const double&) const;

};

// Trapezoid method
class TrapezoidMethod:public Integrator{

    private:
    int number_trapezoids_;

    public:
    TrapezoidMethod(Function*, const int&);
    virtual ~TrapezoidMethod();
    virtual double integrate(const double&, const double&) const;

};

#endif