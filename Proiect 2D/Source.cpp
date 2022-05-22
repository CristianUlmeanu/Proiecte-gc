#include <windows.h>
#include <gl/freeglut.h>
#include <cmath>
#include <ctime>
#include <vector>
#include <iostream>

double x_barca = 0;
double y_barca = 0;
double rotation = 0;
int scor = 0;
GLfloat grade_elice = 45;

struct originePeste {
	int x, y;
};

std::vector<originePeste> v;

void deseneazaMoara(void)
{
	// corp moara de vant
	glColor3f(0.866, 0.749, 0.372);
	glBegin(GL_POLYGON);
	glVertex2f(900, 720);
	glVertex2f(950, 720);
	glVertex2f(950, 800);
	glVertex2f(900, 800);
	glEnd();

	// intrare moara
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(915, 720);
	glVertex2f(935, 720);
	glVertex2f(935, 745);
	glVertex2f(915, 745);
	glEnd();

	// fereastra moara
	glColor3f(0.501, 0.776, 0.737);
	glBegin(GL_POLYGON);
	glVertex2f(925, 780);
	glVertex2f(915, 770);
	glVertex2f(925, 760);
	glVertex2f(935, 770);
	glEnd();

	// linii fereastra
	glLineWidth(1.4f);
	glColor3f(0.721, 0.501, 0.117);
	glBegin(GL_LINES);
	glVertex2f(925, 780);
	glVertex2f(925, 760);
	glVertex2f(915, 770);
	glVertex2f(935, 770);
	glEnd();

	// cadran fereastra
	glLineWidth(2);
	glColor3f(0.670, 0.517, 0.247);
	glBegin(GL_LINE_LOOP);
	glVertex2f(925, 780);
	glVertex2f(915, 770);
	glVertex2f(925, 760);
	glVertex2f(935, 770);
	glEnd();

	// acoperis moara de vant
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(900, 800);
	glVertex2f(950, 800);
	glVertex2f(925, 820);
	glEnd();

	// mijloc elice moara
	glColor3f(0.8, 0.686, 0.219);
	glBegin(GL_POLYGON);
	glVertex2f(920, 810);
	glVertex2f(925, 815);
	glVertex2f(930, 810);
	glVertex2f(925, 805);
	glEnd();

	// suporti elice moara
	glColor3f(0.5f, 0.35f, 0.05f);

	glPushMatrix();

	glTranslatef(925.0f, 810.0f, 0.0f);
	glRotatef(grade_elice, 0.0f, 0.0f, 1.0f);
	glTranslatef(-925.0f, -810.0f, 0.0f);

	glBegin(GL_POLYGON);
	glVertex2f(900, 830);
	glVertex2f(905, 835);
	glVertex2f(950, 790);
	glVertex2f(945, 785);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(950, 830);
	glVertex2f(945, 835);
	glVertex2f(900, 790);
	glVertex2f(905, 785);
	glEnd();

	glPopMatrix();
	glutPostRedisplay();
	grade_elice += 0.1;

}

void deseneazaCopac(int origineX, int origineY)
{
	glLineWidth(7);

	glColor3f(0.4, 0.27, 0.11);
	// trunchi copac
	glBegin(GL_LINES);
	glVertex2f(origineX + 20, origineY + 40);
	glVertex2f(origineX + 20, origineY + 60);
	glEnd();

	// coroana copac
	glColor3f(0.07, 0.36, 0.12);
	glBegin(GL_TRIANGLES);
	glVertex2i(origineX + 0, origineY + 60);
	glVertex2i(origineX + 40, origineY + 60);
	glVertex2i(origineX + 20, origineY + 105);
	glEnd();
}

void init(void)
{

	glClearColor(0.001, 0.53, 0.98, 0.0);
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);

}

