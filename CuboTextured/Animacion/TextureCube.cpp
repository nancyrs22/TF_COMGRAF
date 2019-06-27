#include<iostream>
#include <glut.h>
#include <ctime>
#include "getBMP.h"

using namespace std;

GLfloat xrot;
GLfloat yrot;
GLfloat zrot;

GLint sleetTime = 5;

//Array of textures ID's
static unsigned int texture[1];

//Load image(BMP) and convert to texture

int LoadTextures() {
	int textureLoad = FALSE;
	imageFile* image[1]; //create a storage in memory to image.
	if (image[0] = getBMP("../Textures/UPC-NATURAL.bmp")) {
		textureLoad = TRUE; //image file can be readed
		glGenTextures(1, &texture[0]);

		//Gen the texture using the image (bitmap)
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		//
		glTexImage2D(
			GL_TEXTURE_2D, //target
			0, //level-of-detail: use 0 if you don't want to use MIP-MAP
			GL_RGBA, //internal format
			image[0]->width,//image width
			image[0]->height,//image height
			0, //0 no border, 1 with border, border are power of 2 + 2
			GL_RGBA,//format of image data
			GL_UNSIGNED_BYTE, //type: data type of image data
			image[0]->data//pointer to image
		);

		//---Parameter Filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	return(textureLoad); //Error to read image file

}


//======================================================================

int init() {
	if (!LoadTextures()) {
		return FALSE;
	}
	//Enable Texture Mapping
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH); //Active Smooth Shading
	glClearColor(.0f, .0f, .0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);//Depth Buffer TesT
	glDepthFunc(GL_LEQUAL);//Type of Depth Testing 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	return TRUE;
}

void reshape(int width, int height) {
	if (height == 0) height = 1;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(
		45.0f,
		(GLfloat)width/(GLfloat)height,
		0.1f,
		100.0f
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	//---
	//Cube Faces

	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	//---
	xrot += 0.3f;
	yrot += 0.2f;
	zrot += 0.4f;
	//glFlush();
	glutSwapBuffers();
}

void idle(void) {
	Sleep(sleetTime);
	glutPostRedisplay();
}

/* Program entry point */

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		case 27: 
			exit(0); 
			break;
		case '+':
			if (sleetTime < 30) sleetTime++;
			break;
		case '-':
			if (sleetTime > 0) sleetTime--;
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
	
	glutCreateWindow("Cube Textering...");
	if(!init()){
		cout<<"Error in texturing..."<<endl;  /// 5 spheres
		exit(0);
	}
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}