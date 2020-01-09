/*
 This file contains a constructor and helper functions that
 help to generate particle information.
 Author: George Baldini and Eddie Garcia-Alamilla
 Date: September 18, 2018
 */

#include "Particle.hpp"

#include <iostream>
#include <math.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <stdlib.h>
#  include <GLUT/glut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib")
#endif

/* A constructor for a single particle that initializes the radius,
 * velocity, color, location, and time.
 
 * Param(s): void.
 *
 * Returns: void.
 */
Particle::Particle() {
    out_radius = ((float)(rand() % 3) + 1);
    velocity = rand() % 80;
    
    color = new float[3];
    color[0] = ((float)(rand() % 10) + 1) * .1;
    color[1] = ((float)(rand() % 10) + 1) * .1;
    color[2] = ((float)(rand() % 10) + 1) * .1;
    
    randomLoc = (float)(rand()%65) - (rand()%65);

    location = new float[3];
    location[0] = randomLoc;
    location[1] = 0;
    location[2] = -100;

    t = 0;
}

/* A deconstructor that deletes all pointer instance variables for
 * that particular particle.
 
 * Param(s): void.
 *
 * Returns: void.
 */
Particle::~Particle(){
    delete[] color;
    delete[] location;
}
/* A getter function that updates the y-location of a particle given the time t
 * and returns a pointer to the location of that particle.
 
 * Param(s): float t - the current time of that particle.
 *
 * Returns: location - a pointer to the location of the particle.
 */
float* Particle::get_location(float t){

    float particle_location = (-16 * (pow(t, 2))) + (velocity * t);

    location[1] = particle_location;
    
    return location;
}

/* A getter function that retrieves the color of a given particle.
 
 * Param(s): void.
 *
 * Returns: color - a pointer to the color of the particle.
 */
float* Particle::get_color() {
    return color;
}

/* A getter function that retrieves the radius of a given particle.
 
 * Param(s): void.
 *
 * Returns: radius - a float representing the radius of a particle.
 */
float Particle::get_radius() {
    return out_radius;
}

/* A getter function that retrieves the time of a particle. If location is
 * <= -65, then time is reset to 0.
 
 * Param(s): void.
 *
 * Returns:  float t - a float representing the time of the particle.
 */
float Particle::get_time() {
    t += .01;
    
    if (location[1] < -65) {
        t = 0;
    }
    return t;
}
