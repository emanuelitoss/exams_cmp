#include "Integration.h"

#define EPS 0.001

using namespace std;

// ABSTRACT CLASSES:

// Function
Function::Function(const string& name){ name_ = name; }
void Integrator::setIntegrand(Function* function){
    f_ = function;
}
// Integrator
Function* Integrator::integrand() const { return f_; }
double Integrator::integrandValue(const double& x) const {
    return f_->value(x);
}
double Integrator::Maximum(const double& xlow, const double& xhigh) const {
    double maximum = f_->value(xlow);
    double DeltaX = xhigh-xlow;
    for(int i = 0; i<round(DeltaX/EPS); ++i){
        if(f_->value(xlow + DeltaX*EPS*i) > maximum)
            maximum = f_->value(xlow + DeltaX*EPS*i);
    }
    return maximum;
}

// CONCRETE (AND CHILDREN) CLASSES METHODS

// A) Functions

// #1 Gaussian
Gauss::Gauss(const double& meanValue, const double& sdtDeviation, const string& name):Function(name){
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
    return exp(-(x-mean_)*(x - mean_)/2/std_deviation_)/sqrt(2*M_PI)/std_deviation_;
}
void Gauss::Print() const {
    cout << "Gaussian function with mean = " << mean_ << " and std deviation = " << std_deviation_ << endl;
}

// #2 Line
Line::Line(const double& coefficient, const double& quote, const string& name):Function(name){
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
void Line::Print() const{
    cout << "Line function with coefficient = " << coefficient_ << " and quote = " << quote_ << endl;
}

// #3 Exponential
Exponential::Exponential(const double& lambda, const string& name):Function(name){
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
Exponential::Exponential(const double& lambda, const double& normalization, const string& name):Function(name){
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
void Exponential::Normalize(){ normalization_ = parameter_; }
double Exponential::value(const double& x) const {
    if (x < 0) return 0;
    else return normalization_*exp(-x/parameter_);
}
void Exponential::Print() const {
    cout << "Exponential function with parameter lambda = " << parameter_ << " and normalization = " << normalization_ << endl;
}

// B) Integration methods

// Monte Carlo method:

MonteCarloMethod::MonteCarloMethod(Function* function, const int& numberOFpoints):Integrator(function){
    counter_ = 0;
    number_points_ = numberOFpoints;
}

//  I will generate random points in the interval [a,b] and I will count the number of points within
//  the area to integrate. Then this number is normalized and multiplied by the area in wich these points
//  are generated. This final result is the value of the integrand
double MonteCarloMethod::integrate(const double& xlow, const double& xhigh){

    double DeltaX = xhigh - xlow;
    double x, y;
    for(int i = 0; i < number_points_; ++i){
        // generation of a random number in x axis
        x = xlow + drand48()*DeltaX;
        // generation of a random number in y axis
        y = drand48()*this->Maximum(xlow,xhigh);

        if(integrand()->value(x) > y) counter_++;
    }

    double area = this->Maximum(xlow,xhigh)*DeltaX*counter_/number_points_;
    counter_ = 0;
    return area;
}

// Rectangles method
RectangleMethod::RectangleMethod(Function* function, const int& numberOFpoints):Integrator(function){
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
TrapezoidMethod::TrapezoidMethod(Function* function, const int& numberOFpoints):Integrator(function){
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