#include "complex.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

Complex::Complex(){
    re_ = 0;
    im_ = 0;
    std::cout << " >> Creating a complex number" << std::endl;
};

Complex::Complex(const double& x, const double& y){
    re_ = x;
    im_ = y;
    std::cout << " >> Creating a complex number: (" << x << ") + i(" << y << ")" << std::endl;
};

Complex::~Complex(){
    std::cout << " >> Destroying a complex number" << std::endl;
}

const double Complex::Re() const { return re_; }
const double Complex::Im() const { return im_; }
const double Complex::R() const { return sqrt(re_*re_ + im_*im_); }
const double Complex::Phi() const {
    if(im_ == 0){
        if(re_ > 0) return 0;
        else return M_PI;
    }
    else return atan(im_/re_);
}

const Complex Complex::operator+(const double& number) const{ return Complex(re_ + number, im_); }
const Complex Complex::operator-(const double& number) const{ return Complex(re_ - number, im_); }
const Complex Complex::operator*(const double& number) const{ return Complex(re_*number, im_*number); }
const Complex Complex::operator/(const double& number) const{
    if (number != 0) return Complex(re_/number, im_/number);
    else{
        std::cerr << "Error: you cannot divide a number by 0." << std::endl;
        return Complex(re_, im_);
    }
}

const Complex Complex::operator+(const Complex& z) const{ return Complex(re_ + z.Re(), im_ + z.Im()); }
const Complex Complex::operator-(const Complex& z) const{ return Complex(re_ - z.Re(), im_ - z.Im()); };
const Complex Complex::operator*(const Complex& z) const{
    return Complex(re_*z.Re() - im_*z.Im(), re_*z.Im() + im_*z.Re());
}
const Complex Complex::operator/(const Complex& z) const{
    if(z.R()!=0){
        double real_unnormalized = re_*z.Re() + im_*z.Im();
        double imm_unnormalized = im_*z.Re() - re_*z.Im();
        return Complex(real_unnormalized/z.R()/z.R(), imm_unnormalized/z.R()/z.R());
    }else{
        std::cerr << "Error: you cannot divide a number by 0." << std::endl;
        return Complex(re_, im_);
    }
}

ostream& operator<<(ostream& os, const Complex& z){
    os << "(Re: " << z.Re() << ", Im: " << z.Im() << ")";
    return os;
}

Complex operator+(const double& number, const Complex& z){ return Complex(z.Re() + number, z.Im()); }
Complex operator-(const double& number, const Complex& z){ return Complex(z.Re() - number, z.Im()); }
Complex operator*(const double& number, const Complex& z){ return Complex(z.Re()*number, z.Im()*number); }
Complex operator/(const double& number, const Complex& z){
    if(z.R() != 0){
        return Complex(z.Re(),-z.Im())*number/z.R()/z.R();
    }else{
        std::cerr << "Error: you cannot divide a number by 0." << std::endl;
        return Complex(z.Re(),z.Im());
    }
}