#include <iostream>
#include <gl/glut.h>
#include <vector>
#include <cmath>
#include <string>
#include "flappyHeader.h"
#include"../SOIL2/SOIL2.h"
using namespace std;

int resX, resY;

//... Reshaping setting & rendering
void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glOrtho(0, resX, 0, resY, -5, 10);
	glLoadIdentity();
}