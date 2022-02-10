#include "CompositeParticle.h"
#include <iostream>

#define BOLD_RED "\033[1;31m"
#define BOLD_WHITE "\033[1;37m"
#define CYAN "\033[1;36m"
#define COLOR_RESET "\033[0m"

CompositeParticle::CompositeParticle(){
    name_ = "Not defined";
}

CompositeParticle::CompositeParticle(const std::string& name){
    name_ = name;
}

CompositeParticle::~CompositeParticle(){}

void CompositeParticle::setName(const std::string& name){
    name_ = name;
}

void CompositeParticle::add(const Particle& particle){
    particles_->push_back(particle);
    std::cout << "(" << particle.name() << ", " << particle.id() << ") joined " << this->name_ << std::endl;
}

void CompositeParticle::Add(const CompositeParticle& composition){
    std::cout << BOLD_WHITE << composition.name() << COLOR_RESET << " joined "
        << BOLD_WHITE << this->name() << COLOR_RESET << std::endl;
    for(std::vector <Particle>::iterator d = composition.particleVector()->begin(); d != composition.particleVector()->end(); ++d){
        particles_->push_back(*d);
        std::cout << "\t(" << d->name() << ", " << d->id() << ") joined " << this->name_ << std::endl;
    }
}

void CompositeParticle::clear(){
    particles_->clear();
}

const std::string& CompositeParticle::name() const {
    return name_;
}

Particle& CompositeParticle::element(const int& index) const {
    if(index >= particles_->size() || index < 0){
        std::cout << BOLD_RED << "ERROR: You're trying to select a particle not in the Composite particle " << name_ << " set." << COLOR_RESET << std::endl;
        exit(EXIT_FAILURE);
    }
    else return (*particles_)[index];
}

std::vector <Particle>* CompositeParticle::particleVector() const {
    return particles_;
}

int CompositeParticle::NumberOfParticles() const {
    return particles_->size();
}

void CompositeParticle::print() const {
    std::cout << "Composition of particles:"
    << "\n\tName: " << BOLD_WHITE << name_ << COLOR_RESET
    << "\n\tNumber of particles: " << BOLD_WHITE << particles_->size() << COLOR_RESET
    << std::endl;
}

void CompositeParticle::printParticles() const {
    this->print();
    for(std::vector <Particle>::iterator d = particles_->begin(); d != particles_->end(); ++d)  d->print();
}

double CompositeParticle::energy() const {
    double Energy = 0;
    for(std::vector <Particle>::iterator d = particles_->begin(); d != particles_->end(); ++d){
        Energy += d->energy();
    }
    return Energy;
}

TVector3 CompositeParticle::totalMomenutm() const {
    TVector3 totalP(0,0,0);
    for(std::vector <Particle>::iterator d = particles_->begin(); d != particles_->end(); ++d){
        totalP += d->momentum();
    }
    return totalP;
}

double CompositeParticle::invariantMass() const {
    return sqrt( this->energy()*this->energy() - this->totalMomenutm().Mag()*this->totalMomenutm().Mag() );
}

void CompositeParticle::setMomentum(const TVector3& singleP){
    if(particles_->size() != 3){
        std::cerr << "Error: number of particles: " << particles_->size() << " different from 2.\nIt is impossible to simulate a 2 body decay!" << std::endl;
    }else{
        TVector3 singleK = this->totalMomenutm - singleP;
        if( sqrt( (*particles_)[1].mass()*(*particles_)[1].mass() + singleP.Mag()*singleP.Mag() ) + sqrt( (*particles_)[2].mass()*(*particles_)[2].mass() + singleK.Mag()*singleK.Mag() ) ==  (*particles_)[2].energy()){
            (*particles_)[1].setMomentum(singleP);
            (*particles_)[2].setMomentum(singleK);
        }
    }
}