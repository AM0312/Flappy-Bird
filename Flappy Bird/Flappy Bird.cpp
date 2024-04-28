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

double queuedMilliseconds, prev0, fps, responseTime;

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
	if (key == 32) startFlag = 1;
	else str[idx++] = key;
	switch (key) {
		case 27:
			exit(0);
			break;
		case 32:
			if (!gameover) inputKeys.push_back('U');
			break;
	}
	if (idx == 7)
	{
		if (strcmp(str, "god_mode") == 0) god = 1;
		else idx = 0;
	}
}

int main(int argc, char** argv) {
	//.. update frame limits
	queuedMilliseconds = 0;
	prev0 = 0;
	fps = 60;
	responseTime = (1 / fps) * 1000;

	//.. render resolutions
	resX = 854;
	resY = 480;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutGameModeString("10x10");
display_choice:
	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) glutEnterGameMode();
	else {
		cout << "Select Screen Resolution, if you are unsure select Window mode" << endl
			<< "1. 1920x1080" << endl
			<< "2. 1600x900" << endl
			<< "3. 1280x720" << endl
			<< "4. 1368x768" << endl
			<< "5. 1366x768" << endl
			<< "6. 800x600" << endl
			<< "7. 640x480" << endl;
		int ch;
		cin >> ch;
		
		if (ch == 1) glutGameModeString("1920x1080");
		else if (ch == 2) glutGameModeString("1600x900");
		else if (ch == 3) glutGameModeString("1280x720");
		else if (ch == 4) glutGameModeString("1368x768");
		else if (ch == 5) glutGameModeString("1366x768");
		else if (ch == 6) glutGameModeString("800x600");
		else glutGameModeString("640x480");
		if (ch != 8)
			goto display_choice;
	}
	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(draw);
	glutIdleFunc(mixedStepLoop);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
