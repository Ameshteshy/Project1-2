#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
//Ahmad Azhari & Kevin

static float X = 0.0;
static float Y = 0.0;
static float Z = -15.0;

const int ArraySize = 1;

static float rotX = 0, rotY = 0, rotZ = 0, rotAngle = 0;

void loadTextureFromFile(const char* filename, unsigned int texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture - " << filename << std::endl;
	}
	stbi_image_free(data);
}

//declare texture file to be imported
const char* filename1 = "Textures/white_texture.jpg";
unsigned int tob[ArraySize]; //jumlah texture yang akan dimasukkan array

void textureSetup()
{
	glGenTextures(ArraySize, &tob[0]);

	loadTextureFromFile(filename1, tob[0]);
}

static void
drawBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2d(0.0, 0.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2d(0.0, 1.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2d(1.0, 1.0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2d(1.0, 0.0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void myglutSolidCube(GLdouble size)
{
	drawBox(size, GL_QUADS);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	// Modeling transformations.
	//Kamera
	glTranslatef(X, Y, Z);
	//glRotatef(0, rotX, rotY, rotZ);

	
	glBindTexture(GL_TEXTURE_2D, tob[0]);
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glScalef(1,1,1);
	myglutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-10, 4, 0);
	glRotatef(20, 0,0,1);
	glScalef(5, 0.3, 1);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(10, 4, 0);
	glRotatef(-20, 0, 0, 1);
	glScalef(5, 0.3, 1);
	glutSolidCube(2);
	glPopMatrix();

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	//glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		X += 0.5;
		glutPostRedisplay();
		break;
	case 'd':
		X -= 0.5;
		glutPostRedisplay();
		break;
	case 's':
		Y -= 0.5;
		glutPostRedisplay();
		break;
	case 'w':
		Y += 0.5;
		glutPostRedisplay();
		break;
	case 'q':
		Z -= 0.5;
		glutPostRedisplay();
		break;
	case 'e':
		Z += 0.5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void RotKeyInput(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'j':
		rotX = 1;
		glutPostRedisplay();
		break;
	case 'l':
		rotX = 1;
		glutPostRedisplay();
		break;
	case 'k':
		rotY = 1;
		glutPostRedisplay();
		break;
	case 'i':
		rotY = 1;
		glutPostRedisplay();
		break;
	case 'o':
		rotZ = 1;
		glutPostRedisplay();
		break;
	case 'u':
		rotZ = 1;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tugas Kelompok Open GL");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();
	textureSetup();

	glutMainLoop();
}