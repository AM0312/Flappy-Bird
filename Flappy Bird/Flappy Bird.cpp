#include <iostream>
#include <gl/glut.h>
#include <vector>
#include <cmath>
#include <string>
#include "flappyHeader.h"
#include"../SOIL2/SOIL2.h"
using namespace std;

int resX, resY, movX, startFlag;
double movY;

vector<char> inputKeys;
double v, grav, temp2;
int cnt;

int idx;
char str[13];

//... Reshaping setting & rendering
void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glOrtho(0, resX, 0, resY, -5, 10);
	glLoadIdentity();
}

void gameOver() {
	inputKeys.push_back('U');
	v = 1.2;
}

void movPhysics() {
	grav = 10;
	for (int _ = 0; _ < inputKeys.size(); _++) {
		if (inputKeys[_] == 'U') {
			if ((movY + (resY / 2) + 50) < resY) movY += 4;
			cnt++;
		}
		if (cnt >= 10) {
			cnt = 0;
			inputKeys.erase(inputKeys.begin() + _);
		}
	}
	if (startFlag) {
		//... Gravity exists
		if (inputKeys.size() == 0) {
			if (gameover == 0) {
				temp2 = resY / 2;
				v = 0.65 + (abs(movY) / temp2) / 5;
			}
			else {
				if ((inputKeys.size() == 0) and (movY < -(resY / 2))) {
					gameover = 0;
					resetFunc();
				}
			}
			if ((movY < (-resY / 2 - 30))) {
				if (!god) movY -= v * v / 2 * grav;
			}
			else {
				movY -= v * v / 2 * grav;
			}
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 32)
		startFlag = 1;
	else
		str[idx++] = key;

	switch (key) {
		case 27:
			exit(0);
			break;
		case 32:
			if (gameover == 0)
				inputKeys.push_back('U');
			break;
	}
	if (idx == 7)
	{
		if (strcmp(str, "god_mode") == 0)
			god = 1;
		else
			idx = 0;
	}

}