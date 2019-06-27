#pragma once

#include "vec3d.h"
#include "constants.h"
#include "cloud.h"
#include<string>

class particle{	
	float mass;  // entre 2 y 8
	vec3d velocity;
	vec3d position;

public:
	particle(
		/*mass*/
		float = rand() % (MAX_MASS-MIN_MASS) + MIN_MASS,
		/*velocity*/
		vec3d = vec3d(
			vec3d(
				rand_float(), //x
				rand_float(), //y
				rand_float()  //z
			), /*mag initial between 10 y 100*/
			MIN_INIT_VELOCITY + rand() % (MAX_INIT_VELOCITY - MIN_INIT_VELOCITY)
		),
		/*position*/
		vec3d = vec3d(
			(1-2*rand_float())*LENGTH, 
			(1-2*rand_float())*LENGTH, 
			(1-2*rand_float())*LENGTH
		)
		//
		
	);
	~particle(void);

	//Function to advance state of particle by time t in ms and force in given direction
	void advance(float, vec3d = vec3d(0.0,0.0,0.0));

	//Function to get position
	vec3d get_pos();

	//Function to draw a particle
	//void draw(int);

	string toString() {
		return
			"mass: "      + to_string(mass) +
			"velocity: "  + velocity.toString() +
			"position: "  + position.toString() +"\n";
	}

};


//========================================================================

particle::particle(float _mass, vec3d _velocity, vec3d _position) 
	: mass(_mass), 
	velocity(_velocity), 
	position(_position) 
{}




//function to advance state by time t in ms
void particle::advance(float t, vec3d force){
	//calculating acceleration
	vec3d acc = force / mass;

	//calculating velocity
	velocity = velocity + acc*(t / 1000.0);

	if (velocity.mag() >= MAX_VELOCITY)
		velocity = vec3d(velocity.unit(), MAX_VELOCITY);

	//changing position
	position = position + velocity*(t / 1000.0);

	if (position.x <= -LENGTH)		position.x = LENGTH;
	else if (position.x >= LENGTH)	position.x = -LENGTH;

	if (position.y <= -LENGTH)		position.y = LENGTH;
	else if (position.y >= LENGTH)	position.y = -LENGTH;

	if (position.z <= -LENGTH)		position.z = LENGTH;
	else if (position.z >= LENGTH)	position.z = -LENGTH;
}


particle::~particle(void) {
}

//Function to get position
vec3d particle::get_pos(){
	return position;
}

/*/Function to draw a particle
void particle :: draw(int trail_size)
{
vec3d temp = (force - position).unit();
if(temp.x < 0)
temp.x *= -1;
if(temp.y < 0)
temp.y *= -1;
if(temp.z < 0)
temp.z *= -1;

}*/