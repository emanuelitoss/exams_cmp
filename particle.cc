#include "particle.h"
#include <cmath>

// PARTICLE

// constructors
Particle::Particle(){
    mass_ = 0;
    momentum_ = 0;
}

Particle::Particle(const double& mass){
    mass_ = mass;
    momentum_ = 0;
}

Particle::Particle(const double& mass, const double& momentum){
    mass_ = mass;
    momentum_ = momentum;
}

// setters
void Particle::setMass(const double& mass){ mass_ = mass; }
void Particle::setP(const double& momentum){ momentum_ = momentum; }

// getters
double Particle::Momentum() const { return momentum_; }
double Particle::Energy() const { return sqrt(mass_*mass_ + (this->Momentum())*(this->Momentum())); }
double Particle::Mass() const { return mass_; }

// overloaded operators
Particle Particle::operator+(const Particle& particle) const{
    return Particle(mass_ + particle.Mass(), momentum_ + particle.Momentum());
}

// COMPOSITE PARTICLE

// constructors
CompositeParticle::CompositeParticle(){
        mass_ = 0;
    momentum_ = 0;
}

CompositeParticle::CompositeParticle(const double& mass){
    mass_ = mass;
    momentum_ = 0;
}

CompositeParticle::CompositeParticle(const double& mass, const double& momentum){
    mass_ = mass;
    momentum_ = momentum;
}

CompositeParticle::CompositeParticle(const Particle& particle){
    momentum_ = particle.Momentum();
    mass_ = sqrt(particle.Mass()*particle.Mass() + momentum_*momentum_);
}

// getters
double CompositeParticle::Momentum() const { return momentum_; }
double CompositeParticle::Energy() const { return mass_; }

// utility methods
void CompositeParticle::Add(const Particle& particle){
    momentum_ += particle.Momentum();
    mass_ += sqrt(particle.Mass()*particle.Mass() + particle.Momentum()*particle.Momentum());
}

// overloaded operators
CompositeParticle CompositeParticle::operator<<(const Particle& particle){
    this->mass_ += particle.Mass();
    this->momentum_ += particle.Momentum();
    return *this;
}