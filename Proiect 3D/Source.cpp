//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include<gl/freeglut.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <string>
#include "SOIL.h"

#define PI 3.1415927
#define	imageHeight 64
#define	imageWidth 64
#define mijlocY 540;
#define mijlocX 960;

using namespace std;

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 1;;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 1.0f;

GLfloat texpts[2][2][2] = { {{1.0, 1.0}, {1.0, 0.0}},
			{{0.0, 1.0}, {0.0, 0.0}} };
GLubyte image[3 * imageWidth * imageHeight];
GLuint texture1;
GLfloat grade_elice = 45;
POINT p;

float lateralX, lateralY, lateralZ, lAngle;
float yAngle = 0.0f;
bool cursorInvizibil = false;

void lumina(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	// initializari si proprietatile universale
	GLfloat alphaAmb;
	GLfloat alphaDifuz;
	GLfloat difuzLumina[4];
	GLfloat unghiCutOff;

	GLfloat alb[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
	float xs = -2.0, ys = -1.0, zs = 5.0, ts = 1.0;
	ts = 1.0;
	alphaAmb = 0.3;
	alphaDifuz = 0.3;
	difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;
	unghiCutOff = 180;

	// Sursa de lumina
	GLfloat ambientLumina[] = { alphaAmb, alphaAmb, alphaAmb, alphaAmb };

	GLfloat pozitial0[] = { xs, ys, zs, ts };
	GLfloat directieSpot[] = { 0, 0, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLumina);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuzLumina);
	glLightfv(GL_LIGHT0, GL_SPECULAR, alb);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, directieSpot);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, unghiCutOff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 3.0);
};

void LoadTexture(const char* textureName)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image(textureName, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

}

void pozitieCursor() {

	if (GetCursorPos((&p)) && cursorInvizibil) {

		float diffX = p.x - mijlocX;
		float diffY = p.y - mijlocY;

		angle += diffX * 0.0015;

		lx = sin(angle);
		lz = -cos(angle);

		if (yAngle - diffY * 0.0015 >= -1.8 && yAngle - diffY * 0.0015 <= 1.8)
		{
			yAngle -= diffY * 0.0015;
		}

		ly = sin(yAngle);
		SetCursorPos(960, 540);

	}
}

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawTree1()
{

	//culoarea trunchiului
	GLfloat color[] = { 0.403, 0.317, 0.137 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	glColor3f(0.403, 0.317, 0.137);

	// Trunchi
	glTranslatef(0.0f, 2.2f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.3f, 2.0f, 20, 50);

	// culoarea coroanei
	GLfloat color2[] = { 0.180, 0.396, 0.141 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color2);
	glColor3f(0.180, 0.396, 0.141);

	// Coroana Con
	glRotatef(180, 1, 0, 0);
	glutSolidCone(2.0f, 2.0f, 20, 50);

}

void drawTree2()
{

	//culoarea trunchiului
	GLfloat color[] = { 0.403, 0.317, 0.137 };
	glColor3f(0.403, 0.317, 0.137);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);

	// Trunchi
	glTranslatef(0.0f, 2.45f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.3f, 2.0f, 20, 50);

	// culoarea coroanei
	GLfloat color2[] = { 0.180, 0.396, 0.141 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color2);
	glColor3f(0.180, 0.396, 0.141);


	// Coroana sfera
	glutSolidSphere(1.2f, 20, 20);

}

void drawPatrat(float x, float y, float plus)
{
	float h = 0.61;
	glBegin(GL_QUADS);
	GLfloat color[] = { 0.64, 0.25, 0.25 };
	// stanga-jos rosu-slab
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	glColor3f(0.64, 0.25, 0.25);
	glVertex3f(x, h, y);
	glVertex3f(x + plus, h, y);
	glVertex3f(x + plus, h, y + plus);
	glVertex3f(x, h, y + plus);

	//stanga-sus rosu
	GLfloat color2[] = { 0.75, 0.11, 0.1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color2);
	glColor3f(0.75, 0.11, 0.11);
	glVertex3f(x + plus, h, y + plus);
	glVertex3f(x + plus, h, y + plus * 2);
	glVertex3f(x, h, y + plus * 2);
	glVertex3f(x, h, y + plus);

	//dreapta-jos alb
	GLfloat color3[] = { 1, 1, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color3);
	glColor3f(1, 1, 1);
	glVertex3f(x + plus, h, y);
	glVertex3f(x + plus * 2, h, y);
	glVertex3f(x + plus * 2, h, y + plus);
	glVertex3f(x + plus, h, y + plus);

	//dreapta-sus rosu-slab
	GLfloat color4[] = { 0.64, 0.25, 0.25 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color4);
	glColor3f(0.64, 0.25, 0.25);
	glVertex3f(x + plus, h, y + plus);
	glVertex3f(x + plus, h, y + plus * 2);
	glVertex3f(x + plus * 2, h, y + plus * 2);
	glVertex3f(x + plus * 2, h, y + plus);
	glEnd();

}

