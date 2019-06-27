#pragma once

/////////////////////////////////////////////////////////
// Archivo l-sphere.h
/////////////////////////////////////////////////////////
#ifndef l_sphere_h
#define l_sphere_h
#include <stdlib.h>
#include <ctime>
#include <math.h>

int pass = 0;

//typedef 
class TSphere {
private:
	float maxpos; //posic. max.
	
	float pos[3];   //posicion
	float dir[3];   //direccion
	
	float color[3]; //color  0 1 2
	
	float speed;  //velocidad
public:
	TSphere(float maxpos, float speed);
	void test();
	void modifySpeed(float inc);
	float * getPosv();
	float * getColor();
};

// TSphere;


TSphere::TSphere(float maxpos, float speed) {
	this->maxpos = maxpos;
	if (!pass) {
//		srand(time(NULL));
		srand(time_t(NULL));
		pass = 1;
	}

	pos[0] = (rand() % (int)maxpos) - maxpos / 2.0f;
	pos[1] = (rand() % (int)maxpos) - maxpos / 2.0f;
	pos[2] = (rand() % (int)maxpos) - maxpos / 2.0f;
	
	dir[0] = (float)rand();
	dir[1] = (float)rand();
	dir[2] = (float)rand();

	color[0] = (rand() % 1001) / 1000.0f;
	color[1] = (rand() % 1001) / 1000.0f;
	color[2] = (rand() % 1001) / 1000.0f;

	float dirmod = sqrt(
		dir[0] * dir[0] +
		dir[1] * dir[1] +
		dir[2] * dir[2]
	)*1.0f;

	dir[0] /= dirmod;
	dir[1] /= dirmod;
	dir[2] /= dirmod;
	dir[0] *= speed;
	dir[1] *= speed;
	dir[2] *= speed;
}

void TSphere::test() {
	((pos[0] < -maxpos) || (pos[0] > maxpos)) ? dir[0] *= -1 : 0;
	((pos[1] < -maxpos) || (pos[1] > maxpos)) ? dir[1] *= -1 : 0;
	((pos[2] < -maxpos) || (pos[2] > maxpos)) ? dir[2] *= -1 : 0;
	pos[0] += dir[0];
	pos[1] += dir[1];
	pos[2] += dir[2];
}

void TSphere::modifySpeed(float inc) {
	float factor = (speed + inc) / speed;
	speed += inc;
	dir[0] *= factor;
	dir[1] *= factor;
	dir[2] *= factor;
}

float* TSphere::getPosv() { return pos; }
float* TSphere::getColor() { return color; }


#endif



