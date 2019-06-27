#include <glut.h>
#include <ctime>
#include "sphere.h"
#include "getBMP.h"

//============================================
GLfloat light_color[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };

float * pos;

// Iluminacion Focal
float spot_dir[] = {0.0, 1.0, 0.0};
float spot_cutoff = 30;
float spot_exponent = 1.0;

float rot_angle_y = 0.0;
float rot_angle_x = 0.0;

//Vector de esferas
TSphere** sphere = NULL;
GLint NUMSPHERES = 1;
//radio de la esfera
GLfloat SPHERE_RADIOUS = 0.5;

//static unsigned int texture[1];

void addSphere() 
{
	TSphere** temp =new TSphere*[NUMSPHERES];
	//
	for (int i = 0; i < NUMSPHERES; i++){
		temp[i] = sphere[i];
	}
	//insert al final
	temp[NUMSPHERES] = new TSphere(5, 0.1 + (rand() % 10) / 20);
	NUMSPHERES++;
	sphere = temp;
	temp = nullptr;
}

void initgl(int numSpheres) {
	NUMSPHERES = numSpheres;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//=ILUMINATION:LIGHT========================================
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color); //diffuse
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color); //specular
	glEnable(GL_LIGHT0);
	//=ILUMINATION:LIGHT========================================

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 100.0);
	// Proyección perspectiva. El ángulo de visualización es de 60
	//grados, la razón ancho/alto es 1 (son inguales), la distancia
	//mínima es z=1.0, y la distancia máxima es z=100.0
	
	//sphere = new TSphere(5, 0.3);
	sphere = new TSphere*[numSpheres];
	for (int i = 0; i < numSpheres; i++){
		sphere[i] = new TSphere(5, 0.1 + (rand() % 10) / 20.0);
	}
	
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(3, 3, 14, 0, 0, 0, 0, 1, 0);
	//=ILUMINATION:LIGHT========================================
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//=ILUMINATION:LIGHT========================================

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//=ILUMINATION:LIGHT========================================
	glDisable(GL_LIGHTING); //Para dibujar el box 
	
	//=ILUMINATION:LIGHT========================================
	//glRotatef(30.0, 0., 0.0, 1.0);
	//glRotatef(rot_angle_y, 0., 0.0, 1.0);
	//**** continuar


	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(10); //Draw the box

	//=ILUMINATION:LIGHT========================================
	glEnable(GL_LIGHTING); //Para dibujar el box 
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//=ILUMINATION:LIGHT========================================

	for (int i = 0; i < NUMSPHERES; i++){
		glPushMatrix();
		//glColor3f(0.0, 0.0, 1.0);
		//=ILUMINATION:LIGHT========================================
		glColor4fv(sphere[i]->getColor());
		//=ILUMINATION:LIGHT========================================

		pos = sphere[i]->getPosv();
		glTranslatef(pos[0], pos[1], pos[2]);
		glutSolidSphere(SPHERE_RADIOUS, 10, 10);
		glPopMatrix();
		sphere[i]->test();
	}

	//=ILUMINATION:LIGHT========================================
	glDisable(GL_COLOR_MATERIAL);
	//=ILUMINATION:LIGHT========================================
	//glFlush();
	glutSwapBuffers();
}

void idle(void) {
	//sphere->test();
	Sleep(33);
	glutPostRedisplay();
}

/* Program entry point */

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: 
			exit(0); 
			break;
		case '+':
			SPHERE_RADIOUS += 0.1f;
			if (SPHERE_RADIOUS > 1.0) SPHERE_RADIOUS = 1.0;
			glutPostRedisplay();
			break;
		case '-':
			SPHERE_RADIOUS -= 0.1f;
			if (SPHERE_RADIOUS < 0.1) SPHERE_RADIOUS = 0.1f;
			glutPostRedisplay();
			break;
		case 'a':
		case 'A':
			addSphere();
			glutPostRedisplay();
			break;
		default:
			break;
	}
}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);//////////////////////////////////////
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH)-600)/2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 500) / 2
	);
	
	glutCreateWindow("Bouncing Ball");
	initgl(5);  /// 5 spheres
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}