void drawPatura(float x, float y, float plus, float xx, float yy)
{
	for (int i = 1; i <= xx; i++)
		for (int j = 1; j <= yy; j++)
		{
			drawPatrat(x + i * plus * 2, y + j * plus * 2, plus);
		}
	glPushMatrix();
	glTranslatef((x + xx * plus), 0.71, (y + yy * plus));
	GLfloat color[] = { 0.38, 0.46, 0.35 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	glColor3f(0.38, 0.46, 0.35);
	glutSolidTeapot(0.12);
	glTranslatef(0, -0.04, 0.4);
	glutSolidTeacup(0.12);
	glTranslatef(0.3, 0, 0);
	glutSolidTeacup(0.12);
	glPopMatrix();


}

void moara_de_vant()
{
	GLfloat color[] = { 0.866, 0.749, 0.372 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	glColor3f(0.866, 0.749, 0.372);
	glBegin(GL_QUADS);

	// baza
	glVertex3f(-20, 0.7, -30);
	glVertex3f(-15, 0.7, -30);
	glVertex3f(-15, 0.7, -25);
	glVertex3f(-20, 0.7, -25);

	// partea superioara
	glVertex3f(-19, 10, -29);
	glVertex3f(-16, 10, -29);
	glVertex3f(-16, 10, -26);
	glVertex3f(-19, 10, -26);

	// latura spate
	glVertex3f(-20, 0.7, -30);
	glVertex3f(-15, 0.7, -30);
	glVertex3f(-16, 10, -29);
	glVertex3f(-19, 10, -29);

	//latura stanga
	glVertex3f(-15, 0.7, -30);
	glVertex3f(-15, 0.7, -25);
	glVertex3f(-16, 10, -26);
	glVertex3f(-16, 10, -29);

	//latura fata
	glVertex3f(-15, 0.7, -25);
	glVertex3f(-20, 0.7, -25);
	glVertex3f(-19, 10, -26);
	glVertex3f(-16, 10, -26);

	//latura dreapta
	glVertex3f(-20, 0.7, -25);
	glVertex3f(-20, 0.7, -30);
	glVertex3f(-19, 10, -29);
	glVertex3f(-19, 10, -26);
	glEnd();

	// ACOPERISUL
	GLfloat color2[] = { 0.6, 0.29, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color2);
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);

	glVertex3f(-19, 10, -29);
	glVertex3f(-16, 10, -29);
	glVertex3f(-17.5, 12, -27.5);

	glVertex3f(-16, 10, -29);
	glVertex3f(-16, 10, -26);
	glVertex3f(-17.5, 12, -27.5);

	glVertex3f(-16, 10, -26);
	glVertex3f(-19, 10, -26);
	glVertex3f(-17.5, 12, -27.5);

	glVertex3f(-19, 10, -29);
	glVertex3f(-19, 10, -26);
	glVertex3f(-17.5, 12, -27.5);
	glEnd();

	// USA
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-16.5, 0.7, -25);
	glVertex3f(-18.5, 0.7, -25);
	glVertex3f(-18.5, 3, -25.1);
	glVertex3f(-16.5, 3, -25.1);
	glEnd();


	// SUPORT MOARA
	glColor3f(0.6, 0.29, 0.0);
	glTranslatef(-17.5, 11, -28);
	glutSolidCylinder(0.1, 3, 10, 10);

	// ELICE 1
	glPushMatrix();
	GLfloat color3[] = { 0.7, 0.3, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color3);
	glColor3f(0.7, 0.3, 0.0);
	glRotatef(grade_elice, 0, 0, 1);
	glScalef(4, 0.25, 0.25);
	glTranslatef(0, 0, 11.1);
	glutSolidCube(2);
	glPopMatrix();

	// ELICE 2
	glPushMatrix();
	GLfloat color4[] = { 0.7, 0.3, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color4);
	glColor3f(0.7, 0.3, 0.0);
	glRotatef(grade_elice, 0, 0, 1);
	glScalef(0.25, 4, 0.25);
	glTranslatef(0, 0, 11.1);
	glutSolidCube(2);
	glPopMatrix();

	glPopMatrix();
	glutPostRedisplay();
	grade_elice += 0.4f;

}

