#include "Tools.hpp"
#include "WorldObject.hpp"

// Constructor: Creates a WorldObject with the given vertices and type
// - For PAVEMENT and ROAD: stores all vertices to draw a polygon shape
// - For TREES: only stores the first vertex as the center position for drawing
WorldObject::WorldObject(vector<Vertex> vertices, TYPE objectType)
{
  // Store what type of object this is (pavement, road, or tree)
  this->objectType = objectType;
  // If this is pavement (grass), store all vertices to draw the green strip
  if (objectType == TYPE::PAVEMENT)
  {
    this->vertices = vertices;
  }
    // If this is a road, store all vertices to draw the gray strip
  else if (objectType == TYPE::ROAD)
  {
    this->vertices = vertices;
  }
     // For trees, we only need the center position (not all vertices)
     // Trees are drawn procedurally using circles and triangles
  else if (objectType == TYPE::FLORA_TREE_1 || objectType == TYPE::FLORA_TREE_2)
  {
    this->offsetX = vertices.at(0).x;  // X position of tree center 
    this->offsetY = vertices.at(0).y;  // Y position of tree center
  }
}
// Draw method: Renders this object using OpenGL based on its type
void WorldObject::draw() 
{
  if (objectType == TYPE::PAVEMENT)
  {
    //Green strip for pavement
    glColor3f(0.0f, 1.0f, 0.0f);
  }
  else if (objectType == TYPE::ROAD)
  {
    //Gray strip for road
    glColor3f(0.5f, 0.5f, 0.5f);
  }
  else if (objectType == TYPE::FLORA_TREE_1)
  {
    GLint r = 20; // Radius for the main circle
    //circle canopy plus four triangle arms
    glColor3f(0, 0.5f, 0); // dark green colour for tree foliage
    
    // Draw the main circular canopy at the center of the tree
    Tools::drawCircle(this->offsetX, this->offsetY, r);
    
    // Draw four triangular branches pointing in cardinal directions (left, right, up, down)
    // Each triangle has 3 vertices (points)
    glBegin(GL_TRIANGLES);
    // Right-pointing triangle branch
    glVertex2f(this->offsetX + r / 2, this->offsetY + 0.8*r);
    glVertex2f(this->offsetX + r / 2, this->offsetY - 0.8*r);
    glVertex2f(this->offsetX + 2 * r, this->offsetY);
    
    // Left-pointing triangle branch
    glVertex2f(this->offsetX - r / 2, this->offsetY - 0.8*r);
    glVertex2f(this->offsetX - r / 2, this->offsetY + 0.8*r);
    glVertex2f(this->offsetX - 2 * r, this->offsetY);
    
    // Upward-pointing triangle branch
    glVertex2f(this->offsetX + 0.8*r, this->offsetY + r / 2);
    glVertex2f(this->offsetX - 0.8*r, this->offsetY + r / 2);
    glVertex2f(this->offsetX, this->offsetY + 2 * r);
   
    // Downward-pointing triangle branch
    glVertex2f(this->offsetX - 0.8*r, this->offsetY - r / 2);
    glVertex2f(this->offsetX + 0.8*r, this->offsetY - r / 2);
    glVertex2f(this->offsetX, this->offsetY - 2 * r);
    glEnd();

    // Draw a brown dot at the center to represent the tree trunk
    glColor3f(0.2f, 0.0f, 0);
    glBegin(GL_POINTS);
    glVertex2f(this->offsetX, this->offsetY);
    glEnd();
    return;
  }

  else if (objectType == TYPE::FLORA_TREE_2)
  {
    GLint r = 20;
     // Circle canopy made of one core circle plus smaller satellites
    glColor3f(0, 0.5f, 0);
    Tools::drawCircle(this->offsetX, this->offsetY, r);

    // Draw 8 smaller satellite circles around the main circle to create a bushy effect
    // These are positioned in cardinal and diagonal directions
    Tools::drawCircle(this->offsetX + r, this->offsetY, r / 2);
    Tools::drawCircle(this->offsetX + r, this->offsetY + r / 1.2, r / 2);
    Tools::drawCircle(this->offsetX - r, this->offsetY, r / 2);
    Tools::drawCircle(this->offsetX - r, this->offsetY + r / 1.2, r / 2);
    Tools::drawCircle(this->offsetX, this->offsetY + r, r / 2);
    Tools::drawCircle(this->offsetX + r, this->offsetY - r / 1.2, r / 2);
    Tools::drawCircle(this->offsetX - r, this->offsetY - r / 1.2, r / 2);
    Tools::drawCircle(this->offsetX, this->offsetY - r, r / 2);

    glColor3f(0.2f, 0.0f, 0);
    glBegin(GL_POINTS);
    glVertex2f(this->offsetX, this->offsetY);
    glEnd();
    return;
  }

  // Default case: Draw pavement or road as a filled polygon using stored vertices
  // This only runs if the object is PAVEMENT or ROAD (trees already returned above)
  glBegin(GL_POLYGON);
  // Loop through each vertex in the stored vertices list
  for (vector<Vertex>::iterator vertex = this->vertices.begin(); vertex != this->vertices.end(); ++vertex) 
  {
    glVertex2f(vertex->x, vertex->y);
  }
  glEnd();
}
