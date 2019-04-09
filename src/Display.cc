/*
 * Display.cc
 *
 *  Created on: Apr 8, 2019
 *      Author: user1
 */

#include "Logging.h"
#include "Display.h"
#include "Render.h"
#include <X11/Xlib.h>

/*************************************************/
display::display() :
      _width(600), _height(800), _onDraw(nullptr) {

}

/*************************************************/
display::~display() {

}

/*************************************************/
XVisualInfo* get_glx_visual(Display *dpy) {
   XVisualInfo *visinfo;
   int attrib[] = {
   GLX_RGBA,
   GLX_DEPTH_SIZE, 24,
   GLX_DOUBLEBUFFER,
   None };
   int screen = DefaultScreen(dpy);

   visinfo = glXChooseVisual(dpy, screen, attrib);
   if (visinfo == NULL) {
      LOGE("Couldn't get an RGBA, double-buffered visual");
   }

   return visinfo;
}

/*************************************************/
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

/*************************************************/
void display::createWindow(int width, int height, Render* renderer) {
   _width = width;
   _height = height;
   _renderer = std::make_shared<Render>(*renderer);

   Display *dpy = XOpenDisplay(NULL);

   if (!dpy) {
      LOGE("couldn't open display");
   };

   GLXContext ctx;
   XVisualInfo *visinfo = get_glx_visual(dpy);
   Window win = get_glx_window(dpy, visinfo, false);

   XMapWindow(dpy, win);
   XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

   ctx = glXCreateContext(dpy, visinfo, False, True);
   if (ctx == None) {
      LOGE("glXCreateContext failed");
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

         if (_renderer != nullptr) {
            _renderer->render();
         }

         glXSwapBuffers(dpy, win);
      }

      else if (xev.type == KeyPress) {
         glXMakeCurrent(dpy, None, NULL);
         glXDestroyContext(dpy, ctx);
         XDestroyWindow(dpy, win);
         XCloseDisplay(dpy);
      }
   }
   LOGI("Exit ");
}

/*************************************************/
int display::getHeight() const {
   return _height;
}

/*************************************************/
int display::getWidth() const {
   return _width;
}
