#include <time.h>
#include <stdlib.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <functional>
#include <memory>
#include <string>
#include "World.hpp"

using namespace std;

GLsizei wh = 600, ww = 525; // initial window size, resizing is disabled

World *world; // Main world object

void processSpecialKeys(GLint key, GLint x, GLint y)
{
	// If game is over, ignore player input
	if (world->state == World::STATE::GAME_OVER) 
  {
		return;
	}

	switch (key) {
	case GLUT_KEY_UP:
		// Agent tried to go wrong direction:
		if (world->agent->direction == Actor::DIRECTION::DOWN && world->agent->stateY != Agent::AGENT_STATUS::MOVING && world->agent->offsetY != wh - world->squareSize) {
      world->soundManager->setVolume(world->soundManager->ambienceSource, 0.15f);
      world->soundManager->playSound(world->soundManager->gameOver, world->soundManager->effectSource);
			world->agent->triedToGoBack = 1;
			world->state = World::STATE::GAME_OVER;
		}
		// Move agent:
		else if (world->agent->step(Actor::DIRECTION::UP) == 1 && world->agent->offsetY != wh - world->squareSize) {
			if (world->worldLayout[world->agent->currentRow] == WorldObject::PAVEMENT) {
        world->soundManager->playSound(world->soundManager->footstepGrass, world->soundManager->effectSource);
			}
			else {
        world->soundManager->playSound(world->soundManager->footstepRoad, world->soundManager->effectSource);
			}
			world->score++; // Increase score if direction of agent and movement is same
		}
		break;
	case GLUT_KEY_DOWN:
		// Agent tried to go wrong direction:
		if (world->agent->direction == Actor::DIRECTION::UP && world->agent->stateY != Agent::AGENT_STATUS::MOVING && world->agent->offsetY != 0) {
      world->soundManager->setVolume(world->soundManager->ambienceSource, 0.15f);
      world->soundManager->playSound(world->soundManager->gameOver, world->soundManager->effectSource);
			world->agent->triedToGoBack = 1;
			world->state = World::STATE::GAME_OVER;
		}
		// Move agent:
		else if (world->agent->step(Actor::DIRECTION::DOWN) == 1 && world->agent->offsetY != 0) {
			if (world->worldLayout[world->agent->currentRow] == WorldObject::PAVEMENT) {
        world->soundManager->playSound(world->soundManager->footstepGrass, world->soundManager->effectSource);
			}
			else {
        world->soundManager->playSound(world->soundManager->footstepRoad, world->soundManager->effectSource);
			}
			world->score++; // Increase score if direction of agent and movement is same
		}
		break;
	case GLUT_KEY_RIGHT:
		if (world->worldLayout[world->agent->currentRow] == WorldObject::PAVEMENT) {
      world->soundManager->playSound(world->soundManager->footstepGrass, world->soundManager->effectSource);
		}
		else {
      world->soundManager->playSound(world->soundManager->footstepRoad, world->soundManager->effectSource);
		}
		world->agent->step(Actor::DIRECTION::RIGHT);
		break;
	case GLUT_KEY_LEFT:
		if (world->worldLayout[world->agent->currentRow] == WorldObject::PAVEMENT) {
      world->soundManager->playSound(world->soundManager->footstepGrass, world->soundManager->effectSource);
		}
		else {
      world->soundManager->playSound(world->soundManager->footstepRoad, world->soundManager->effectSource);
		}
		world->agent->step(Actor::DIRECTION::LEFT);
		break;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 113 || key == 81) // ASCII Q = 81, ASCII q = 113
		exit(0);
}

void mouseInput(GLint button, GLint state, GLint x, GLint y) {
	switch (button) {
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN && world->state == World::STATE::RUN)
			world->state = World::STATE::PAUSE;
		break;
	case GLUT_LEFT_BUTTON:
		if (world->state == World::STATE::PAUSE && state == GLUT_DOWN) {
			world->state = World::STATE::RUN;
		}
	case GLUT_RIGHT_BUTTON:
		if (world->state == World::STATE::PAUSE && state == GLUT_DOWN) {
			world->state = World::STATE::ONEFRAME;
		}
	}
}

void resize(GLsizei w, GLsizei h) {
	// Do not let user resize the window
	glutReshapeWindow(ww, wh);
}

void init(void) {
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	world = new World(25, ww, wh, 1); // Create game world
	glFlush();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	world->drawWorld();
	glFlush();
	glutSwapBuffers();
}

void timer(GLint) {
	// Agent is alive:
	if (world->state != World::STATE::PAUSE) {
		world->updateWorld();
		glutPostRedisplay();
		// Draw current frame and pause again
		if (world->state == World::STATE::ONEFRAME) {
			world->state = World::STATE::PAUSE;
		}
	}
	glutTimerFunc(1000.0 / 60.0, timer, 0); // 60 FPS
}

int main(GLint argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Road Crossing Game");

	init();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(mouseInput);
	glutTimerFunc(1000.0 / 60.0, timer, 0); // 60 FPS
	glutMainLoop();
}