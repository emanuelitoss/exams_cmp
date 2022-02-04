#include "bethe_bloch.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define ELECTRON_RADIUS 2.8179403267E-15 // Meters
#define ELECTRON_MASS 0.51099895000 // MeV/c/c
#define AVOGADRO 6.022E23 // adimensional
#define K_BETHE_BLOCH 0.307075 // Mev*cm^2/mol 
#define ELEMENTARY_CHARGE 1.602E-19 // Coulomb

#define EPS 1E-4
/**************************************** PARTICLE CLASS ****************************************/

// Particle constructor #0
Particle::Particle(){
    mass_ = 0;
    charge_ = 0;
    px_ = 0;
    py_ = 0;
    pz_ = 0;
}

// Particle constructor #1
Particle::Particle(const std::string& name, const double& mass, const int& charge){
    name_ = name;
    mass_ = mass;
    charge_ = charge;
    px_ = 0;
    py_ = 0;
    pz_ = 0;
}

// Particle constructor #2
Particle::Particle(const std::string& name, const double& px, const double& py, const double& pz){
    name_ = name;
    mass_ = 0;
    charge_ = 0;
    px_ = px;
    py_ = py;
    pz_ = pz;
}

// Particle constructor #3
Particle::Particle(const std::string& name, const double& mass, const int& charge, const double& px, const double& py, const double& pz){
    name_ = name;
    mass_ = mass;
    charge_ = charge;
    px_ = px;
    py_ = py;
    pz_ = pz;
}

// Particle destructor
Particle::~Particle(){}

// Particle setters
void Particle::setMass(const double& mass){ mass_ = mass; }
void Particle::setCharge(const int& charge){ charge_ = charge; }
void Particle::setPx(const double& momentum){ px_ = momentum; }
void Particle::setPy(const double& momentum){ py_ = momentum; }
void Particle::setPz(const double& momentum){ pz_ = momentum; }
void Particle::set3P(const double& x, const double& y, const double& z){
    px_ = x;
    py_ = y;
    pz_ = z;
}

// Particle getters
const double Particle::Mass() const{ return mass_; }
const int Particle::Charge() const{ return charge_; }
const double Particle::Px() const{ return px_; }
const double Particle::Py() const{ return py_; }
const double Particle::Pz() const{ return pz_; }
const std::string Particle::Name() const{ return name_; }

// Particle quantities (getters/utility)
const double Particle::P() const{ return sqrt(px_*px_ + py_*py_ + pz_*pz_); }
const double Particle::Energy() const{ return sqrt( this->P()*this->P() + mass_*mass_*1E6 ); }
const double Particle::beta() const{ return this->P()/this->Energy(); }
const double Particle::gamma() const{ return this->Energy()/mass_/1E3; }
const double Particle::betagamma() const{ return this->beta()*this->gamma(); }

std::ostream& operator<<(std::ostream& output, const Particle& particle){
    output << "Particle: " << particle.Name() <<"\tmass: " << 1000*particle.Mass() << " Mev\tcharge: " << particle.Charge() << "e";
    return output;
}

/**************************************** MATERIAL CLASS ****************************************/

// Material constructor #0
Material::Material(){
    density_ = 0;
    atomic_mass_ = 0;
    charge_ = 0;
    ionization_energy_ = 0;
    std::cout << "Creating an empty material" << std::endl;
}

// Material constructor #1
Material::Material(const double& rho, const double& mu, const int& q, const double& IE){
    density_ = rho;
    atomic_mass_ = mu;
    charge_ = q;
    ionization_energy_ = IE;
    std::cout << "Creating a material with these features" << std::endl;
    std::cout << "\tDensity:\t" << rho << " g/cm^3" << std::endl;
    std::cout << "\tAtomic Mass:\t" << mu << " g/mol" << std::endl;
    std::cout << "\tElectric charge:\t" << q << " *e" << std::endl;
    std::cout << "\tMean ionization energy:\t" << IE << " eV" << std::endl;

}

// Material destructor
Material::~Material(){}


// Metrial setters
void Material::setDensity(const double& rho){
    density_ = rho;
}
void Material::setAtomicMass(const double& mu){
    atomic_mass_ = mu;
}
void Material::setCharge(const int& charge){
    charge_ = charge;
}
void Material::setIonizationEnergy(const double& IE){
    ionization_energy_ = IE;
}

// Material getters
const double& Material::Density() const { return density_; }
const double& Material::AtomicMass() const { return atomic_mass_; }
const int& Material::Charge() const { return charge_; }
const double& Material::IonizationEnergy() const { return ionization_energy_; }

// Bethe bloch formula -> from Particle Data Group
// https://pdg.lbl.gov/2018/reviews/rpp2018-rev-passage-particles-matter.pdf
double Material::dEdx(const Particle& particle, const double& kinetic) const{
    // coefficient of Bethe Bloch formula
    double coefficient = this->density_*K_BETHE_BLOCH*particle.Charge()*particle.Charge()*this->charge_/this->atomic_mass_/particle.beta()/particle.beta();
    // inside the log
    double inside_log = 2*ELECTRON_MASS*particle.betagamma()*particle.betagamma()*kinetic/ionization_energy_/ionization_energy_;
    // Bethe Bloch formula in Mev/cm
    return fabs(coefficient*(0.5*log(inside_log) - particle.beta()*particle.beta()));
}

std::pair<double,double> Material::BraggPeak(Particle& particle, std::vector < std::pair <double,double> > data, const double& kineticMaximum, const double& length, const double& dx) const {

    using namespace std;
    
    double puntual_dEdx = 0;
    double energy_losses[(int)(length/dx)];
    pair<double,double> bragg_peak = make_pair(0.,0.);

    for (int step = 0; step < (int)(length/dx); step++){

        puntual_dEdx = this->dEdx(particle, kineticMaximum);
        energy_losses[step] = step*dx*puntual_dEdx;
        data.push_back(make_pair( step*dx, puntual_dEdx ));

        if(fabs(( particle.Energy() - puntual_dEdx*dx )*( particle.Energy() - puntual_dEdx*dx ) - particle.Mass()*particle.Mass()*1E6) < EPS){
            particle.setPx( sqrt( ( particle.Energy() - puntual_dEdx*dx )*( particle.Energy() - puntual_dEdx*dx ) - particle.Mass()*particle.Mass()*1E6) );
        }else{
            cout << "La particella " << particle.Name() << " si è fermata!" << endl;
            break;
        }

        if(bragg_peak.second <= puntual_dEdx){
            bragg_peak.second = puntual_dEdx;
            bragg_peak.first = step*dx;
        }

    }

    cout << "\n" << particle << "\n\tBragg peak at " << bragg_peak.first << " (cm) with value: " << bragg_peak.second << " (MeV/cm)\n" << endl;

    return bragg_peak;
    
}