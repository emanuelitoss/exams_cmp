#include <iostream>

class Particle{
    public:

    // constructors
    Particle();
    Particle(const double&);
    Particle(const double&, const double&);

    // destructor
    ~Particle();

    // setters
    void setP(const double&);
    void setMass(const double&);

    // getters
    double Momentum() const;
    double Energy() const;
    double Mass() const;

    // overloaded operators
    Particle operator+(const Particle&) const;

    private:
    double mass_;
    double momentum_;
};

class CompositeParticle{
    public:

    // constructors
    CompositeParticle();
    CompositeParticle(const double&);
    CompositeParticle(const double&, const double&);
    CompositeParticle(const Particle&);

    // destructor
    ~CompositeParticle();

    // getters
    double Momentum() const;
    double Energy() const;

    // methods
    void Add(const Particle&);
    void Remove(const Particle&);

    // overloaded operators
    CompositeParticle operator<<(const Particle&);
    
    private:
    double mass_;
    double momentum_;
};