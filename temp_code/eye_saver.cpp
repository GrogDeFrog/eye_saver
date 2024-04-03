#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xinerama.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <iostream>
#include <chrono>
#include <thread>

#include <sys/select.h>

#include <cstdlib>
#include <cstring>

class XApp
{
private:
    // Variables to store the window-rendering information
    Display *display;
    Window *windows;
    XineramaScreenInfo *screens;
    GC *gcs;

    int numScreens;

    bool timeExpired;
    int restDuration; // (seconds)
    int breakSpacing; // (seconds)

    static void timerFunction(XApp *app)
    {
        std::this_thread::sleep_for(std::chrono::seconds(app->restDuration));
        app->timeExpired = true;
    }

    void handleExpose(Display* display, Window window, int screenIndex)
    {
        // Assuming you want to draw the same text on each screen
        const char* text = "Hello, World!";
        int textLength = strlen(text);

        XFontStruct* fontInfo = XLoadQueryFont(display, "fixed");
        if (!fontInfo) {
            std::cerr << "Unable to load font\n";
            return;
        }
        XSetFont(display, gcs[screenIndex], fontInfo->fid);

        // Set foreground color to white for drawing text
        unsigned long white = WhitePixel(display, DefaultScreen(display));
        XSetForeground(display, gcs[screenIndex], white);

        // Use local variable for screen info to avoid calling XineramaQueryScreens repeatedly
        screens[screenIndex];
        int textWidth = XTextWidth(fontInfo, text, textLength);
        int x = (screens[screenIndex].width - textWidth) / 2;
        int y = (screens[screenIndex].height + fontInfo->ascent) / 2;

        XDrawString(display, window, gcs[screenIndex], x, y, text, textLength);

        XFreeFont(display, fontInfo);
    }

public:
    XApp() : timeExpired(false), restDuration(5)
    {
        display = XOpenDisplay(nullptr);
        if (display == nullptr)
        {
            std::cerr << "Cannot open display\n";
            std::exit(EXIT_FAILURE);
        }

        screens = XineramaQueryScreens(display, &numScreens);
        if (!screens)
        {
            std::cerr << "Error querying screens" << std::endl;
            exit(EXIT_FAILURE);
        }

        windows = new Window[numScreens];
        gcs = new GC[numScreens];

        for (int i = 0; i < numScreens; ++i)
        {
            Window rootWindow = RootWindow(display, DefaultScreen(display));

            int screenNum = screens[i].screen_number;

            unsigned long background = BlackPixel(display, screenNum);
            unsigned long border = BlackPixel(display, screenNum);
            int screenWidth = screens[i].width;
            int screenHeight = screens[i].height;
            int xOrg = screens[i].x_org;
            int yOrg = screens[i].y_org;

            windows[i] = XCreateSimpleWindow(display, rootWindow, xOrg, yOrg,
                    screenWidth, screenHeight, 0, border, background);

            // These handle renderings (GC means graphics context)
            gcs[i] = XCreateGC(display, windows[i], 0, nullptr);

            XSelectInput(display, windows[i], ExposureMask | KeyPressMask);

            // This removes the decoration of the window and makes it fullscreen
            Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
            Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN",
                    False);
            XChangeProperty(display, windows[i], wmState, XA_ATOM, 32,
                    PropModeReplace, (unsigned char*)&fullscreen, 1);

            XMapWindow(display, windows[i]);
        }

        // Start the timer thread to count how long to take breaks for
        std::thread timerThread(timerFunction, this);
        timerThread.detach();
    }

    void run()
    {
        int x11_fd = ConnectionNumber(display);
    
        bool running = true;
        while (running)
        {
            // Handle all pending X events first
            while (XPending(display) > 0)
            {
                XEvent event;
                XNextEvent(display, &event);
    
                for (int i = 0; i < numScreens; ++i)
                {
                    if (event.xany.window == windows[i] && event.type == Expose)
                    {
                        handleExpose(display, windows[i], i);
                    }
                }
    
                if (event.type == KeyPress)
                {
                    KeySym key = XLookupKeysym(&event.xkey, 0);
                    if (key == XK_Escape)
                    {
                        running = false;
                        std::cerr << "Escape key pressed, exiting now.\n";
                        return;  // Exit immediately on escape key press
                    }
                }
            }
    
            // Define the timeout duration
            struct timeval timeout;
            timeout.tv_sec = 5;  // wait for 5 seconds
            timeout.tv_usec = 0;
    
            // Create a file descriptor set and add the X11 file descriptor to it
            fd_set in_fds;
            FD_ZERO(&in_fds);
            FD_SET(x11_fd, &in_fds);
    
            // Wait for an event or a timeout
            int select_result = select(x11_fd + 1, &in_fds, nullptr, nullptr, &timeout);
            if (select_result == 0)
            {
                // Timeout occurred
                std::cout << "5-second timeout reached, closing windows..." << std::endl;
                break;  // Exit loop after 5 seconds
            }
            else if (select_result < 0)
            {
                // Error occurred
                perror("select");
                break;
            }
        }
    }

    ~XApp()
    {
        if (display)
        {
            for (int i = 0; i < numScreens; ++i) {
                XFreeGC(display, gcs[i]);
            }
            delete[] gcs;
            delete[] windows;
            XCloseDisplay(display);

            XFree(screens);
        }
    }
};

int main() {
    XApp app;
    app.run();

    return 0;
}
