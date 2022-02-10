#ifndef Particle_h
#define Particle_h

#include <string>
#include "TVector3.h"
using namespace std;

class Particle{

private:
    // data members
    int id_;
    string name_;
    double mass_;
    int charge_;
    TVector3 momentum_;

public:

    // constructors & destructor(s)
    Particle(const int& id, const string& name, const double& mass);
    Particle(const int& id, const string& name, const double& mass, const int& charge);
    Particle(const int& id, const string& name, const double& mass, const double& px, const double& py, const double& pz);
    Particle(const int& id, const string& name, const double& mass, const int& charge, const double& px, const double& py, const double& pz);
    // destructor
    ~Particle();

    // getters
    const int& id() const;
    const string& name() const;
    const double& mass() const;
    const int& charge() const;
    const TVector3& momentum() const;
    double energy() const;

    // setters
    void setId(const int& id);
    void setName(const string& name);
    void setMass(const double& mass);
    void setCharge(const int& q);
    void setMomentum(const TVector3& momentum);

    // untility methods
    void print() const;

};


#endif