#pragma once

float rand_float(){
	float value = rand() / float(RAND_MAX);
	return value;
}