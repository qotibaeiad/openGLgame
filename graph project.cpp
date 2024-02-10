#include <GL/glut.h>
#include <String.h>
#include <math.h>

int rot = 30, rot1 = 30, j = 0;
float down = 1.5, up = -1.5, dis, longball = 0.6; 
float r = 1, b = 1, g = 1, gr = 1, gre = 0.4, blu = 0.3, red = 1; // color
char  m[10] = "Score:", a[3] = "00"; //score
char Start_msg[100] = "Press 'p' to Start";
char top_view[100] = "Press 'g' for Top View";
int f = 0, f2 = 0, f3 = 0, f4 = 0, flagset = 0;
float righmax = 4.5, leftmax = -9, upmax = -4.5, downmax = 4.5;
int cntarr[5] = { 0,0,0,0,0 };
float kx[5] = { -3,-5,-2,0,-3 }, kz[5] = { 1,-1.5,-2.5,1,-3.5 };
int Start = 0;


float balls[5];
struct ball {
	float x;
	float y;
	float z;
	int flagpint;
	int flagmoveupdown;
	int flagleftright;
};
struct ball kador[5];

float two_dis(float x1, float y1, float x2, float y2)
{
	// Calculating distance 
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) );
}

void output(float x, float y, char* string)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void score_out() {
	if (a[0] == '0' && a[1] >= '2') {
		a[0] = '0';
		a[1] -= 2;
	}
	else if (a[0] == '1' || (a[1] == '1' && a[0] != '-')) {
		a[0] = '-';
		a[1] = '1';
	}
	else if (a[0] <= '0' || a[1] <= '0') {
		a[0] = '-';
		a[1] += 2;

	}
}

void score_in() {

	if (a[0] == '0' && a[1] < '5') {
		a[1]++;
		a[0] = '0';
	}
	if (a[0] == '-' && a[1] == '1') {
		a[0] = '0';
		a[1] = '0';
	}
	if (a[0] == '-') {
		a[0] = '-';
		a[1] -= 1;
	}
}



void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(1);
	if (key == 'v') {
		rot += 5,
			rot %= 360;
	}
	if (key == 'r') {
		rot -= 5,
			rot %= 360;
	}
	if (key == 'f') {
		rot1 -= 5,
			rot1 %= 360;
	}
	if (key == 'h') {
		rot1 += 5,
			rot1 %= 360;
	}
	if (key == 'g') {
		rot = 90;
		gre = 0;
		blu = 0;
		red = 1;
		rot1 = 0;
	}

	if (key == 'p') {
		Start = 1;
		gr = 0;
	}


	if (key == 'w')
	{
		if (up >= -3.5)
		{
			up -= 0.50;
			down -= 0.50;
		}
	}

	if (key == 's')
	{
		if (down <= 3.5)
		{
			up += 0.50;
			down += 0.50;
		}
	}
	glutPostRedisplay();
}


void ball()
{
	for (int i = 0; i < 5; i++)
	{
		kador[i].x = kx[i];
		kador[i].y = 0.3;
		kador[i].z = kz[i];
		if (cntarr[i] == 0)
		{
			kador[i].flagleftright = flagset;
			kador[i].flagmoveupdown = flagset;
			kador[i].flagpint = flagset;
			cntarr[i]++;
		}
	}
}
void line()
{
	glColor3f(1.0, 0.2, 0.3);
	glBegin(GL_QUADS);
	//up
	glVertex3f(-8, 0, up);
	glVertex3f(-8, 0.5, up);
	glVertex3f(-8, 0.5, down);
	glVertex3f(-8, 0, down);

	//front
	glVertex3f(-8.5, 0, up);
	glVertex3f(-8.5, 0.5, up);
	glVertex3f(-8.5, 0.5, down);
	glVertex3f(-8.5, 0, down);

	// up up
	glVertex3f(-8, 0.5, up);
	glVertex3f(-8.5, 0.5, up);
	glVertex3f(-8.5, 0.5, down);
	glVertex3f(-8, 0.5, down);

	//right
	glVertex3f(-8.5, 0, up);
	glVertex3f(-8.5, 0.5, up);
	glVertex3f(-8, 0.5, up);
	glVertex3f(-8, 0, up);

	//left
	glVertex3f(-8.5, 0, down);
	glVertex3f(-8.5, 0.5, down);
	glVertex3f(-8, 0.5, down);
	glVertex3f(-8, 0, down);
}
void kunt2()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);

	// Front	

	glVertex3f(4, 0, -4);
	glVertex3f(4, 1, -4);
	glVertex3f(4, 1, 4);
	glVertex3f(4, 0, 4);

	// Back

	glVertex3f(5, 0, -4);
	glVertex3f(5, 1, -4);
	glVertex3f(5, 1, 4);
	glVertex3f(5, 0, 4);


	// up side

	glVertex3f(4, 1, 4);
	glVertex3f(5, 1, 4);
	glVertex3f(5, 1, -4);
	glVertex3f(4, 1, -4);

	glEnd();
}

