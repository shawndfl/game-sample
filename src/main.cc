#include <iostream>
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <X11/Xlib.h>

XVisualInfo *
get_glx_visual(Display *dpy)
{
   XVisualInfo *visinfo;
   int attrib[] = {
      GLX_RGBA,
      GLX_RED_SIZE, 1,
      GLX_GREEN_SIZE, 1,
      GLX_BLUE_SIZE, 1,
      GLX_DOUBLEBUFFER,
      None
   };
   int screen = DefaultScreen(dpy);

   visinfo = glXChooseVisual(dpy, screen, attrib);
   if (visinfo == NULL) {
      fputs("Couldn't get an RGBA, double-buffered visual\n", stderr);
      exit(1);
   }

   return visinfo;
}

Window
get_glx_window(Display *dpy, XVisualInfo *visinfo, bool map)
{
   XSetWindowAttributes window_attr;
   unsigned long mask;
   int screen = DefaultScreen(dpy);
   Window root_win = RootWindow(dpy, screen);
   Window win;

   window_attr.background_pixel = 0;
   window_attr.border_pixel = 0;
   window_attr.colormap = XCreateColormap(dpy, root_win,
                      visinfo->visual, AllocNone);
   window_attr.event_mask = StructureNotifyMask | ExposureMask |
      KeyPressMask;
   mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;
   win = XCreateWindow(dpy, root_win, 0, 0,
             10, 10, /* width, height */
             0, visinfo->depth, InputOutput,
             visinfo->visual, mask, &window_attr);

   return win;
}


int main(int argc, char *argv[]) {
   Display *dpy = XOpenDisplay(NULL);

   if (!dpy) {
      fputs("couldn't open display\n", stderr);
      exit(77);
   };

   GLXContext ctx;
   XVisualInfo *visinfo = get_glx_visual(dpy);
   Window win = get_glx_window(dpy, visinfo, false);

   ctx = glXCreateContext(dpy, visinfo, False, True);
   if (ctx == None) {
      fputs("glXCreateContext failed\n", stderr);
      exit(1);
   }

   glXMakeCurrent(dpy, win, ctx);

   std::cout << "Hi epoxyL " << epoxy_gl_version() << std::endl;
   return 0;
}
