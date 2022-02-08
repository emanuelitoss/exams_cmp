#include "Functions.h"
#include <iostream>
#include <cmath>

using namespace std;

// ABSTRACT CLASSES:

// Function
Function::Function(const string& name){ name_ = name; }

// CONCRETE (AND CHILDREN) CLASSES METHODS

// #1 Gaussian
Gauss::Gauss(const double& meanValue, const double& sdtDeviation, const string& name) : Function(name){
    mean_ = meanValue;
    std_deviation_ = sdtDeviation;
}
void Gauss::setMean(const double& meanValue){ mean_ = meanValue; }
void Gauss::setStdDev(const double& sdtDeviation){ std_deviation_ = sdtDeviation; }
const double& Gauss::Mean() const { return mean_;}
const double& Gauss::StdDev() const { return std_deviation_; }
double Gauss::SigmasFromMu(const double& x) const {
    return (fabs(x - mean_)/std_deviation_);
}
double Gauss::FWHM() const { return std_deviation_*sqrt(2*log(2)); }
double Gauss::value(const double& x) const{
    return exp(-(x-mean_)*(x - mean_)/2/std_deviation_/std_deviation_)/sqrt(2*M_PI)/std_deviation_;
}
ostream& Gauss::Print(ostream& output) const {
    output << "#Gaussian function with mean = " << mean_ << " and std deviation = " << std_deviation_ << endl;
    return output;
}

// #2 Line
Line::Line(const double& coefficient, const double& quote, const string& name) : Function(name){
    coefficient_ = coefficient;
    quote_ = quote;
}
void Line::setCoefficient(const double& coefficient){ coefficient_ = coefficient; }
void Line::setQuote(const double& quote){ quote_ = quote; }
const double& Line::Coefficient() const { return coefficient_; }
const double& Line::Quote() const { return quote_; }
double Line::value(const double& x) const {
    return x*coefficient_ + quote_;
}
ostream& Line::Print(ostream& output) const{
    output << "#Line function with coefficient = " << coefficient_ << " and quote = " << quote_ << endl;
    return output;
}

// #3 Exponential
Exponential::Exponential(const double& lambda, const string& name) : Function(name){
    if (lambda < 0){
        cerr << "Error: exponential function must have positive value for the parameter lambda" << endl;
        cout << "Insert a new value:" << endl;
        cin >> parameter_;
        normalization_ = parameter_;
    }else{
        parameter_ = lambda;
        normalization_ = lambda;
    }
}
Exponential::Exponential(const double& lambda, const double& normalization, const string& name) : Function(name){
    if (lambda < 0){
        cerr << "Error: exponential function must have positive value for the parameter lambda" << endl;
        cout << "Insert a new value:" << endl;
        cin >> parameter_;
        normalization_ = normalization;
    }else{
        parameter_ = lambda;
        normalization_ = normalization;;
    }
}
void Exponential::setParameter(const double& lambda){ parameter_ = lambda; }
void Exponential::setNormalization(const double& norm){ normalization_ = norm; }
const double& Exponential::Parameter() const { return parameter_; }
const double& Exponential::Normalization() const { return normalization_; }
void Exponential::Normalize(){ normalization_ = parameter_; }
double Exponential::value(const double& x) const {
    if (x < 0) return 0;
    else return normalization_*exp(-x/parameter_);
}
ostream& Exponential::Print(ostream& output) const {
    output << "#Exponential function with parameter lambda = " << parameter_ << " and normalization = " << normalization_ << endl;
    return output;
}