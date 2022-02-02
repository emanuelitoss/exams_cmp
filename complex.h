#ifndef complex_h
#define complex_h

#include <fstream>
#include <iostream>
using namespace std;

class Complex{
    public:

    Complex();
    Complex(const double&, const double&);

    ~Complex();

    const double Re() const;
    const double Im() const;
    const double R() const;
    const double Phi() const;

    const Complex operator+(const double&) const;
    const Complex operator-(const double&) const;
    const Complex operator*(const double&) const;
    const Complex operator/(const double&) const;

    const Complex operator+(const Complex&) const;
    const Complex operator-(const Complex&) const;
    const Complex operator*(const Complex&) const;
    const Complex operator/(const Complex&) const;

    private:
    double re_;
    double im_;

};

ostream& operator<<(ostream&, const Complex&);

Complex operator+(const double& number, const Complex& z);
Complex operator-(const double& number, const Complex& z);
Complex operator*(const double& number, const Complex& z);
Complex operator/(const double& number, const Complex& z);

#endif