#include <iostream>

class Particle{
    public:

    // constructors
    Particle();
    Particle(const double&);
    Particle(const double&, const double&, const double&);
    Particle(const double&, const double&, const double&, const double&);

    // destructor
    ~Particle();

    // setters
    void setPx(const double&);
    void setPy(const double&);
    void setPz(const double&);
    void setMass(const double&);

    // getters
    double Px() const;
    double Py() const;
    double Pz() const;
    double Mass() const;
    double P() const;
    double Theta() const;
    double Phi() const;
    double Energy() const;

    // overloaded operators
    Particle operator+(const Particle&) const;
    Particle operator<<(const Particle&) const;

    private:
    double mass_;
    double px_;
    double pz_;
    double py_;
};

class CompositeParticle{
    public:
    
    
    private:
    double mass_;
    double momentum_;
};