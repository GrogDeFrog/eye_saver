#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>

int main() {
    Display *display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open display\n";
        return -1;
    }

    int screen = DefaultScreen(display);
    unsigned long border = BlackPixel(display, screen);
    unsigned long background = WhitePixel(display, screen);

    // Creating a full-screen window
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                        0, 0, DisplayWidth(display, screen), DisplayHeight(display, screen),
                                        0, border, background);

    // Make the window top-most
    XSetWindowAttributes attributes;
    attributes.override_redirect = True;
    XChangeWindowAttributes(display, window, CWOverrideRedirect, &attributes);

    // Map (show) the window
    XMapWindow(display, window);
    XStoreName(display, window, "Red Screen");

    // Set the window's background color to an arbitrary hex value
    XColor color;
    Colormap colormap = DefaultColormap(display, screen);
    // For red color, hex value is #FF0000
    if (!XParseColor(display, colormap, "#FF0000", &color)) {
        std::cerr << "Failed to parse color\n";
        return -1;
    }
    if (!XAllocColor(display, colormap, &color)) {
        std::cerr << "Failed to allocate color\n";
        return -1;
    }
    XSetWindowBackground(display, window, color.pixel);
    XClearWindow(display, window); // Clear the window to update the background color

    // Process events
    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == KeyPress)
            break; // Exit on key press
    }

    XCloseDisplay(display);
    return 0;
}