void barca()
{
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	LoadTexture("numaipot.png");
	//Spate fata jos de tot
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 0.0f, 0.0f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-51.0f, 0.9f, -0.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-49.0f, 0.9f, -0.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 0.0f, 0.0f);

	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 0.0f, 15.0f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-51.0f, 0.9f, 15.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-49.0f, 0.9f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 0.0f, 15.0f);

	//Laterale jos de tot
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 0.0f, 0.0f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-50.0f, 0.0f, 15.0f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-51.0f, 0.9f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-51.0f, 0.9f, -0.5f);

	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 0.0f, 0.0f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-50.0f, 0.0f, 15.0f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-49.0f, 0.9f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-49.0f, 0.9f, -0.5f);

	//Baza barca
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-52.5f, 1.0f, -0.51f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-52.5f, 1.0f, 15.51f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-51.0f, 0.9f, 15.51f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-51.0f, 0.9f, -0.51f);

	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-47.5f, 1.0f, -0.51f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-47.5f, 1.0f, 15.51f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-49.0f, 0.9f, 15.51f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-49.0f, 0.9f, -0.51f);

	//glColor3f(0.647, 0.176, 0.011);

	//Bot Spate
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-52.5f, 1.0f, 15.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-50.0f, 1.5f, 17.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 3.0f, 19.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-52.5f, 1.0f, 15.5f);

	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-47.5f, 1.0f, 15.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-50.0f, 1.5f, 17.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 3.0f, 19.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-47.5f, 1.0f, 15.5f);

	//Bot Fata
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-52.5f, 1.0f, -0.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-50.0f, 1.5f, -2.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 3.0f, -4.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-52.5f, 1.0f, -0.5f);

	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-47.5f, 1.0f, -0.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-50.0f, 1.5f, -2.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 3.0f, -4.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-47.5f, 1.0f, -0.5f);

	//Capace fata/spate
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, -2.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-52.5f, 1.0f, -0.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 0.82f, -0.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, -2.5f);
	//
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, -2.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-47.5f, 1.0f, -0.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 0.82f, -0.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, -2.5f);
	//
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, 17.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-52.5f, 1.0f, 15.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 0.82f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, 17.5f);
	//
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, 17.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-47.5f, 1.0f, 15.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-50.0f, 0.82f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 1.5f, 17.5f);
	//
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, -4.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-54.0f, 3.0f, -0.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-52.5f, 1.0f, -0.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, -4.5f);
	//
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, -4.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-46.0f, 3.0f, -0.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-47.5f, 1.0f, -0.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, -4.5f);
	//
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, 19.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-54.0f, 3.0f, 15.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-52.5f, 1.0f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, 19.5f);
	//
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, 19.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-46.0f, 3.0f, 15.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-47.5f, 1.0f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-50.0f, 3.0f, 19.5f);

	//Laterale mari sus
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-52.5f, 1.0f, -0.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-52.5f, 1.0f, 15.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-54.0f, 3.0f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-54.0f, 3.0f, -0.5f);

	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-46.0f, 3.0f, -0.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-46.0f, 3.0f, 15.5f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-47.5f, 1.0f, 15.5f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-47.5f, 1.0f, -0.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Podea 1
	glEnable(GL_TEXTURE_2D);
	LoadTexture("Podea.png");
	glBegin(GL_POLYGON);
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-52.5f, 1.0f, -0.51f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-52.5f, 1.0f, 15.51f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-47.5f, 1.0f, 15.51f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-47.5f, 1.0f, -0.51f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Podea 2
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glTexCoord3f(1.0, 1.0, 0.0);  glVertex3f(-53.8f, 2.75f, 8.0f);
	glTexCoord3f(1.0, 0.0, 0.0);  glVertex3f(-53.8f, 2.75f, 15.51f);
	glTexCoord3f(0.0, 0.5, 0.0);  glVertex3f(-50.0f, 2.75f, 19.1f);
	glTexCoord3f(0.0, 0.0, 0.0);  glVertex3f(-46.2f, 2.75f, 15.51f);
	glTexCoord3f(0.0, 1.0, 0.0);  glVertex3f(-46.2f, 2.75f, 8.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glTexCoord3f(1.0, 1.0, 0.0);  glVertex3f(-46.2f, 2.75f, 5.5f);
	glTexCoord3f(1.0, 0.0, 0.0);  glVertex3f(-46.2f, 2.75f, -0.51f);
	glTexCoord3f(0.0, 0.0, 0.0);  glVertex3f(-50.0f, 2.75f, -4.1f);
	glTexCoord3f(0.0, 0.0, 0.0);  glVertex3f(-53.8f, 2.75f, -0.51f);
	glTexCoord3f(0.0, 1.0, 0.0);  glVertex3f(-53.8f, 2.75f, 5.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f(1.0, 1.0, 0.0);  glVertex3f(-53.8f, 2.75f, 5.5f);
	glTexCoord3f(1.0, 0.0, 0.0);  glVertex3f(-53.8f, 2.75f, 8.0f);
	glTexCoord3f(0.0, 0.0, 0.0);  glVertex3f(-51.5f, 2.75f, 8.0f);
	glTexCoord3f(0.0, 1.0, 0.0);  glVertex3f(-51.5f, 2.75f, 5.5f);

	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-46.2f, 2.75f, 5.5f);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-46.2f, 2.75f, 8.0f);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-48.5f, 2.75f, 8.0f);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-48.5f, 2.75f, 5.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	LoadTexture("numaipot.png");
	//Scara
	glBegin(GL_QUADS);
	//glColor3f(0.305, 0.301, 0.294);
	glVertex3f(-50.5f, 2.75f, 8.0f);
	glVertex3f(-50.5f, 1.0f, 7.0f);
	glVertex3f(-49.5f, 1.0f, 7.0f);
	glVertex3f(-49.5f, 2.75f, 8.0f);

	//Balustrada
	//glColor3f(0, 0, 0);
	glVertex3f(-50.0f, 3.0f, -4.5f);
	glVertex3f(-54.0f, 3.0f, -0.5f);
	glVertex3f(-54.0f, 3.3f, -0.5f);
	glVertex3f(-50.0f, 3.3f, -4.5f);
	glVertex3f(-54.0f, 3.0f, -0.5f);
	glVertex3f(-54.0f, 3.0f, -0.0f);
	glVertex3f(-54.0f, 3.3f, -0.0f);
	glVertex3f(-54.0f, 3.3f, -0.5f);
	//
	glVertex3f(-50.0f, 3.0f, -4.5f);
	glVertex3f(-46.0f, 3.0f, -0.5f);
	glVertex3f(-46.0f, 3.3f, -0.5f);
	glVertex3f(-50.0f, 3.3f, -4.5f);
	glVertex3f(-46.0f, 3.0f, -0.5f);
	glVertex3f(-46.0f, 3.0f, -0.0f);
	glVertex3f(-46.0f, 3.3f, -0.0f);
	glVertex3f(-46.0f, 3.3f, -0.5f);
	glEnd();

	//Cascarabeta
	glPushMatrix();
	//glColor3f(0.647, 0.176, 0.011);
	glTranslatef(-50.0, 3.0, 13.5);
	glutSolidCube(4);
	glPopMatrix();

	glBegin(GL_QUADS);
	//glColor3f(0, 0, 0);
	glVertex3f(-47.20f, 2.75f, 12.5f);
	glVertex3f(-47.25f, 3.25f, 12.5f);
	glVertex3f(-48.0f, 3.25f, 12.5f);
	glVertex3f(-48.0f, 2.75f, 12.5f);
	//
	glVertex3f(-47.20f, 3.25f, 12.5f);
	glVertex3f(-47.25f, 3.25f, 13.0f);
	glVertex3f(-48.0f, 3.25f, 13.0f);
	glVertex3f(-48.0f, 3.25f, 12.5f);
	//
	glVertex3f(-47.20f, 3.25f, 13.0f);
	glVertex3f(-47.25f, 3.75f, 13.0f);
	glVertex3f(-48.0f, 3.75f, 13.0f);
	glVertex3f(-48.0f, 3.25f, 13.0f);
	//
	glVertex3f(-47.20f, 3.75f, 13.0f);
	glVertex3f(-47.25f, 3.75f, 13.5f);
	glVertex3f(-48.0f, 3.75f, 13.5f);
	glVertex3f(-48.0f, 3.75f, 13.0f);
	//
	glVertex3f(-47.20f, 3.75f, 13.5f);
	glVertex3f(-47.25f, 4.25f, 13.5f);
	glVertex3f(-48.0f, 4.25f, 13.5f);
	glVertex3f(-48.0f, 3.75f, 13.5f);
	//
	glVertex3f(-47.20f, 4.25f, 13.5f);
	glVertex3f(-47.25f, 4.25f, 14.0f);
	glVertex3f(-48.0f, 4.25f, 14.0f);
	glVertex3f(-48.0f, 4.25f, 13.5f);
	//
	glVertex3f(-47.20f, 4.25f, 14.0f);
	glVertex3f(-47.25f, 4.75f, 14.0f);
	glVertex3f(-48.0f, 4.75f, 14.0f);
	glVertex3f(-48.0f, 4.25f, 14.0f);
	//
	glVertex3f(-47.20f, 4.75f, 14.0f);
	glVertex3f(-47.25f, 4.75f, 14.5f);
	glVertex3f(-48.0f, 4.75f, 14.5f);
	glVertex3f(-48.0f, 4.75f, 14.0f);
	//
	//glColor3f(0, 0, 0);
	glVertex3f(-48.0, 5.0, 13.25);
	glVertex3f(-48.0, 5.0, 11.5);
	glVertex3f(-48.0, 5.3, 11.5);
	glVertex3f(-48.0, 5.3, 13.25);

	glVertex3f(-52.0, 5.0, 11.5);
	glVertex3f(-52.0, 5.3, 11.5);
	glVertex3f(-48.0, 5.3, 11.5);
	glVertex3f(-48.0, 5.0, 11.5);

	glVertex3f(-52.0, 5.0, 13.25);
	glVertex3f(-52.0, 5.0, 11.5);
	glVertex3f(-52.0, 5.3, 11.5);
	glVertex3f(-52.0, 5.3, 13.25);
	glEnd();
	//Usa
	glPushMatrix();
	glTranslatef(-50.0, 3.5, 11.5);
	glScalef(1.4, 3, 0.2);
	glutSolidCube(0.5);
	glPopMatrix();


	//Motoare
	glPushMatrix();
	//glColor3f(0.603, 0.603, 0.596);
	glTranslatef(-50.0, 1, 3.5);
	glRotatef(240, 1, 1, 1);
	glutSolidCylinder(0.65, 7, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-50.0, 1, 1.5);
	glRotatef(240, 1, 1, 1);
	glutSolidCylinder(0.55, 6, 20, 20);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Carma
	glPushMatrix();
	glColor3f(0.647, 0.176, 0.011);
	glTranslatef(-50.0, 1, 9.0);
	glRotatef(240, 1, 1, 1);
	glutSolidCylinder(0.05, 3.25, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(-50.0, 3.75, 9.0);
	glutSolidCylinder(0.1, 0.25, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647, 0.176, 0.011);
	glTranslatef(-50.0, 3.75, 9.1);
	glutSolidCylinder(0.45, 0.1, 20, 20);
	glPopMatrix();




}


