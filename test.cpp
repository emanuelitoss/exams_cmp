#include "Particle.h"
#include "CompositeParticle.h"
#include <iostream>
using namespace std;

int main(){

    // testing composite pattern for Particle class... This is a terrible coding: please don't judje me, it's just a test :')

    Particle* proton = new Particle(0123, "Proton", 938.4, 1, 69., 0, 0);
    Particle* electron = new Particle(4567, "Electron", 0.511, -1, 6900., 0, 0);
    Particle* muon = new Particle(8910, "Muon", 105.66, -1, 680., 0, 0);
    Particle* pion = new Particle(1112, "Pion", 140.0, 0, 400., 0, 0);
    
    CompositeParticle* composition1 = new CompositeParticle("Atom");
    CompositeParticle* composition2 = new CompositeParticle("CosmicRay");

    composition1->add(*proton);
    composition1->add(*electron);

    composition2->add(*pion);
    composition2->print();
    composition2->add(*muon);
    composition2->print();

    cout << "Composition 2 energy: " << composition2->energy() << " and momentum" << composition2->totalMomenutm().Mag() << endl;

    composition2->Add(*composition1);

    cout << "Number of particles in " << composition2->name() << " is:" << composition2->NumberOfParticles() << endl;

    composition2->print();

    delete composition1;
    delete composition2;
    delete pion;
    delete muon;
    delete electron;

    return(EXIT_SUCCESS);
}