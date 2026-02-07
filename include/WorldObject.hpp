#pragma once
#include <vector>
#include "Vertex.hpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Static objects in game world
class WorldObject {
public:
  enum TYPE
  {
    PAVEMENT=1,
    FLORA_TREE_1=3,
    FLORA_TREE_2=4,
    ROAD=2,
  };

  TYPE objectType;
  vector<Vertex> vertices;
  GLint offsetX;
  GLint offsetY;

  WorldObject(vector<Vertex> vertices, TYPE objectType);
  void draw();
};