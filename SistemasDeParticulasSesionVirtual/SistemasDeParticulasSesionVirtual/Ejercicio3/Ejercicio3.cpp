#pragma comment(lib, "SOIL.lib")

#include <windows.h>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <glut.h>

#include "particle_system.h"
#include "SOIL.h"
#include "constants.h"
#include "cloud.h"

using namespace std;

particle_system p(NUMBER_OF_PARTICLES);

float  win_width = 640;
float  win_height = 480;

void init(){
	// Make big points and wide lines
	glPointSize(5);  //initial point 3

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Draws the 3D scene
void display()
{
	glLoadIdentity();

	//Draw particles
	glPushMatrix();
		p.advance(DELTA);
		p.draw();
	glPopMatrix();

	//Draw overlaying quad for trail
	glColor4f(0, 0, 0, 0.1);
	glBegin(GL_QUADS);
	glVertex3f(-LENGTH, -LENGTH, 100);
	glVertex3f(LENGTH, -LENGTH, 100);
	glVertex3f(LENGTH, LENGTH, 100);
	glVertex3f(-LENGTH, LENGTH, 100);
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();
}


void reshape(int w, int h){
	//setup windows width and height
	win_width  = (w == 0) ? 1 : w;
	win_height = (h == 0) ? 1 : h;

	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, win_width, win_height);

	//Switch to setting the camera perspective
	glMatrixMode(GL_PROJECTION);

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	glOrtho(-LENGTH, LENGTH, -LENGTH, LENGTH, -LENGTH, LENGTH);

	glMatrixMode(GL_MODELVIEW);
}




//Called when a key is pressed
void keyInput(unsigned char key, int x, int y) {
	switch (key) {
	case '+':
		p.addParticles(10);
		break;
	case '-':
		p.deleteParticles(10);
		break;
	case 's':
	case 'S':
		SOIL_save_screenshot("awesome.bmp", SOIL_SAVE_TYPE_BMP, 0, 0, 1024, 768);
		break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

//Handle mouse movement
void mouseMotion(int x, int y) {
	float ww_ratio = float(x) / win_width;
	float wh_ratio = float(y) / win_height;

	p.set_gravity(vec3d((2 * ww_ratio - 1)*LENGTH, (1 - 2 * wh_ratio)*LENGTH, 0));
}


void msg() {
	cout << "Initial Particle 3 maximum" << endl;
	cout << "+ add particles" << endl;
	cout << " - delete particles" << endl;
	cout << " s/S save screenshot" << endl;
}


int main(int argc, char** argv){
	msg();
	srand(time(0));
	p.set_gravity();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width, win_height);

	glutCreateWindow("Particle System");
	init();

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutKeyboardFunc(keyInput);
	glutPassiveMotionFunc(mouseMotion);
	
	glutFullScreen();

	glutMainLoop();
	return 0; 
}