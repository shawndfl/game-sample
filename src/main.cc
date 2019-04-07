#include <iostream>
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <X11/Xlib.h>
#include <GL/glu.h>

#include "Render.h"
#include "Logging.h"

XVisualInfo *
get_glx_visual(Display *dpy) {
   XVisualInfo *visinfo;
   int attrib[] = {
   GLX_RGBA,
   GLX_DEPTH_SIZE, 24,
   GLX_DOUBLEBUFFER,
   None };
   int screen = DefaultScreen(dpy);

   visinfo = glXChooseVisual(dpy, screen, attrib);
   if (visinfo == NULL) {
      fputs("Couldn't get an RGBA, double-buffered visual\n", stderr);
      exit(1);
   }

   return visinfo;
}

void DrawAQuad() {
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1., 1., -1., 1., 1., 20.);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

   glBegin(GL_QUADS);
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

Window get_glx_window(Display *dpy, XVisualInfo *visinfo, bool map) {
   XSetWindowAttributes window_attr;
   unsigned long mask;
   int screen = DefaultScreen(dpy);
   Window root_win = RootWindow(dpy, screen);
   Window win;

   window_attr.background_pixel = 0;
   window_attr.border_pixel = 0;
   window_attr.colormap = XCreateColormap(dpy, root_win, visinfo->visual,
   AllocNone);
   window_attr.event_mask = StructureNotifyMask | ExposureMask |
   KeyPressMask;
   mask = CWColormap | CWEventMask;
   win = XCreateWindow(dpy, root_win, 0, 0, 600, 600, /* width, height */
   0, visinfo->depth, InputOutput, visinfo->visual, mask, &window_attr);

   return win;
}

int main(int argc, char *argv[]) {

   Render render;
   render.initialize();

   LOGD("Testing... %f ", 12.6);

   Display *dpy = XOpenDisplay(NULL);

   if (!dpy) {
      fputs("couldn't open display\n", stderr);
      exit(77);
   };

   GLXContext ctx;
   XVisualInfo *visinfo = get_glx_visual(dpy);
   Window win = get_glx_window(dpy, visinfo, false);

   XMapWindow(dpy, win);
   XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

   ctx = glXCreateContext(dpy, visinfo, False, True);
   if (ctx == None) {
      fputs("glXCreateContext failed\n", stderr);
      exit(1);
   }

   glXMakeCurrent(dpy, win, ctx);

   LOGI("Epoxy version: %d ", epoxy_gl_version());
   while (1) {
      XEvent xev;
      XWindowAttributes gwa;
      XNextEvent(dpy, &xev);

      if (xev.type == Expose) {
         XGetWindowAttributes(dpy, win, &gwa);
         glViewport(0, 0, gwa.width, gwa.height);
         DrawAQuad();
         glXSwapBuffers(dpy, win);
      }

      else if (xev.type == KeyPress) {
         glXMakeCurrent(dpy, None, NULL);
         glXDestroyContext(dpy, ctx);
         XDestroyWindow(dpy, win);
         XCloseDisplay(dpy);
         exit(0);
      }
   }
   LOGI("Exit ");
   return 0;
}
