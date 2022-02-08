#include <string>

#ifndef Function_h
#define Function_h

using namespace std;

// ABSTRACT CLASS:
// Function
class Function{

    public:
    Function(const std::string& name);
    virtual ~Function(){};
    virtual double value(const double&) const = 0;
    virtual void Print() const = 0;
    virtual string Name() const { return name_; }

    private:
    std::string name_;

};

// CONCRETE (AND CHILDREN) CLASSES:
// Gauss
class Gauss:public Function{

    public:
    Gauss(const double&, const double&, const string&);
    virtual ~Gauss(){};
    void setMean(const double&);
    void setStdDev(const double&);
    const double& Mean() const;
    const double& StdDev() const;
    double SigmasFromMu(const double&) const;
    double FWHM() const;
    virtual double value(const double&) const;
    virtual void Print() const;

    private:
    double mean_;
    double std_deviation_;

};

// Exponential
class Exponential:public Function{

    public:
    Exponential(const double&, const string&);
    Exponential(const double&, const double&, const string&);
    virtual ~Exponential(){};
    void setParameter(const double&);
    void setNormalization(const double&);
    const double& Parameter() const;
    const double& Normalization() const;
    void Normalize();
    virtual double value(const double&) const;
    virtual void Print() const;

    private:
    double parameter_;
    double normalization_;

};

// Line
class Line:public Function{

    public:
    Line(const double&, const double&, const string&);
    virtual ~Line(){};
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