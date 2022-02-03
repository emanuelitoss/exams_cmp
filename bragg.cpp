#include "bethe_bloch.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

// PARTICLES
#define PROTON_MASS 938.27208816 // MeV
#define ALPHA_MASS 3727.379378 // MeV
#define ELECTRON_MASS 0.51099895000 // MeV
#define MOMENTUM 7. // MeV >> initial momentum of incoming particle

// MATERIAL
#define WATER_DENSITY 1. // g/cm^3
#define WATER_ATOMIC_MASS 18. // g/mol
#define WATER_Z 8 // charge in terms of elementary charge e
#define WATER_IONIZATION 80. // eV >> minum of ionization energy

using namespace std;

int main(){

// MATERIAL DECLARATION

    Material water(WATER_DENSITY, WATER_ATOMIC_MASS, (int)WATER_Z, WATER_IONIZATION);
    double Maximum_kinetic_energy = 78.; // MeV

// OUTPUT FILE

    ofstream outputFile;
    outputFile.open("dataBragg.txt");
    if(!outputFile.is_open()){
        cerr << "Cannot open output file!" << endl;
        return(EXIT_FAILURE);
    }

    outputFile << "#x (cm)\tProton\tAlpha\tElectron\n" << endl;

//LENGTH & INTEGRATION STEP

    // length
    double length = 0;
    cout << "Inserire la lunghezza massima (in cm): ";
    cin >> length; // cm
    cout << endl;

    // integration step
    double dx = 0;
    cout << "Inserire lo step di integrazione (in cm): ";
    cin >> dx; // cm
    cout << "\n" << endl;

// DATA STORAGE

    // vector of data
    vector< pair <double,double> > data;
    // general datum
    pair<double,double> point = make_pair(0.,0.);
    // special datum
    pair<double,double> bragg_peak;

// PARTICLES DEFINITION

    // vector containing the incoming particles
    vector< pair <Particle, vector< pair <double,double> > > > particles;

    // inserting particles in vector
    particles.push_back(make_pair(Particle("PROTON", PROTON_MASS/1000, 1, MOMENTUM, 0, 0), data));
    particles.push_back(make_pair(Particle("ALPHA PARTICLE", ALPHA_MASS/1000, 2, MOMENTUM, 0, 0), data));
    particles.push_back(make_pair(Particle("ELECTRON", ELECTRON_MASS/1000, -1, MOMENTUM, 0, 0), data));

    // useful variables in the loop
    double energy_loss, puntual_dEdx;

    // loop over different particles
    for(vector< pair <Particle, vector< pair <double,double> > > >::iterator p = particles.begin(); p!=particles.end(); ++p){

        // finding Bragg's peak for a particle and storage its position and value in a pair (x, dEdX)
        bragg_peak = water.BraggPeak(p->first, p->second, Maximum_kinetic_energy, length, dx);
        
    }

    for (int i = 0; i < (int)length/dx; i++){
        outputFile << i*dx << "\t" << particles[0].second[i].second << "\t" << particles[1].second[i].second << "\t" << particles[2].second[i].second << endl;
        cout << i*dx << "\t" << particles[0].second[i].second << "\t" << particles[1].second[i].second << "\t" << particles[2].second[i].second << endl;
    }
    
    outputFile.close();

    return(EXIT_SUCCESS);
}