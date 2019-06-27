#pragma once
#include <vector>
#include <glut.h>
#include <math.h>


#include "particle.h"

class particle_system{
	vector<particle> particles;
	vec3d gravity_point;

public:
	//construct system given n number of particles
	particle_system(int);
	
	//Function to advance state of particle system by time t in ms
	void advance(float);

	//Function to set gravity point
	void set_gravity(vec3d = vec3d(0, 0, 0));

	//Function to add particles
	bool addParticles(int);

	//Function to delete particles
	bool deleteParticles(int);

	//Function to draw particles
	void draw();

	~particle_system(void);
};

//=======================================================================
//CTOR
particle_system::particle_system(int n){
	if (n > MAX_PARTICLES)	n = MAX_PARTICLES;
	for (int i = 0; i < n; i++)	{
		particle temp;
		//cout << temp.toString() << endl;
		particles.push_back(temp);
	}
}
//DTOR
particle_system::~particle_system(void){
}


//Function to advance state of particle system by time t in ms
void particle_system::advance(float time){
	vector<particle>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++){
		vec3d force = vec3d(
			(gravity_point - it->get_pos()).unit(), 
			FORCE_MAG
		);
		it->advance(time, force);
	}
}

//Function to set gravity point
void particle_system::set_gravity(vec3d gravity) {
	gravity_point = gravity;
}

//Function to add particles
bool particle_system::addParticles(int num){
	int i;
	for (i = 0; i < num && particles.size() < MAX_PARTICLES; i++){
		particle p;
		//cout << p.toString() << endl;
		particles.push_back(p);
	}
	return (i >= num);
}

//Function to delete particles(least is 0)
bool particle_system::deleteParticles(int num){
	int i;
	for (i = 0; i < num && particles.size() > 0; i++){
		particles.pop_back();
	}
	return (i >= num);
}

//Function to draw a particle
void particle_system::draw()
{
	vector<particle>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++) {
		vec3d pos = it->get_pos();
		float k = (gravity_point - pos).mag() / (1.5*LENGTH);
		//---------------------------
		//        R  G B   A
		glColor4f(1, k, 0, 1);
		glBegin(GL_POINTS);
			glVertex3f(pos.x, pos.y, pos.z);
		glEnd();
	}
}


