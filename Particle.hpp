/* Particle_hpp */

#ifndef Particle_hpp
#define Particle_hpp

class Particle{
private:
    float out_radius;
    float velocity;
    float* color;
    float* location;
    float randomLoc;
    float t;
    
public:
    Particle();
    Particle(float);
    ~Particle();
    float* get_location(float);
    float* get_color();
    float get_radius();
    float get_time();
};
#endif
