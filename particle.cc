#include "particle.h"
#include <cmath>

// CONSTRUCTORS

Particle::Particle(){
    mass_ = 0;
    px_ = 0;
    py_ = 0;
    pz_ = 0;
}

Particle::Particle(const double& mass){
    mass_ = mass;
    px_ = 0;
    py_ = 0;
    pz_ = 0;
}

Particle::Particle(const double& px, const double& py, const double& pz){
    mass_ = 0;
    px_ = px;
    py_ = py;
    pz_ = pz;
}

Particle::Particle(const double& mass, const double& px, const double& py, const double& pz){
    mass_ = mass;
    px_ = px;
    py_ = py;
    pz_ = pz;
}

// SETTERS
void Particle::setPx(const double& momentum_x){ px_ = momentum_x; }
void Particle::setPy(const double& momentum_y){ py_ = momentum_y; }
void Particle::setPz(const double& momentum_z){ pz_ = momentum_z; }
void Particle::setMass(const double& mass){ mass_ = mass; }

// GETTERS
double Particle::Px() const { return px_; }
double Particle::Py() const { return py_; }
double Particle::Pz() const { return pz_; }
double Particle::Mass() const { return mass_; }
double Particle::P() const { return sqrt(px_*px_ + py_*py_ + pz_*pz_); }
double Particle::Theta() const {
    if(px_*px_ + py_*py_ == 0 && pz_ > 0) return 0;
    else if(px_*px_ + py_*py_ == 0 && pz_ > 0) return M_PI;
    else return atan(sqrt(px_*px_ + py_*py_)/pz_);
}
double Particle::Phi() const{
    if(px_ == 0 && py_ > 0) return M_PI;
    else if(px_ == 0 && py_ < 0) return 0.5*3*M_PI;
     else return atan(py_/px_);
}
double Particle::Energy() const { return sqrt(mass_*mass_ + (this->P())*(this->P())); }

// OVERLOADED OPERATORS
Particle Particle::operator+(const Particle& second_particle) const{
    double px = px_ + second_particle.Px();
    double py = py_ + second_particle.Py();
    double pz = pz_ + second_particle.Pz();
    double mass = mass_ + second_particle.Mass();
}