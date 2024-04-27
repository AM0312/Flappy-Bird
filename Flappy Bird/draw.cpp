#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "../SOIL2/SOIL2.h"
using namespace std;

struct bricks
{
	int x, y;
	int objdisp;
} obj;

vector<bricks> obstacleBrick;
unsigned char* image;
static GLuint texBird[4], texBac[2], texObj[3];
int width, height, score;
float skyX, treeX, treeX2, groundX;
int birdPhys, tmp, highscore, insidebrick, gameover, prevy;
double syncBird;
unsigned int i, j;

void init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//............BIRD...............
	glGenTextures(4, texBird);
	glBindTexture(GL_TEXTURE_2D, texBird[0]);  //texture 1 active 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/bird/frame-1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	glBindTexture(GL_TEXTURE_2D, texBird[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/bird/frame-2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	glBindTexture(GL_TEXTURE_2D, texBird[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/bird/frame-3.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	glBindTexture(GL_TEXTURE_2D, texBird[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/bird/frame-4.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	//.......BACKGROUND.............
	glGenTextures(2, texBac);
	glBindTexture(GL_TEXTURE_2D, texBac[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/background/cloud.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, texBac[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/background/ground.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	//..OBJECTS	
	glGenTextures(3, texObj);
	glBindTexture(GL_TEXTURE_2D, texObj[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/objects/trees_near.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, texObj[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/objects/brick.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, texObj[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Assets/objects/trees_far.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glEnable(GL_TEXTURE_2D);
}

GLuint base;
void initialiseList()
{
	base = glGenLists(6);
	glListBase(base);
}

void update(double temp)
{
	syncBird += temp;
	if (syncBird >= 120)
	{
		birdPhys++;
		if (birdPhys == 3)
			birdPhys = 0;
		syncBird -= 120;
	}

}

void updateSynchronised()
{
	if (gameover == 0)
	{
		groundX -= 4;
		if (groundX < -resX)
			groundX = 0;

		skyX -= 0.75;
		if (skyX < -resX)
			skyX = 0;

		treeX -= 2;
		if (treeX < -resX)
			treeX = 0;

		treeX2 -= 1.75;
		if (treeX2 < -resX)
			treeX2 = 0;
	}

}

void staticBird()
{
	glNewList(base + 0, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, resY / 2, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(30, resY / 2, 0);
	glTexCoord2f(1.0, -1.0); glVertex3f(30, (resY / 2) + 30, 0);
	glTexCoord2f(0.0, -1.0); glVertex3f(0, (resY / 2) + 30, 0);
	glEnd();
	glEndList();
}

void staticGround()
{
	glNewList(base + 1, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(resX * 2, 0, 0);
	glTexCoord2f(1.0, -1.0); glVertex3f(resX * 2, (resY * 10) / 100, 0);
	glTexCoord2f(0.0, -1.0); glVertex3f(0, (resY * 10) / 100, 0);
	glEnd();
	glEndList();
}

void staticSky()
{
	glNewList(base + 2, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(resX * 2, 0, 0);
	glTexCoord2f(1.0, -1.0); glVertex3f(resX * 2, resY, 0);
	glTexCoord2f(0.0, -1.0); glVertex3f(0, resY, 0);
	glEnd();
	glEndList();
}

void staticTrees()
{
	glNewList(base + 3, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(resX * 2, 0, 0);
	glTexCoord2f(1.0, -1.0); glVertex3f(resX * 2, resY, 0);
	glTexCoord2f(0.0, -1.0); glVertex3f(0, resY, 0);
	glEnd();
	glEndList();
}

void staticTrees_2()
{
	glNewList(base + 5, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(resX * 2, 0, 0);
	glTexCoord2f(1.0, -1.0); glVertex3f(resX * 2, resY, 0);
	glTexCoord2f(0.0, -1.0); glVertex3f(0, resY, 0);
	glEnd();
	glEndList();
}

void staticBrick()
{
	//... BOTTOM BRICK	
	glNewList(base + 4, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(resX, -resY / 2, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(resX + 50, -resY / 2, 0);
	glTexCoord2f(1.0, -1.0); glVertex3f(resX + 50, resY / 2 - 38, 0);
	glTexCoord2f(0.0, -1.0); glVertex3f(resX, resY / 2 - 38, 0);
	glEnd();

	//.... TOP BRICK
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(resX, resY + resY / 2, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(resX + 50, resY + resY / 2, 0);
	glTexCoord2f(1.0, -1.0); glVertex3f(resX + 50, resY / 2 + 38, 0);
	glTexCoord2f(0.0, -1.0); glVertex3f(resX, resY / 2 + 38, 0);
	glEnd();

	glEndList();
}