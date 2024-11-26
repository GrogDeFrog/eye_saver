#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

class Window
{
public:
    Window();
    ~Window();

private:
    std::vector<Message> messages;

    hide();
    setFullScreen();
};

#endif