void scoreboard()
{
	int cifra, nr_cifre = 0;
	int aux = scor;
	glColor3f(0.1, 0.1, 0.1);
	while (aux)
	{
		cifra = aux % 10;

		switch (cifra)
		{
		case 0:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			//top
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			//bottom
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			//left
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			//right
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			break;
		case 1:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			break;
		case 2:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);

			break;
		case 3:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);

			break;
		case 4:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			break;
		case 5:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			break;
		case 6:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			break;
		case 7:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			break;
		case 8:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			break;
		case 9:
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 792.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(415 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(415 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 752.5);
			glVertex2f(435 - 50 * nr_cifre, 792.5);
			glVertex2f(435 - 50 * nr_cifre, 772.5);
			break;
		default:
			break;
		}
		nr_cifre += 1;
		aux = aux / 10;
	}
	glEnd();
	for (int i = 3; i > nr_cifre - 1; i--)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		//top
		glVertex2f(415 - 50 * i, 792.5);
		glVertex2f(435 - 50 * i, 792.5);
		//bottom
		glVertex2f(435 - 50 * i, 752.5);
		glVertex2f(415 - 50 * i, 752.5);
		//left
		glVertex2f(415 - 50 * i, 792.5);
		glVertex2f(415 - 50 * i, 752.5);
		//right
		glVertex2f(435 - 50 * i, 792.5);
		glVertex2f(435 - 50 * i, 752.5);
		glEnd();
	}
}

void deseneazaPeste(int origineX, int origineY)
{
	//std::cout << "pestii" << std::endl;
	glColor3f(0.686, 0.631, 0.631);
	glLineWidth(3.0f);
	// corp peste
	glBegin(GL_POLYGON);
	glVertex2f(origineX + 290, origineY + 85);
	glVertex2f(origineX + 315, origineY + 85);
	glVertex2f(origineX + 320, origineY + 80);
	glVertex2f(origineX + 315, origineY + 75);
	glVertex2f(origineX + 290, origineY + 75);
	glVertex2f(origineX + 280, origineY + 80);
	glEnd();

	//coada peste
	glBegin(GL_TRIANGLES);
	glVertex2f(origineX + 320, origineY + 80);
	glVertex2f(origineX + 330, origineY + 85);
	glVertex2f(origineX + 330, origineY + 75);
	glEnd();

	glutPostRedisplay();
}

