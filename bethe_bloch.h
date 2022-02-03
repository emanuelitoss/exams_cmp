#ifndef bethe_bloch_h
#define bethe_bloch_h

#include <string>
#include <vector>

class Particle{

    public:
    
    // CONSTRUCTORS
    Particle();
    // mass and charge
    Particle(const std::string&, const double&, const int&);
    // 3 momenutm
    Particle(const std::string&, const double&, const double&, const double&);
    // all the quantities
    Particle(const std::string&, const double&, const int&, const double&, const double&, const double&);

    // DESTRUCTOR
    ~Particle();

    // SETTERS
    void setMass(const double&);
    void setCharge(const int&);
    void setPx(const double&);
    void setPy(const double&);
    void setPz(const double&);
    void set3P(const double&, const double&, const double&);

    // GETTERS
    const double Mass() const;
    const int Charge() const;
    const double Px() const;
    const double Py() const;
    const double Pz() const;
    const std::string Name() const;

    // UTILITY METHODS
    const double P() const;
    const double Energy() const;
    const double beta() const;
    const double gamma() const;
    const double betagamma() const;

    private:

    std::string name_;
    double mass_;   // GeV
    int charge_;    // in terms of e
    double px_;     // GeV
    double py_;     // GeV
    double pz_;     // GeV
};

class Material{

    public:

    // CONSTRUCTORS >> I should build a lot of constructors... but it will take a lot of time and energies.
    Material();
    Material(const double&, const double&, const int&, const double&);

    // DESTRUCTOR
    ~Material();

    // SETTERS
    void setDensity(const double&);
    void setAtomicMass(const double&);
    void setCharge(const int&);
    void setIonizationEnergy(const double&);

    // GETTERS
    const double& Density() const;
    const double& AtomicMass() const;
    const int& Charge() const;
    const double& IonizationEnergy() const;

    // UTILITY METHODS
    double dEdx(const Particle&, const double&) const;
    std::pair<double,double> BraggPeak(Particle&, std::vector< std::pair<double,double> >, const double&, const double&, const double&) const;

    private:

    double density_;            // g/cm^3
    double atomic_mass_;        // g
    int charge_;                //in terms of e
    double ionization_energy_;  //in eV

};

std::ostream& operator<<(std::ostream&, const Particle&);

#endif