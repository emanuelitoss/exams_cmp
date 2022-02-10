#include "Particle.h"

#ifndef CompositeParticle_h
#define CompositeParticle_h

#include <vector>

using namespace std;

class CompositeParticle{

private:
    vector <Particle>* particles_ = new vector <Particle>;
    string name_;
    
public:
    // costructor(s) and destuctor(s)
    CompositeParticle();
    CompositeParticle(const std::string& name);
    ~CompositeParticle();
    // setters
    void add(const Particle& particle);
    void Add(const CompositeParticle& composition);
    void setName(const std::string& name);
    void clear();
    // accessors
    const string& name() const;
    Particle& element(const int& index) const;
    vector <Particle>* particleVector() const;
    // member functions
    int NumberOfParticles() const;
    void print() const;
    void printParticles() const;
    double energy() const;
    TVector3 totalMomenutm() const;
    double invariantMass() const;
    void setMomentum() const;

};

#endif

// NEED: total momentum, invariant mass of the system, ... other mechanical quantities