void deseneazaScena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glColor3f(0.53, 0.74, 0.96); // cer
	glBegin(GL_TRIANGLES);
	glVertex2i(-30, 600);
	glVertex2i(-30, 900);
	glVertex2i(1200, 900);
	glEnd();



	glColor3f(0.03, 0.61, 0.16);
	glBegin(GL_POLYGON); //iarba
	glVertex2i(-30, 600);
	glVertex2i(-30, 300);
	glVertex2i(1500, 900);
	glVertex2i(1200, 900);
	glEnd();
	//-----------------------------------copac
	glLineWidth(7);
	glColor3f(0.4, 0.27, 0.11);
	glBegin(GL_LINES);
	glVertex2f(1300, 830);
	glVertex2f(1300, 850);
	glEnd();

	glColor3f(0.07, 0.36, 0.12);
	glBegin(GL_TRIANGLES);
	glVertex2i(1280, 850);
	glVertex2i(1320, 850);
	glVertex2i(1300, 895);
	glEnd();



	//-----------------------------------casa 
	glColor3f(0.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(1200, 820); //colt stanga jos
	glVertex2i(1230, 820); //colt dreapta jos
	glVertex2i(1230, 850); //colt dreapta sus
	glVertex2i(1200, 850); //colt stanga sus
	glEnd();
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(1200, 850);
	glVertex2i(1230, 850);
	glVertex2i(1215, 870);
	glEnd();
	glColor3f(0.0, 0.8, 0.4);
	glBegin(GL_POLYGON); // usa casa
	glVertex2i(1212, 820); //colt stanga jos + 12
	glVertex2i(1218, 820); //colt dreapta jos + 18
	glVertex2i(1218, 840); //colt dreapta sus + h= 20
	glVertex2i(1212, 840); //colt stanga sus + h = 20
	glEnd();
	//-------------------------------------


	//-----------SOARE
	glColor3f(1.0, 0.84, 0);
	GLuint regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glBegin(GL_POLYGON);
	int nr_laturi = 30;
	for (int k = 0; k < nr_laturi; k++)
	{
		const double TWO_PI = 6.2831853;
		double hexTheta = TWO_PI * k / nr_laturi;
		double x = 30 + 150 * cos(hexTheta);
		double y = 850 + 150 * sin(hexTheta);
		glVertex2i(x, y);
	}
	glEnd();
	glEndList();
	glCallList(regHex);
	glPopMatrix();


	deseneazaCopac(300, 600);
	deseneazaCopac(340, 570);
	deseneazaCopac(470, 630);
	deseneazaCopac(520, 550);
	deseneazaCopac(780, 640);
	deseneazaCopac(660, 600);
	deseneazaCopac(800, 700);
	deseneazaCopac(200, 370);
	deseneazaCopac(150, 400);
	deseneazaCopac(100, 500);

	deseneazaMoara();

	//---------------------------------------------barca 
	glPushMatrix();

	glTranslated(420, 80, 0);
	glTranslated(x_barca, y_barca, 0.0);
	glScaled(rotation, 1, 1);
	glTranslated(-420, -80, 0);
	glColor3f(0.015, 0.007, 0.58);
	glBegin(GL_POLYGON); //barca 
	glVertex2f(300, 100);
	glVertex2f(500, 100);
	glVertex2f(450, 70); /// hitbox
	glVertex2f(350, 70);
	glEnd();

	/// debugging
	//glPointSize(5);
	//glBegin(GL_POINTS);
	//glColor3f(1, 1, 1);
	//glVertex2f(450, 70);
	//glEnd();

	glColor3f(0.67, 0.05, 0.001);
	glBegin(GL_TRIANGLES);
	glVertex2f(300, 105);
	glVertex2f(400, 105);
	glVertex2f(400, 160);
	glEnd();

	glLineWidth(5);
	glColor3f(0.33, 0.33, 0.34);
	glBegin(GL_LINES);
	glVertex2f(420, 100);
	glVertex2f(420, 155);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(440, 100);
	glVertex2f(440, 155);
	glEnd();

	glColor3f(1.0, 0.84, 0);
	glPopMatrix();

	for (originePeste p : v) {
		deseneazaPeste(p.x, p.y);
	}

	// hitbox barca peste === 451 + x_barca + (rotation == 1 ? 0 : -60), 70 + y_barca 

	for(int i = 0 ; i < v.size() ; i++)
		if (abs(451 + x_barca + (rotation == 1 ? 0 : -60) - v[i].x - 300) < 10 && abs(70 + y_barca - v[i].y - 80) < 10) {
			scor++;
			v.erase(v.begin() + i);
			break;
		}
	//-------------------------//
	//		Scoreboard		//

	glLineWidth(5);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	//S
	glVertex2f(290, 875);
	glVertex2f(290, 890);
	glVertex2f(290, 890);
	glVertex2f(260, 890);
	glVertex2f(260, 890);
	glVertex2f(260, 860);
	glVertex2f(260, 860);
	glVertex2f(290, 860);
	glVertex2f(290, 860);
	glVertex2f(290, 830);
	glVertex2f(290, 830);
	glVertex2f(260, 830);
	glVertex2f(260, 830);
	glVertex2f(260, 845);

	//C
	glVertex2f(335, 890);
	glVertex2f(305, 890);
	glVertex2f(305, 890);
	glVertex2f(305, 830);
	glVertex2f(305, 830);
	glVertex2f(335, 830);

	//O
	glVertex2f(382.5, 890);
	glVertex2f(347.5, 890);
	glVertex2f(347.5, 890);
	glVertex2f(347.5, 830);
	glVertex2f(347.5, 830);
	glVertex2f(382.5, 830);
	glVertex2f(382.5, 830);
	glVertex2f(382.5, 890);

	//R
	glVertex2f(397.5, 827);
	glVertex2f(397.5, 890);
	glVertex2f(397.5, 890);
	glVertex2f(427.5, 890);
	glVertex2f(427.5, 890);
	glVertex2f(427.5, 860);
	glVertex2f(427.5, 860);
	glVertex2f(397.5, 860);
	glEnd();
	glLineWidth(8.25);
	glBegin(GL_LINES);
	glVertex2f(397.5, 860);
	glVertex2f(427.5, 827);
	glEnd();

	//:
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2f(445, 870);
	glVertex2f(445, 845);
	glEnd();

	//Tabela
	glLineWidth(6.5);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(245, 805);
	glVertex2f(455, 805);
	glVertex2f(455, 745);
	glVertex2f(245, 745);
	glEnd();


	//0000
	if (scor == 0)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		for (int i = 0; i < 200; i += 50)
		{
			//top
			glVertex2f(415 - i, 792.5);
			glVertex2f(435 - i, 792.5);
			//bottom
			glVertex2f(435 - i, 752.5);
			glVertex2f(415 - i, 752.5);
			//left
			glVertex2f(415 - i, 792.5);
			glVertex2f(415 - i, 752.5);
			//right
			glVertex2f(435 - i, 792.5);
			glVertex2f(435 - i, 752.5);

		}
		glEnd();
	}
	else
		scoreboard();

	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

