#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Main class for vertex structure used in game world
class Vertex {
public:
  GLfloat x;
  GLfloat y;
  Vertex(GLfloat x, GLfloat y);
};