void kunt()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	// Front	
	glNormal3f(0, 0, 0.5);
	glVertex3f(-9, 0, 0.5);
	glVertex3f(-9, 1, 0.5);
	glVertex3f(5, 1, 0.5);
	glVertex3f(5, 0, 0.5);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-9, 0, -0.5);
	glVertex3f(-9, 1, -0.5);
	glVertex3f(5, 1, -0.5);
	glVertex3f(5, 0, -0.5);

	// Left side
	glNormal3f(-1, 0, 0);
	glVertex3f(-9, 0, 0.5);
	glVertex3f(-9, 1, 0.5);
	glVertex3f(-9, 1, -0.5);
	glVertex3f(-9, 0, -0.5);

	// Right side
	glNormal3f(1, 0, 0);
	glVertex3f(5, 0, 0.5);
	glVertex3f(5, 1, 0.5);
	glVertex3f(5, 1, -0.5);
	glVertex3f(5, 0, -0.5);

	// up side
	glNormal3f(0, 1, 0);
	glVertex3f(-9, 1, 0.5);
	glVertex3f(-9, 1, -0.5);
	glVertex3f(5, 1, -0.5);
	glVertex3f(5, 1, 0.5);

	glEnd();
}
void regel()
{
	glColor3f(0.3, 0.5, 0.4);
	glBegin(GL_QUADS);
	// Front	
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -2, 0.5);
	glVertex3f(0.5, -2, 0.5);
	glVertex3f(0.5, 0, 0.5);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -2, -0.5);
	glVertex3f(-0.5, -2, -0.5);

	// Left side
	glNormal3f(-0.5, 0, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -2, 0.5);
	glVertex3f(-0.5, -2, -0.5);
	glVertex3f(-0.5, 0, -0.5);

	// Right side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -2, -0.5);
	glVertex3f(0.5, -2, 0.5);
	glEnd();
}
void hole() {
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(2.5, 0.01, 1);
	glVertex3f(4, 0.01, 1);
	glVertex3f(4, 0.01, -1);
	glVertex3f(2.5, 0.01, -1);
	glEnd();
}

