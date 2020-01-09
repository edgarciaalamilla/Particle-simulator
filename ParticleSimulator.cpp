/*
 This file draws a particle simulator.
 Author: George Baldini and Eddie Garcia-Alamilla
 Date: September 18, 2018
 Time spent: 12 hours
 */

#include "Particle.hpp"
#include <vector>

#include <cstdlib>
#include <cmath>
#include <iostream>

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

#include <math.h>

using namespace std;

float win_width = 500;
float win_height = 500;

static long frames = 0; // frames
static float fps = 0; //frames per second

static int numParticles = 250; //initial number of particles that is incremented when fps >= 30

vector<Particle*> particles; //vector array containing particle info
GLUquadricObj* quadratic; //used by gluDisk().

/* This function calculates the frames per second by dividing the
 * total number of frames that have been displayed through drawScene()
 * and divides by the number of seconds that have passed since glutInit()
 * is called in the main() function.
 *
 * Param(s): void.
 *
 * Returns: a float representing the frames per second.
 */
float calculateFPS(void) {
    return (frames / (glutGet(GLUT_ELAPSED_TIME) / 1000.0));
}

/* This function draws numParticles particles to the scene using
 * gluDisk() to represent each individual particle. If the frames
 * per second is greater than or equal to 30, 20 new particles are
 * pushed into the global vector array particles.
 *
 * Param(s): void.
 *
 * Returns: void.
 */
void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    std::cout<<numParticles;
    std::cout<<" ";
    std::cout<<fps;
    std::cout<<"\n";
    
    //Iterate through vector array of particles
    for (int i = 0; i < numParticles; i++) {
        //Update location and get color and radius of particle[i] in vector array
        float* location = particles[i]->get_location(particles[i]->get_time());
        float* color = particles[i]->get_color();
        float radius = particles[i]->get_radius();
        
        //Push particle into the viewing area
        glPushMatrix();
        glTranslatef(location[0], location[1], location[2]);
        glColor4f(color[0], color[1], color[2], .8);
        gluDisk(quadratic, 0, radius, 32, 32);
        glPopMatrix();
    }
    
    //If frames per second is greater than 30, add 20 new particles.
    if (fps >= 30) {
        for (int i = 0; i < 20; i++) {
            particles.push_back(new Particle());
            numParticles++;
        }
    }
    
    //The entire drawScene() function displays a single frame
    frames++;
    
    glFlush();
    
}

/* This function enables particles to be blended and sets the
 * background color to black. setup() sets the quadratic
 * variable that is used by the gluDrawDisk() function in drawScene().
 * Additionally, this function populates the global vector array
 * with 250 particles with random y- locations, sizes, and colors.
 *
 * Param(s): void.
 *
 * Returns: void.
 */
void setup(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);

    for (int i = 0; i < numParticles; i++) {
        particles.push_back(new Particle());
    }
}

/* This function sets up the viewing window that will display the
 * particle simulator.
 *
 * Param(s): int w - the window width in pixels.
 *           int h - the window height in pixels.
 *
 * Returns: void.
 */
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.f, win_width/win_height, .1f, 500.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* This function recalculates the frames per second and
 * redisplays the scene.
 *
 * Param(s): void.
 *
 * Returns: void.
 */
void idle( void ){
    fps = calculateFPS();
    glutPostRedisplay();
}

/* This function makes use of the ~particles() deconstructor.
 * When the escape key is pressed, it will iterate through the
 * vector array and delete the pointer instance variables for
 * each particle.
 *
 * Param(s): unsigned char key - an input key.
 *           int x - I'm not seeing an x in this function
 *                   but I'll keep it in here anyway.
 *           int y - No y either.
 *
 * Returns: void.
 */
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            for (int i = 0; i < numParticles; i++) {
                particles[i]->~Particle();
            }
            exit(0);
            break;
        default:
            break;
    }
    glFlush();
}

/* The main routine. The chef. The program coordinator.
 * It calls every function that is needed to show a bunch of
 * particles on your screen.
 *
 * Param(s): int argc - number of command line arguments.
 *           char **argv - full list of all command line arguments.
 *
 * Returns: 0;
 */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Particle Simulator");
    glutDisplayFunc(drawScene);
    glutIdleFunc(idle);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    setup();
    glutMainLoop();

    return 0;
}
