#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/extensions/XInput2.h>

// Compile with:
// sudo apt-get install build-essential libx11-dev libxi-dev libxcursor-dev
// gcc xiset.c `pkg-config --cflags --libs x11 xi xcursor` -o ~/xiset

int main(int argc, char **argv) {
  Display *disp = XOpenDisplay(NULL);
  Window rootwin = DefaultRootWindow(disp);
  Cursor cursor = XCreateFontCursor(disp, XC_left_ptr);
  int devices_count;
  XIDeviceInfo *devices = XIQueryDevice(disp, XIAllMasterDevices,
      &devices_count);

  int i;
  for (i = 0; i < devices_count; i++)
    if (devices[i].use == XIMasterPointer)
      XIDefineCursor(disp, devices[i].deviceid, rootwin, cursor);

  XIFreeDeviceInfo(devices);
  XFreeCursor(disp, cursor);
  XCloseDisplay(disp);
  return 0;
}