void draw()
{
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(1.8, 0, -15);
	glRotatef(rot, 1, 0, 0);
	glRotatef(rot1, 0, 1, 0);
	/********************/
	GLfloat lightpos[] = { 0.7, 1, 0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	// Floor
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.7, 0.3);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-9, 0, -5);
	glVertex3f(5, 0, -5);
	glVertex3f(5, 0, 5);
	glVertex3f(-9, 0, 5);
	glEnd();
	glTranslatef(4.5, 0, -4.5);
	regel();
	glTranslatef(-13, 0, 0);
	regel();
	glTranslatef(0, 0, 9);
	regel();
	glTranslatef(13, 0, 0);
	regel();
	glTranslatef(-4.5, 0, -4.5);

	glTranslatef(0, 0, 4.5);
	kunt();
	glTranslatef(0, 0, -9);
	kunt();
	glTranslatef(0, 0, 4.5);
	line();
	kunt2();
	ball();


	r = 0.8;
	g = 0.8;
	b = 0.8;

	///first ball
	for (int i = 0; i < 5; i++)
	{
		glTranslatef(kador[i].x, kador[i].y, kador[i].z);
		glColor3f(r, g, b);
		if (kador[i].flagpint == 0)
			glutSolidSphere(0.3, 30, 30);
		glTranslatef(-kador[i].x, -kador[i].y, -kador[i].z);
		g -= 0.2;
		r -= 0.2;
	}
	glFlush();

	glTranslatef(0, 0, 3.5);
	hole();
	glTranslatef(0, 0, -7);
	hole();

	glColor3f(1, 1, 1);
	output(-2.5, 8.2, m);
	output(-2, 8.2, a);
	glColor3f(0, gr, 0);
	output(-2.9, 7.6, Start_msg);
	glColor3f(red, gre, blu);
	output(-4, 3, top_view);
	glutSwapBuffers();			// display the output
}
void Idle(void) {
	if (Start == 1) {

		for (int i = 0; i < 5; i++)
		{
			if (i != j)
			{
				for (j = 0; j < 5; j++)
				{
					dis = two_dis(kador[i].x, kador[i].z, kador[j].x, kador[j].z);
					//righ
					if (kador[i].x <= righmax && kador[i].flagleftright == 0)
					{
						if (kador[i].flagpint == 0)
						{
							kx[i] += 0.001118;
						}
						if (kador[i].x >= righmax - 1)
						{
							kador[i].flagleftright = 1;
						}
						
					}
					//left
					if (kador[i].x >= leftmax && kador[i].flagleftright == 1)
					{
						if (kador[i].flagpint == 0)
						{
							kx[i] -= 0.001118;
						}
						if (kador[i].x <= leftmax - 6 || kador[i].z >= up && kador[i].z <= down && kador[i].x <= -7.5)
						{
							kador[i].flagleftright = 0;
						}
						
					}
					////up
					if (kador[i].z >= upmax && kador[i].flagmoveupdown == 0)
					{
						if (kador[i].flagpint == 0)
						{
							kz[i] -= 0.001115;
						}
						if (kador[i].z <= upmax + 1)
						{
							kador[i].flagmoveupdown = 1;
							
						}
						
					}
					//down
					if (kador[i].z <= downmax && kador[i].flagmoveupdown == 1)
					{
						if (kador[i].flagpint == 0)
						{
							kz[i] += 0.001115;
						}
						if (kador[i].z >= downmax - 1)
						{
							kador[i].flagmoveupdown = 0;
						}
						

						
					}

					if (dis <= longball)
					{
						if (i != j)
						{
							if (kador[i].flagleftright == 1 && kador[j].flagleftright == 0)
							{
								kador[i].flagleftright = 0;
								kador[j].flagleftright = 1;
							}
							if (kador[i].flagmoveupdown == 1 && kador[j].flagmoveupdown == 0)
							{
								kador[i].flagmoveupdown = 0;
								kador[j].flagmoveupdown = 1;
							}
							
						}
					}
				}
			}
			if (kador[i].x <= leftmax) {
				kador[i].flagpint = 1;
				score_out();
				kx[i] = 100000;
			}
			// right up
			if (kador[i].x >= 2.5 && kador[i].z <= -2.5 && kador[i].x <= 10) {
				kador[i].flagpint = 1;
				score_in();
				kx[i] = 100000;
			}
			// left up
			if (kador[i].x >= 2.5 && kador[i].z >= 2.5 && kador[i].x <= 10) {
				kador[i].flagpint = 1;
				score_in();
				kx[i] = 100000;
			}
		}
	}
	draw();
}
// Set OpenGL parameters
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	// Lighting parameters


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	// RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(1000, 1000);					// 1000 x 1000 pixels
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Mini Game");
	glutDisplayFunc(draw);		// Set the display function
	glutIdleFunc(Idle); // Set the idle function
	glutKeyboardFunc(keyboard);	// Set the keyboard function

	init();
	glutMainLoop();							// Start the main event loop
}