void renderScene(void) {
	pozitieCursor();
	// Clear Color and Depth Buffers
	lumina();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.1f, 0.0f);

	// Draw water
	GLfloat color2[] = { 0.1f, 0.1f, 0.9f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color2);
	glColor3f(0.1f, 0.1f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw ground
	//Daca se deseneaza un cuboid in paint pentru referinta ce e pe desen este ce nu este in paranteza
	//Ce e in paranteza e cum se vede in open gl
	GLfloat color[] = { 0.098f, 0.556f, 0.082f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	glColor3f(0.098f, 0.556f, 0.082f);
	glBegin(GL_QUADS);
	//Fata(sus)
	glVertex3f(-25.0f, 0.6f, -35.0f);
	glVertex3f(-25.0f, 0.6f, 35.0f);
	glVertex3f(35.0f, 0.6f, 35.0f);
	glVertex3f(35.0f, 0.6f, -35.0f);
	//Spate(jos)
	glVertex3f(35.0f, 0.1f, -35.0f);
	glVertex3f(-25.0f, 0.1f, -35.0f);
	glVertex3f(-25.0f, 0.1f, 35.0f);
	glVertex3f(35.0f, 0.1f, 35.0f);
	//Laterala stanga(dreapta)
	glVertex3f(35.0f, 0.1f, -35.0f);
	glVertex3f(35.0, 0.6, -35.0);
	glVertex3f(-25.0, 0.6, -35.0);
	glVertex3f(-25.0, 0.1, -35.0);
	//Laterala dreapta(stanga)
	glVertex3f(-25.0f, 0.1f, 35.0f);
	glVertex3f(-25.0, 0.6, 35.0);
	glVertex3f(35.0, 0.6, 35.0);
	glVertex3f(35.0, 0.1, 35.0);
	//Top(fata)
	glVertex3f(35.0, 0.6, 35.0);
	glVertex3f(35.0, 0.6, -35.0);
	glVertex3f(35.0, 0.1, -35.0);
	glVertex3f(35.0, 0.1, 35.0);
	//Bottom(spate)
	glVertex3f(-25.0, 0.1, 35.0);
	glVertex3f(-25.0, 0.6, 35.0);
	glVertex3f(-25.0, 0.6, -35.0);
	glVertex3f(-25.0, 0.1, -35.0);


	glEnd();

	// Draw 18 copaci
	int random_value = 3;
	for (int i = -1; i < 3; i++)
		for (int j = -2; j < 3; j++) {
			int tip_coroana = i + j;
			glPushMatrix();
			glTranslatef(i * 10.0 + i % random_value, 0, j * 10.0 + (j * i - j / (2 * i + 1)) % random_value);
			if (tip_coroana % 2 == 0)
				drawTree1();
			else drawTree2();
			glPopMatrix();
		}

	drawPatura(19, 20, 0.1, 10, 10);
	drawPatura(-3, -10, 0.1, 10, 10);
	drawPatura(0, 10, 0.1, 10, 10);
	drawPatura(23, -1, 0.1, 10, 10);

	barca();
	moara_de_vant();
	glutSwapBuffers();
}

void functiiMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			cursorInvizibil = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			cursorInvizibil = true;
			angle += 0.2;
			ly = sin(angle);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		break;

	}
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	float fraction = 0.4f;
	float unghi = 80;

	if (key == 'a') {
		lx = sin(angle + unghi);
		lz = -cos(angle + unghi);
		x += lx * fraction;
		z += lz * fraction;
	}
	if (key == 'd') {
		lx = sin(angle + unghi);
		lz = -cos(angle + unghi);
		x -= lx * fraction;
		z -= lz * fraction;
	}
	if (key == 'w') {
		x += lx * fraction;
		z += lz * fraction;
	}
	if (key == 's') {
		x -= lx * fraction;
		z -= lz * fraction;
	}
	if (key == ' ') {
		y += 0.1;
	}
	if (key == 'z') {
		y -= 0.1;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.4f;
	float unghi = 80;
	switch (key) {
	case GLUT_KEY_LEFT:
		lx = sin(angle + unghi);
		lz = -cos(angle + unghi);
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_RIGHT:
		lx = sin(angle + unghi);
		lz = -cos(angle + unghi);
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case GLUT_KEY_F1:
		exit(0);
		break;
	}
}


