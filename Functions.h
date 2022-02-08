#include <string>

#ifndef Function_h
#define Function_h

using namespace std;

// ABSTRACT CLASS: Function
// A simple mathematical function with some features
class Function{

    public:
    // constructor
    Function(const std::string& name);
    // (virtual) destructor
    virtual ~Function(){};
    // value of the function in a given point x
    virtual double value(const double& x) const = 0;  //pure virtual
    // useful for checks
    virtual ostream& Print(ostream& output) const = 0;  //pure virtual
    // name of the custom function (for example "Planck distribution")
    virtual string Name() const { return name_; }

    private:
    std::string name_;

};

// CONCRETE (AND CHILDREN) CLASSES:

// #1 Gaussian function
class Gauss:public Function{

    public:
    // constructor
    Gauss(const double& mean, const double& sigma, const string&);
    // destructor + "implementation"
    virtual ~Gauss(){};
    // setters
    void setMean(const double& mean);
    void setStdDev(const double& sigma);
    // getters
    const double& Mean() const;
    const double& StdDev() const;
    // distance from the center in units of standard deviation
    double SigmasFromMu(const double& x) const;
    // Full Width Half Maximum
    double FWHM() const;
    // virtual functions of base class
    virtual double value(const double& x) const;
    virtual ostream& Print(ostream& output) const;

    private:
    double mean_;
    double std_deviation_;

};

// #2 Exponential function (decreasing, valid for x>0)
class Exponential:public Function{

    public:
    // constructor
    Exponential(const double& alpha, const string&);
        //NOTE: the standard normalization is a*exp(-a*x), but you can choose a different constant.
    Exponential(const double& alpha, const double& norm, const string&);
    // destructor
    virtual ~Exponential(){};
    // setters
    void setParameter(const double& alpha);
    void setNormalization(const double& Norm);
    // getters
    const double& Parameter() const;
    const double& Normalization() const;
    // operation to normalize the exponential function to something like that: a*exp(-a*x)
    void Normalize();   // cannot be const
    // virtual functions of base class
    virtual double value(const double& x) const;
    virtual ostream& Print(ostream& output) const;

    private:
    double parameter_;
    double normalization_;

};

// Line function
class Line:public Function{

    public:
    // constructor
    Line(const double& angularCoefficient, const double& quote, const string& name);
    // (virtual) destructor
    virtual ~Line(){};
    // setters
    void setCoefficient(const double& angularCoefficient);
    void setQuote(const double& quote);
    // getters
    const double& Coefficient() const;
    const double& Quote() const;
    // virtual functions of base class
    virtual double value(const double& x) const;
    virtual ostream& Print(ostream& output) const; 

    private:
    double coefficient_;
    double quote_;

};

#endif