bool verificaImpact(int x, int y) {
	if ((-60 * x + 153 * y - 47700) >= 0) {
		return true; // hitboxul atinge sau se afla chiar deasupra liniei de tarm
	}
	else {
		return false; // hitboxul nu atinge === se afla sub linie
	}
}

void keyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (verificaImpact(410 + x_barca + (rotation == 1 ? -160 : 0), y_barca + (rotation == 1 ? 40 : 80)))
			break;
		y_barca += 10;
		break;
	case GLUT_KEY_DOWN:
		if (y_barca <= -70)
			break;
		y_barca -= 10;
		break;
	case GLUT_KEY_LEFT:
		if (verificaImpact(410 + x_barca + (rotation == 1 ? -160 : 0), y_barca + (rotation == 1 ? 40 : 80)) || x_barca <= -360)
			break;
		x_barca -= 10;
		rotation = -1;
		break;
	case GLUT_KEY_RIGHT:
		if (x_barca >= 1000)
			break;
		x_barca += 10;
		rotation = 1;
		break;
	default:
		break;
	}
	
	std::cout << x_barca << " " << y_barca << std::endl;
	glutPostRedisplay();
}

void deseneazaPesti(int value) {
	srand(time(0)); // generare seed de random folosind timpul curent
	bool OK = false;
	int x, y;
	while (!OK) {
		x = rand() * rand() % 1000; // folosim rand()*rand() ca sa nu apara pesti unii sub altii 
		y = rand() * rand() % 900;  // sa fie practic mai departati
		if(!verificaImpact(x, y + 10))
			OK = true;// daca nu se afla deasupra liniei sau pe ea chiar, iesim din while
			// altfel generam alt punct si verificam
	}
	v.push_back({ x, y }); // adaugam in vectorul de puncte de origine de pesti
	glutTimerFunc(4000, deseneazaPesti, 0); // timerul pentru generare
}

void customSceneDrawing(void) {
	deseneazaScena();
}

void maiTaieDinPesti(int value) {
	if (v.size()) {
		v.erase(v.begin());
	}
	glutTimerFunc(20000, maiTaieDinPesti, 0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lac cu barcute");
	init();
	glutSpecialFunc(keyboard);
	glutDisplayFunc(customSceneDrawing);
	glutReshapeFunc(reshape);
	glutTimerFunc(4000, deseneazaPesti, 0);
	glutTimerFunc(20000, maiTaieDinPesti, 0);
	glutMainLoop();
}