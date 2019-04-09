/*
 * Render.cc
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <GL/glu.h>
#include "Render.h"


/*************************************************/
Render::Render() {
   // TODO Auto-generated constructor stub

}

/*************************************************/
Render::~Render() {
   // TODO Auto-generated destructor stub
}

/*************************************************/
void Render::initialize() {

}

/*************************************************/
void Render::render() {
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1., 1., -1., 1., 1., 20.);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

   glBegin (GL_QUADS);
   glColor3f(1., 0., 0.);
   glVertex3f(-.75, -.75, 0.);
   glColor3f(0., 1., 0.);
   glVertex3f(.75, -.75, 0.);
   glColor3f(0., 0., 1.);
   glVertex3f(.75, .75, 0.);
   glColor3f(1., 1., 0.);
   glVertex3f(-.75, .75, 0.);
   glEnd();
}
