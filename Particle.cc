#include "Particle.h"
#include <iostream>
#include <cmath>
using namespace std;

#define BOLD_RED "\033[1;31m"
#define BOLD_WHITE "\033[1;37m"
#define CYAN "\033[1;36m"
#define COLOR_RESET "\033[0m"

// constructors
Particle::Particle(const int& id, const string& name, const double& mass){
    id_ = id;
    name_ = name;
    mass_ = mass;
    charge_ = 0;
    momentum_ = TVector3(0,0,0);
}
Particle::Particle(const int& id, const string& name, const double& mass, const int& charge){
    id_ = id;
    name_ = name;
    mass_ = mass;
    charge_ = charge;
    momentum_ = TVector3(0,0,0);
}
Particle::Particle(const int& id, const string& name, const double& mass, const double& px, const double& py, const double& pz){
    id_ = id;
    name_ = name;
    mass_ = mass;
    charge_ = 0;
    momentum_ = TVector3(px,py,pz);
}
Particle::Particle(const int& id, const string& name, const double& mass, const int& charge, const double& px, const double& py, const double& pz){
    id_ = id;
    name_ = name;
    mass_ = mass;
    charge_ = charge;
    momentum_ = TVector3(px,py,pz);
}

// destructors
Particle::~Particle(){
    cout << "Destroying particle \"" << name_ << "\"" << endl;
}

// getters
const int& Particle::id() const { return id_; }
const string& Particle::name() const { return name_; }
const double& Particle::mass() const { return mass_; }
const int& Particle::charge() const { return charge_; }
const TVector3& Particle::momentum() const { return momentum_; }
double Particle::energy() const {
    return sqrt( mass_*mass_ + momentum_.Mag()*momentum_.Mag() );
}

// setters
void Particle::setId(const int& id) { id_ = id; }
void Particle::setName(const string& name) { name_ = name; }
void Particle::setMass(const double& mass) { mass_ = mass; }
void Particle::setCharge(const int& q) { charge_ = q; }
void Particle::setMomentum(const TVector3& momentum) { momentum_ = momentum; }

// utility
void Particle::print() const {
    cout << "Paticle (id, name) = (" << CYAN << id_ << COLOR_RESET << ", " << CYAN << name_ << COLOR_RESET << ")\t"
    << "Mass = " << mass_ << "\tCharge = " << charge_ << endl;
}