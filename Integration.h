#include <iostream>
#include <cmath>
#include <string>

#ifndef Integration_h
#define Integration_h

using namespace std;

// ABSTRACT CLASSES:

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

#endif