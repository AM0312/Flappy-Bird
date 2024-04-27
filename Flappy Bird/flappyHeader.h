#pragma once
extern double queuedMilliseconds, prev0, fps, responseTime;
extern int resX, resY, movX, insidebrick, gameover, startFlag, god;
extern double movY;

void adjustBrick();
void draw();
void resetFunc();
void gameoverAnimation();
void mixedStepLoop();
void update(double);
void updateSynchronised();
void processSpecialKeys(int, int, int);
void movePhysics();