// Meniu

int keybBackground, currentColor;

void Initialize(int key)
{


	switch (key)
	{
	case 0:
		glClearColor(0.0, 0.0, 0.0, 1.0);
		break;
	case 1:
		glClearColor(1, 0.0, 0.0, 0.0);
		keybBackground = 1;
		break;
	case 2:
		glClearColor(0.0, 1.0, 0.0, 0.0);
		keybBackground = 2;
		break;
	case 3:
		glClearColor(0.090, 0.741, 0.768, 0.5);
		keybBackground = 3;
		break;
	}



}

void desen(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	if (currentColor == 0)
		glColor3f(0.2, 0.2, 0.2);
	if (currentColor == 1)
		glColor3f(1.0, 1.0, 1.0);
	glVertex2i(370, 30);
	glVertex2i(20, 380);

	glVertex2i(10, 10);
	glVertex2i(500, 500);
	glEnd();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}
void callback_Main(int key)
{
	if (key == 0)
	{
		exit(0);
	}
}
void callback_Color(int key)
{
	currentColor = key;
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char** argv) {

	// init GLUT and create window

	int menuMain, menuBackground, menuColor;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Scena 3D cu padure, lac si barca");
	Initialize(keybBackground);
	glutDisplayFunc(desen);
	glutReshapeFunc(reshape);


	menuBackground = glutCreateMenu(Initialize);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	menuColor = glutCreateMenu(callback_Color);
	glutAddMenuEntry("Grey ", 0);
	glutAddMenuEntry("White ", 1);

	menuMain = glutCreateMenu(callback_Main);

	glutAddSubMenu("Culoare fundal ", menuBackground);
	glutAddMenuEntry("Iesire ", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glClearColor(0.090, 0.741, 0.768, 0.5);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutMouseFunc(functiiMouse);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}